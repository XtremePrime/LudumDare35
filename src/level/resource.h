#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>
#include <string>

enum class ResourceType{
	IRON
};

class Resource
{
private:
	std::string name;
	sf::Texture texture;
	sf::Sprite sprite;
public:
    void init(std::string, std::string);
};

#endif // RESOURCE_H
