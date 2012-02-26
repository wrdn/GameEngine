varying vec4 pos;

void main()
{
	float depth = pos.z / pos.w;
	depth = depth * 0.5 + 0.5; // convert depth to linear [0,1] coordinate system
	
	float dx = dFdx(depth), dy = dFdy(depth);
	float moment2 = (depth*depth) + 0.25*(dx*dx+dy*dy); // moment1 is depth
	
	gl_FragColor = vec4(depth, moment2, 0,0);
};