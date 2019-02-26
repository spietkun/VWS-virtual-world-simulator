#include "Plant.h"
#include <iostream>
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoMoving.h"
#include "CONSTinfoFiles.h"
#include "Animal.h"

using namespace std;

Plant::Plant(position_t _pos, World* _current_world, int _strength, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age, int _initiative)
	:Organism(_pos, _current_world, _strength, _initiative, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age)
{
	gender = PERFECT;
	std::string born_communique = "A plant was sowed: " + return_organism_info_();
	current_world->write_to_file(born_communique, F_ROUND_RAPORT);
}

void Plant::action()
{
	std::string communique;
	if (age >= death_age)
	{
		communique = "Plant (" + species_name + ")" + "[" + to_string(pos.x) + "," + to_string(pos.y) +
			"]" + " died of old age :(" + '\n';
		(current_world->get_organisms())[pos.y][pos.x]->annihilate();
		current_world->write_to_file(communique, F_ROUND_RAPORT);
	}
	else if (plant_propagation())
	{
		//cout << "Roslina sie rozmnozyla." << endl;
	}
	//else cout << "Roslina nie dojrzala" << endl;
}

bool Plant::plant_propagation()
{
	int number_of_reproduction = get_general_propagation_am();
	bool if_mature = is_organism_mature();
	if (if_mature)
	{
		for (int i = 0; i < number_of_reproduction; i++)
		{
			multiplication();
		}
	}
	return if_mature;
}

int Plant::get_general_propagation_am()
{
	return GENERAL_PROPAGATION_AMOUNT;
}

void Plant::collision(Organism* attacker)
{
	Animal* attacker_casted = dynamic_cast<Animal*>(attacker); // attacker is an animal (plants dont initialize attack)
	position_t att_pos = attacker->get_position();
	std::string communique;

	int fight_result = collision_course(attacker);
	switch (fight_result)
	{
	case DEFENDER_WON:
		if (attacker_casted)
		{
			attacker_casted->annihilate();
			communique = "An animal (" + attacker_casted->get_species_name() + ")" + " - " + "A[" + to_string(pos.x) + "," + to_string(pos.y) +
				"]" + " stepped on the plant: (" + species_name + ")" + " D[" + to_string(att_pos.x) + "," + to_string(att_pos.y) + "]" + " - " + "and ANIMAL DIED becasue of eating it.\n";
			current_world->write_to_file(communique, F_ROUND_RAPORT);
		}
		break;
	case ATTACKER_WON:
		if (attacker_casted)
		{
			//annihilate(); zrobiæ destruktor
			attacker_casted->change_position(pos); // attacker takes place of the defender
			communique = "An animal (" + attacker_casted->get_species_name() + ")" + " - " + "A[" + to_string(pos.x) + "," + to_string(pos.y) +
				"]" + " stepped on the plant: (" + species_name + ") D[" + to_string(att_pos.x) + "," + to_string(att_pos.y) + "]" + " - " + "and ANIMAL is HAPPY becasue of eating it.\n";
			current_world->write_to_file(communique, F_ROUND_RAPORT);
			//cout << "This plant was eaten and an animal is happy now." << endl;
		}
		break;
	case DRAW:
		communique = "An animal (" + attacker_casted->get_species_name() + ")" + " - " + "A[" + to_string(pos.x) + "," + to_string(pos.y) +
			"]" + " stepped on the plant: (" + species_name + ") D[" + to_string(att_pos.x) + "," + to_string(att_pos.y) + "]" + " - " + "and they are both alive becasue of the same strength.\n";
		current_world->write_to_file(communique, F_ROUND_RAPORT);
		break;
	
	}
}


Plant::~Plant()
{
}
