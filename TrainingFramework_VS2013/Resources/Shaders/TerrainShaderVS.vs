attribute vec3 a_posL;
attribute vec2 a_uv;

uniform mat4 u_mvpMatrix;
uniform sampler2D heightMap;

varying vec2 v_uv;
varying float dis;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_mvpMatrix*posL;
dis = length(gl_Position.xyz);
v_uv = a_uv;
}