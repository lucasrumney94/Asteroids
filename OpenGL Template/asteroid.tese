#version 430

in vec3 tesPos[];

layout (triangles, equal_spacing, cw) in; // TRY BOTH WAYS

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main()
{
	gl_Position = proj_matrix * mv_matrix * vec4(vec3(gl_TessCoord.x) * tesPos[0] + 
		 vec3(gl_TessCoord.y) * tesPos[1] + 
		 vec3(gl_TessCoord.z) * tesPos[2], 1.0);

}
