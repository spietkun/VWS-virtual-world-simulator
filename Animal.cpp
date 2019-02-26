#include "Animal.h"
#include <iostream>
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoMoving.h"
#include "CONSTinfoFiles.h"
using namespace std;

Animal::Animal(position_t _pos, World* _current_world, int _strength, int _initiative, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age, int _step_size, int _chance_of_moving)
	:Organism(_pos, _current_world, _strength, _initiative, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age), 
	step_size(_step_size), chance_of_moving(_chance_of_moving)
{
	int draw_gender = rand() % 2; // 2 genders
	switch (draw_gender)
	{
	case MALE:
		gender = MALE;
		break;
	case FEMALE:
		gender = FEMALE;
		break;
	}
	std::string born_communique = "An animal was born: " + return_organism_info_();
	current_world->write_to_file(born_communique, F_ROUND_RAPORT);
	
}

int Animal::get_step_size()
{
	return step_size;
}

int Animal::get_chance_of_moving()
{
	return chance_of_moving;
}

void Animal::change_position(position_t new_pos)
{
	int height = current_world->get_height();
	int width = current_world->get_width();

	for (int i = 0; i < height*width; i++)
	{
		if (current_world->get_sorted_organisms()[i] == current_world->get_organisms()[new_pos.y][new_pos.x]) // set sorted pointer to nullptr - this new field will be taken so it musn't call action in sorted board
		{
			current_world->get_sorted_organisms()[i] = nullptr;
			break;
		}
	}
	(current_world->get_organisms())[new_pos.y][new_pos.x] = (current_world->get_organisms())[pos.y][pos.x]; //change pointers
	(current_world->get_organisms())[pos.y][pos.x] = nullptr;

	set_position(new_pos); // change position (move an animal)
}
void Animal::action()
{
	bool if_animal_moves = (rand() % 100) < chance_of_moving; // chance that animal will move
	std::string communique;
	if (age >= death_age)
	{
		communique = "Animal (" + species_name + ")" + "[" + to_string(pos.x) + "," + to_string(pos.y) +
			"]" + " died of old age :(" + '\n';
		(current_world->get_organisms())[pos.y][pos.x]->annihilate();
		current_world->write_to_file(communique, F_ROUND_RAPORT);
	}

	else if (if_animal_moves)
	{
		position_t new_pos;
		int directions[NUMBER_OF_DIRECTIONS]; // all directions
		directions[0] = FAILURE; //assume, that animal can go nowhere
		directions[1] = FAILURE;
		directions[2] = FAILURE;
		directions[3] = FAILURE;
		int amount_of_poss_dir = 0;
		int drawn_direction;

		check_possible_directions(directions, amount_of_poss_dir, step_size);
		if (amount_of_poss_dir) // if there are no possible ways of moving, then don't move an animal
		{
			drawn_direction = draw_direction(directions, amount_of_poss_dir);
			new_pos = return_position(drawn_direction, step_size);
			if (current_world->get_organisms()[new_pos.y][new_pos.x] == nullptr)
			{
				change_position(new_pos);
			}
			else
			{
				(current_world->get_organisms()[new_pos.y][new_pos.x])->collision(this); // defender calls collision() 
				//and attacker information (this) is sent
			}
		}
		//else //cout << "No place for moving!" << endl;
	}
	else
	{
		communique = "Animal (" + species_name + ")" + "[" + to_string(pos.x) + "," + to_string(pos.y) +
			"]" + " doesn't want to move" + '\n';
		current_world->write_to_file(communique, F_ROUND_RAPORT);
	}
}

