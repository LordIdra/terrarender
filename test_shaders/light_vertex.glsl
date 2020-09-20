#version 330 core

//Vertex inputs
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 texture_position;
layout (location = 3) in float texture_id;

layout (location = 8) in vec4 color_blend;


//Uniform inputs
uniform mat4 transform_matrix[200];
uniform mat4 camera_matrix;
uniform mat4 projection_matrix;

//Outputs
out vec2 texture_coord;
out vec4 texture_color;
flat out float texture_index;


//Main function
void main()
{
    gl_Position = projection_matrix * camera_matrix * transform_matrix[gl_InstanceID] * vec4(vertex_position, 1.0);

    texture_coord = texture_position;
    texture_index = texture_id;
    texture_color = color_blend;
}