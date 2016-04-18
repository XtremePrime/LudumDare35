#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "resource.h"

enum class TileType{
	GRASS,
	AIR,
	WATER,
	IRON,
	MAGIBERRIES
};

class Tile
{
protected:
	std::string txref;
	sf::Sprite sprite;
	sf::Vector2i pos;
	int size = 32;
	sf::FloatRect bbox;
public:
	bool is_solid, is_hazard, is_liquid, is_resource;
	int resource_code = 0;

	Tile(){}

	Tile(TileType tt, sf::Texture& tx, int grid_x, int grid_y)
	{
		this->txref = txref;
		init(tt, tx);
		sprite.setPosition(sf::Vector2f(grid_x*size, grid_y*size));
		this->bbox = sprite.getGlobalBounds();
	}

	void reset(TileType tt, sf::Texture& tx)
	{
		this->txref = txref;
		init(tt, tx);
	}

	void init(TileType tt, sf::Texture& tx)
	{
		auto set = [&](bool solid, bool hazard, bool liquid, bool res)
		{
			sprite.setTexture(tx);

			this->is_solid = solid;
			this->is_hazard = hazard;
			this->is_liquid = liquid;
			this->is_resource = res;
		};

		switch(tt)
		{
			case TileType::GRASS:
				set(false, false, false, false);
			break;
			case TileType::AIR:
				set(true, false, false, false);
			break;
			case TileType::WATER:
				set(true, false, true, false);
			break;
			case TileType::IRON:
				set(false, false, false, true);
				resource_code = 2;
			break;
			case TileType::MAGIBERRIES:
				set(false, false, false, true);
				resource_code = 1;
			break;
		}
	}

	void update()
	{
		this->bbox = sprite.getGlobalBounds();
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(this->sprite);
	}

	sf::Vector2i get_pos(){ return this->pos; }
	sf::FloatRect& get_bbox() { return this->bbox; }
};

#endif // TILE_HPP
