uniform sampler2DShadow ShadowMap;
varying vec4 ShadowCoord;
uniform float xPixelOffset, yPixelOffset;

float lookup_pix(vec2 offSet)
{
	vec4 shadow_offset = vec4(offSet.x * xPixelOffset * ShadowCoord.w, offSet.y * yPixelOffset * ShadowCoord.w, 0.0005, 0.0);
	return shadow2DProj(ShadowMap, ShadowCoord+shadow_offset).z;
};

void main()
{
	float shadow = 0;
	
	if(ShadowCoord.w > 0.0)
	{
		/*float x=0,y=0;
		for (y = -1.5 ; y <=1.5 ; y+=1.0)
		{
			for (x = -1.5 ; x <=1.5 ; x+=1.0)
			{
				shadow += lookup_pix(vec2(x,y));
			}
		}
		
		shadow /= 16.0;*/
		
		// 8x8 pcf
		float x,y;
		for (y = -3.5 ; y <=3.5 ; y+=1.0)
		{
			for (x = -3.5 ; x <=3.5 ; x+=1.0)
			{
					shadow += lookup_pix(vec2(x,y));
			}
		}	
		shadow /= 64.0 ;
	}
	
	gl_FragColor = (shadow+0.2) * gl_Color;
};