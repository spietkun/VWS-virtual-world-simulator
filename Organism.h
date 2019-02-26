#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>
#include "CONSTinfoDrawing.h"

class World; //

class Organism
{
protected:
	int strength;
	int initiative;
	bool if_moved; //holds information if an organism moved in current round;
	position_t pos;
	World* current_world;
	char gender;
	int age;
	int ID_number; // start from nr 0
	//default variables
	const char symbol;
	const int maturity_age;
	const std::string species_name;
	const int propagation_chance;
	const int death_age;

	//METHODS //////////////
	void check_free_fields(int* directions, int &amount_of_possible_directions, int range);
	virtual void check_possible_directions(int* directions, int &amount_of_possible_directions, int step_size); //check possible directions that don't lead to the outside of the board // virtual because e.g fox may have other conditions to move																					
	virtual void create_a_descendant(position_t new_pos) = 0;
	int draw_direction(int* directions, int amount_of_poss_dir); // draw one of possible directions
	position_t return_position(int direction, int step_size); // return future position 
	int random_next_field();
	virtual int collision_course(Organism* attacker);
	std::string return_organism_info_(); // use it only in derived classess

public:
	Organism(position_t _pos, World* _current_world, int _strength, int _initiative, char _symbol, int _maturity_age, 
		std::string _species_name, int _propagation_chance, int _death_age);
	virtual ~Organism();
	virtual void draw() = 0;
	void grow_older();
	void annihilate();
	char get_symbol();
	int get_maturity_age();
	void set_position(position_t new_pos);
	void set_if_moved(bool value);
	bool get_if_moved();
	position_t get_position();
	int get_strength();
	void set_strength(int _strength);
	int get_initiative();
	int get_gender();
	void set_gender(int _gender);
	std::string get_species_name();
	int get_propagation_chance();
	int get_death_age();
	int get_age();
	void set_age(int _age);
	int get_ID_number();
	void set_ID_number(int _ID_number);
	virtual void action() = 0;
	virtual void collision(Organism* defender) = 0;
	bool is_organism_mature();
	void increase_strength(int power);
	int multiplication();
	virtual int get_smell_skill(); // check if an organism has such a good smell, that can avoid stronger animals
	
};
#endif

