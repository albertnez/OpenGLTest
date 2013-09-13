#version 420

uniform float time;

in vec2 a_position;

out vec2 pos;

void main() {
    gl_Position = vec4(a_position, 0.0, 1.0) ;
    pos = a_position*0.5+0.5;
}
