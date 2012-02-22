varying vec2 TexCoord;
varying vec4 pos;
varying vec3 vlightDirection, vNormal;

void main()
{
	gl_Position = ftransform();
	
	pos = gl_Position;
	TexCoord = gl_MultiTexCoord0.xy;
	vlightDirection = vec3(0,0,1);
	vNormal = normalize(gl_NormalMatrix * gl_Normal);
}