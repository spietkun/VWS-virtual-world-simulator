#include "Human.h"
#include "CONSTinfoMoving.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoFiles.h"

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

Human::Human(position_t _pos, World* _current_world, int _strength, int _initiative, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age)
	: Animal(_pos, _current_world, _strength, _initiative, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age)
{
}

void Human::create_a_descendant(position_t new_pos)
{
	current_world->get_organisms()[new_pos.y][new_pos.x] = new Human(new_pos, current_world);
}

void Human::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, HUMAN_COLOUR);
	cout << symbol;
	SetConsoleTextAttribute(hConsole, GENERAL_COLOUR);
}

void Human::action()
{
	int step_size = get_step_size();
	int chance_of_moving = get_chance_of_moving();
	bool if_human_moves = (rand() % 100) < chance_of_moving; // chance that human will move
	if (if_human_moves)
	{
		position_t new_pos;
		int directions[NUMBER_OF_DIRECTIONS]; // all directions
		directions[0] = FAILURE; //assume, that animal can go nowhere
		directions[1] = FAILURE;
		directions[2] = FAILURE;
		directions[3] = FAILURE;
		int amount_of_poss_dir = 0;
		int human_direction = current_world->get_human_direction();
		//cout << human_direction << endl;
		bool if_can_move = FAILURE;

		check_possible_directions(directions, amount_of_poss_dir, step_size);
		for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++)
		{
			if (directions[i] == human_direction)
			{
				if_can_move = SUCCESS;
				break;
			}
		}

		//cout << human_direction << endl << "////////////////////" << endl;
		if (if_can_move) // if there are no possible ways of moving, then don't move a human
		{
			new_pos = return_position(human_direction, step_size);
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
		//else cout << "No place for moving!" << endl;
	}
}

int Human::collision_course(Organism* attacker)
{
	int result;
	super_power_t alzur_buf = current_world->get_alzur_power();
	if (alzur_buf.is_power_on == true)
	{
		std::string communique = "Human uses super_power - ALZUR_SHIELD. " + to_string(alzur_buf.duration) + " rounds left!\n";
		current_world->write_to_file(communique, F_ROUND_RAPORT);
		int result;
		Animal* attacker_casted = dynamic_cast<Animal*>(attacker); // attacker is an animal (plants dont initialize attack)

		if (attacker_casted)
		{
			result = INDIVIDUAL;
			position_t new_pos;
			position_t old_att_pos = attacker->get_position();
			int amount_of_poss_dir;
			int directions[NUMBER_OF_DIRECTIONS]; // all directions
			directions[0] = FAILURE; //assume, that every neighbouring field is taken
			directions[1] = FAILURE;
			directions[2] = FAILURE;
			directions[3] = FAILURE;
			amount_of_poss_dir = 0;
			int drawn_direction;
			int step;

			check_free_fields(directions, amount_of_poss_dir, step_size);
			if (amount_of_poss_dir) // if there are no possible ways of moving, then don't move an animal
			{
				drawn_direction = draw_direction(directions, amount_of_poss_dir);
				new_pos = return_position(drawn_direction, step_size);
				if (current_world->get_organisms()[new_pos.y][new_pos.x] == nullptr) // just to make sure
				{
					attacker_casted->change_position(new_pos);
					communique = "ALZUR SHIELD: " + attacker->get_species_name() + " was knocked back to [" + to_string(new_pos.x)
						+ "," + to_string(new_pos.y) + "]!\n";
					current_world->write_to_file(communique, F_ROUND_RAPORT);
				}
			}
			else // animals goes back (stays) to his original place
			{
				communique = "ALZUR SHIELD: " + attacker->get_species_name() + " was knocked back to its original place![" + to_string(old_att_pos.x)
					+ "," + to_string(old_att_pos.y) + "]!\n";
				current_world->write_to_file(communique, F_ROUND_RAPORT);
			}
		}
	}
	else // normal strength comparision
	{
		result = Organism::collision_course(attacker); // just compare strength
	}
	return result;
}

Human::~Human()
{
}
