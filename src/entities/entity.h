#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Vector2f pos;
	int w, h;
	sf::FloatRect bbox;
	sf::Texture texture;
	sf::Sprite sprite;
public:
    bool removed = false;
    enum Direction{UP,DOWN,LEFT,RIGHT};
    Direction dir;

    virtual void init(sf::Vector2f pos, int w, int h) = 0;
	virtual void render(sf::RenderWindow& win) = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void handle_events(sf::Event& event) = 0;

    bool intersects(Entity& e){
        return this->bbox.intersects(e.get_bbox());
    }

	sf::Vector2f get_pos(){ return this->pos; }
    void set_x(float xx){ this->pos.x = xx; }
    void set_y(float yy){ this->pos.y = yy; }
	sf::Texture& get_texture() { return this->texture; }
    void remove(){ this->removed = true; }
    float get_rotation(){ return this->sprite.getRotation(); }
    sf::Sprite& get_model() { return this->sprite; }
    sf::FloatRect& get_bbox() { return this->bbox; }
    int get_w(){ return this->w; }
    int get_h(){ return this->h; }
};

#endif // ENTITY_H
