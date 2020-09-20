# terrarender
My attempt at making a clean and [relatively] organized OpenGL-based library for building 3D scenes.
I'm still very much a beginner to OpenGL (and C++) so take everything here with a truckload of salt.

**classes**
- WorldObject is a pre-loaded object that can be placed many times around the scene (colour can be changed)
- TextureHandler loads and stores materials (they can be referenced by ID)
- MaterialHandler stores materials (they can be referenced by ID)
- LightingHandler stores light positions, atrributes, etc

**todo**
- Allow instances and light attributes to be modified
- Switch from Uniforms to UBOs (currently this means no more than ~100 types of any instance or light can be on a scene at once)
- Add SpotLights
- Further improve lighting (shadows?)
