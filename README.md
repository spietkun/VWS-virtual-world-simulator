
# VWS - Virtual World Simulator
## Sections

 - [Visuals](#visuals)
 - [Description](#description)
	 - [General](#general)
	 - [Rules](#rules)
	 - [Programming languages](#programming-languages)
	 - [Systems](#systems)
	 - [Notes](#notes)
 - [Usage](#usage)
 - [Date](#date) (optional)
 
## Visuals

![Screenshot](docs/images/screenshot.jpg)

## Description

### General

**VWS** is a program that simulates a world and living organisms in it.

### Rules

**Main rules:**

 - the world is a **two-dimensional board** NxM given by the user. 
 - there are simple organisms living in the world, each of them situated on one "field/tile"
 - program is **turn-based**
 - user is moving the character
 - organism interact with each other - when they are about to move to the same field there is a specified action e.g. fight or propagation
 - Organisms have its stats e.g. strength, inititative
	 - Inititative decides about move order (when equal then age is compared)
	 - Strength decides about result of the fight
- Animals can have special abilities
- User can activate special ability - "alzur shield" which protects him from any attacks for 5 turns
- game can be saved and loaded

**Detailed rules:**

**Human**

| Strength | Inititative | Action                             | Collision                                                |
|----------|-------------|------------------------------------|----------------------------------------------------------|
| 5        | 4           | user chooses direction of the move | alzur shield - protects from being  attacked for 5 turns |

**Animals**

| ID | Animal   | Strength | Inititative | Action                   | Collision                                                                        |
|----|----------|----------|-------------|--------------------------|----------------------------------------------------------------------------------|
| 1  | wolf     | 9        | 5           | x                        | x                                                                                |
| 2  | sheep    | 4        | 4           | x                        | x                                                                                |
| 3  | turtle   | 2        | 1           | 75% chance of not moving | Resists attacks of attack with strength < 5 Attacker must come back to its field |
| 4  | antelope | 4        | 4           | move range is 2          | 50% chance of fleeing before fight - then move to the nearby empty field         |

**Plants**

| ID | Plant      | Strength | Action                             | Collision                           |
|----|------------|----------|------------------------------------|-------------------------------------|
| 1  | grass      | 0        | x                                  | x                                   |
| 2  | sowthistle | 0        | 3 attemps of propagation in 1 turn | x                                   |
| 3  | guarana    | 0        |                                    | Increases animal's strength by 3    |
| 4  | belladonna | 99       |                                    | Eating it results in animal's death |
| 5  | hogweed    | 10       | kills all nearby animals           | Eating it results in animal's death |

### Programming languages

 - C++ (objective)
 
### Notes

Additional notes

## Usage

 - university project
 - practising objective thinking
