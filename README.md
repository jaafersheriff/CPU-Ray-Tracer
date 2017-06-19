# CSC-473-Raytracer

### Project Description
The goal of this project was to create a robust and efficient ray tracer using C++. Implementation features include:
* POV-Ray file parsing
* Blinn-Phong shading
* Refractions and reflections
* Object transformations
* Spatial data structures
* Monte Carlo ray tracing 
* Texture and Normal mapping
* Bilinear Interpolation

### Final Project
For my final project I chose to do texture mapping. Texture mapping is a low-cost, high-reward feature in computer graphics that is conceptually straightforward, relatively simple to implement, and makes our project much more realistic.

### Software Design
Adding textures to a ray tracer isn't terribly difficult, but doing it well from a software design standpoint requires some extra functionality.

The first thing I did was I implemented what I call a TextureBatch. The TextureBatch contains a list of all the different textures that have been loaded thus far. When my POV-Ray parser finds a texture, it first communicates with the TextureBatch to make sure that texture hasn't already been loaded. If the texture already exists, we can reference that texture rather than load it again.

As of now each texture is individualized by only its file name. I would like to implement unique ID's per texture for added security and efficiency. 

The other thing I had to implement was different texture *types*. In my implementation I allow objects to reference both color maps and normal maps. Looking ahead I want to add bump maps or specular maps, so I created a system that would allow objects to contain multiple texture types. To do this, I used enums to denote a texture's type. I also allow objects to reference at most one of each texture type. This design allows me to add many different types of textures in the future.

### Research
Realistic Ray Tracing by Peter Shirley and R. Keith Morley

Ray Tracing Tutorial by The CoderMind Team

opengameart.org for color and normal map pairs

Normal Map Online for creating my own normal maps

# Output

### Reflection 
![shiny](output/shiny.png)

### Refraction  
![fresnel](output/fresnel1.png)

### Object Transformations
![valentine](output/valentine.png)

### Spatial Data Structures
![balls](output/balls2.png)

### Monte Carlo Ray tracing
![boxes](output/boxgi.png)

### Texture mapping
![texture](output/texture.png)

### Normal mapping
![norm](output/norm.png)
![norm1](output/norm1.png)

### Bilinear Interpolation
![bi](output/bi.png)

