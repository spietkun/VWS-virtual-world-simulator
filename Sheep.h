#ifndef SHEEP_H
#define SHEEP_H
#include "Animal.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Sheep : // step_size and chance_of_moving are general
	public Animal
{
public:
	Sheep(position_t _pos, World* _current_world, int _strength = SHEEP_BASIC_STR, int _initiative = SHEEP_BASIC_INIT, char _symbol = SHEEP_SYMBOL,
		int _maturity_age = SHEEP_MATURE_AGE, std::string _species_name = SHEEP_NAME, int _propagation_chance = SHEEP_PROPAGATION_CHANCE,
		int _death_age = SHEEP_DEATH_AGE);
	void create_a_descendant(position_t new_pos) override;
	void draw() override;
	~Sheep();
	// sheep's action is a standard animal's action
};
#endif