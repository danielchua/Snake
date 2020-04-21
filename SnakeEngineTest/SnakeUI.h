#pragma once

#include <SnakeEngine.h>

class SnakeUI
{
public:
	SnakeUI();
	~SnakeUI(); 
	
	void RenderFrame(SnakeEngine::PlayerAction action);
	bool IsGameOver();
private:
	void printBoard();

	const SnakeEngine::TileRepresentations m_tiles;
	const uint8_t m_width;
	const uint8_t m_height;
	SnakeEngine m_engine;
};

