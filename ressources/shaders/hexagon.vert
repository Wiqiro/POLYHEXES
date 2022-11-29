#version 330 core
layout (location = 0) in vec2 pos;

uniform mat3 model;
uniform mat3 proj;

void main() {

   vec3 crnt_pos = vec3(proj * model * vec3(pos, 1.0));

   gl_Position = vec4(crnt_pos.x, crnt_pos.y, 0.0, 1.0);
   
   //gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}