#include "player.h"

void Player::init(sf::Vector2f pos, int w, int h)
{
	this->pos = pos;
	texture.loadFromFile("res/tiles/ss.png");
	sprite_source = sf::IntRect(shape_sprite, 0, 64, 64);
	sprite.setTexture(texture);
	sprite.setTextureRect(sprite_source);
	sprite.scale((float)w/64, (float)h/64);
	// std::cout << sprite.getScale().x << "\n";
	sprite.setOrigin(sf::Vector2f(64/2, 64/2));
	sprite.setPosition(pos);
	this->bbox = sprite.getGlobalBounds();
	anim_clock.restart();

	//- Init keys
	keys["up"] = sf::Keyboard::W;
	keys["down"] = sf::Keyboard::S;
	keys["left"] = sf::Keyboard::A;
	keys["right"] = sf::Keyboard::D;
	keys["action"] = sf::Keyboard::C;
	keys["shift"] = sf::Keyboard::F;
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
			case sf::Keyboard::F:
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
			case sf::Keyboard::F:
				if(!shift)
				{
					if(power <= 0.0f){
						std::cout << "[PLAYER]: No power!\n";
						break;
					}

					if(this->shape != Shape::IRON){
						shape = Shape::IRON;
						std::cout << "[PLAYER]: turned into IRON\n";
						started = true;

						shape_sprite = 1;
						sprite_source.top = shape_sprite*64;

						shape_timer.restart();
					}
					else{
						started = false;
						power -= shape_timer.getElapsedTime().asSeconds();
						this->shape = Shape::STANDARD;
						std::cout << "[PLAYER]: turned into STANDARD\n";
						shape_sprite = 0;
					}
					shift = true;

					sprite_source.top = shape_sprite*64;
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

	sprite_source.top = shape_sprite*64;

	//- End of timer
	// if(shape_timer.getElapsedTime().asSeconds() >= power && started)
	// {
	// 	started = false;
	// 	power = 0.0f;
	// 	shape = Shape::STANDARD;
	// 	std::cout << "[PLAYER]: Out of power! Back to STANDARD!\n";
	// 	shape_sprite = 0;
	// }
	if(power <= 0.0f && started)
	{
		power = 0.0f;
		started = false;
		shape = Shape::STANDARD;
		std::cout << "[PLAYER]: Out of power! Back to STANDARD!\n";
		shape_sprite = 0;
	}
	if(shape_timer.getElapsedTime().asSeconds() >= 0.1f && started)
	{
		power -= 0.1f;
		shape_timer.restart();
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
	if(press(keys["up"])){
		up = true;
		dir = Direction::UP;
	}else if(press(keys["down"])){
		down = true;
		dir = Direction::DOWN;
	}
	if(press(keys["right"])){
		right = true;
		dir = Direction::LEFT;
	}else if(press(keys["left"])){
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
		if(pos.y >= 640-32/2)
			pos.y = 640-32/2;
		else
			vy += speed;
	}

	if(right)
	{
		//- Wall coll
		if(pos.x >= 860-32/2)
			pos.x = 860-32/2;
		else
			vx += speed;
	}
	else if(left)
	{
		//- Wall coll
		if(pos.x <= 0)
			pos.x = 0;
		else
			vx -= speed;
	}

	pos.x += vx * dt.asSeconds();
	pos.y += vy * dt.asSeconds();
	sprite.setPosition(pos);
}
