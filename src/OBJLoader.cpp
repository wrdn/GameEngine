#include <fstream>
#include <sstream>
#include "OBJLoader.h"
#include "strutils.h"
#include "ResourceManager.h"
using namespace std;

const c8* OBJLoader::OBJMaterialValidLineInitiators[] =
{
	"newmtl",
	"map_Kd",
	"map_Ks",
	"map_Bump",
	"map_d",
	"Ka",
	"Kd",
	"Ks"
};
const OBJLoader::OBJMaterialNodeType OBJLoader::OBJMaterialAssociatedNodeTypes[] =
{
	Mat_NewMaterial,
	Mat_MapKd,
	Mat_MapKs,
	Mat_MapBump,
	Mat_MapD,
	Mat_Ka,
	Mat_Kd,
	Mat_Ks,
};
const c8* OBJLoader::ValidLineInitiators[] =
{
	"v",
	"vn",
	"vt",
	"f",
	"o",
	"mtllib",
	"usemtl",
};
const OBJLoader::OBJLineType OBJLoader::AssociatedLineTypes[] = // associate the start of the line (above) with the type of line it is
{
	VertexLine, // "v"
	NormalLine, // "vn"
	TextureCoordinateLine, // "vt"
	FaceLine, // "f"
	ObjectLine, // "o"
	MTLLIBLine, // "mtllib"
	USEMTLLine, // "usemtl"
};

const c8* OBJLoader::LineTypeAsString(OBJLineType t)
{
	switch(t)
	{
	case IgnoredLine: return "";
	case VertexLine: return "VertexLine";
	case TextureCoordinateLine: return "TextureCoordinateLine";
	case NormalLine: return "NormalLine";
	case FaceLine: return "FaceLine";
	case ObjectLine: return "ObjectLine";
	case MTLLIBLine: return "MTLLIBLine";
	case USEMTLLine: return "USEMTLLine";
	}
	return "";
};

OBJLoader::OBJMaterialNodeType OBJLoader::ValidateOBJMaterialLineStart(const string &str)
{
	for(u32 i=0;i<sizeof(OBJMaterialValidLineInitiators)/sizeof(const c8*);++i)
		if(str == OBJMaterialValidLineInitiators[i])
			return OBJMaterialAssociatedNodeTypes[i];
	return IgnoredNode;
};

OBJLoader::OBJLineType OBJLoader::ValidateLineStart(const string &lineStart)
{
	for(u32 i=0;i< sizeof(ValidLineInitiators)/sizeof(const c8*); ++i)
		if(lineStart == ValidLineInitiators[i])
			return AssociatedLineTypes[i];
	return IgnoredLine;
};

bool OBJLoader::ParseMaterialFile(const c8* mtl_filename, std::map<u32, OBJMaterial> &outputMap)
{
	ifstream mtlFile((const char*)mtl_filename);
	if(mtlFile.fail()) return false;

	u32 activeNode = 0;

	while(!mtlFile.eof())
	{
		string buff, tmp;
		getline(mtlFile, buff);
		stringstream line(buff);
		line >> tmp;

		OBJMaterialNodeType matNode = ValidateOBJMaterialLineStart(tmp);
		if(!matNode || (matNode != Mat_NewMaterial && activeNode == 0)) { continue; } // check we have a material

		switch(matNode)
		{
		case IgnoredLine: break;
		case Mat_NewMaterial:
			{
				string materialName; line >> materialName;
				activeNode = hash_djb2((const uc8*)materialName.c_str());
				outputMap[activeNode].hashedName = activeNode;
			}
			break;
		case Mat_MapKd:
			line >> outputMap[activeNode].map_Kd_filename;
			break;
		case Mat_MapKs:
			line >> outputMap[activeNode].map_Ks_filename;
			break;
		case Mat_MapBump:
			line >> outputMap[activeNode].map_Bump_filename;
			break;
		case Mat_MapD:
			line >> outputMap[activeNode].map_d_filename;
			break;
		case Mat_Ka:
			line >> outputMap[activeNode].ka;
			break;
		case Mat_Kd:
			line >> outputMap[activeNode].kd;
			break;
		case Mat_Ks:
			line >> outputMap[activeNode].ks;
			break;
		}
	}
	return true;
};

