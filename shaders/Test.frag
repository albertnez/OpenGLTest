#version 420

uniform float time;
uniform vec2 mousePosition;
uniform float alpha;
uniform vec3 color;

in vec2 pos;

void main( void )
{
        float amount = 1 - sqrt( (pos.x-0.5)*(pos.x-0.5) + (pos.y-0.5)*(pos.y-0.5))/0.5;
//	float amount = 1.0f;
    gl_FragColor = vec4(color, amount*alpha);
}
