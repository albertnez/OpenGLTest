#version 420

uniform float time;

in vec2 pos;

void main() {

    float mult = 10*sin(time);
    float timeMult = mult;
    vec3 v = vec3(int(pos.x*mult)&1, int(pos.y*mult)&1, (1-int(pos.x*mult)&1) & (1-int(pos.y*mult)&1));

    gl_FragColor = vec4( v[int(time*timeMult)%3], v[(int(time*timeMult)+1)%3], v[(int(time*timeMult)+2)%3], 1.0);
}

