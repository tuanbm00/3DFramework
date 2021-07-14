precision mediump float;

uniform sampler2D u_texture;

varying vec3 v_tangent;
varying vec3 v_bitangent;
varying vec3 v_normal;
varying vec2 v_uv;

void main()
{
//	gl_FragColor = vec4(v_color);
	gl_FragColor = texture2D(u_texture, v_uv);
}
