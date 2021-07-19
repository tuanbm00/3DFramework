precision mediump float;

uniform samplerCube u_samplerCubeMap;

varying vec3 v_pos;

void main()
{
//	gl_FragColor = vec4(v_color);
	gl_FragColor = textureCube(u_samplerCubeMap, v_pos);
}
