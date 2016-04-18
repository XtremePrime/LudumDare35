#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>

class TextureManager
{
private:
	std::map<std::string, sf::Texture> textures;
public:
	TextureManager(){}
	~TextureManager(){}

	void load_texture(const std::string& name, const std::string& filename)
	{
		sf::Texture tx;
		tx.loadFromFile("res/tiles/"+filename);
		std::cout << "[TXMGR] Loaded: " << filename << "\n";

		textures[name] = tx;
	}

	sf::Texture& get_ref(const std::string& texture)
	{
		return this->textures.at(texture);
	}
};

#endif // TEXTUREMANAGER_H
