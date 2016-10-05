#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec3 c_face;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

// Terrain specific
const float maxHeight = 40;

const vec3 lightVecNormalized = normalize(vec3(1.5, 1.0, 2.3));
const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float lightIntensity = 0.6;

void main()
{
	// Calculate normal
	vec3 P0 = gl_in[0].gl_Position.xyz;
	vec3 P1 = gl_in[1].gl_Position.xyz;
	vec3 P2 = gl_in[2].gl_Position.xyz;

	vec3 normal = normalize(cross(P1 - P0, P2 - P0));

	// Decide color
	float h = clamp(P0.y / maxHeight, 0.0, 1.0);
	//float R = -1.33333 *h*h*h + 3.66667 *h*h - 2.05333 *h + 0.67;
	float R = -2.2381 * h*h*h + 5.4524 * h*h - 3.1343 * h + 0.87;
	//float G = -1.5 *h*h*h + 3.625 *h*h - 1.885 *h + 0.62;
	float G = 3.79 * h*h*h - 3.75 * h*h - 0.02 * h + 0.84;

	float B = 5.43 * h*h*h - 6.95 * h*h + 1.86 * h + 0.31;
	//float B = 5.5 *h*h*h-7.125 *h*h+1.995 *h+0.28;


	//float R = 0.042 * h*h*h + 1.333 * h*h - 0.715 * h + 0.27;
	//float G = 5.375 * h*h*h - 6.042 * h*h + 0.907 * h + 0.65;
	//float B = -1.583 * h*h*h + 3.25 * h*h - 1.047 * h;
	vec3 terrainColor = vec3(R, G, B);
	

	float diffuse = clamp(dot(lightVecNormalized, normal.xyz), -1.0, 1.0);
	vec4 c = vec4(terrainColor + diffuse * lightColor * lightIntensity, 1.0);

	for(int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = projection_matrix * view_matrix * gl_in[i].gl_Position;
		c_face = c.xyz;

		EmitVertex();
	}
	EndPrimitive();
}