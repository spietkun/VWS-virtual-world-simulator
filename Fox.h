#ifndef FOX_H
#define FOX_H
#include "Animal.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Fox : // step_size and chance_of_moving are general
	public Animal
{
public:
	Fox(position_t _pos, World* _current_world, int _strength = FOX_BASIC_STR, int _initiative = FOX_BASIC_INIT, char _symbol = FOX_SYMBOL,
		int _maturity_age = FOX_MATURE_AGE, std::string _species_name = FOX_NAME, int _propagation_chance = FOX_PROPAGATION_CHANCE,
		int _death_age = FOX_DEATH_AGE);
	void create_a_descendant(position_t new_pos) override;
	void draw() override;
	//void action() override;
	//void check_possible_directions(int* directions, int &amount_of_possible_directions, int step_size) override;
	int get_smell_skill() override;
	~Fox();
};
#endif