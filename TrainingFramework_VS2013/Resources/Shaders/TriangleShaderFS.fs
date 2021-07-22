precision mediump float;

uniform sampler2D u_texture;

varying vec2 v_uv;
varying float dis;

void main()
{
//	gl_FragColor = vec4(v_color);
	float fogValue = clamp((dis - 1.0) / 50.0, 0.0, 1.0);
	vec4 textColor = texture2D(u_texture, v_uv);
	gl_FragColor = fogValue*vec4(1.0, 1.0, 1.0, 1.0) + (1.0-fogValue)*textColor;
}
