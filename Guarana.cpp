#include "Guarana.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoMoving.h"
#include "Animal.h"

#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

Guarana::Guarana(position_t _pos, World* _current_world, int _strength, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age, int _power)
	: Plant(_pos, _current_world, _strength, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age), power(_power)
{
	/*std::string born_communique = "A plant was created: " + return_organism_info_();
	current_world->write_to_raport(born_communique);*/
}

void Guarana::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, GUARANA_COLOUR);
	cout << symbol;
	SetConsoleTextAttribute(hConsole, GENERAL_COLOUR);
}

void Guarana::create_a_descendant(position_t new_pos)
{
	current_world->get_organisms()[new_pos.y][new_pos.x] = new Guarana(new_pos, current_world);
}

int Guarana::collision_course(Organism* attacker)
{
	Animal* attacker_casted = dynamic_cast<Animal*>(attacker);
	attacker->increase_strength(power);
	return ATTACKER_WON;
}

Guarana::~Guarana()
{
}
