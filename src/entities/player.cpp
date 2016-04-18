#include "player.h"

void Player::init(sf::Vector2f pos, int w, int h)
{
	texture.loadFromFile("res/tiles/cat_spritesheet.png");
	sprite_source = sf::IntRect(0, 0, 64, 64);
	sprite.setTexture(texture);
	sprite.setTextureRect(sprite_source);
	sprite.scale((float)w/64, (float)h/64);
	// std::cout << sprite.getScale().x << "\n";
	sprite.setOrigin(sf::Vector2f(64/2, 64/2));
	sprite.setPosition(pos);
	anim_clock.restart();

	//- Init keys
	keys["up"] = sf::Keyboard::W;
	keys["down"] = sf::Keyboard::S;
	keys["left"] = sf::Keyboard::A;
	keys["right"] = sf::Keyboard::D;
	keys["arrow-up"] = sf::Keyboard::Up;
	keys["arrow-down"] = sf::Keyboard::Down;
	keys["arrow-left"] = sf::Keyboard::Left;
	keys["arrow-right"] = sf::Keyboard::Right;
	keys["action"] = sf::Keyboard::C;
}

void Player::handle_events(sf::Event& event)
{
    if(event.type == sf::Event::KeyReleased)
    {
		switch(event.key.code)
		{
			case sf::Keyboard::W:
				up = false;
			break;
			case sf::Keyboard::S:
				down = false;
			break;
			case sf::Keyboard::D:
				right = false;
			break;
			case sf::Keyboard::A:
				left = false;
			break;
			case sf::Keyboard::Space:
				action = false;
			break;
			case sf::Keyboard::Q:
				shift = false;
			break;
			default:
			break;
		}
    }
    else if(event.type == sf::Event::KeyPressed)
    {
 		switch(event.key.code)
		{
			case sf::Keyboard::Space:
				action = true;
			break;
			case sf::Keyboard::Q:
				if(!shift)
				{
					if(this->shape != Shape::IRON){
						shape = Shape::IRON;
						std::cout << "[PLAYER]: turned into IRON\n";
						started = true;
						power = (float)inventory.get_iron();
						shape_timer.restart();
					}
					else{
						this->shape = Shape::STANDARD;
						std::cout << "[PLAYER]: turned into STANDARD\n";
					}
					shift = true;
				}
			break;
			default:
			break;
		}
    }
}


void Player::update(sf::Time deltaTime)
{
	move(deltaTime);

	if(shape_timer.getElapsedTime().asSeconds() >= power && started)
	{
		started = false;
		power = 0.0f;
		shape = Shape::STANDARD;
		std::cout << "[PLAYER]: Out of power! Back to STANDARD!\n";
	}

	if(anim_clock.getElapsedTime().asSeconds() > 0.15f)
	{
		if(sprite_source.left >= 64*2)
			sprite_source.left = 0;
		else
			sprite_source.left += 64;

		sprite.setTextureRect(sprite_source);
		anim_clock.restart();
	}
	this->bbox = sprite.getGlobalBounds();
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(sprite);
}


void Player::move(sf::Time dt)
{
	vx = vy = 0;

	#define press(key) sf::Keyboard::isKeyPressed(key)
	if(press(keys["up"]) || press(keys["arrow-up"])){
		up = true;
		dir = Direction::UP;
	}else if(press(keys["down"]) || press(keys["arrow-down"])){
		down = true;
		dir = Direction::DOWN;
	}
	if(press(keys["right"]) || press(keys["arrow-right"])){
		right = true;
		dir = Direction::LEFT;
	}else if(press(keys["left"]) || press(keys["arrow-left"])){
		left = true;
		dir = Direction::RIGHT;
	}
	#undef press
}

void Player::move2(sf::Time dt)
{
	if(up)
	{
		//- Wall coll
		if(pos.y <= 0)
			pos.y = 0;
		else
			vy -= speed;
	}
	else if(down)
	{
		//- Wall coll
		// if(pos.y <= 0)
		// 	pos.y = 0;
		// else
		// 	vy -= speed;
		vy += speed;
	}

	if(right)
	{
		//- Wall coll
		// if(pos.y <= 0)
		// 	pos.y = 0;
		// else
		// 	vy -= speed;
		vx += speed;
	}
	else if(left)
	{
		//- Wall coll
		// if(pos.y <= 0)
		// 	pos.y = 0;
		// else
		// 	vy -= speed;
		vx -= speed;
	}

	pos.x += vx * dt.asSeconds();
	pos.y += vy * dt.asSeconds();
	sprite.setPosition(pos);
}
