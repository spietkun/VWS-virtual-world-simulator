#include "Organism.h"
#include "World.h"

#include "CONSTinfoOrganisms.h"
#include "CONSTinfoDrawing.h"
#include "CONSTinfoMoving.h"
#include "CONSTinfoFiles.h"
#include "Animal.h"
#include <stdio.h>
#include <iostream>
using namespace std;

Organism::Organism(position_t _pos, World* _current_world, int _strength, int _initiative, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age)
	:ID_number(current_world->get_number_of_organisms()), symbol(_symbol), maturity_age(_maturity_age), species_name(_species_name),
	propagation_chance(_propagation_chance), death_age(_death_age)
{
	strength = _strength;
	initiative = _initiative;
	pos = _pos;
	current_world = _current_world;
	age = 0; 
	current_world->increase_number_of_organisms();
}

char Organism::get_symbol()
{
	return symbol;
}

int Organism::get_maturity_age()
{
	return maturity_age;
}

std::string Organism::get_species_name()
{
	return species_name;
}

int Organism::get_propagation_chance()
{
	return propagation_chance;
}

int Organism::get_death_age()
{
	return death_age;
}

int Organism::random_next_field()
{
	int buf = rand() % NUMBER_OF_DIRECTIONS;
	return buf;
}

void Organism::set_position(position_t new_pos)
{
	pos = new_pos;
}

position_t Organism::get_position()
{
	return pos;
}

bool Organism::get_if_moved()
{
	return if_moved;
}

void Organism::set_if_moved(bool value)
{
	if_moved = value;
}

int Organism::get_strength()
{
	return strength;
}

void Organism::set_strength(int _strength)
{
	strength = _strength;
}

int Organism::get_gender()
{
	return gender;
}

void Organism::set_gender(int _gender)
{
	gender = _gender;
}

int Organism::get_smell_skill()
{
	return NORMAL_SMELL_SKILL;
}

void Organism::check_free_fields(int* directions, int &amount_of_possible_directions, int range)
{
	Organism***buf = current_world->get_organisms();
	if ((pos.x - range) >= 0 && buf[pos.y][pos.x - range] == nullptr)
	{
		directions[0] = LEFT;  // e.g. there's a free place on the left
		amount_of_possible_directions++;
	}
	if ((pos.x + range) < current_world->get_width() && buf[pos.y][pos.x + range] == nullptr)
	{
		directions[1] = RIGHT;
		amount_of_possible_directions++;
	}
	if ((pos.y - range) >= 0 && buf[pos.y - range][pos.x] == nullptr)
	{
		directions[2] = UP;
		amount_of_possible_directions++;
	}
	if ((pos.y + range) < current_world->get_height() && buf[pos.y + range][pos.x] == nullptr)
	{
		directions[3] = DOWN;
		amount_of_possible_directions++;
	}
}

int Organism::collision_course(Organism* attacker)
{
	int attacker_str = attacker->get_strength();
	int result;

	if (strength > attacker_str) result = DEFENDER_WON;
	else if (strength == attacker_str) result = DRAW;
	else result = ATTACKER_WON;

	return result;
}

void Organism::annihilate() 
{
	int height = current_world->get_height();
	int width = current_world->get_width();

	for (int i = 0; i < height*width; i++)
	{
		if (current_world->get_sorted_organisms()[i] == current_world->get_organisms()[pos.y][pos.x]) // set sorted pointer to nullptr
		{
			current_world->get_sorted_organisms()[i] = nullptr;
			break;
		}
	}
	(current_world->get_organisms())[pos.y][pos.x] = nullptr;
	delete (current_world->get_organisms())[pos.y][pos.x];
}

void Organism::grow_older()
{
	age++;
}

bool Organism::is_organism_mature()
{
	bool result = false;
	int mature = get_maturity_age();
	if (age >= mature) // ktory mature_age?
	{
		result = true;
	}
	return result;
}

void Organism::check_possible_directions(int* directions, int &amount_of_possible_directions, int step_size)
{
	int smell_skill = get_smell_skill();
	Organism*** buf = current_world->get_organisms();
	if ((pos.x - step_size) >= 0)
	{
		if (smell_skill == AVOID_STR_SMELL_SKILL)
		{
			if (buf[pos.y][pos.x - step_size] == nullptr || (buf != nullptr && buf[pos.y][pos.x - step_size]->get_strength() <= strength)) // if there's an animal next to the moving organism
																																		   //it won't go there if an organism has more strength
			{
				directions[0] = LEFT;  // going left, an animal is still in the "board"; let it go
				amount_of_possible_directions++;
			}
		}
		else
		{
			directions[0] = LEFT;
			amount_of_possible_directions++;
		}
	}
	if ((pos.x + step_size) < current_world->get_width())
	{
		if (smell_skill == AVOID_STR_SMELL_SKILL)
		{
			if (buf[pos.y][pos.x + step_size] == nullptr || (buf != nullptr && buf[pos.y][pos.x + step_size]->get_strength() <= strength))
			{
				directions[1] = RIGHT;
				amount_of_possible_directions++;
			}
		}
		else
		{
			directions[1] = RIGHT;
			amount_of_possible_directions++;
		}
	}
	if ((pos.y - step_size) >= 0)
	{
		if (smell_skill == AVOID_STR_SMELL_SKILL)
		{
			if (buf[pos.y - step_size][pos.x] == nullptr || (buf != nullptr && buf[pos.y - step_size][pos.x]->get_strength() <= strength))
			{
				directions[2] = UP;
				amount_of_possible_directions++;
			}
		}
		else
		{
			directions[2] = UP;
			amount_of_possible_directions++;
		}
	}
	if ((pos.y + step_size) < current_world->get_height())
	{
		if (smell_skill == AVOID_STR_SMELL_SKILL)
		{
			if (buf[pos.y + step_size][pos.x] == nullptr || (buf != nullptr && buf[pos.y + step_size][pos.x]->get_strength() <= strength))
			{
				directions[3] = DOWN;
				amount_of_possible_directions++;
			}
		}
		else
		{
			directions[3] = DOWN;
			amount_of_possible_directions++;
		}
	}
}

