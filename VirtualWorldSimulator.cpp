#include "World.h"
#include "CONSTinfoKeys.h"
#include "CONSTinfoFiles.h"

#include <time.h>
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;
int main()
{
	int x;
	int y;
	do
	{
		cout << "HEIGTH and WIDTH: min width is " << MIN_BOARD_WIDTH << " and min heigth is " << MIN_BOARD_HEIGHT << ": ";
		cin >> y;
		cin >> x;
	} while (y < MIN_BOARD_HEIGHT && x < MIN_BOARD_WIDTH);

	//system("color %");
	srand(time(NULL));
	position_t pos1;
	pos1.x = 4;
	pos1.y = 5;
	World* Koleczkowo = new World(y, x);
	World* Loaded_world;
	//Koleczkowo.open_raport();
	Koleczkowo->open_and_clear_file(F_ROUND_RAPORT);
	Koleczkowo->drawConstStatement(AUTHOR_INFO);
	Koleczkowo->drawConstStatement(TITLE_INFO);
	Koleczkowo->initialFirstRound();
	Koleczkowo->set_human_direction(0);
	Koleczkowo->initialWorldformation(Koleczkowo);
	Koleczkowo->drawWorld();
	Koleczkowo->read_from_file(F_ROUND_RAPORT);

	Koleczkowo->close_file(F_ROUND_RAPORT);

	int command = START_DOWNLOADING_KEYS;

	while ((command = Koleczkowo->download_key()) && (command != EXIT))
	{
		int do_next; // hold info what to do after follow command is done
		Koleczkowo->open_and_clear_file(F_ROUND_RAPORT);

		do_next = Koleczkowo->follow_command(command);
		
		bool if_continue = false;

		switch (do_next)
		{
		case CONTINUE_ROUND:
			//just perform round
			break;
		case DOWNLOAD_KEY:
			if_continue = true;
			break;
		}

		if (if_continue)
		{
			Koleczkowo->close_file(F_ROUND_RAPORT);
			continue;
		}

		if (command == LOAD_VIRTUAL_WORLD_STATE)
		{
			Koleczkowo->open_file(F_SAVE_STATE); // if the save file is empty, tap another key
			if ((Koleczkowo->get_save_file()).peek() == EOF)
			{
				Koleczkowo->close_file(F_SAVE_STATE);
				cout << "The save file is empty. Click s to save a file first. " << endl;
				continue;
			}
			Koleczkowo->close_file(F_SAVE_STATE);

			Loaded_world = Koleczkowo->load_world_state(Koleczkowo);
			Koleczkowo->close_file(F_ROUND_RAPORT);
			delete Koleczkowo;
			Koleczkowo = Loaded_world;
			system("cls");
			Koleczkowo->drawConstStatement(AUTHOR_INFO);
			Koleczkowo->drawConstStatement(TITLE_INFO);
			Koleczkowo->drawWorld();
			continue;
		}
		else if (command == SAVE_VIRTUAL_WORLD_STATE)
		{
			Koleczkowo->save_world_state();
			continue;
		}
		system("cls");
		Koleczkowo->drawConstStatement(AUTHOR_INFO);
		Koleczkowo->drawConstStatement(TITLE_INFO);
		Koleczkowo->performRound();
		Koleczkowo->drawWorld();

		Koleczkowo->read_from_file(F_ROUND_RAPORT);
		
		Koleczkowo->close_file(F_ROUND_RAPORT);
	}
	delete Koleczkowo;
	
    return 0;
}

