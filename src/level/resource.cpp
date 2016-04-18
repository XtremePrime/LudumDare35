#include "resource.h"

void Resource::init(std::string name, std::string filename)
{
	this->name = name;
	this->texture.loadFromFile("res/tiles/"+filename);
	this->sprite.setTexture(texture);
	//this->sprite.setPosition(sf::Vector2f(grid_x*32, grid_y*32));
}
