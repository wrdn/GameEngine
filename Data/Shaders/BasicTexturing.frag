varying vec2 TexCoord;
uniform sampler2D baseMap;
varying vec4 pos;
varying vec3 vlightDirection, vNormal;

void main()
{
	vec3 lightDir = normalize(vlightDirection);
	vec3 Normal = normalize(vNormal);
	float ndotl = max(0,dot(Normal, lightDir));
	
	vec4 baseCol = texture2D(baseMap, TexCoord);
	
	vec4 AmbResult = vec4(0.2,0.2,0.2,1) * baseCol;
	vec4 DiffResult = vec4(1,1,1,1) * ndotl * baseCol;
	gl_FragColor = AmbResult + DiffResult;
}