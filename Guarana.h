#ifndef GUARANA_H
#define GUARANA_H
#include "Plant.h"
#include "CONSTinfoOrganisms.h"
#include <string>

class Guarana :
	public Plant
{
private:
	const int power; // increase attacker's strength by the power number
public:
	Guarana(position_t _pos, World* _current_world, int _strength = GUARANA_BASIC_STR, char _symbol = GUARANA_SYMBOL,
		int _maturity_age = GUARANA_MATURE_AGE, std::string _species_name = GUARANA_NAME, int _propagation_chance = GUARANA_PROPAGATION_CHANCE,
		int _death_age = GUARANA_DEATH_AGE, int _power = GUARANA_POWER);
	void draw() override;
	void create_a_descendant(position_t new_pos) override;
	int collision_course(Organism* attacker) override;
	~Guarana();
};
#endif