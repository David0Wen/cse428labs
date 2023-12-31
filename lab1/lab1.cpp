/**
// File: lab1.cpp
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: contain the main function, test whether the game goes correctly.
*/
#include <iostream>
#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include "Game.h"
#include <memory>
#include <cstring>
#include "PinochleGame.h"
#include "HoldEmGame.h"


const int SUCCESS = 0;
const int INVALIDINPUT = 1;
const int INVALIDPLAYERNUM = 2;
const int INVALIDGAMENAME = 3;
const int INVALIDPTR = 4;
const int OTHERERROR = 5;

// Function to create a game based on command line arguments
std::shared_ptr<Game> create(int argc, const char *argv[]) {
	std::shared_ptr<Game> myGamePtr;
	if (strcmp(argv[1], "Pinochle") == 0) {
		myGamePtr = std::make_shared<PinochleGame>(argc, argv);
	}
	else if (strcmp(argv[1], "HoldEm") == 0) {
		myGamePtr = std::make_shared<HoldEmGame>(argc, argv);
	}
	return myGamePtr;
}

// Function to display correct usage of the program
void usage(std::ostream& os) {
	os << "Usage: lab1 <Game> <Players>" << std::endl;
	os << "Game should be either Pinochle or HoldEm." << std::endl;
	os << "Pinochle needs 4 players." << std::endl;
	os << "HoldEm needs 2-9 players." << std::endl;
}

int main(int argc, const char *argv[]){
    // Check for minimum number of arguments
    if (argc < 2)
	{
		usage(std::cout);
		return INVALIDINPUT;
	}
    // Check for Pinochle game-specific conditions
	else if (strcmp(argv[1], "Pinochle") == 0) {
		if (argc != 6) {
			usage(std::cout);
			return INVALIDPLAYERNUM;
		}
	}
    // Check for HoldEm game-specific conditions
    else if (strcmp(argv[1], "HoldEm") == 0) {
		if (argc < 4 || argc > 11) {
			usage(std::cout);
			return INVALIDPLAYERNUM;
		}
	}
    // Game other than Pinochle or HoldEm
    else
	{
		usage(std::cout);
		return INVALIDGAMENAME;
	}

	try
	{
        // Create the game based on command line arguments
        std::shared_ptr<Game> myGame = create(argc, argv);
		if (myGame)
		{
			myGame->play();
		}
		else
		{
			std::cout << "Error: Invalid ptr";
			return INVALIDPTR;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return OTHERERROR;
	}

	return SUCCESS;
}