// SnakeEngineTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "SnakeUI.h"
#include <stdio.h> 
#include <conio.h> 

int main()
{
    std::cout << "Hello World!\n"; 
	SnakeUI ui;

	while (true)
	{	
		int keyPressed = _getch();
		//printf("Input: %c\n", keyPressed);
		switch (keyPressed)
		{
		case 'w':
			ui.RenderFrame(SnakeEngine::PlayerAction::MoveUp);
			break;
		case 'a':
			ui.RenderFrame(SnakeEngine::PlayerAction::MoveLeft);
			break;
		case 's':
			ui.RenderFrame(SnakeEngine::PlayerAction::MoveDown);
			break;
		case 'd':
			ui.RenderFrame(SnakeEngine::PlayerAction::MoveRight);
			break;
		case 'q':
			std::cout << "Quit";
			return 0;
			break;
		default:
			ui.RenderFrame(SnakeEngine::PlayerAction::NoAction);
			break;
		}
		if (ui.IsGameOver())
		{
			std::cout << "xxx GAME OVER xxx" << std::endl;
			return 0;
		}
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
