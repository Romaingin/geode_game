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
const float lightIntensity = 0.2;

void main()
{
	// Calculate normal
	vec3 P0 = gl_in[0].gl_Position.xyz;
	vec3 P1 = gl_in[1].gl_Position.xyz;
	vec3 P2 = gl_in[2].gl_Position.xyz;

	vec3 normal = normalize(cross(P1 - P0, P2 - P0));

	vec3 terrainColor = vec3(0.99,0.79,0.47);


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
