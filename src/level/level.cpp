#include "level.h"

void Level::init(int w, int h)
{
	this->w = w;
	this->h = h;

	//- setup txmgr
	txmgr.load_texture("GRASS", "grass.png");
	txmgr.load_texture("AIR", "road.png");
	txmgr.load_texture("IRON", "vine_3.png");
	txmgr.load_texture("MAGIBERRIES", "magiberries.png");	

	//- Build level
	construct_world();
}

void Level::update(sf::Time deltaTime)
{
	for(Village* v : villages)
		v->update(deltaTime);
}

void Level::render(sf::RenderWindow& window, sf::Vector2f player_pos)
{

	// std::cout << camera_pos.x << "," << camera_pos.y << " | " << player_pos.x << "," << player_pos.y << "\n";

	for(Tile* t : tiles)
		t->render(window);
	for(Village* v : villages)
		v->render(window);


	// view.zoom();
}

void Level::construct_world()
{
	//- Build grass around world
	for(int i = 0; i < w*h; ++i){
		tiles.push_back(new Tile(TileType::GRASS, txmgr.get_ref("GRASS"), i%w, i/h));
	}

	//- Custom tiles
	// tiles[5] = new ResourceTile(TileType::IRON, ResourceType::IRON, txmgr.get_ref("IRON"), 5, 0);
	// tiles[6] = new ResourceTile(TileType::IRON, ResourceType::IRON, txmgr.get_ref("IRON"), 6, 0);

	tiles[27*1+1 + 2-1] = new ResourceTile(TileType::MAGIBERRIES, ResourceType::MAGIBERRIES, txmgr.get_ref("MAGIBERRIES"), 2, 1);
	tiles[27*1+1 + 3-1] = new ResourceTile(TileType::MAGIBERRIES, ResourceType::MAGIBERRIES, txmgr.get_ref("MAGIBERRIES"), 3, 1);
	tiles[27*2+1 + 2-1] = new ResourceTile(TileType::MAGIBERRIES, ResourceType::MAGIBERRIES, txmgr.get_ref("MAGIBERRIES"), 2, 2);
	tiles[27*2+1 + 3-1] = new ResourceTile(TileType::MAGIBERRIES, ResourceType::MAGIBERRIES, txmgr.get_ref("MAGIBERRIES"), 3, 2);

	tiles[27*1+1 + 24-1] = new ResourceTile(TileType::IRON, ResourceType::IRON, txmgr.get_ref("IRON"), 24, 1);
	tiles[27*1+1 + 25-1] = new ResourceTile(TileType::IRON, ResourceType::IRON, txmgr.get_ref("IRON"), 25, 1);
	tiles[27*2+1 + 24-1] = new ResourceTile(TileType::IRON, ResourceType::IRON, txmgr.get_ref("IRON"), 24, 2);
	tiles[27*2+1 + 25-1] = new ResourceTile(TileType::IRON, ResourceType::IRON, txmgr.get_ref("IRON"), 25, 2);


	//- Villages
	villages.push_back(new Village("Eggplant Town", "house.png", 12, 8));
}

Tile& Level::get_tile(int x, int y, int w)
{
	int xa = floor(x/32);
	int ya = floor(y/32);
	std::cout << "TEST: " << xa << "," << ya << " | " << xa*w+ya << "\n";
	return *tiles[ya * w + xa];
}

