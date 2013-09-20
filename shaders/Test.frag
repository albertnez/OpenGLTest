
#version 420

uniform float time;
uniform vec2 mousePosition;


in vec2 pos;

void main( void )
{
    float amount = 1 - sqrt( (pos.x-0.5)*(pos.x-0.5) + (pos.y-0.5)*(pos.y-0.5))/0.5;
    //amount = 1;
    //vec3 color = vec3(1.0, 1.0, 1.0);
    //vec3 color = vec3(1.0*sin(time), 1.0*sin(time+3.141592)+(1-pos.x), pos.x);
    vec3 color = vec3(0.5, mousePosition.y, mousePosition.x);
    gl_FragColor = vec4(color, amount);
}
