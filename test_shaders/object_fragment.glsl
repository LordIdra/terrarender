#version 330 core

/* INPUTS AND OUTPUTS */
//Texture inputs
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;

uniform sampler2D texture9;
uniform sampler2D texture10;
uniform sampler2D texture11;
uniform sampler2D texture12;

//Vertex inputs
flat in float texture_index;
in vec4 texture_color;
in vec2 texture_coord;

flat in vec3 normal;
in vec3 fragment_position;

//Color output
out vec4 color;

//Constants
#define POINT_LIGHT_NUMBER 100
#define DIRECTION_LIGHT_NUMBER 100
#define SPECULAR_STRENGTH 0.5
#define SPECULAR_EXPONENT 32

#define LIGHT_CONSTANT 1.0


//Material input
flat in vec3 material_ambient;
flat in vec3 material_diffuse;
flat in vec3 material_specular;
flat in float material_reflective;

//Lighting structs
struct PointLight
{
    vec3 position;
    vec3 diffuse;
    vec3 specular;

    float linear;
    float quadratic;
};

struct DirectionLight
{
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
};

//Lighting inputs
uniform PointLight point_lights[POINT_LIGHT_NUMBER];
uniform DirectionLight direction_lights[DIRECTION_LIGHT_NUMBER];

uniform vec3 ambient;
uniform vec3 camera_position;


/* TEXTURE HANDLING */
vec4 GetBaseColor()
{
    //Get texture color based on texture index
    vec4 texture_base;

    switch (int(texture_index))
    {
        case 1: texture_base = texture(texture1, texture_coord); break;
        case 2: texture_base = texture(texture2, texture_coord); break;
        case 3: texture_base = texture(texture3, texture_coord); break;
        case 4: texture_base = texture(texture4, texture_coord); break;

        case 5: texture_base = texture(texture5, texture_coord); break;
        case 6: texture_base = texture(texture6, texture_coord); break;
        case 7: texture_base = texture(texture7, texture_coord); break;
        case 8: texture_base = texture(texture8, texture_coord); break;

        case 9: texture_base = texture(texture9, texture_coord); break;
        case 10: texture_base = texture(texture10, texture_coord); break;
        case 11: texture_base = texture(texture11, texture_coord); break;
        case 12: texture_base = texture(texture12, texture_coord); break;
    }

    return mix(texture_base, texture_color, texture_color.a);
}


/* LIGHTING HANDLING */
vec3 GetAmbientColor()
{
    return ambient * material_ambient;
}

vec3 GetPointLightColor()
{
    vec3 point_light_base;

    for (int i = 0; i < POINT_LIGHT_NUMBER; i++)
    {
        //Attenuation
        float distance = length(point_lights[i].position - fragment_position);
        float attenuation = 1.0f /
            (LIGHT_CONSTANT + 
            (point_lights[i].linear * distance) +
            (point_lights[i].quadratic * distance * distance));

        //Diffuse
        vec3 light_direction = normalize(point_lights[i].position - fragment_position);
        point_light_base += max(dot(normal, light_direction), 0.0) * point_lights[i].diffuse * material_diffuse * attenuation;

        //Specular
        vec3 view_direction = normalize(camera_position - fragment_position);
        vec3 reflect_direction = reflect(-light_direction, normal);

        float specular_intensity = pow(max(dot(view_direction, reflect_direction), 0.0), material_reflective);
        point_light_base += SPECULAR_STRENGTH * specular_intensity * point_lights[i].specular * material_specular * attenuation;  
    }

    return point_light_base;
}

vec3 GetDirectionLightColor()
{
    vec3 direction_light_base;
    for (int i = 0; i < DIRECTION_LIGHT_NUMBER; i++)
    {
        //Diffuse
        vec3 light_direction = normalize(-direction_lights[i].direction);
        direction_light_base += max(dot(normal, light_direction), 0.0) * direction_lights[i].diffuse * material_diffuse;

        //Specular
        vec3 view_direction = normalize(camera_position - fragment_position);
        vec3 reflect_direction = reflect(-light_direction, normal);

        float specular_intensity = pow(max(dot(view_direction, reflect_direction), 0.0), material_reflective);
        direction_light_base += SPECULAR_STRENGTH * specular_intensity *direction_lights[i].specular * material_specular;  
    }

    return direction_light_base;
}


/* MAIN FUNCTION */
void main()
{
    vec4 base_color = GetBaseColor();

    vec4 ambient_color = vec4(GetAmbientColor(), 1.0);
    vec4 point_color = vec4(GetPointLightColor(), 1.0);
    vec4 direction_color = vec4(GetDirectionLightColor(), 1.0);

    color = base_color * (ambient_color + point_color + direction_color);
}