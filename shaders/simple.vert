#version 330 core

uniform mat4 model_matrix;

in vec3 v_Pos;

void main(){
	gl_Position = model_matrix * vec4(v_Pos,1.0);
}
