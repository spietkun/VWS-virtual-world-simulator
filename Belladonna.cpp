#include "Belladonna.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoMoving.h"
#include "Animal.h"

#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

Belladonna::Belladonna(position_t _pos, World* _current_world, int _strength, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age)
	: Plant(_pos, _current_world, _strength, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age)
{
	/*std::string born_communique = "A plant was created: " + return_organism_info_();
	current_world->write_to_raport(born_communique);*/
}

void Belladonna::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BELLADONNA_COLOUR);
	cout << symbol;
	SetConsoleTextAttribute(hConsole, GENERAL_COLOUR);
}

void Belladonna::create_a_descendant(position_t new_pos)
{
	current_world->get_organisms()[new_pos.y][new_pos.x] = new Belladonna(new_pos, current_world);
}

/*int Belladonna::collision_course(Organism* attacker)
{
	Animal* attacker_casted = dynamic_cast<Animal*>(attacker);
	if (attacker_casted)
	{
		attacker_casted->change_position(pos);
		attacker_casted->annihilate();
	}
	//cout << "Belladona was eaten." << endl;
	return INDIVIDUAL;
}*/

Belladonna::~Belladonna()
{
}
