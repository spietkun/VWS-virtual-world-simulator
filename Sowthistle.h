#ifndef SOWTHISTLE_H
#define SOWTHISTLE_H
#include "Plant.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Sowthistle :
	public Plant
{
public:
	Sowthistle(position_t _pos, World* _current_world, int _strength = SOWTHISTLE_BASIC_STR, char _symbol = SOWTHISTLE_SYMBOL,
		int _maturity_age = SOWTHISTLE_MATURE_AGE, std::string _species_name = SOWTHISTLE_NAME, int _propagation_chance = SOWTHISTLE_PROPAGATION_CHANCE,
		int _death_age = SOWTHISTLE_DEATH_AGE);
	void draw() override;
	void create_a_descendant(position_t new_pos) override;
	//void action() override;
	int get_general_propagation_am() override;
	~Sowthistle();
};
#endif