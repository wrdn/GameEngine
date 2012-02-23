varying vec4 pos;

void main()
{
	float depth = pos.z / pos.w;
	depth = depth * 0.5 + 0.5;
	
	float moment2 = depth * depth;

	// Adjusting moments (this is sort of bias per pixel) using derivative
	float dx = dFdx(depth);
	float dy = dFdy(depth);
	moment2 += 0.25*(dx*dx+dy*dy) ;
	

	gl_FragColor = vec4( depth,moment2, 0.0, 0.0 );
}