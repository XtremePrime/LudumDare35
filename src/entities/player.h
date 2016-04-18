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

enum class Shape
{
	STANDARD, IRON
};

/*struct Shape
{
	sf::Clock timer;
	float time; // 10 magib = 1 second
	ShapeType type;

	void run()
	{
		timer.restart();

	}
};*/

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

	//- Shapeshift stuff
	Shape shape;

	float power = 0.0f;
	sf::Clock shape_timer;
	bool started = false;
public:
	int vx = 0, vy = 0;
	int speed = 150;
	bool up = false, down = false, left = false, right = false, action = false, shift = false;
	int shape_sprite = 0;

	void init(sf::Vector2f, int, int);
	void render(sf::RenderWindow&);
	void update(sf::Time);
	void handle_events(sf::Event&);
	void move(sf::Time);
	void move2(sf::Time);

	Inventory& get_inventory(){ return this->inventory; }
	Shape get_shape() { return this->shape; }
	float get_power() { return this->power; }
	void set_power(float n) { this->power = n; }
	void erase_movement() { up = down = left = right = false; }
};

#endif // PLAYER_H
