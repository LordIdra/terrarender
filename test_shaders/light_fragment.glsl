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

//Color output
out vec4 color;

//Constants
#define POINT_LIGHT_NUMBER 100
#define SPECULAR_STRENGTH 0.5
#define SPECULAR_EXPONENT 32


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


/* MAIN FUNCTION */
void main()
{
    vec4 base_color = GetBaseColor();

    color = base_color;
}