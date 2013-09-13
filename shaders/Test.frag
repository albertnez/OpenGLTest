#version 420

uniform float time;
vec2 mouse = vec2(0,0);
vec2 resolution = vec2(800, 600);
void main( void ) {
        vec2 pos = gl_FragCoord.xy / resolution;
        vec2 pos2 = vec2(pos.x, 1-pos.y);

        float amnt = 0.0;
        float nd = 0.0;
        vec4 cbuff = vec4(0.0);


        float desvX = 0.2*sin(time*0.2);
        float desvY = 0.2*cos(time*0.2);

        for(float i=0.0; i<21.0;i++){
            nd =sin(3.14*0.8*pos.x + i*0.6 + time*(pos.x > 0.5 +desvX ? -1 : 1))  * ((pos.x-0.5-desvX)*0.9)+0.5 + desvY;
        amnt = 1.0/abs(nd-pos.y)*0.0005;

        cbuff += vec4(amnt, amnt*0.3 , amnt*pos.y, 1.0);
        }


        for(float i=0.0; i<21.0;i++){
            nd =sin(3.14*pos.y + i*0.6 + time*(pos.y > 0.5+desvY ? -1 : 1)) * (pos.y-0.5-desvY)*0.9 + 0.5 +desvX;
        amnt = 1.0/abs(nd-pos.x)*0.0005;

        cbuff += vec4(amnt*0.2, amnt*0.3 , amnt*pos.x, 1.0);
        }


        vec4 dbuff = vec4(0);
  gl_FragColor = cbuff + dbuff;
}
