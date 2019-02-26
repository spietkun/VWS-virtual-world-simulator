#ifndef CONSTINFODRAWING_H
#define CONSTINFODRAWING_H
#include <string>

// AREAS INFO //
const int MIN_BOARD_HEIGHT = 1;
const int MIN_BOARD_WIDTH = 1;
//CONDITIONS - 1) only one thing in a line; 2) Order of areas is AUTHOR->TITLE->WORLD->STATEMENT
const int AUTHOR_SX = 10; // author start coordinate X
const int AUTHOR_SY = 0; // author start coordinate Y
const int SPACE_Y_BETWEEN_AREAS = 1;
const int SPACE_X_BETWEEN_AREAS = 2;

// AUTHOR INFO //
const std::string AUTHOR_INFO= "Szymon Pietkun 171653 projekt nr 1 - C++ ";

// TITLE INFO //
const std::string TITLE_INFO = "VIRTUAL WORLD SIMULATOR";

// WORLD INFO //
const char TOP_FENCE_SYMBOL = '_';
const char SIDE_FENCE_SYMBOL = '|';
const char BOTTOM_FENCE_SYMBOL = '-';

// STATEMENT INFO //
const std::string STATEMENT_INFO = "This happened now: ";

typedef struct
{
	int x;
	int y;
}position_t;

//SORT OPTIONS
const int SORT_BY_INITIATIVE = 1;
const int SORT_BY_AGE = 2;
#endif