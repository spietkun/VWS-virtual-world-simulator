#include "Antelope.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoMoving.h"
#include "CONSTinfoFiles.h"

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

Antelope::Antelope(position_t _pos, World* _current_world, int _strength, int _initiative, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age, int _step_size)
	: Animal(_pos, _current_world, _strength, _initiative, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age, _step_size)
{
}

void Antelope::create_a_descendant(position_t new_pos)
{
	current_world->get_organisms()[new_pos.y][new_pos.x] = new Antelope(new_pos, current_world);
}

void Antelope::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ANTELOPE_COLOUR);
	cout << symbol;
	SetConsoleTextAttribute(hConsole, GENERAL_COLOUR);
}

int Antelope::collision_course(Organism* attacker)
{
	Animal* attacker_casted = dynamic_cast<Animal*>(attacker);
	std::string communique;
	int amount_of_poss_dir;

	bool ant_escape_chance = rand() % 100 < ANTELOPE_ESCAPE_CHANCE;
	int attacker_str = attacker->get_strength();
	int result;
	if (ant_escape_chance)
	{
		position_t new_pos;
		int directions[NUMBER_OF_DIRECTIONS]; // all directions
		directions[0] = FAILURE; //assume, that every neighbouring field is taken
		directions[1] = FAILURE;
		directions[2] = FAILURE;
		directions[3] = FAILURE;
		amount_of_poss_dir = 0;
		int drawn_direction;
		int step = GENERAL_STEP_SIZE;

		check_free_fields(directions, amount_of_poss_dir, step_size);
		if (amount_of_poss_dir) // if there is a possibility, escape making a big jump (2 fields)
		{
			step = step_size;
		}
		else // if not, try to escape with a smaller jump (1 field)
		{
			check_free_fields(directions, amount_of_poss_dir, GENERAL_STEP_SIZE);
			step = GENERAL_STEP_SIZE;
		}

		if (amount_of_poss_dir) 
		{
			drawn_direction = draw_direction(directions, amount_of_poss_dir);
			new_pos = return_position(drawn_direction, step);
			if (current_world->get_organisms()[new_pos.y][new_pos.x] == nullptr)
			{
				position_t old_ant_pos = pos;
				change_position(new_pos);
				if (attacker_casted)
				{
					attacker_casted->change_position(old_ant_pos); // attacker takes an old place of the antelope
				}
			}
			result = ESCAPE;
			communique = "Antelope managed to escape making a jump of size: " + to_string(step) + "!\n";
		} // if there are no possible ways of moving, then don't escape 
		else //cout << "There was no place for escaping with moving range = 2 :(" << endl;
		{
			communique = "There was no room for antelope to escape :( \n";
			result = Organism::collision_course(attacker); // just compare strength
		}
	}
	else 
	{
		result = Organism::collision_course(attacker); // just compare strength
		communique = "Antelope wasn't lucky enough to escape :( \n";
	}
	current_world->write_to_file(communique, F_ROUND_RAPORT);
	return result;
}

Antelope::~Antelope()
{
}
