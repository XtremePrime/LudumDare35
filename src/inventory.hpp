#ifndef INVENTORY_HPP
#define INVENTORY_HPP

class Inventory
{
private:
	int iron = 0;
	int magiberries = 0;
public:
	void add_magiberries(int n){ magiberries+=n; }
	int get_magiberries(){ return this->magiberries; }
	void add_iron(int n){ iron+=n; }
	int get_iron(){ return this->iron; }
};

#endif // INVENTORY_HPP