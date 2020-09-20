#include <vector>

#include <functions/initialize.cpp>

#include <classes/containers/WorldObject.cpp>
#include <classes/containers/Window.cpp>
#include <classes/move/Camera.cpp>

#include <gen/cube.cpp>


Camera camera;

const float camera_speed = 0.2f;
const float rotate_speed = 0.1f;


//Adjusts camera position and rotation
void camera_callback(Window& window)
{
    //Calculate how much we should move the camera
    float translate_magnitude = camera_speed;
    float rotate_magnitude = rotate_speed;

    //Handle position
    if (window.KeyPressed(GLFW_KEY_W)) camera.Translate(glm::vec3(0.0f, 0.0f, translate_magnitude));
    if (window.KeyPressed(GLFW_KEY_S)) camera.Translate(glm::vec3(0.0f, 0.0f, -translate_magnitude));

    if (window.KeyPressed(GLFW_KEY_E)) camera.Translate(glm::vec3(0.0f, translate_magnitude, 0.0f));
    if (window.KeyPressed(GLFW_KEY_Q)) camera.Translate(glm::vec3(0.0f, -translate_magnitude, 0.0f));

    if (window.KeyPressed(GLFW_KEY_D)) camera.Translate(glm::vec3(translate_magnitude, 0.0f, 0.0f));
    if (window.KeyPressed(GLFW_KEY_A)) camera.Translate(glm::vec3(-translate_magnitude, 0.0f, 0.0f));

    //Handle rotation
    float yaw = ((float)(window.cursor_x) - (float)(window.previous_cursor_x)) * rotate_speed;
    float pitch = ((float)(window.previous_cursor_y) - (float)(window.cursor_y)) * rotate_speed;

    camera.Rotate(glm::vec3(yaw, pitch, 0.0f));

    //Handle closing window via ESC
    if (window.KeyPressed(GLFW_KEY_ESCAPE)) window.Close();
}


//Main function
int main()
{
    //Initialize GLFW
    InitializeGLFW();
    SetVersion(3, 3, true);

    //Create window
    Window window(800, 800, "TEST", 4, NULL, NULL);
    window.SetCursorState(false);

    //Initialize camera
    camera = Camera(800.0f, 800.0f, 45.0f, 0.1f, 1000.0f);

    //Initialize GLAD
    InitializeGLAD();

    //Initialize handlers
    MaterialHandler material_handler;
    TextureHandler texture_handler;
    LightingHandler lighting_handler;

    lighting_handler.SetAmbience(glm::vec3(0.1f, 0.1f, 0.1f));

    //Create materials
    Material grass_material {
        glm::vec3(0.05, 0.05, 0.05),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(0.7, 0.7, 0.7),
        128.0
    };

    Material wood_material {
        glm::vec3(0.05, 0.05, 0.05),
        glm::vec3(0.3, 0.3, 0.3),
        glm::vec3(0.0, 0.3, 0.3),
        128.0
    };

    material_handler.AddMaterial(&grass_material);                      //ID 0
    material_handler.AddMaterial(&wood_material);                       //ID 1

    //Create textures
    Texture2D wood_texture("test_textures/wood.jpg", GL_RGB);
    Texture2D grass_texture("test_textures/grass.jpg", GL_RGB);
    Texture2D background_texture("test_textures/background.png", GL_RGBA);
    
    texture_handler.AddTexture(&wood_texture);                          //ID 1
    texture_handler.AddTexture(&grass_texture);                         //ID 2
    texture_handler.AddTexture(&background_texture);                    //ID 3

    //Create lights
    lighting_handler.AddPointLight(PointLight{
        glm::vec3(1.0f, 3.0f, 1.0f),        //Position
        glm::vec3(3.0f, 3.0f, 3.0f),        //Diffuse
        glm::vec3(0.5f, 0.5f, 0.5f),        //Specular
        0.35f, 0.44f});                     //Linear and quadratic (read: range)

    lighting_handler.AddPointLight(PointLight{
        glm::vec3(7.0f, 3.0f, 7.0f),        //Position
        glm::vec3(3.0f, 3.0f, 3.0f),        //Diffuse
        glm::vec3(0.5f, 0.5f, 0.5f),        //Specular
        0.14f, 0.07f});                     //Linear and quadratic (read: range)

    //Create shader and cube object
    Shader cube_shader("test_shaders/object_vertex.glsl", "test_shaders/object_fragment.glsl");
    Shader light_shader("test_shaders/light_vertex.glsl", "test_shaders/light_fragment.glsl");

    WorldObject cube(cube_shader, GenerateCube(glm::vec4(0.0, 0.0, 0.0, 0.0), 2, 0), texture_handler, material_handler, lighting_handler);
    WorldObject light(light_shader, GenerateCube(glm::vec4(1.0, 1.0, 1.0, 1.0), 2, 1), texture_handler, material_handler, lighting_handler);

    //Generate tiles
    for (int x = 0.0f; x < 10; x++)
    {
        for (int z = 0.0f; z < 10; z++)
        {
            cube.AddInstance(Instance(
                glm::vec3((float)x, (rand() % 10)/10.0f, (float)z),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 1.0f)
            ));
        }
    }

    //Generate light objects
    light.AddInstance(Instance(
        glm::vec3(14.0, 3.0, 7.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.5, 0.5, 0.5)
    ));

    //Enter mainloop
    while(!window.ShouldClose())
    {
        //Handle events from previous render
        camera_callback(window);

        //Clear screen
        window.Clear();
        window.SetColor(0.0f, 0.3f, 0.6f, 0.5f);
        window.SetDepthTesting(true);

        //Render objects
        cube.Draw(camera);
        light.Draw(camera);

        //Update window
        window.Update();
    }

    return 0;
}