#ifndef CONSTINFOORGANISMS
#define CONSTINFOORGANISMS

#include <string>
#include "CONSTinfoColours.h"
// ANIMALS /////////////

//GENERAL
const int SUCCESS = 1;
const int FAILURE = 0;

const int N_SPECIES = 11; // without cyber sheep // with human
const double MULTIPLIER_FOR_ORGANISMS = 0.3; // percent of the board that will be filled with animals (0.1 = 10%)
const std::string GENERAL_SPECIES_NAME = "Organism";
const char GENERAL_ORGANISM_SYMBOL = 'o';
const int GENERAL_STEP_SIZE = 1;
const int GENERAL_CHANCE_OF_MOVING = 100; //100% desire to move
const int GENERAL_MATURE_AGE = 0;
const int GENERAL_PROPAGATION_CHANCE = 0;
const int ANIMAL_PROPAGATION_CHANCE = 100; //in % 
const int GENERAL_COLOUR = WHITE;
const int GENERAL_DEATH_AGE = 15;
const int NORMAL_SMELL_SKILL = 0; // animal's smell doesn't influence moving on the board
const int AVOID_STR_SMELL_SKILL = 1; // animals won't step on the board, where a stronger organism stands

//BREEDING
const int MALE = 0;
const int FEMALE = 1;
const int PERFECT = 2; //(term for plants)
const int BREEDING_RANGE = 1;
//BREEDING RESULTS
const int NO_PLACE_FOR_A_DESCENDANT = 0;
const int NOT_ENOUGH_LUCK_FOR_BREEDING = 1;
const int BREEDING_SUCCESS = 2;

//INDIVIDUAL

//WOLF
const std::string WOLF_NAME = "Wolf";
const int WOLF_BASIC_STR = 9;
const int WOLF_BASIC_INIT = 5;
const char WOLF_SYMBOL = 'w';
const int WOLF_MATURE_AGE = 3;
const int WOLF_COLOUR = GREY;
const int WOLF_PROPAGATION_CHANCE = 100; //in % 
const int WOLF_DEATH_AGE = 120;

//SHEEP
const std::string SHEEP_NAME = "Sheep";
const int SHEEP_BASIC_STR = 4;
const int SHEEP_BASIC_INIT = 4;
const char SHEEP_SYMBOL = 's';
const int SHEEP_MATURE_AGE = 4;
const int SHEEP_COLOUR = LIGHT_GREY;
const int SHEEP_PROPAGATION_CHANCE = 100; //in % 
const int SHEEP_DEATH_AGE = 95;

//FOX
const std::string FOX_NAME = "Fox";
const int FOX_BASIC_STR = 3;
const int FOX_BASIC_INIT = 7;
const char FOX_SYMBOL = 'f';
const int FOX_MATURE_AGE = 2;
const int FOX_COLOUR = YELLOW;
const int FOX_PROPAGATION_CHANCE = 100; //in % 
const int FOX_DEATH_AGE = 90; //in %

//TURTLE
const std::string TURTLE_NAME = "Turtle";
const int TURTLE_BASIC_STR = 2;
const int TURTLE_BASIC_INIT = 1;
const char TURTLE_SYMBOL = 't';
const int TURTLE_MATURE_AGE = 10;
const int TURTLE_CHANCE_OF_MOVING = 25; // (%)
const int TURTLE_REFLECTION_CONDITION = 5; // (max strength of attacker = 5)
const int TURTLE_COLOUR = DARK_GREEN;
const int TURTLE_PROPAGATION_CHANCE = 100; //in % 
const int TURTLE_DEATH_AGE = 400; //in % 

//ANTELOPE
const std::string ANTELOPE_NAME = "Antelope";
const int ANTELOPE_BASIC_STR = 4;
const int ANTELOPE_BASIC_INIT = 4;
const char ANTELOPE_SYMBOL = 'a';
const int ANTELOPE_MATURE_AGE = 3;
const int ANTELOPE_STEP_SIZE = 2;
const int ANTELOPE_ESCAPE_CHANCE = 51; // (in %)
const int ANTELOPE_COLOUR = GOLD;
const int ANTEOPE_PROPAGATION_CHANCE = 100; //in % 
const int ANTELOPE_DEATH_AGE = 100; //in % 

