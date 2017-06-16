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
For my final project I chose to do texture mapping. Texture mapping is a low-cost, high-reward feature in graphics that is conceptually straightforward, relatively simple to implement, and makes our project look much more realistic.

### Software Design Improvement
Adding textures to this project was easy enough, but doing it properly from a software design standpoint added some extra modifications.

The first thing I did was I implemented what I call a TextureBatch. The TextureBatch holds on to all of the different textures that have been loaded thus far. When my POV-Ray parser finds a texture, it first checks with the TextureBatch to make sure the texture hasn't already been loaded. If the texture already exists, we can reference that texture rather than loading it again.
As of now each texture is individualized only by its file name, but I would like to implement unique ID's per texture for added security and efficiency. 

The other thing I had to think about was the added functionality of texture *types*. In my implementation I include color maps and normal maps. Looking ahead, I may add bump maps or specular maps, so I wanted to create a system that would allow objects to contain different texture types.  To do this, I used enums to denote which type a texture is, and in my GeoObject class I have struct of textures that contains one texture pointer of each type. This design allows me to add many different types of textures for future implementations.

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

