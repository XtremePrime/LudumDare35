#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Audio.hpp>

class State;
class Game
{
private:
	sf::RenderWindow window;
	const int GAME_WIDTH = 860, GAME_HEIGHT = 640;
	const float SCALE = 1.0;
	bool is_running = true;
	sf::Clock clock;
	std::vector<State*> state_stack;
	sf::Image icon;
	sf::ContextSettings settings;
	sf::View view;
	sf::Font font;

	void init();
	void update(sf::Time);
	void handle_events(sf::Event);
	void render(sf::RenderWindow&);
public:
	void change_state(State* state);
	void push_state(State* state);
	void pop_state();

	void run();
	void quit();

	sf::RenderWindow* get_window() { return &window; }
	std::vector<State*> get_state_stack() { return state_stack; }
	int get_width() { return this->GAME_WIDTH/this->SCALE; }
	int get_height() { return this->GAME_HEIGHT/this->SCALE; }
	float get_scale(){ return this->SCALE; }
};

#endif // GAME_H
