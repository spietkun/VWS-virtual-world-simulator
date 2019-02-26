#ifndef ANIMAL_H
#define ANIMAL_H

#include "Organism.h"
#include "World.h"
class Animal :
	public Organism
{
protected:
	const int step_size;
	const int chance_of_moving;

	//METHODS //////////////////
	void breed_next_to_parent(Organism* attacker); // first call this function with a mother (FEMALE animal) and if there's no place for a descendant call it with a father (MALE animal)
	int get_step_size();
	int get_chance_of_moving();
public:
	Animal (position_t _pos, World* _current_world, int _strength, int _initiative, char _symbol, int _maturity_age,
		std::string _species_name, int _propagation_chance, int _death_age, int _step_size = GENERAL_STEP_SIZE, int _chance_of_moving = GENERAL_CHANCE_OF_MOVING);
	void action() override;
	void collision(Organism* defender) override;
	//void check_free_fields(int* directions, int &amount_of_possible_directions, int range) override; // used for breeding // range - how far from the parent
	void change_position(position_t new_pos); // move an animal based on future position
	virtual ~Animal();
};
#endif