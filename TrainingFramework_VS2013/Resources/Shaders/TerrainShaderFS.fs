precision mediump float;

uniform sampler2D u_texture;
uniform sampler2D r_texture;
uniform sampler2D g_texture;
uniform sampler2D b_texture;

varying vec2 v_uv;
varying float dis;

void main()
{
//	gl_FragColor = vec4(v_color);
	float fogValue = clamp((dis - 1.0) / 50.0, 0.0, 1.0);
	vec4 blendTexture = texture2D(u_texture, v_uv);
	vec2 uv = v_uv*40.0;
	vec4 r = texture2D(r_texture, uv) * blendTexture.r;
	vec4 g = texture2D(g_texture, uv) * blendTexture.g;
	vec4 b = texture2D(b_texture, uv) * blendTexture.b;
	vec4 textColor = (r + g + b) / (blendTexture.r + blendTexture.g + blendTexture.b);
	gl_FragColor = fogValue*vec4(1.0, 1.0, 1.0, 1.0) + (1.0-fogValue)*textColor;
}
