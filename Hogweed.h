#ifndef HOGWEED_H
#define HOGWEED_H
#include "Plant.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Hogweed :
	public Plant
{
public:
	Hogweed(position_t _pos, World* _current_world, int _strength = HOGWEED_BASIC_STR, char _symbol = HOGWEED_SYMBOL,
		int _maturity_age = HOGWEED_MATURE_AGE, std::string _species_name = HOGWEED_NAME, int _propagation_chance = HOGWEED_PROPAGATION_CHANCE,
		int _death_age = HOGWEED_DEATH_AGE);
	void draw() override;
	void create_a_descendant(position_t new_pos) override;
	//int collision_course(Organism* attacker) override;
	void action() override;
	void kill_surrounding_animals(int direction);
	~Hogweed();
};
#endif