#include "gameoverstate.h"

GameOverState* GameOverState::_instance;
GameOverState* GameOverState::instance(){
	if(_instance == NULL)
		_instance = new GameOverState();
	return _instance;
}

void GameOverState::init(Game* game)
{
	tx.loadFromFile("res/tiles/ending.png");
	sprite.setTexture(tx);
	sprite.setPosition(sf::Vector2f(0, 0));
}

void GameOverState::cleanup()
{

}

void GameOverState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
		{
			game->quit();
		}
	}
}

void GameOverState::update(Game* game, sf::Time deltaTime)
{

}

void GameOverState::render(Game* game)
{
	game->get_window()->draw(sprite);
}

void GameOverState::pause()
{

}
void GameOverState::resume()
{

}
