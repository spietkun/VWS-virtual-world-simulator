#include "Sowthistle.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoFiles.h"

#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

Sowthistle::Sowthistle(position_t _pos, World* _current_world, int _strength, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age)
	: Plant(_pos, _current_world, _strength, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age)
{
	/*std::string born_communique = "A plant was created: " + return_organism_info_();
	current_world->write_to_raport(born_communique);*/
}

void Sowthistle::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, SOWTHISTLE_COLOUR);
	cout << symbol;
	SetConsoleTextAttribute(hConsole, GENERAL_COLOUR);
}

void Sowthistle::create_a_descendant(position_t new_pos)
{
	current_world->get_organisms()[new_pos.y][new_pos.x] = new Sowthistle(new_pos, current_world);
}

/*void Sowthistle::action()
{
	bool if_mature = is_organism_mature();
	std::string communique;
	if (age >= death_age)
	{
		communique = "Plant (" + species_name + ")" + "[" + to_string(pos.x) + "," + to_string(pos.y) +
			"]" + " died of old age :(" + '\n';
		(current_world->get_organisms())[pos.y][pos.x]->annihilate();
		current_world->write_to_file(communique, F_ROUND_RAPORT);
	}
	else if (if_mature)
	{
		for (int i = 0; i < SOWTHISTLE_PROPAGATION_AMOUNT; i++)
		{
			multiplication();
			//cout << "Sowthistle rozmnozyl sie" << endl;
		}
	}
	//else cout << "Sowthistle nie dojrzal" << endl;
}*/

int Sowthistle::get_general_propagation_am()
{
	return SOWTHISTLE_PROPAGATION_AMOUNT;
}

Sowthistle::~Sowthistle()
{
}
