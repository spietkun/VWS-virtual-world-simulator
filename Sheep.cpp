#include "Sheep.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoFiles.h"

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

Sheep::Sheep(position_t _pos, World* _current_world, int _strength, int _initiative, char _symbol, int _maturity_age,
	std::string _species_name, int _propagation_chance, int _death_age)
	: Animal(_pos, _current_world, _strength, _initiative, _symbol, _maturity_age, _species_name, _propagation_chance, _death_age)
{
}

void Sheep::create_a_descendant(position_t new_pos)
{
	current_world->get_organisms()[new_pos.y][new_pos.x] = new Sheep(new_pos, current_world);
}

void Sheep::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, SHEEP_COLOUR);
	cout << symbol;
	SetConsoleTextAttribute(hConsole, GENERAL_COLOUR);
}

Sheep::~Sheep()
{
}

