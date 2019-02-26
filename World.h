#ifndef WORLD_H
#define WORLD_H

#include "Organism.h"
#include "CONSTinfoOrganisms.h"
#include <fstream>

class World
{
private:
	int height;
	int width;
	int n_fields;
	int round;
	Organism*** organisms;
	std::fstream raport_file;
	std::fstream save_file;
	int human_direction;
	super_power_t alzur_shield;
	Organism** sorted_organism;
	static int number_of_organisms; // initialize with 0
public:
	World(int _length, int _width);

	void drawConstStatement(std::string statement);
	void drawWorld();
	//void drawStatement();
	void performRound();
	void initialFirstRound();
	void initialWorldformation(World* this_world);
	void placeAreaY(int coordinateY);
	void placeAreaX(int coordinateX);
	int get_height();
	int get_width();
	int get_round();
	void set_round(int _round);
	Organism*** get_organisms();
	position_t randomPosition(int x, int y);
	int download_key();
	void set_human_direction(int _direction);
	int get_human_direction();
	int follow_command(int command);
	std::fstream& get_raport_file();
	std::fstream& get_save_file();
	void write_to_file(std::string text, int choice); // use it when file is OPENED; 
	void read_from_file(int choice); // use it when raport is OPENED; 
	// choice is describing the file to be used (using CONST from CONSTinfoFiles)
	void open_file(int choice);
	void close_file(int choice);
	void open_and_clear_file(int choice);
	void set_alzur_power(bool if_activated, int duration, int pause);
	super_power_t get_alzur_power();
	void copy_organisms_to_sorted();
	int get_number_of_organisms();
	void set_number_of_organisms(int _number_of_organisms);
	void increase_number_of_organisms();
	void sort_buff_organism(); // sport by initiative and if it is equal than compaere ID number (lower ID number is higher age)
	Organism** get_sorted_organisms();
	void save_world_state();
	World* load_world_state(World* &world);

	~World();
};
#endif