int Organism::draw_direction(int* directions, int amount_of_poss_dir)
{
	int* possible_directions;
	possible_directions = new int[amount_of_poss_dir];
	int counter = 0;
	for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++)
	{
		if (directions[i] != FAILURE)
		{
			possible_directions[counter] = directions[i];
			//cout << "possible directions: " << possible_directions[counter] << endl;
			counter++;
		}
	}

	int random_index = rand() % amount_of_poss_dir;
	//cout << "random index: " << random_index << endl;
	//cout << "ilosc kierunkow: " << amount_of_poss_dir << endl;
	int drawn_direction = possible_directions[random_index];
	//cout << "drawn direction: " << drawn_direction << endl;
	delete[] possible_directions;
	return drawn_direction;
}

position_t Organism::return_position(int direction, int step_size) // based on direction
{
	position_t new_pos;
	switch (direction)
	{
	case LEFT:
		//cout << "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL" << endl;
		new_pos.x = pos.x - step_size;
		new_pos.y = pos.y; // stays the same
		break;
	case RIGHT:
		//cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR" << endl;
		new_pos.x = pos.x + step_size;
		new_pos.y = pos.y;
		break;
	case UP:
		//	cout << "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu" << endl;
		new_pos.y = pos.y - step_size;
		new_pos.x = pos.x;
		break;
	case DOWN:
		//cout << "DDDDDDDDDDDDDDDDDDDDDDDDDD" << endl;
		new_pos.y = pos.y + step_size;
		new_pos.x = pos.x;
		break;
	default:
		new_pos.y = pos.y;
		new_pos.x = pos.x;
	}
	//cout << "strength: " << strength << endl;
	//cout << "OLD_X: " << pos.x << " -> " << new_x << endl;
	//cout << "OLD_Y: " << pos.y << " -> " << new_y << endl << endl;
	return new_pos;
}

int Organism::multiplication()
{
	int result = NOT_ENOUGH_LUCK_FOR_BREEDING;
	int chance_of_propagating = get_propagation_chance();
	bool if_propagate = (rand() % 100) < chance_of_propagating; // chance that organism will propagate
	if (if_propagate)
	{
		position_t new_pos;
		int directions[NUMBER_OF_DIRECTIONS]; // all directions
		directions[0] = FAILURE; //assume, that every neighbouring field is taken
		directions[1] = FAILURE;
		directions[2] = FAILURE;
		directions[3] = FAILURE;
		int amount_of_poss_dir = 0;
		int drawn_direction;

		check_free_fields(directions, amount_of_poss_dir, BREEDING_RANGE);
		if (amount_of_poss_dir) 
		{
			drawn_direction = draw_direction(directions, amount_of_poss_dir);
			new_pos = return_position(drawn_direction, BREEDING_RANGE);
			create_a_descendant(new_pos);
			result = BREEDING_SUCCESS; // multiplication was a success
		}
		else // if there are no possible fields, then don't multiplicate
		{
			result = NO_PLACE_FOR_A_DESCENDANT; // multiplication didnt happen
		}
	}
	else 
	{
		result = NOT_ENOUGH_LUCK_FOR_BREEDING;
	}
	return result;
}

void Organism::increase_strength(int power)
{
	strength += power;
}

int Organism::get_age()
{
	return age;
}

void Organism::set_age(int _age)
{
	age = _age;
}

std::string Organism::return_organism_info_()
{
	std::string gender_string;
	int gender = get_gender();
	switch (gender)
	{
	case MALE:
		gender_string = "M";
		break;
	case FEMALE:
		gender_string = "F";
		break;
	case PERFECT:
		gender_string = "P";
		break;
	default:
		gender_string = "undentified";
	}
	std::string info_communique = get_species_name() + " - its info is: str: " + std::to_string(get_strength()) +
	", age: " + std::to_string(get_age()) + ", gender: " + gender_string + ", pos: [" + std::to_string(pos.x) +
	", " + std::to_string(pos.y) + "]" + "\n";
	
	return info_communique;
}

int Organism::get_initiative()
{
	return initiative;
}

int Organism::get_ID_number()
{
	return ID_number;
}

void Organism::set_ID_number(int _ID_number)
{
	ID_number = _ID_number;
}
Organism::~Organism()
{
	//std::string death_communique = get_species_name() + " died. \n";
	//current_world->write_to_file(death_communique, F_ROUND_RAPORT);
}
