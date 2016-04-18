#ifndef RESOURCE_TILE_HPP
#define RESOURCE_TILE_HPP

#include "resource.h"
#include "tile.hpp"
#include <SFML/Graphics.hpp>

class ResourceTile : public Tile
{
private:
	Resource res;
public:
	ResourceTile(TileType tt, ResourceType rt, sf::Texture& tx, int grid_x, int grid_y)
	{
		this->txref = txref;
		Tile::init(tt, tx);
		init(rt);
		sprite.setPosition(sf::Vector2f(grid_x*size, grid_y*size));
		this->bbox = sprite.getGlobalBounds();
	}

	void init(ResourceType rt)
	{
		switch(rt)
		{
			case ResourceType::IRON:
				//res.init("Iron", "vine_3.png");
			break;
			case ResourceType::MAGIBERRIES:
				//res.init("Magiberries", "magiberries.png");
			break;
			default:
			break;
		}
	}
};

#endif // RESOURCE_TILE_HPP
