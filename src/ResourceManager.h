#pragma once

#include "Resource.h"
#include "util.h"
#include <map>
#include <memory>
using namespace std;

// Resource manager used to manager game resources (e.g. textures, audio)
// Returns an id to the resource, then use GetResource(id) to get the actual shared
// pointer to it. Anything inheriting from Resource can be managed by this
// To skip retrieving the ID first, call CreateAndGetResource(). All created resources
// contain their associated ID, so you can easily call GetID() on it
class ResourceManager
{
private:
	// maps resource id (generated by hashing string, see HashResourceString function) to the Resource itself
	// Pointers used to allow objects inheriting Resource to use same structure
	map<i32, ResourceHandle> resourceMap;

	// singleton, all accesses through this (using get() function)
	static ResourceManager *resMan;
	static i32 idProvider; // if user doesn't provide a name for the resource, we create the ID by incrementing this value

	static i32 GenerateResourceMapUniqueID()
	{
		while(resMan->resourceMap.count(idProvider)) { ++idProvider; }
		return idProvider;
	};

	// constructor and destructor private so only 1 instance can exist (resMan singleton)
	ResourceManager() {};
	~ResourceManager() {};

	void AddResource(i32 id, const char *name, Resource *r);

public:
	// get the resource manager singleton
	static ResourceManager& get();

	static void Cleanup()
	{
		delete resMan;
		resMan = 0;
	};

	// gets resource ID using string hashing given name (str)
	static i32 GetResourceID(const char *str) { return (i32)hash_djb2((const uc8*)str); };

	template<class T>
	i32 CreateResource()
	{
		i32 id = GenerateResourceMapUniqueID();
		AddResource(id, 0, new T());
		return id;
	};

	template<class T>
	i32 CreateResource(const char *resourceName) // creates a new resource using hashed resourceName, or returns the ID of the resource if it already exists
	{
		i32 resHash = GetResourceID(resourceName);
		if(resourceMap.count(resHash)) { return resHash; };

		AddResource(resHash, resourceName, new T());
		return resHash;
	};

	template<class T>
	std::tr1::shared_ptr<T> GetResource(i32 id)
	{
		if(resourceMap.count(id))
		{
			return std::tr1::static_pointer_cast<T>(resourceMap[id]);
		}
		return std::tr1::shared_ptr<T>((T*)0);
	};

	template<class T>
	std::tr1::shared_ptr<T> GetResource(const char *resourceName)
	{
		return GetResource<T>(GetResourceID(resourceName));
	};

	// Preferred functions, built out of CreateResource() and GetResource()
	template<class T>
	std::tr1::shared_ptr<T> CreateAndGetResource()
	{
		return GetResource<T>(CreateResource<T>());
	};
	
	template<class T>
	std::tr1::shared_ptr<T> CreateAndGetResource(const char *resourceName)
	{
		return GetResource<T>(CreateResource<T>(resourceName));
	};

	// Removes the resource from the map of resources (hence the current resource can no longer be accessed)
	// Note it deletes no memory - this should be done in the destructor. Then when the last object has finished
	// using the memory, the shared_ptr destructor will automatically delete the object (which will clean itself up)
	void RemoveResource(i32 id)
	{
		if(resourceMap.count(id))
		{
			resourceMap.erase(id);
		}
	};
	void RemoveResource(const char *resourceName) { return RemoveResource(GetResourceID(resourceName)); };
};

#ifdef _WIN32
#pragma warning(disable:4505) // disable glut warnings
#endif

// UTILITY FUNCTIONS (USED TO MAKE IT EASIER TO LOAD SPECIFIC TYPES OF RESOURCE)
// NOTE THESE Load FUNCTIONS WILL RELOAD DATA EVEN IF IT EXISTS, TO AVOID THIS
// CALL GetResource() OR PASS AROUND THE SHARED POINTER TO THE OBJECT
#include "Texture.h"
#include "Shader.h"
#include "ShaderObject.h"
#include "RenderTarget.h"

TextureHandle LoadTexture(const char *filename, const char *textureResourceName=0); // if not provided, the default resource name used is the filename
ShaderHandle LoadShader(const char *vertexShaderFilename, const char *fragmentShaderFilename, const char *shaderResourceName=0); // if not provided, there is no default shader resource name
RenderTargetHandle CreateRenderTarget(int width, int height, const char *renderTargetResourceName=0); // if not provided, there is no default render target resource name