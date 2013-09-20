
#version 420

uniform float time;

in vec2 pos;

void main( void )
{
    float amount = 1 - sqrt( (pos.x-0.5)*(pos.x-0.5) + (pos.y-0.5)*(pos.y-0.5))/0.5;
    //amount = 1;
    //vec3 color = vec3(1.0, 1.0, 1.0);
    vec3 color = vec3(1.0*sin(time), 1.0*sin(time+3.141592), pos.x);
    gl_FragColor = vec4(color, amount);
}
