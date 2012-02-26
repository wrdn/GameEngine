varying vec4 shadowCoord;
uniform sampler2D shadowMap;
vec4 ShadowCoordPostW;

const float lightbleed = 0.3f;
const float invlightbleed = 1.0f / (1.0f - lightbleed );

float chebyshevUpperBound( float distance)
{
	vec2 moments = texture2D(shadowMap,ShadowCoordPostW.xy).rg;
	
	if (distance <= moments.x) { return 1.0 ; }

	float variance = moments.y - (moments.x*moments.x);
	//variance = max(variance,0.000003);
	variance = max(variance,0.0000025);

	float d = moments.x - distance;
	float p_max = variance / (variance + d*d);
	p_max = clamp((p_max-lightbleed) * invlightbleed, 0, 1);
	return p_max;
}


void main()
{	
	ShadowCoordPostW = shadowCoord / shadowCoord.w;
	float dist = texture2D(shadowMap,ShadowCoordPostW.xy).x;
	
	float shadow = 1.0;
	if(shadowCoord.w > 0.0)
	{
		shadow = dist < ShadowCoordPostW.z ? 0.5 : 1.0;
	}
	
	gl_FragColor = shadow * gl_Color;
	
	//float shadow = chebyshevUpperBound(ShadowCoordPostW.z);
	//gl_FragColor = vec4(shadow) * gl_Color;
	//gl_FragColor = vec4(1,1,0,1);
}