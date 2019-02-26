#ifndef GRASS_H
#define GRASS_H
#include "Plant.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Grass :
	public Plant
{
public:
	Grass(position_t _pos, World* _current_world, int _strength = GRASS_BASIC_STR, char _symbol = GRASS_SYMBOL,
		int _maturity_age = GRASS_MATURE_AGE, std::string _species_name = GRASS_NAME, int _propagation_chance = GRASS_PROPAGATION_CHANCE,
		int _death_age = GRASS_DEATH_AGE);
	void draw() override;
	void create_a_descendant(position_t new_pos) override;
	~Grass();
};
#endif