bool OBJLoader::LoadOBJFile(const string& filename, vector<GraphicsObject> &output_vec)
{
	//ifstream fileStream(filename.c_str());
	ifstream fileStream;
	if(!fileStream.good()) { return false; } // no file

	vector<float3> vertices, normals;
	vector<float2> uvs;

	vector<VERTEX> faceVertices; // formed from face "f" lines
	vector<u32> indexSet;
	map<unsigned long, u32> hashMap; // hash vertex face definition (e.g. 1/2/3) and insertion position (for fast retrieval)

	u32 currentLine=0, objectCount=0;

	map<u32, OBJMaterial> materials;
	OBJMaterial activeMaterial;

	while(!fileStream.eof())
	{
		++currentLine;
		string buff, tmp; getline(fileStream, buff);
		stringstream line(buff);
		line >> tmp;
		OBJLineType p = ValidateLineStart(tmp); // p is the type of line we have
		if(!p) { continue; }

		switch(p) // by the time we get here, we know the line is valid
		{
		case IgnoredLine: break;
		case USEMTLLine:
		{
		  // TODO: WRITE THIS
		} break;
		case MTLLIBLine:
			{
				// note: material files are specified relative to the OBJ file, so we need to build the
				// material file name out of the OBJ filename (extract directory and add material filename)
				string tmpFilename = filename;
				size_t lsp = filename.find_last_of("/");

				if(lsp != string::npos)
					tmpFilename = filename.substr(0, lsp+1);

				string materialFilename; line >> materialFilename;
				tmpFilename += materialFilename;

				ParseMaterialFile(tmpFilename.c_str(), materials);
			} break;

		case VertexLine:
			{
				float3 _vertex;
				line >> _vertex;
				if(!line.fail()) { vertices.push_back(_vertex); }
			} break;


		case TextureCoordinateLine:
			{
				float2 _uv; line >> _uv;
				if(!line.fail()) { uvs.push_back(_uv); }
			} break;


		case NormalLine:
			{
				float3 _normal; line >> _normal;
				if(!line.fail()) { normals.push_back(_normal); }
			} break;
		case FaceLine: // 3 face vertex definitions per line e.g. "1/2/3 4/5/6 7/8/9", v/vt/vn, v/vn, v/vt, v, only v/vt/vn and v/vn should be supported (don't want to recalculate normals)
			{
				// no vertices (we can't make a face)
				if(!vertices.size())
					break;

				for(u32 i=0;i<3;++i) // expect 3 face vertex definitions per face line
				{
					// Grab and check the face vertex is legal
					string faceVertexDefinition; line >> faceVertexDefinition;
					u32 NumberOfForwardSlashes = CountCharacterOccurrence(faceVertexDefinition.c_str(), '/');
					if(NumberOfForwardSlashes > 2) { break; } // e.g. 1/2/3/4. If we encounter this, ignore the entire face

					// Look for existing hash to reuse index
					unsigned long faceDefHash = hash_djb2((const uc8*)faceVertexDefinition.c_str());
					std::map<unsigned long,u32>::iterator foundIndex = hashMap.find(faceDefHash);
					if(foundIndex != hashMap.end())
					{
						indexSet.push_back(foundIndex->second);
						continue;
					}

					// Parse the face vertex definition
					switch(NumberOfForwardSlashes)
					{
					case 0: // v
						{
							i32 vertexIndex=-1; stringstream fvstr(faceVertexDefinition);
							fvstr >> vertexIndex; --vertexIndex;
							if(vertexIndex < 0 || (u32)vertexIndex >= vertices.size()) { break; } // can't have negative indices or index>vertex count
							faceVertices.push_back(VERTEX(vertices[vertexIndex], float3(), float2())); // vertex valid if we get here
							indexSet.push_back(faceVertices.size()-1);
							hashMap[faceDefHash] = indexSet.size()-1;
							break;
						}

					case 2: // v/vt/vn
						{
							vector<string> vs; split(faceVertexDefinition, '/', vs);

							i32 vertexIndex=-1, uvIndex=-1, normalIndex=-1;
							stringstream buff(vs[0]); buff >> vertexIndex; --vertexIndex;
							if(vertexIndex < 0 || (u32)vertexIndex >= vertices.size()) { break; } // can't survive an invalid vertex index

							stringstream buff_uv(vs[1]), buff_nm(vs[2]); // REQUIRED TO ALLOW COMPILATION UNDER G++ (WITH -std=c++00x)
							buff_uv >> uvIndex; --uvIndex;
							buff_nm >> normalIndex; --normalIndex;

							float3 vert(vertices[vertexIndex]), normal; float2 uv;
							if(normalIndex >= 0 && (u32)normalIndex < normals.size()) { normal = normals[normalIndex]; } // can survive invalid normal/uv indices
							if(uvIndex >= 0 && (u32)uvIndex < uvs.size()) { uv = uvs[uvIndex]; }

							faceVertices.push_back(VERTEX(vert, normal, uv));
							indexSet.push_back(faceVertices.size()-1);
							hashMap[faceDefHash] = faceVertices.size()-1;
							break;
						}

					case 1: // vertex and uv OR vertex and normal (depending on what we already have), can survive as long as vertex index valid
						{
							if(vertices.size())
							{
								vector<string> vs; split(faceVertexDefinition, '/', vs);
								i32 vertexIndex=-1, otherIndex=-1; // other index is vt or vn
								stringstream buff(vs[0]); buff >> vertexIndex; --vertexIndex;
								if(vertexIndex < 0 || (u32)vertexIndex >= vertices.size()) { break; } // can't survive an invalid vertex index
								
                                                                stringstream buff2(vs[1]);
								buff2 >> otherIndex; --otherIndex;

								float3 vert(vertices[vertexIndex]), normal; float2 uv;

								if(uvs.size() && !normals.size() && (otherIndex >= 0 && (u32)otherIndex < uvs.size())) // v/vt
									uv = uvs[otherIndex];
								else if(normals.size() && !uvs.size() && (otherIndex >= 0 && (u32)otherIndex < normals.size())) // v/vn
									normal = normals[otherIndex];

								faceVertices.push_back(VERTEX(vert, normal, uv));
								indexSet.push_back(faceVertices.size()-1);
								hashMap[faceDefHash] = indexSet.size()-1;
								break;
							}
						}
					} // switch(NumberOfForwardSlashes)
				} // for(u32 i=0;i<3;++i)
			} break; // case FaceLine
		case ObjectLine: // "o" line, try and create a model using existing data then clear vertices,uvs,normals,faceVertices,indexSet and hashMap
			{
				if(faceVertices.size() && indexSet.size())
				{
					++objectCount;
					GraphicsObject g;
					MeshHandle mh = ResourceManager::get().CreateAndGetResource<Mesh>();
					mh->SetName("objfile");
					mh->BuildVBO(&faceVertices[0], faceVertices.size(), &indexSet[0], indexSet.size());
					g.SetMesh(mh);
					output_vec.push_back(g);

					faceVertices.clear();
					indexSet.clear();
					hashMap.clear(); // dont reuse the indices of faces for new objects
				}

				//vertices = std::vector<float3>();
				//normals = std::vector<float3>();
				//uvs = std::vector<float2>();
			} break;

		} // switch(p)
	} // while(!fileStream.eof())

	// Reached end of file, try to create a model using data
	if(faceVertices.size() && indexSet.size())
	{
		++objectCount;
		GraphicsObject g;
		MeshHandle mh = ResourceManager::get().CreateAndGetResource<Mesh>();
		mh->SetName("objfile");
		mh->BuildVBO(&faceVertices[0], faceVertices.size(), &indexSet[0], indexSet.size());
		g.SetMesh(mh);
		output_vec.push_back(g);

		faceVertices.clear();
		indexSet.clear();
		hashMap.clear();
	}

	return true;
};