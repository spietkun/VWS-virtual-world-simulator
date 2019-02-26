#ifndef CONSTINFOMOVING_H
#define CONSTINFOMOVING_H
//MOVING
const int NUMBER_OF_DIRECTIONS = 4;

//DIRECTIONS
// use FAILURE if organism can't make action in this direction
const int LEFT = 1;
const int RIGHT = 2;
const int UP = 3;
const int DOWN = 4;

//FIGHTING
const int ATTACKER_WON = 0;
const int DEFENDER_WON = 1;
const int DRAW = 2;
const int ESCAPE = 3;
const int REFLECTION = 4;
const int INDIVIDUAL = 5;
#endif