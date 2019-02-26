#include "World.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Human.h"

#include "Grass.h"
#include "Sowthistle.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "Hogweed.h"

#include "CONSTinfoDrawing.h"
#include "CONSTinfoOrganisms.h"
#include "CONSTinfoMoving.h"
#include "CONSTinfoKeys.h"
#include "CONSTinfoFiles.h"

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <fstream>
using namespace std;

World::World(int _height, int _width)
{
	height = _height;
	width = _width;
	n_fields = height*width;

	organisms = new Organism**[height];
	for (int i = 0; i < height; i++)
	{
		organisms[i] = new Organism*[width];
		for (int j = 0; j < width; j++)
		{
			organisms[i][j] = nullptr;
		}
	}

	sorted_organism = new Organism*[height*width];
	for (int i = 0; i < height*width; i++)
	{
		sorted_organism[i] = nullptr;
	}

	set_alzur_power(false, HUMAN_ALZUR_SHIELD_DURATION, 0);
};

int World::number_of_organisms = 0;

position_t World::randomPosition(int y, int x)
{
	position_t pos;
	pos.x = 0;
	pos.y = 0;
	bool already_occ;

	do
	{
		already_occ = false;
		pos.x = rand() % x;
		pos.y = rand() % y;

		if (organisms[pos.y][pos.x] != nullptr) already_occ = true;
		else already_occ = false;

	} while (already_occ);

	return pos;
}

