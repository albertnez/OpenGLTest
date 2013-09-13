#version 420
/*
uniform float time;

in vec2 pos;

void main() {

    float mult = 10*sin(time);
    float timeMult = mult;
    vec3 v = vec3(int(pos.x*mult)&1, int(pos.y*mult)&1, (1-int(pos.x*mult)&1) & (1-int(pos.y*mult)&1));

    // gl_FragColor = vec4( v[int(time*timeMult)%3], v[(int(time*timeMult)+1)%3], v[(int(time*timeMult)+2)%3], 1.0);
    gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}

*/

uniform float time;
vec2 mouse = vec2(0,0);
vec2 resolution = vec2(800, 600);
uniform sampler2D backbuffer;
void main( void ) {
        vec2 pos = gl_FragCoord.xy / resolution;
        vec2 pos2 = vec2(pos.x, 1-pos.y);

        float amnt = 0.0;
        float nd = 0.0;
        vec4 cbuff = vec4(0.0);

        /*
        for(float i=0.0; i<8.0;i++){
        nd =sin(3.14*0.8*pos.x + (i*0.8+sin(+time)*0.3) + time)*0.9+0.5 + pos.x;
        amnt = 1.0/abs(nd-pos.y)*0.01;
        cbuff += vec4(amnt, amnt*0.3 , amnt*pos.y, 1.0);
        }
        */

        for(float i=0.0; i<20.0;i++){
            nd =sin(3.14*0.8*pos.x + i*0.6 + time*(pos.x > 0.5 ? -1 : 1))*(pos.x-0.5)*0.9+0.5;
        amnt = 1.0/abs(nd-pos.y)*0.002;

        cbuff += vec4(amnt, amnt*0.3 , amnt*pos.y, 1.0);
        }

        for(float i=0.0; i<20.0;i++){
            nd =sin(3.14*pos.y + i*0.6 + time*(pos.y > 0.5 ? -1 : 1))*(pos.y-0.5)*0.75+0.5;
        amnt = 1.0/abs(nd-pos.x)*0.002;

        cbuff += vec4(amnt*0.2, amnt*0.3 , amnt*pos.x, 1.0);
        }

        /*
        for(float i=0.0; i<10.0;i++){
        nd =sin(3.14*pos2.y + i*0.6 + time)*pos2.y*0.5+0.5;
        amnt = 1.0/abs(nd-pos2.x)*0.01;

        cbuff += vec4(amnt*0.2, amnt*0.3 , amnt*pos2.x, 1.0);
        }
        */


        //vec4 dbuff =  texture2D(backbuffer,1.0-pos)*0.;
        vec4 dbuff = vec4(0);
  gl_FragColor = cbuff + dbuff;
}
