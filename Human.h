#ifndef HUMAN_H
#define HUMAN_H
#include "Animal.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Human :
	public Animal
{
public:
	Human(position_t _pos, World* _current_world, int _strength = HUMAN_BASIC_STR, int _initiative = HUMAN_BASIC_INIT, char _symbol = HUMAN_SYMBOL,
		int _maturity_age = HUMAN_MATURE_AGE, std::string _species_name = HUMAN_NAME, int _propagation_chance = HUMAN_PROPAGATION_CHANCE,
		int _death_age = HUMAN_DEATH_AGE);
	void draw() override;
	void create_a_descendant(position_t new_pos) override;
	void action() override;
	int collision_course(Organism* attacker) override;
	~Human();
};
#endif