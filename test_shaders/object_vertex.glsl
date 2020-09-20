#version 330 core

//Vertex inputs
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 texture_position;
layout (location = 2) in vec3 norm;
layout (location = 3) in float texture_id;

layout (location = 4) in vec3 material_ambient_in;
layout (location = 5) in vec3 material_diffuse_in;
layout (location = 6) in vec3 material_specular_in;
layout (location = 7) in float material_reflective_in;

layout (location = 8) in vec4 color_blend;


//Uniform inputs
uniform mat4 transform_matrix[200];
uniform mat4 camera_matrix;
uniform mat4 projection_matrix;

//General outputs
out vec2 texture_coord;
out vec4 texture_color;
flat out float texture_index;

flat out vec3 normal;
out vec3 fragment_position;

//lighting outputs
flat out vec3 ambient;

//Material outputs
flat out vec3 material_ambient;
flat out vec3 material_diffuse;
flat out vec3 material_specular;
flat out float material_reflective;


//Main function
void main()
{
    gl_Position = projection_matrix * camera_matrix * transform_matrix[gl_InstanceID] * vec4(vertex_position, 1.0);

    texture_coord = texture_position;
    texture_index = texture_id;
    texture_color = color_blend;

    normal = normalize(mat3(transpose(inverse(transform_matrix[gl_InstanceID]))) * norm);
    fragment_position = vec3(transform_matrix[gl_InstanceID] * vec4(vertex_position, 1.0));

    material_ambient = material_ambient_in;
    material_diffuse = material_diffuse_in;
    material_specular = material_specular_in;
    material_reflective = material_reflective_in;
}