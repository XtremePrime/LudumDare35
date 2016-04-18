#ifndef LEVEL_H
#define LEVEL_H

#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "../util/texturemanager.hpp"
#include "resource.h"
#include "resource_tile.hpp"
#include "village.h"

class Level
{
private:
	int w, h;
	std::vector<Tile*> tiles;
	std::vector<Village*> villages;
	TextureManager txmgr;
	void construct_world();
	sf::View view;
public:
	void init(int, int);
	void update(sf::Time);
	void render(sf::RenderWindow&, sf::Vector2f);

	sf::View& get_view(){ return this->view; }
	Tile& get_tile(int, int, int);
	std::vector<Tile*> get_tiles() { return this->tiles; }
	std::vector<Village*> get_villages() { return this->villages; }	
};

#endif // LEVEL_H
