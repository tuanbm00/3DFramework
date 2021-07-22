attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec3 a_normal;

uniform mat4 u_mvpMatrix;
uniform sampler2D heightMap;

varying vec2 v_uv;
varying float dis;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
posL.y = normalize(texture2D(heightMap, a_posL.xz)).r;
gl_Position = u_mvpMatrix*posL;
dis = length(gl_Position.xyz);
v_uv = a_uv;
}
   