#include "TextureBatch.hpp"
#include <iostream>  // cout

Texture* TextureBatch::addTexture(std::string name) {
   Texture *texture = new Texture(name);
   textures.push_back(texture);
   return texture;
}

Texture* TextureBatch::getTexture(std::string name) {
   for (Texture *t : textures) {
      if (!name.compare(t->name)) {
         return t;
      }
   }

   return addTexture(name);
}

void TextureBatch::print() {
   std::cout << "Textures: " << textures.size() << std::endl;
   for (Texture *t : textures) {
      std::cout << t->name << std::endl;
   }
}