void Animal::collision(Organism* attacker)
{
	position_t att_pos = attacker->get_position();
	std::string communique;
	if (get_symbol() == attacker->get_symbol() && (get_gender()!= attacker->get_gender())) // BREED when animals are of the same
		//type and of other genders
	{
		bool is_defender_mature = is_organism_mature();
		bool is_attacker_mature = attacker->is_organism_mature();
		if (is_defender_mature && is_attacker_mature)
		{
			communique = "Animals of the same species (" + species_name + ")" + " - " + "D[" + to_string(pos.x) + "," + to_string(pos.y) +
				"]" + " A[" + to_string(att_pos.x) + "," + to_string(att_pos.y) + "]" + " - " + "met and try to BREED.\n";
			current_world->write_to_file(communique, F_ROUND_RAPORT);

			breed_next_to_parent(attacker); // place a new animal next to mother or if there's no place next to its father
		}
		else
		{
			communique = "Animals of the same species (" + species_name + ")" + " - " + "D[" + to_string(pos.x) + "," + to_string(pos.y) +
				"]" + " A[" + to_string(att_pos.x) + "," + to_string(att_pos.y) + "]" + " - " + "met but at least one of them is not mature.\n";
			current_world->write_to_file(communique, F_ROUND_RAPORT);
		}

	}
	else if (get_symbol() == attacker->get_symbol()) // DO NOTHING - two animals of the same sex met
	{
		communique = "Animals of the same species (" + species_name + ")" + " - " +  "D[" + to_string(pos.x) + "," + to_string(pos.y) +
			"]" + " A[" + to_string(att_pos.x) + "," + to_string(att_pos.y) + "]" + " - " + "met but they are of the same SEX.\n";
		current_world->write_to_file(communique, F_ROUND_RAPORT);
	}
	else // FIGHT - two animals of different species met
	{
		communique = "Animals of different species: " + species_name + " D[" + to_string(pos.x) + "," + to_string(pos.y) +
			"]" + " str=" + to_string(get_strength()) + " and " + attacker->get_species_name() + " A[" + to_string(att_pos.x) + "," 
			+ to_string(att_pos.y) + "]" + " str=" + to_string(attacker->get_strength())  + " - " + "met and they started to FIGHT!\n";
		current_world->write_to_file(communique, F_ROUND_RAPORT);

		Animal* attacker_casted = dynamic_cast<Animal*>(attacker); // attacker is an animal (plants dont initialize attack)

		int fight_result = collision_course(attacker);
		switch (fight_result)
		{
		case DEFENDER_WON:
			if (attacker_casted)
			{
				attacker_casted->annihilate();
				communique = "The winner is: defender - " + species_name + "!\n";
				current_world->write_to_file(communique, F_ROUND_RAPORT);
			}
			break;
		case DRAW: // The attacking animal wins
				   communique = "DRAW! The same strength! But the attacking animal has an advantage\n";
				   current_world->write_to_file(communique, F_ROUND_RAPORT);
		//do the next case
		case ATTACKER_WON:
			if (attacker_casted)
			{
				annihilate();
				attacker_casted->change_position(pos); // attacker takes place of the defender
				communique = "The winner is: attacker - " + attacker->get_species_name() + "!\n";
				current_world->write_to_file(communique, F_ROUND_RAPORT);
			}
			break;
		}
	}
}

void Animal::breed_next_to_parent(Organism* attacker)
{
	std::string communique;
	bool if_attacker_is_father = false;
	int breeding_result;
	// first, look for a place for a small animal next to its mother //
	if (get_gender() == FEMALE)
	{
		breeding_result = multiplication(); // defender is a mother
		if_attacker_is_father = true;
	}
	else
	{
		breeding_result = attacker->multiplication(); // attacker is a mother
		if_attacker_is_father = false;
	}

	if (breeding_result == NO_PLACE_FOR_A_DESCENDANT) // if there was no place next to small animal's mother, place it next to its father
	{
		if (if_attacker_is_father) breeding_result = attacker->multiplication();
		else breeding_result = multiplication();
	}
	
	//COMMUNIQUES
	if (breeding_result == NO_PLACE_FOR_A_DESCENDANT)
	{
		communique = "Multiplication attemp of (" + get_species_name() + "s) wasn't succesful - no place for a descendant. \n";
		current_world->write_to_file(communique, F_ROUND_RAPORT);
	}
	else if (breeding_result == NOT_ENOUGH_LUCK_FOR_BREEDING)
	{
		communique = "Multiplication attemp of (" + get_species_name() + "s) wasn't succesful - maybe next time. \n";
		current_world->write_to_file(communique, F_ROUND_RAPORT);
	}
}

Animal::~Animal()
{
}
