#version 430

in vec3 tcsPos[];

layout (vertices = 3) out;

out vec3 tesPos[];

void main(void)
{
	

	tesPos[gl_InvocationID] = tcsPos[gl_InvocationID];

	gl_TessLevelOuter[0] = 6.0f;
	gl_TessLevelOuter[1] = 6.0f;
	gl_TessLevelOuter[2] = 6.0f;

	gl_TessLevelInner[0] = 6.0f;

}
