#version 420

uniform float time;
uniform vec2 mousePosition;

in vec2 pos;

void main( void )
{
    float amount = 1 - sqrt( (pos.x-0.5)*(pos.x-0.5) + (pos.y-0.5)*(pos.y-0.5))/0.5;
	vec3 color = vec3(1-mousePosition.y, mousePosition.y, mousePosition.x);
    gl_FragColor = vec4(color, amount);
}
