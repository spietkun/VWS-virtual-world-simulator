#include "Hogweed.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoMoving.h"
#include "CONSTinfoFiles.h"
#include "Animal.h"

#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

Hogweed::Hogweed(position_t _pos, World* _current_world, int _strength, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age)
	: Plant(_pos, _current_world, _strength, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age)
{
	/*std::string born_communique = "A plant was created: " + return_organism_info_();
	current_world->write_to_raport(born_communique);*/
}

void Hogweed::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, HOGWEED_COLOUR);
	cout << symbol;
	SetConsoleTextAttribute(hConsole, GENERAL_COLOUR);
}

void Hogweed::create_a_descendant(position_t new_pos)
{
	current_world->get_organisms()[new_pos.y][new_pos.x] = new Hogweed(new_pos, current_world);
}

void Hogweed::action()
{
	std::string communique;
	if (age >= death_age)
	{
		communique = "Plant (" + species_name + ")" + "[" + to_string(pos.x) + "," + to_string(pos.y) +
			"]" + " died of old age :(" + '\n';
		(current_world->get_organisms())[pos.y][pos.x]->annihilate();
		current_world->write_to_file(communique, F_ROUND_RAPORT);
	}
	else // if Hogweed is alive
	{
		if (plant_propagation())
		{
			//cout << "Hogweed sie rozmnozyla." << endl;
		}
		//else cout << "Hogweed nie dojrzala" << endl;

		int directions[NUMBER_OF_DIRECTIONS]; // all directions
		directions[0] = FAILURE; //assume, that animal can go nowhere
		directions[1] = FAILURE;
		directions[2] = FAILURE;
		directions[3] = FAILURE;
		int amount_of_poss_dir = 0;
		int drawn_direction;

		check_possible_directions(directions, amount_of_poss_dir, HOGWEED_KILLING_ZONE);
		for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++)
		{
			if (directions[i] != FAILURE)
			{
				kill_surrounding_animals(directions[i]);
			}
		}
	}
}

void Hogweed::kill_surrounding_animals(int direction) // conditions, if directions dont exceed outside the board, must be checked
// before using this function
{
	std::string communique;
	Organism***buf = current_world->get_organisms();
	Animal* animal_casted;
	position_t animal_pos;
	switch (direction)
	{
	case LEFT:
		animal_casted = dynamic_cast<Animal*>(buf[pos.y][pos.x - HOGWEED_KILLING_ZONE]);
		if (animal_casted) // kill only animals
		{
			animal_pos = animal_casted->get_position();
			communique = "A plant (" + species_name + ")" + " A[" + to_string(pos.x) + "," + to_string(pos.y) +
				"]" + " killed animal on the left: " + "(" + animal_casted->get_species_name() + ")" + "-" + 
				 " D[" + to_string(animal_pos.x) + "," + to_string(animal_pos.y) + "]" + "\n";
			current_world->write_to_file(communique, F_ROUND_RAPORT);
			buf[pos.y][pos.x - HOGWEED_KILLING_ZONE]->annihilate();
		}
		break;
	case RIGHT:
		animal_casted = dynamic_cast<Animal*>(buf[pos.y][pos.x + HOGWEED_KILLING_ZONE]);
		if (animal_casted) // kill only animals
		{
			animal_pos = animal_casted->get_position();
			communique = "A plant (" + species_name + ")" + " A[" + to_string(pos.x) + "," + to_string(pos.y) +
				"]" + " killed animal on the right: " + "(" + animal_casted->get_species_name() + ")" + "-" 
				 " D[" + to_string(animal_pos.x) + "," + to_string(animal_pos.y) + "]" + "\n";
			current_world->write_to_file(communique, F_ROUND_RAPORT);
			buf[pos.y][pos.x + HOGWEED_KILLING_ZONE]->annihilate();
		}
		break;
	case UP:
		animal_casted = dynamic_cast<Animal*>(buf[pos.y - HOGWEED_KILLING_ZONE][pos.x]);
		if (animal_casted) // kill only animals
		{
			animal_pos = animal_casted->get_position();
			communique = "A plant (" + species_name + ")" + " A[" + to_string(pos.x) + "," + to_string(pos.y) +
				"]" + " killed animal on the top: " + "(" + animal_casted->get_species_name() + ")" + "-" +
				+ " D[" + to_string(animal_pos.x) + "," + to_string(animal_pos.y) + "]" + "\n";
			current_world->write_to_file(communique, F_ROUND_RAPORT);
			buf[pos.y - HOGWEED_KILLING_ZONE][pos.x]->annihilate();
		}
		break;
	case DOWN:
		animal_casted = dynamic_cast<Animal*>(buf[pos.y + HOGWEED_KILLING_ZONE][pos.x]);
		if (animal_casted) // kill only animals
		{
			animal_pos = animal_casted->get_position();
			communique = "A plant (" + species_name + ")" + " A[" + to_string(pos.x) + "," + to_string(pos.y) +
				"]" + " killed animal on the bottom: " + "(" + animal_casted->get_species_name() + ")" + "-" +
				" D[" + to_string(animal_pos.x) + "," + to_string(animal_pos.y) + "]" + "\n";
			current_world->write_to_file(communique, F_ROUND_RAPORT);
			buf[pos.y + HOGWEED_KILLING_ZONE][pos.x]->annihilate();
		}
		break;
	}
}

/*int Hogweed::collision_course(Organism* attacker)
{
	Animal* attacker_casted = dynamic_cast<Animal*>(attacker);
	if (attacker_casted)
	{
		attacker_casted->change_position(pos);
		attacker_casted->annihilate();
	}
	//cout << "Hogweed was eaten." << endl;
	return INDIVIDUAL;
}*/

Hogweed::~Hogweed()
{
}
