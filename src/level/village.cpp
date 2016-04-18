#include "village.h"

Village::Village(std::string name, std::string filename, int grid_x, int grid_y)
{
	init(name, filename, grid_x, grid_y);
}

void Village::init(std::string name, std::string filename, int grid_x, int grid_y)
{
	this->name = name;
	this->texture.loadFromFile("res/tiles/"+filename);
	this->sprite.setTexture(texture);

	this->sprite.setPosition(sf::Vector2f(grid_x*32, grid_y*32));

	this->favour = 0.0f;

	this->bbox = sprite.getGlobalBounds();
}

void Village::update(sf::Time deltaTime)
{
	this->bbox = sprite.getGlobalBounds();
}

void Village::render(sf::RenderWindow& window)
{
	window.draw(sprite);
}
