#include "resource.h"

void Resource::init(std::string name, std::string filename, sf::Vector2f pos, int size_x=32, int size_y=32)
{
	this->name = name;
	this->texture.loadFromFile("res/tiles/"+filename);
	sprite.setTexture(texture);
	sprite.scale((float)size_x/32, (float)size_y/32);
	// std::cout << sprite.getScale().x << "\n";
	// sprite.setOrigin(sf::Vector2f(size_x/2, size_x/2));
	sprite.setPosition(pos);
}

void Resource::render(sf::RenderWindow& window)
{
	window.draw(sprite);
}