#version 430

#define VERTEX_DRIFT .3

in vec3 tesPos[];

layout (triangles, equal_spacing, ccw) in; // TRY BOTH WAYS

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform int objectId;

float rand(float x)
{
    return fract(sin(x) * 100000.0);
}

// Will only work with one winding order
vec3 GetNormal(vec3 a, vec3 b, vec3 c)
{
   vec3 i = a - b;
   vec3 j = c - b;
   return normalize(cross(j, i));
}

void main()
{
	vec3 position = vec3(gl_TessCoord.x) * tesPos[0] + 
		 vec3(gl_TessCoord.y) * tesPos[1] + 
		 vec3(gl_TessCoord.z) * tesPos[2];
	

	float posHash = position.x + position.y + position.z;
	position = normalize(position);
	
	vec3 normal = position;
	position = position + position*VERTEX_DRIFT * (rand(posHash + objectId) * 2. - 1.);

	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);

}
