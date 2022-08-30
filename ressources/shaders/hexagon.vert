#version 330 core
layout (location = 0) in vec2 pos;

uniform mat3 model;
uniform mat3 proj;

void main() {

   vec3 crnt_pos = vec3(proj * model * vec3(pos, 1.0));

   gl_Position = vec4(crnt_pos.x, crnt_pos.y, 0.0, 1.0);
   
   //gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}




/* #version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 offset;

void main() {
   gl_Position = vec4(0.2f * (pos.x + offset.x), 0.2f * (pos.y + offset.y), pos.z, 1.0);
} */