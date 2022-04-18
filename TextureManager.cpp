#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures; //redeclare static variable 

void TextureManager::loadTexture(string fileName) {
	string path = "images/"; 
	path += fileName + ".png"; //gets the correct file name 

	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::getTexture(string textureName) { //gets the requested texture, loads it if it hasnt been already
	
	if (textures.find(textureName) == textures.end()) { //checks to see if the texture is loaded, if not, then it does it anyway
		loadTexture(textureName); 
	}

	return textures[textureName]; 
}

void TextureManager::clear() {
	textures.clear(); //get rid of all of the texture objects 
}
