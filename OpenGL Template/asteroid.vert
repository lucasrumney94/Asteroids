#version 430

#define VERTEX_DRIFT .0

in int gl_VertexID;
in int gl_DrawID;

out vec3 tcsPos;

layout (location=0) in vec3 position;


uniform int objectId;


float rand(float x)
{
    return fract(sin(x) * 100000.0);
}

void main(void)
{
	float posHash = position.x + position.y + position.z;
	vec3 pos = position + VERTEX_DRIFT * (rand(posHash + objectId) * 2. - 1.);
	tcsPos = pos;
	gl_Position =  vec4(pos,1.0);
}
