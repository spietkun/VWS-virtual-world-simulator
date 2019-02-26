#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Wolf : // step_size and chance_of_moving are general
	public Animal
{
public:
	Wolf(position_t _pos, World* _current_world, int _strength = WOLF_BASIC_STR, int _initiative = WOLF_BASIC_INIT, char _symbol = WOLF_SYMBOL,
		int _maturity_age = WOLF_MATURE_AGE, std::string _species_name = WOLF_NAME, int _propagation_chance = WOLF_PROPAGATION_CHANCE,
		int _death_age = WOLF_DEATH_AGE);
	void draw() override;
	void create_a_descendant(position_t new_pos) override;
	~Wolf();
};
#endif