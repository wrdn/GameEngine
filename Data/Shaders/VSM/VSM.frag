uniform sampler2D shadowMap;

varying vec4 shadowCoord;
vec4 ShadowCoordPostW;

float chebyshevUpperBound( float distance)
{
	vec2 moments = texture2D(shadowMap,ShadowCoordPostW.xy).rg;
	
	if (distance <= moments.x) { return 1.0 ; }

	float variance = moments.y - (moments.x*moments.x);
	variance = max(variance,0.00025);

	float d = moments.x - distance;
	float p_max = variance / (variance + d*d);
	return p_max;
}

void main()
{	
	ShadowCoordPostW = shadowCoord / shadowCoord.w;
	float shadow = chebyshevUpperBound(ShadowCoordPostW.z);
	gl_FragColor = vec4(shadow) * gl_Color;
}