attribute vec3 a_posL;
attribute vec3 a_tangentL;
attribute vec3 a_bitangentL;
attribute vec3 a_normalL;
attribute vec2 a_uv;

varying vec3 v_tangent;
varying vec3 v_bitangent;
varying vec3 v_normal;
varying vec2 v_uv;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = posL;
v_tangent = a_tangentL;
v_bitangent = a_bitangentL;
v_normal = a_normalL;
v_uv = a_uv;
}
   