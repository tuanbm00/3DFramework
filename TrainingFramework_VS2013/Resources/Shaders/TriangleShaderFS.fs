precision mediump float;

uniform sampler2D u_texture;
uniform float fog_start;
uniform float fog_length;
uniform vec3 fog_color;

varying vec2 v_uv;
varying float dis;

void main()
{
//	gl_FragColor = vec4(v_color);
	float fogValue = clamp((dis - fog_start) / fog_length, 0.0, 1.0);
	vec4 textColor = texture2D(u_texture, v_uv);
	gl_FragColor = fogValue*vec4(fog_color, 1.0) + (1.0-fogValue)*textColor;
}
