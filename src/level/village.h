#ifndef VILLAGE_H
#define VILLAGE_H

#include <SFML/Graphics.hpp>
#include <string>

class Village
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	std::string name;

	float favour;
	sf::FloatRect bbox;
public:
	Village(std::string name, std::string filename, int grid_x, int grid_y);
	void init(std::string name, std::string filename, int grid_x, int grid_y);
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);

	sf::FloatRect get_bbox(){ return this->bbox; }
};

#endif // VILLAGE_H
