# CSC-473-Raytracer

### Project Description
The goal of this project was to create a robust and efficient raytracer using C++. Implementation features include:
* POV-Ray file parsing
* Blinn-Phong shading
* Refraction and reflection recursive raytracing
* Object transformations
* Spatial data structures
* Monte Carlo ray tracing 
* Texture/Normal mapping
* Bilinear Interpolation

![glitch](output/glitch.png)

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
# TODO - gray bg
![bi](output/bi.png)

### Final Project
For my final project I chose to do texture mapping. Professor Wood always emphasized the importance of this low-cost, high-reward feature in graphics, and I couldn't agree more. Texture mapping is conceptually straightforward, relatively easy to implement, and of course makes our project look much more realistic than just using single RGB values for object shading.

### Research
# TODO 

### Software Design Improvement
In my final project I had to create a completely new data structure to handle loading in new textures. To do this I had to implement a few things. 
The first thing I did was implemented what I call a TextureBatch. The TextureBatch holds on to all of the textures that have been loaded thus far. When my POV parser finds a texture, it first checks with the TextureBatch to make sure the texture hasn't been loaded yet. If it has, we can reference that texture. If it hasn't we load in a new texture.
As of now each texture is defined by its file name. I would like to implement unique ID's per texture for added security and efficiency. 
The other thing I had to think about was that because I was using multiple textures *types*, I had to allow different objects to reference multiple textures. To do this, I used enums to denote which type a texture is (color or normal). And in my GeoObject class I have struct of textures that contains one texture pointer of each type. This design allows me to add many different types of textures (bump, specular, etc.) for future implementations.

