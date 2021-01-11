////////////////////////////////////////////////////////////////////////////////////////////////
// File :			main.cpp
// Author :			Rodney Stoeffler
// Created :		03.24.08
// Last Modified :	10.29.09
// Purpose :		The main driver for the memory game
// Notes :			Property of Full Sail University, Data Structures Course.
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>				// needed for drawing the screen
#include <conio.h>				// needed for _kbhit and _getch.
#include "MemoryFunctions.h"	// interface for drawing the screen and delay function
#include "DynArray.h"
using namespace std;

void PlayGame();
bool Check(DynArray<int> pcComm, DynArray<int> plComm);

////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
	start();
	while (true) {
		if (_kbhit())
		{
			char ch = _getch();
			if (tolower(ch) == 'p') {
				PlayGame();
			}
			if (ch == 'q')
			{
				break;
			}
		}
	}

	return 0;
}
// Game working
void PlayGame() 
{
	empty();

	DynArray<int> pcComm;	//DynArray for random move inputs
	DynArray<int> plComm;	//DynArray for player inputs
	int newNum;				//for the rand
	int score = -10;
	bool lose = false;		//check losing condition

	srand((unsigned)time(0));

	while (true) {
		//generating random move and adding to DynArray
		delay(1000);
		newNum = rand() % 4;
		pcComm.append(newNum);
		score += 10;

		//Displaying random moves to the player
		for (unsigned int i = 0; i < pcComm.size(); ++i) {
			switch (pcComm[i])
			{
			case 0:
			{
				drawUp();
				delay(300);
				empty();
			}
			break;

			case 1:
			{
				drawDown();
				delay(300);
				empty();
			}
			break;

			case 2:
			{
				drawLeft();
				delay(300);
				empty();
			}
			break;

			case 3:
			{
				drawRight();
				delay(300);
				empty();
			}
			break;
			default:
				break;
			}
			delay(150);
		}

		//waiting for inputs from the player and them displaying player inputs
		while (true) {
			if (_kbhit())
			{
				char ch = _getch();
				switch (tolower(ch))
				{
				case 'w':
				{
					drawUp();
					delay(150);
					empty();
					plComm.append(0);
					lose = Check(pcComm, plComm); 
				}
				break;

				case 's':
				{
					drawDown();
					delay(150);
					empty();
					plComm.append(1);
					lose = Check(pcComm, plComm);
				}
				break;

				case 'a':
				{
					drawLeft();
					delay(150);
					empty();
					plComm.append(2);
					lose = Check(pcComm, plComm);
				}
				break;

				case 'd':
				{
					drawRight();
					delay(150);
					empty();
					plComm.append(3);
					lose = Check(pcComm, plComm);
				}
				break;
				}

				if (ch == 'q')
				{
					lose = true;
					break;
				}

				if (pcComm.size() == plComm.size()) {
					plComm.clear();
					break;
					
				}
			}
		}

		//if lost show screen and restart game
		if (lose == true) {
			empty();
			cout << "      YOUR SCORE IS:";
			cout << score << endl;
			cout << "      PLAY AGAIN? PRESS P" << endl;
			cout << "        TO EXIT PRESS Q" << endl;
			break;
		}
	}

}

//Check to see if player lost
bool Check(DynArray<int> pcComm, DynArray<int> plComm) {
	for (unsigned int i = 0; i < plComm.size(); ++i) {
		if (plComm[i] != pcComm[i]) {
			full();
			delay(150);
			empty();
			delay(150);
			full();
			delay(150);
			empty();
			delay(150);
			full();
			delay(150);
			empty();

			return true;
		}
	}
	return false;
}
