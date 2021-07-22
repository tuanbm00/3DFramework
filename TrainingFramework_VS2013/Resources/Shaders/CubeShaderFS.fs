precision mediump float;

uniform samplerCube u_samplerCubeMap;

varying vec3 v_pos;
varying float dis;

void main()
{
//	gl_FragColor = vec4(v_color);
	float fogValue = clamp((dis - 1.0) / 600.0, 0.0, 1.0);
	vec4 textColor = textureCube(u_samplerCubeMap, v_pos);
	gl_FragColor = fogValue*vec4(1.0, 1.0, 1.0, 1.0) + (1.0-fogValue)*textColor;

}
