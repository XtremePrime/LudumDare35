#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include "../util/timer.hpp"
#include "../level/level.h"
#include "../entities/player.h"

class Hud
{
private:
	Timer timer;
    sf::Font font;
    Player player;
    Level level;
public:
	void init()
	{
        font.loadFromFile("res/font/PressStart2P.ttf");
		timer.init(font);
	}

	void update(sf::Time deltaTime, Player& player, sf::View& view)
	{
		this->player = player;

		timer.update(deltaTime, player, view);
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

	void render(sf::RenderWindow& window, sf::Vector2f player_pos, sf::View& view)
	{
		timer.render(window/*, player_pos, view*/);
	}
};

#endif // HUD_HPP
