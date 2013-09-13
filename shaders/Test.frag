#version 420

uniform float time;

in vec2 pos;

void main() {
    gl_FragColor = vec4(sin(pos*5+time*20), sin(time*50), 1.0);
}

