#include "game.h"
#include "states/state.h"
#include "states/introstate.h"
#include "states/gamestate.h"

void Game::init()
{
	//- Init context settings
	settings.antialiasingLevel = 0;

	view.reset(sf::FloatRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
	view.zoom(SCALE);
	view.reset(sf::FloatRect(0, 0, GAME_WIDTH, GAME_HEIGHT));

	//- Init Win Window
	this->window.create(sf::VideoMode(GAME_WIDTH*SCALE, GAME_HEIGHT*SCALE), "Untitled LD35 Game", sf::Style::Titlebar | sf::Style::Close, settings);
	this->window.setVerticalSyncEnabled(true);
	this->window.setKeyRepeatEnabled(false);
	this->window.setView(view);

	//- Handle RNG
	srand(time(NULL));
}

void Game::handle_events(sf::Event ev)
{
	while(window.pollEvent(ev))
	{
		//- Handle state events first, then general states.
		state_stack.back()->handle_events(this, ev);
		switch(ev.type)
		{
			case sf::Event::Closed:
			{
				// window.close();
				quit();
			}break;
			default:
			break;
		}
	}
}

void Game::update(sf::Time dt)
{
	//- Update current state
	state_stack.back()->update(this, dt);
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);
	state_stack.back()->render(this);
	// window.draw(cursor);
	window.display();
}

void Game::change_state(State* state)
{
	//- Cleanup current state
	if(!state_stack.empty()){
		state_stack.back()->cleanup();
		state_stack.pop_back();
	}

	//- Store new state
	state_stack.push_back(state);
	state_stack.back()->init(this);
}

void Game::push_state(State* state)
{
	//- Pause current state
	if(!state_stack.empty()){
		state_stack.back()->pause();
	}

	//- Store new state
	state_stack.push_back(state);
	state_stack.back()->init(this);
}

void Game::pop_state()
{
	//- Cleanup current state
	if(!state_stack.empty()){
		state_stack.back()->cleanup();
		state_stack.pop_back();
	}

	//- Resume previous state
	if(!state_stack.empty()){
		state_stack.back()->resume();
	}
}

void Game::run()
{
	init();
	push_state(GameState::instance());

	while(is_running)
	{
		sf::Event event;
		handle_events(event);
		update(clock.restart());
		render(window);
	}
}

void Game::quit()
{
	this->is_running = false;
	this->window.close();
}
