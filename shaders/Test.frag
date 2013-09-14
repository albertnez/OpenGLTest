#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
void main( void )
{
	vec2 pos = gl_FragCoord.xy / vec2(800, 600);
	float amnt = 0.1;
	float nd = 1.0;
	vec4 cbuff = vec4(0.0);

	float y = 1.0;
	float PI = 3.141592;

	for (float i = 0.0; i < 1.0; ++i) {
		y = sin(2*PI*time)*0.5 + 0.5;
	}

	cbuff += vec4(y, 0.0, 0.0, 1.0);

/*
	for (float i = 0.0; i < 4.0; i++)
	{
		nd = sin(3.14 * 1.0 * pos.x + i * 800.0 + time) * 0.2 * (pos.x + 0.3) + 0.5;
		amnt = 1.0 / abs(nd - pos.x) * 0.005;

		cbuff += vec4(amnt * pos.x, amnt * 0.2, amnt * pos.x, 1.0);
	}

	for (float i = 0.0; i < 4.0; i++)
	{
		nd = sin(3.14 * 1.0 * pos.y + i * 1600.0 + time) * 0.3 * (pos.y + 0.3) + 0.5;
		amnt = 1.0 / abs(nd - pos.y) * 0.005;

		cbuff += vec4(amnt * 0.2, amnt * 0.3, amnt * pos.y, 1.0);
	}

	for (float i = 0.0; i < 2.0; i++)
	{
		nd = sin(3.14 * 1.0 * pos.y + i * 3200.0 + time) * 0.4 * (pos.y + 0.3) + 0.5;
		amnt = 1.0 / abs(nd - pos.y) * 0.005;

		cbuff += vec4(amnt * 0.7, amnt * pos.x, amnt * 0.2, 1.0);
	}
*/
	gl_FragColor = cbuff;
}
