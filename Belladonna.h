#ifndef BELLADONNA_H
#define BELLADONNA_H
#include "Plant.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Belladonna :
	public Plant
{
public:
	Belladonna(position_t _pos, World* _current_world, int _strength = BELLADONNA_BASIC_STR, char _symbol = BELLADONNA_SYMBOL,
		int _maturity_age = BELLADONNA_MATURE_AGE, std::string _species_name = BELLADONNA_NAME, int _propagation_chance = BELLADONNA_PROPAGATION_CHANCE,
		int _death_age = BELLADONNA_DEATH_AGE);
	void draw() override;
	void create_a_descendant(position_t new_pos) override;
	//int collision_course(Organism* attacker) override;
	~Belladonna();
};
#endif