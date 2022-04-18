#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string; 

class TextureManager
{
	static unordered_map<string, sf::Texture> textures; 
	static void loadTexture(string textureName);
public: 
	static sf::Texture& getTexture(string textureName); 
	static void clear(); //call this once at the end of main 
};

