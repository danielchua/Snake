#include "pch.h"
#include "SnakeUI.h"
#include <stdlib.h>
#include <iostream>


SnakeUI::SnakeUI() :
	m_width(11U),
	m_height(10U),
	m_tiles({ ' ', '+', 'o', '*' }),
	m_engine(m_tiles, m_width, m_height)
{
	system("cls");
	std::cout << "~~~ Welcome to Snake ~~~" << std::endl;
	std::cout << "Use w a s d to move" << std::endl;
	m_engine.SetupBoard();
}


SnakeUI::~SnakeUI()
{
}

void SnakeUI::RenderFrame(SnakeEngine::PlayerAction action)
{
	system("cls");
	m_engine.RenderFrame(action);
	printBoard();
}

void SnakeUI::printBoard()
{
	std::cout << "Score:" << static_cast<int>(m_engine.GetScore()) << std::endl;
	std::cout << "-----------------------" << std::endl;
	uint8_t** ppBoard = m_engine.GetBoard();
	for (uint8_t y = 0; y < m_height; y++)
	{
		std::cout << "|";
		for (uint8_t x = 0; x < m_width; x++)
		{
			if (x > 0)
			{
				std::cout << " ";
			}
			const uint8_t tile = ppBoard[x][y];
			std::cout << tile;
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "-----------------------" << std::endl;
}

bool SnakeUI::IsGameOver()
{
	return m_engine.IsGameOver();
}
