#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "../entities/player.h"

class Timer
{
private:
	sf::Font font;
	sf::Text text;
	sf::Clock timer;
public:
	void init(sf::Font font)
	{
		this->font = font;
		text.setFont(this->font);
		text.setCharacterSize(16);
		text.setString("");
		text.setColor(sf::Color::White);
		text.setPosition(sf::Vector2f(10, 10));
	}
	/*
	#define set_x(xr) 5+(xr)-(level.get_view().getSize().x/2)
	#define set_y(yr) 5+(yr)-(level.get_view().getSize().y/2)
	// hpbar.setPosition(t((player.get_x()+screen_width)-280, level.get_view().getSize().x), t((player.get_y()+screen_height)-35, level.get_view().getSize().y));
	score.setPosition(set_x(player.get_x()+0), set_y(player.get_y()+0));
	wave.setPosition(set_x(player.get_x()+275), set_y(player.get_y()+0));
	enemies_left.setPosition(set_x(player.get_x()+425), set_y(player.get_y()+0));
	hpbar.setPosition(set_x(player.get_x()+280), set_y((player.get_y()+screen_height)-35));
	#undef set_y
	#undef set_x
	*/
	sf::Time getElapsedTime()
	{
		return timer.getElapsedTime();
	}

	void update(sf::Time deltaTime, Player& player, sf::View& view)
	{
		std::stringstream ss;
		ss << "Time: " << (int)timer.getElapsedTime().asSeconds();
		text.setString(ss.str());
		/*#define set_x(xr) 10+(xr)-(view.getSize().x/2)
		#define set_y(yr) 10+(yr)-(view.getSize().y/2)
		text.setPosition(set_x(player.get_pos().x), set_y(player.get_pos().y));
		#undef set_y
		#undef set_x*/
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(text);
	}
};

#endif // TIMER_HPP
