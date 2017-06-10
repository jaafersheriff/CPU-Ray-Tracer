#include "TextureBatch.hpp"


Texture* TextureBatch::addTexture(std::string name) {
   Texture *texture = getTexture(name);
   if (texture == nullptr) {
      textures[texture->name] = texture;
   }
   return texture;
}

Texture* TextureBatch::getTexture(std::string name) {
   std::map<std::string, Texture*>::iterator i = textures.find(name);
   if (i != textures.end()) {
      return i->second;
   }
   return nullptr;
}