#ifndef TURTLE_H
#define TURTLE_H
#include "Animal.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Turtle :
	public Animal
{
public:
	Turtle(position_t _pos, World* _current_world, int _strength = TURTLE_BASIC_STR, int _initiative = TURTLE_BASIC_INIT, char _symbol = TURTLE_SYMBOL,
		int _maturity_age = TURTLE_MATURE_AGE, std::string _species_name = TURTLE_NAME, int _propagation_chance = TURTLE_PROPAGATION_CHANCE,
		int _death_age = TURTLE_DEATH_AGE, int _step_size = GENERAL_STEP_SIZE, int _chance_of_moving = TURTLE_CHANCE_OF_MOVING);
	void create_a_descendant(position_t new_pos) override;
	void draw() override;
	//void action() override;
	int collision_course(Organism* attacker) override;
	~Turtle();
};
#endif