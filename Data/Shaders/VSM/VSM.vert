varying vec4 shadowCoord;

void main()
{
	shadowCoord = gl_TextureMatrix[7] * gl_Vertex;
	gl_Position = ftransform();
	gl_FrontColor = gl_Color;
}