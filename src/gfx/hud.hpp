#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include "../util/timer.hpp"
#include "../level/level.h"
#include "../entities/player.h"
#include "sstream"

class Hud
{
private:
	Timer timer;
    sf::Font font;
    Player player;
    Level level;

    sf::RectangleShape rectangle;

    //- Res
    Resource iron, magiberries;
    sf::Sprite heart;
    sf::Texture heart_tx;
    sf::Sprite power;
    sf::Texture power_tx;
    sf::Text iron_text, magiberries_text, favour_text, power_text;
public:
	void init()
	{
        font.loadFromFile("res/font/PressStart2P.ttf");
		timer.init(font);

		magiberries.init("Magiberries", "berry.png", sf::Vector2f(10, 640-32-10), 32, 32);
		iron.init("Iron", "iron_ore.png", sf::Vector2f(135, 640-32-10), 32, 32);

		rectangle.setSize(sf::Vector2f(880, 128));
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setPosition(0, 640-32-25);

		heart_tx.loadFromFile("res/tiles/heart.png");
		heart.setTexture(heart_tx);
		heart.setPosition(sf::Vector2f(135-10 + 135, 640-32-10));
		power_tx.loadFromFile("res/tiles/power.png");
		power.setTexture(power_tx);
		power.setPosition(sf::Vector2f(135-10 + 135 + 135, 640-32-10));

		//-
		magiberries_text.setFont(this->font);
		magiberries_text.setCharacterSize(16);
		magiberries_text.setString("");
		magiberries_text.setColor(sf::Color::White);
		magiberries_text.setPosition(sf::Vector2f(55, 640-32));

		iron_text.setFont(this->font);
		iron_text.setCharacterSize(16);
		iron_text.setString("");
		iron_text.setColor(sf::Color::White);
		iron_text.setPosition(sf::Vector2f(135+45, 640-32));

		favour_text.setFont(this->font);
		favour_text.setCharacterSize(16);
		favour_text.setString("");
		favour_text.setColor(sf::Color::White);
		favour_text.setPosition(sf::Vector2f(135-10 + 135+45, 640-32));

		power_text.setFont(this->font);
		power_text.setCharacterSize(16);
		power_text.setString("");
		power_text.setColor(sf::Color::White);
		power_text.setPosition(sf::Vector2f(135-10 + 135+45+135, 640-32));
	}

	void update(sf::Time deltaTime, Player& player, Village& village)
	{
		this->player = player;

        sf::View view;
		timer.update(deltaTime, player, view);
		{
			std::stringstream ss;
			ss << "x " << player.get_inventory().get_magiberries();
			magiberries_text.setString(ss.str());
		}
		{
			std::stringstream ss;
			ss << "x " << player.get_inventory().get_iron();
			iron_text.setString(ss.str());
		}
		{
			std::stringstream ss;
			ss << "x ";
			ss.precision(2);
			ss << village.favour;
			favour_text.setString(ss.str());
		}
		{
			std::stringstream ss;
			ss << "x ";
			ss.precision(2);
			float xx = (player.get_power() < 0.0f) ? 0.0f : player.get_power();
			ss << xx;
			power_text.setString(ss.str());
		}
	}

	void render(sf::RenderWindow& window, sf::Vector2f player_pos, sf::View& view)
	{
		timer.render(window/*, player_pos, view*/);
		window.draw(rectangle);

		iron.render(window);
		magiberries.render(window);
		window.draw(heart);
		window.draw(power);

		window.draw(magiberries_text);
		window.draw(iron_text);
		window.draw(favour_text);
		window.draw(power_text);
	}
};

#endif // HUD_HPP
