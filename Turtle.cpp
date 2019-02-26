#include "Turtle.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoMoving.h"
#include "CONSTinfoFiles.h"

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

Turtle::Turtle(position_t _pos, World* _current_world, int _strength, int _initiative, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age, int _step_size, int _chance_of_moving)
	: Animal(_pos, _current_world, _strength, _initiative, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age, _step_size, _chance_of_moving)
{
}

void Turtle::create_a_descendant(position_t new_pos)
{
	current_world->get_organisms()[new_pos.y][new_pos.x] = new Turtle(new_pos, current_world);
}

void Turtle::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, TURTLE_COLOUR);
	cout << symbol;
	SetConsoleTextAttribute(hConsole, GENERAL_COLOUR);
}

int Turtle::collision_course(Organism* attacker)
{
	std::string communique;
	int attacker_str = attacker->get_strength();
	int result;
	Animal* attacker_casted = dynamic_cast<Animal*>(attacker); // attacker is an animal (plants dont initialize attack)

	if (attacker_casted)
	{
		if (attacker_str < TURTLE_REFLECTION_CONDITION)
		{
			communique = get_species_name() + " reflected an attack! \n";
			result = REFLECTION;
		}
		else
		{
			communique = get_species_name() + " couldn't reflect an attack.\n";
			result = Organism::collision_course(attacker); // just compare strength
			/*if (strength > attacker_str) result = DEFENDER_WON;
			else if (strength == attacker_str) result = DRAW;
			else result = ATTACKER_WON;*/
		}
	}
	current_world->write_to_file(communique, F_ROUND_RAPORT);
	return result;
}

Turtle::~Turtle()
{
}
