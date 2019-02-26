#ifndef ANTELOPE_H
#define ANTELOPE_H
#include "Animal.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Antelope :
	public Animal
{
public:
	Antelope(position_t _pos, World* _current_world, int _strength = ANTELOPE_BASIC_STR, int _initiative = ANTELOPE_BASIC_INIT, char _symbol = ANTELOPE_SYMBOL, 
		int _maturity_age = ANTELOPE_MATURE_AGE, std::string _species_name = ANTELOPE_NAME, int _propagation_chance = ANTEOPE_PROPAGATION_CHANCE, 
		int _death_age = ANTELOPE_DEATH_AGE, int _step_size = ANTELOPE_STEP_SIZE);
	void create_a_descendant(position_t new_pos) override;
	void draw() override;
	int collision_course(Organism* attacker) override;
	~Antelope();
};
#endif