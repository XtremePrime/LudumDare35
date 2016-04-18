#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../inventory.hpp"

enum Direction
{
	UP, DOWN, LEFT, RIGHT
};

class Player : public Entity
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	std::map<std::string, sf::Keyboard::Key> keys;
	bool moved = false;
	sf::Clock anim_clock;
	sf::IntRect sprite_source;
	Direction dir;
	Inventory inventory;
public:
	int vx = 0, vy = 0;
	int speed = 150;
	bool up = false, down = false, left = false, right = false, action = false;


	void init(sf::Vector2f, int, int);
	void render(sf::RenderWindow&);
	void update(sf::Time);
	void handle_events(sf::Event&);
	void move(sf::Time);
	void move2(sf::Time);

	Inventory& get_inventory(){ return this->inventory; }
};

#endif // PLAYER_H