void World::initialFirstRound()
{
	round = 0;
}
void World::initialWorldformation(World* this_world)
{
	int n_organisms;
	int n_single_species;
	position_t pos;
	if (n_fields > N_SPECIES) // if there are more fields than spieces fill the board with organisms in the number equal to const muliplier * fields
	{
		n_organisms = MULTIPLIER_FOR_ORGANISMS * n_fields;
		n_single_species = n_organisms / N_SPECIES;
		//cout << n_single_species;
		if (n_single_species != 0)
		{
			pos = randomPosition(height, width); // ONE HUMAN
			organisms[pos.y][pos.x] = new Human(pos, this_world);

			for (int i = 0; i < n_single_species; i++)
			{
				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Wolf(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Sheep(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Fox(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Turtle(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Antelope(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Grass(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Sowthistle(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Guarana(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Belladonna(pos, this_world);

				pos = randomPosition(height, width);
				organisms[pos.y][pos.x] = new Hogweed(pos, this_world);
			}
		}
		else n_fields = N_SPECIES; // if multiplier for organisms is too small then create a single instance of each organism 
	}

	if (n_fields == N_SPECIES)
	{
		pos = randomPosition(height, width); // ONE INSTANCE OF EACH SPECIES
		organisms[pos.y][pos.x] = new Human(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Wolf(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Sheep(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Fox(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Turtle(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Antelope(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Grass(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Sowthistle(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Guarana(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Belladonna(pos, this_world);

		pos = randomPosition(height, width);
		organisms[pos.y][pos.x] = new Hogweed(pos, this_world);
	}
	else if (n_fields < N_SPECIES)// if number of the fields is smaller than number of species than create as much as possible
	{
		int counter = 0;

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Human(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Wolf(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Sheep(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Fox(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Turtle(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Antelope(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Grass(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Sowthistle(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Guarana(pos, this_world);
			counter++;
		}

		if (counter < n_fields)
		{
			pos = randomPosition(height, width);
			organisms[pos.y][pos.x] = new Belladonna(pos, this_world);
			counter++;
		}
	}
}

void World::drawConstStatement(std::string statement)
{
	placeAreaX(SPACE_X_BETWEEN_AREAS);
	cout << statement << endl;
	placeAreaY(SPACE_Y_BETWEEN_AREAS);
}

void World::drawWorld()
{
	placeAreaX(SPACE_X_BETWEEN_AREAS);
	for (int i = 0; i < width + 2; i++) printf("%c", TOP_FENCE_SYMBOL); // DRAW FENCE, +2 because of 2 columns
	printf("\n");

	for (int i = 0; i < height; i++)
	{
		placeAreaX(SPACE_X_BETWEEN_AREAS);
		printf("%c", SIDE_FENCE_SYMBOL); // DRAW FENCE
		for (int j = 0; j < width; j++)
		{
			if (organisms[i][j] == nullptr) printf(" ");
			else
			{
				organisms[i][j]->draw();
			}
			
		}
		printf("%c", SIDE_FENCE_SYMBOL); // DRAW FENCE
		printf("\n");
	}

	placeAreaX(SPACE_X_BETWEEN_AREAS);
	for (int i = 0; i < width + 2; i++) printf("%c", BOTTOM_FENCE_SYMBOL); // DRAW FENCE +2 because of 2 columns
	printf("\n");
	placeAreaY(SPACE_Y_BETWEEN_AREAS);
}

void World::placeAreaY(int coordinateY) // for example: "2" = 2 x endl
{
	for (int i = 0; i < coordinateY; i++)
	{
		printf("\n");
	}
}

void World::placeAreaX(int coordinateX) // for example: "2" = 2 x space
{
	for (int i = 0; i < coordinateX; i++)
	{
		printf(" ");
	}
}

int World::get_height()
{
	return height;
}

int World::get_width()
{
	return width;
}

void World::set_round(int _round)
{
	round = _round;
}

int World::get_round()
{
	return round;
}

Organism*** World::get_organisms()
{
	return organisms;
}

void World::performRound()
{
	copy_organisms_to_sorted();
	sort_buff_organism();

	if (alzur_shield.is_power_on == true)
	{
		if (alzur_shield.duration > 1) // decrease till duration = 1 round
		{
			(alzur_shield.duration)--;
		}
		else // if super_power ended, decrease pause time
		{
			alzur_shield.is_power_on = false;
		}
	}
	else
	{
		if (alzur_shield.pause > 0)
		{
			(alzur_shield.pause)--;
		}
	}

	for (int i = 0; i < height*width; i++)
	{
		if (sorted_organism[i] != nullptr)
		{
			sorted_organism[i]->grow_older();
			sorted_organism[i]->action();
			//cout << "init: " << sorted_organism[i]->get_initiative() << " and ID: " << sorted_organism[i]->get_ID_number() << endl;
		}
	}
}

int World::download_key()
{
	int result = OTHER_KEY;
	int key = getch();
	if (key == 0 || key == 224)
	{
		key = getch();
		if (key == UP_ARROW)
		{
			result = MOVE_UP;
		}
		else if (key == DOWN_ARROW)
		{
			result = MOVE_DOWN;
		}
		else if (key == LEFT_ARROW)
		{
			result = MOVE_LEFT;
		}
		else if (key == RIGHT_ARROW)
		{
			result = MOVE_RIGHT;
		}
	}
	else if (key == ESC) //esc
	{
		result = EXIT;
	}
	else if (key == A_small || key == A_big)
	{
		result = ACTIVATE_ALZUR;
	}
	else if (key == S_small || key == S_big)
	{
		result = SAVE_VIRTUAL_WORLD_STATE;
	}
	else if (key == L_small || key == L_big)
	{
		result = LOAD_VIRTUAL_WORLD_STATE;
	}
	return result;
}

void World::set_human_direction(int direction)
{
	human_direction = direction;
}

int World::get_human_direction()
{
	return human_direction;
}

int World::follow_command(int command)
{
	int result = CONTINUE_ROUND;
	switch (command)
	{
	case MOVE_LEFT:
		set_human_direction(LEFT);
		result = CONTINUE_ROUND;
		break;
	case MOVE_RIGHT:
		set_human_direction(RIGHT);
		result = CONTINUE_ROUND;
		break;
	case MOVE_UP:
		set_human_direction(UP);
		result = CONTINUE_ROUND;
		break;
	case MOVE_DOWN:
		set_human_direction(DOWN);
		result = CONTINUE_ROUND;
		break;
	case ACTIVATE_ALZUR:
		super_power_t buf_alzur = get_alzur_power();
		if (buf_alzur.is_power_on == false && buf_alzur.pause == 0) // When you can turn alzur on
		{
			set_alzur_power(true, HUMAN_ALZUR_SHIELD_DURATION, HUMAN_ALZUR_SHIELD_BREAK);
			cout << "Alzur shield was activated. It will last for: " << alzur_shield.duration << " rounds .\n";
			result = DOWNLOAD_KEY;
		}
		else if (buf_alzur.is_power_on == true)// when power has been already turned
		{
			cout << "Alzur shield has been already picked!: " << alzur_shield.duration << " rounds left.\n";
			result = DOWNLOAD_KEY;
		}
		else // when there is a pause from choosing power again
		{
			cout << "Alzur shield has been chosen lately. Relax and wait " << alzur_shield.pause << " rounds.\n";
			result = DOWNLOAD_KEY;
		}
		break;
	case OTHER_KEY:
		result = DOWNLOAD_KEY;
		cout << "Tap another key please. \n";
		break;
	}
	return result;
}

std::fstream& World::get_raport_file()
{
	return raport_file;
}

std::fstream& World::get_save_file()
{
	return save_file;
}

void World::open_file(int choice)
{
	if (choice == F_SAVE_STATE)
	{
		save_file.open(SAVE_STATE_PATH, ios::out | ios::in | ios::app);
	}
	else if (choice == F_ROUND_RAPORT)
	{
		raport_file.open(ROUND_RAPORT_PATH, ios::out | ios::in | ios::app);
	}
}

void World::open_and_clear_file(int choice)
{
	if (choice == F_SAVE_STATE)
	{
		save_file.open(SAVE_STATE_PATH, ios::out | ios::in | ios::trunc);
	}
	else if (choice == F_ROUND_RAPORT)
	{
		raport_file.open(ROUND_RAPORT_PATH, ios::out | ios::in | ios::trunc);
	}
}

void World::close_file(int choice)
{
	if (choice == F_SAVE_STATE)
	{
		if (save_file.is_open() == true)
		{
			save_file.close();
		}
	}
	else if (choice == F_ROUND_RAPORT)
	{
		if (raport_file.is_open() == true)
		{
			raport_file.close();
		}
	}
}

void World::write_to_file(std::string text, int choice)
{
	if (choice == F_SAVE_STATE)
	{
		if (save_file.is_open() == true)
		{
			save_file << text;
		}
	}
	else if (choice == F_ROUND_RAPORT)
	{
		if (raport_file.is_open() == true)
		{
			raport_file << text;
		}
	}
}

void World::read_from_file(int choice)
{
	std::string text;
	if (choice == F_ROUND_RAPORT)
	{
		if (raport_file.is_open() == true)
		{
			raport_file.clear();
			raport_file.seekg(0, ios::beg);

			while (!raport_file.eof())
			{
				getline(raport_file, text);
				cout << text << endl;
			}
		}
	}
	else if (choice == F_SAVE_STATE)
	{
		if (save_file.is_open() == true)
		{
			save_file.clear();
			save_file.seekg(0, ios::beg);

			while (!raport_file.eof())
			{
				getline(raport_file, text);
				cout << text << endl;
			}
		}
	}
}

void World::set_alzur_power(bool if_activated, int duration, int pause)
{
	alzur_shield.is_power_on = if_activated;
	alzur_shield.duration = duration;
	alzur_shield.pause = pause;

}

super_power_t World::get_alzur_power()
{
	return alzur_shield;
}

void World::copy_organisms_to_sorted()
{
	int k = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sorted_organism[k] = organisms[i][j];
			k++;
		}
	}
}

void World::increase_number_of_organisms()
{
	number_of_organisms++;
}

void World::sort_buff_organism() // sort by initiative and if it is equal than compaere ID number
{
	for (int i = 0; i < height*width - 1; i++)
	{
		for (int j = 0; j < height*width - 1; j++)
		{

			if (sorted_organism[j] == nullptr) swap(sorted_organism[j], sorted_organism[j + 1]); // push all nulls to the end
			else if (sorted_organism[j + 1] == nullptr); // dont change if next is null
			else if (sorted_organism[j]->get_initiative() < sorted_organism[j + 1]->get_initiative())
			{
				swap(sorted_organism[j], sorted_organism[j + 1]);
			}
			else if (sorted_organism[j]->get_initiative() == sorted_organism[j + 1]->get_initiative())
			{
				if (sorted_organism[j]->get_ID_number() > sorted_organism[j + 1]->get_ID_number())
				{
					swap(sorted_organism[j], sorted_organism[j + 1]);
				}
			}

		}
	}
}

int World::get_number_of_organisms()
{
	return number_of_organisms;
}

void World::set_number_of_organisms(int _number_of_organisms)
{
	number_of_organisms = _number_of_organisms;
}

Organism** World::get_sorted_organisms()
{
	return sorted_organism;
}

void World::save_world_state()
{
	std::string world_info = WORLD_INFO + '\n';
	std::string s_height = to_string(height) + '\n';
	std::string s_width = to_string(width) + '\n';
	std::string s_round = to_string(round) + '\n';
	std::string s_alzur_shield = to_string(alzur_shield.is_power_on) + '\n' + to_string(alzur_shield.duration) + '\n' + to_string(alzur_shield.pause) + '\n';
	std::string s_number_of_organisms = to_string(number_of_organisms) + '\n';
	
	std::string all_world_info = world_info + s_height + s_width + s_round + s_alzur_shield + s_number_of_organisms;
	open_and_clear_file(F_SAVE_STATE);

	write_to_file(all_world_info, F_SAVE_STATE);

	std::string s_organism_name;
	std::string s_organism_position;
	std::string s_organism_strength;
	std::string s_organism_gender;
	std::string s_organism_age;
	std::string s_organism_ID_number;

	std::string all_organism_info;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (organisms[i][j] != nullptr)
			{
				position_t pos = organisms[i][j]->get_position();

				s_organism_name = organisms[i][j]->get_species_name() + '\n';
				s_organism_position = to_string(pos.x) + '\n' + to_string(pos.y) + '\n';
				s_organism_strength = to_string(organisms[i][j]->get_strength()) + '\n';
				s_organism_gender = to_string(organisms[i][j]->get_gender()) + '\n';
				s_organism_age = to_string(organisms[i][j]->get_age()) + '\n';
				s_organism_ID_number = to_string(organisms[i][j]->get_ID_number()) + '\n';

				all_organism_info = s_organism_name + s_organism_position + s_organism_strength + s_organism_gender + s_organism_age + s_organism_ID_number;
				write_to_file(all_organism_info, F_SAVE_STATE);
			}
		}
	}

	close_file(F_SAVE_STATE);
}

World* World::load_world_state(World* &old_world)
{
	open_file(F_SAVE_STATE);

	int f_height;
	int f_width;
	int f_round;
	super_power_t f_alzur_shield; 
	int f_number_of_organisms;
	std::string text;
	World* New_world = nullptr;

	if (save_file.is_open() == true)
	{
		save_file.clear();
		save_file.seekg(0, ios::beg);

		getline(save_file, text); //World info
		//READ NUMERIC DATA
		getline(save_file, text);
			f_height = std::stoi(text);
		getline(save_file, text);
			f_width = std::stoi(text);
		getline(save_file, text);
			f_round = std::stoi(text);
		getline(save_file, text);
			f_alzur_shield.is_power_on = std::stoi(text);
		getline(save_file, text);
			f_alzur_shield.duration = std::stoi(text);
		getline(save_file, text);
			f_alzur_shield.pause = std::stoi(text);
		getline(save_file, text);
			f_number_of_organisms = std::stoi(text);
		
		New_world = new World(f_height, f_width);
		New_world->set_round(f_round);
		New_world->set_alzur_power(f_alzur_shield.is_power_on, f_alzur_shield.duration, f_alzur_shield.pause);
		New_world->set_number_of_organisms(f_number_of_organisms);
		
		//INITIALIZE ORGANISMS

		std::string f_organism_name;
		position_t f_organism_position;
		int f_organism_strength;
		int f_organism_gender;
		int f_organism_age;
		int f_organism_ID_number;

		while (!save_file.eof())
		{
			getline(save_file, text);
				f_organism_name = text;
				if (text != "") // there is a "" at the end of the save file
				{
					getline(save_file, text);
					f_organism_position.x = std::stoi(text);
					getline(save_file, text);
					f_organism_position.y = std::stoi(text);
					getline(save_file, text);
					f_organism_strength = std::stoi(text);
					getline(save_file, text);
					f_organism_gender = std::stoi(text);
					getline(save_file, text);
					f_organism_age = std::stoi(text);
					getline(save_file, text);
					f_organism_ID_number = std::stoi(text);

					if (f_organism_name == WOLF_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Wolf(f_organism_position, New_world, f_organism_strength);
					else if (f_organism_name == SHEEP_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Sheep(f_organism_position, New_world, f_organism_strength);
					else if (f_organism_name == FOX_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Fox(f_organism_position, New_world, f_organism_strength);
					else if (f_organism_name == TURTLE_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Turtle(f_organism_position, New_world, f_organism_strength);
					else if (f_organism_name == ANTELOPE_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Antelope(f_organism_position, New_world, f_organism_strength);
					else if (f_organism_name == HUMAN_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Human(f_organism_position, New_world, f_organism_strength);
					else if (f_organism_name == GRASS_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Grass(f_organism_position, New_world);
					else if (f_organism_name == SOWTHISTLE_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Sowthistle(f_organism_position, New_world);
					else if (f_organism_name == GUARANA_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Guarana(f_organism_position, New_world);
					else if (f_organism_name == HOGWEED_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Hogweed(f_organism_position, New_world);
					else if (f_organism_name == BELLADONNA_NAME) New_world->get_organisms()[f_organism_position.y][f_organism_position.x] = new Belladonna(f_organism_position, New_world);

					(New_world->get_organisms()[f_organism_position.y][f_organism_position.x])->set_gender(f_organism_gender);
					(New_world->get_organisms()[f_organism_position.y][f_organism_position.x])->set_age(f_organism_age);
					(New_world->get_organisms()[f_organism_position.y][f_organism_position.x])->set_ID_number(f_organism_ID_number);
				}
		}

	}

	close_file(F_SAVE_STATE);
	return New_world;
}

World::~World()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (organisms[i][j] != nullptr)
			{
				delete organisms[i][j];
			}
		}
		delete[] organisms[i];
	}
	delete[] organisms;

	delete[] sorted_organism;
}