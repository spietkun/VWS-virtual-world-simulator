#ifndef PLANT_H
#define PLANT_H

#include "Organism.h"
#include "World.h"
class Plant :
	public Organism
{
public:
	Plant(position_t _pos, World* _current_world, int _strength, char _symbol,
		int _maturity_age, std::string _species_name, int _propagation_chance,
		int _death_age, int _initiative = GENERAL_PLANT_INIT);
	bool plant_propagation();
	void action() override;
	void collision(Organism* defender) override;
	virtual int get_general_propagation_am(); //amount
	virtual ~Plant();
	
};
#endif