//HUMAN
const std::string HUMAN_NAME = "Human";
const int HUMAN_BASIC_STR = 5;
const int HUMAN_BASIC_INIT = 100;
const char HUMAN_SYMBOL = 'H';
const int HUMAN_MATURE_AGE = 18;
const int HUMAN_PROPAGATION_CHANCE = 0;
const int HUMAN_COLOUR = TEAL;
const int HUMAN_ALZUR_SHIELD_DURATION = 5; //5 rounds
const int HUMAN_ALZUR_SHIELD_BREAK = 5; //5 rounds
const int HUMAN_DEATH_AGE = 0; //in %  // 0 means infinite

typedef struct
{
	bool is_power_on;
	int duration;
	int pause; // pause in activating the super_power = duration + break
}super_power_t;

//CYBER SHEEP
/*const int CSHEEP_BASIC_STR = 11;
const int CSHEEP_BASIC_INIT = 4;
const char CSHEEP_SYMBOL = 'c';*/

// PLANTS ////////////////////

//GENERAL
const int GENERAL_PLANT_RANGE = 1; //range of propagation
const int GENERAL_PLANT_INIT = 0;
const int GENERAL_PROPAGATION_AMOUNT = 1;

//INDIVIDUAL

//GRASS
const std::string GRASS_NAME = "Grass";
const int GRASS_BASIC_STR = 0;
const char GRASS_SYMBOL = '1';
const int GRASS_PROPAGATION_CHANCE = 10; //in %
const int GRASS_MATURE_AGE = 1;
//const int GRASS_COLOUR = D_GREEN_BG_WHITE; // COLOUR WITH SYMBOL
const int GRASS_COLOUR = D_GREEN_BG_DARK_GREEN; // ONLY COLOUR
const int GRASS_DEATH_AGE = 10; 

//SOWTHISTLE
const std::string SOWTHISTLE_NAME = "Sowthistle";
const int SOWTHISTLE_BASIC_STR = 0; // mlecz
const char SOWTHISTLE_SYMBOL = '2';
const int SOWTHISTLE_PROPAGATION_CHANCE = 3; //in %
const int SOWTHISTLE_MATURE_AGE = 2;
const int SOWTHISTLE_PROPAGATION_AMOUNT = 3; // how many times a sowthistle will try to propagate
//const int SOWTHISTLE_COLOUR = YELLOW_BG_WHITE; // COLOUR WITH SYMBOL
const int SOWTHISTLE_COLOUR = YELLOW_BG_YELLOW; // ONLY COLOUR
const int SOWTHISTLE_DEATH_AGE = 6;

//GUARANA
const std::string GUARANA_NAME = "Guarana";
const int GUARANA_BASIC_STR = 0;
const char GUARANA_SYMBOL = '3';
const int GUARANA_PROPAGATION_CHANCE = 5; //in %
const int GUARANA_MATURE_AGE = 8;
const int GUARANA_POWER = 3;
//const int GUARANA_COLOUR = RED_BG_WHITE; // COLOUR WITH SYMBOL
const int GUARANA_COLOUR = RED_BG_RED; // ONLY COLOUR
const int GUARANA_DEATH_AGE = 20;

//BELLADONNA
const std::string BELLADONNA_NAME = "Belladonna";
const int BELLADONNA_BASIC_STR = 99; // "wolf berries"
const char BELLADONNA_SYMBOL = '4';
const int BELLADONNA_PROPAGATION_CHANCE = 1; //in %
const int BELLADONNA_MATURE_AGE = 5;
//const int BELLADONNA_COLOUR = PURPLE_BG_WHITE; // COLOUR WITH SYMBOL
const int BELLADONNA_COLOUR = PURPLE_BG_PURPLE; // ONLY COLOUR
const int BELLADONNA_DEATH_AGE = 17;

//HOGWEED
const std::string HOGWEED_NAME = "Hogweed";
const int HOGWEED_BASIC_STR = 10; // barszcz sosnowskiego
const char HOGWEED_SYMBOL = '5';
const int HOGWEED_PROPAGATION_CHANCE = 1; //in %
const int HOGWEED_MATURE_AGE = 9;
const int HOGWEED_KILLING_ZONE = 1;
//const int HOGWEED_COLOUR = LIGHT_GREY_BG_WHITE; // COLOUR WITH SYMBOL
const int HOGWEED_COLOUR = LIGHT_GREY_BG_LIGHT_GREY; // ONLY COLOUR
const int HOGWEED_DEATH_AGE = 18; 

#endif