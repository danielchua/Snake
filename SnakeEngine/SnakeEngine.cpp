
#include "SnakeEngine.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>

SnakeEngine::SnakeEngine(TileRepresentations boardRepresentation, uint8_t boardWidth, uint8_t boardHeight) :
	m_boardVisuals(boardRepresentation),
	m_width(boardWidth),
	m_height(boardHeight),
	m_boardSz(boardWidth * boardHeight),
	m_ppBoard(new uint8_t*[m_width]),
	m_startPos({ boardWidth / 2U, boardHeight / 3U }),
	m_player({ 0U, PlayerAction::MoveUp, 0U, }),
	m_gameOver(false),
	m_point()
{
	for (uint8_t i = 0; i < m_width; i++)
	{
		m_ppBoard[i] = new uint8_t[m_height];
		for (uint8_t j = 0; j < m_height; j++)
		{
			m_ppBoard[i][j] = m_boardVisuals.Empty;
		}
	}
	
	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

SnakeEngine::~SnakeEngine()
{
}

void SnakeEngine::SetupBoard()
{
	m_player.BodyPositions.clear();
	clearBoard();
	m_player.Score = 0U;
	m_player.BodyPositions.insert(m_player.BodyPositions.begin(), m_startPos);
	spawnPoint();
	setHead(m_player.BodyPositions.back());
	m_gameOver = false;
}

void SnakeEngine::RenderFrame(PlayerAction action)
{
	movePlayer(action);
}

uint8_t** SnakeEngine::GetBoard()
{
	return m_ppBoard;
}
uint8_t SnakeEngine::GetWidth()
{
	return m_width;
}
uint8_t SnakeEngine::GetHeight()
{
	return m_height;
}

uint16_t SnakeEngine::GetScore()
{
	return m_player.Score;
}

bool SnakeEngine::IsGameOver()
{
	return m_gameOver;
}

/* PRIVATE METHODS */

void SnakeEngine::clearBoard()
{
	for (uint8_t i = 0; i < m_height; i++)
	{
		for (uint8_t j = 0; j < m_width; j++)
		{
			m_ppBoard[j][i] = m_boardVisuals.Empty;
		}
	}
}

void SnakeEngine::setTile(Coordinate position, uint8_t object)
{
	m_ppBoard[position.x][position.y] = object;
}

void SnakeEngine::clearTile(Coordinate position)
{
	m_ppBoard[position.x][position.y] = m_boardVisuals.Empty;
}

void SnakeEngine::setPoint(Coordinate position)
{
	setTile(position, m_boardVisuals.Point);
}

void SnakeEngine::setHead(Coordinate position)
{
	setTile(position, m_boardVisuals.SnakeHead);
}

void SnakeEngine::setBody(Coordinate position)
{
	setTile(position, m_boardVisuals.Snake);
}

void SnakeEngine::movePlayer(PlayerAction action)
{
	// calculate new position
	Coordinate newPos = m_player.BodyPositions.front();
	switch (action)
	{
	case PlayerAction::NoAction:
		if (m_player.PreviousAction != PlayerAction::NoAction)
		{
			movePlayer(m_player.PreviousAction);
		}
		else
		{
			ASSERT(false); // infinite recursion
		}
		return;
		break;
	case PlayerAction::MoveUp:
		if (newPos.y > 0)
		{
			newPos.y--;
		}
		else
		{
			newPos.y = m_height - 1U;
		}
		break;
	case PlayerAction::MoveDown:
		newPos.y = (newPos.y + 1U) % m_height;
		break;
	case PlayerAction::MoveLeft:
		if (newPos.x > 0)
		{
			newPos.x--;
		}
		else
		{
			newPos.x = m_width - 1U;
		}
		break;
	case PlayerAction::MoveRight:
		newPos.x = (newPos.x + 1U) % m_width;
		break;
	default:
		ASSERT(false);
	}
	
	m_player.BodyPositions.insert(m_player.BodyPositions.begin(), newPos);
	clearTile(m_player.BodyPositions.back());

	// collision check
	const uint8_t tile = getTile(newPos);
	bool scored = false;
	if (tile == m_boardVisuals.Point)
	{
		m_player.Score++;
		scored = true;
	}
	else if (tile == m_boardVisuals.Empty)
	{
		m_player.BodyPositions.erase(--m_player.BodyPositions.end());
	}
	else if ((tile == m_boardVisuals.Snake) || (tile == m_boardVisuals.SnakeHead))
	{
		gameOver();
	}
	else
	{
		ASSERT(false);
	}

	renderPlayer();

	if(scored)
	{
		spawnPoint();
	}

	if (action != PlayerAction::NoAction)
	{
		m_player.PreviousAction = action;
	}
}

uint8_t SnakeEngine::getTile(Coordinate position)
{
	return m_ppBoard[position.x][position.y];
}

SnakeEngine::Coordinate SnakeEngine::getRandomCoordinate()
{
	const uint8_t x = std::rand()%m_width;
	const uint8_t y = std::rand()%m_height;
	const Coordinate p = { x, y };
	return p;
}

void SnakeEngine::gameOver()
{
	m_gameOver = true;
}

void SnakeEngine::spawnPoint()
{
	uint32_t collisions = 0U;
	do 
	{
		const Coordinate pos = getRandomCoordinate();
		if (getTile(pos) == m_boardVisuals.Empty)
		{
			setPoint(pos);
			m_point = pos;
			return;
		}
		collisions++;
	} while(collisions < 10000U);
	ASSERT(false); // no empty spaces?
}

void SnakeEngine::renderPlayer()
{
	setHead(m_player.BodyPositions.front());
	for (uint16_t i = 1U; i < m_player.BodyPositions.size(); i++) // skip head
	{
		setBody(m_player.BodyPositions[i]);
	}
}
