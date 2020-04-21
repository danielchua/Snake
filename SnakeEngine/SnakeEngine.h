#ifndef SNAKEENGINE_H_
#define SNAKEENGINE_H_

#include "Defines.h"
#include <stdint.h>
#include <vector>

class SnakeEngine
{
public:

	struct TileRepresentations
	{
		uint8_t Empty;
		uint8_t Snake;
		uint8_t SnakeHead;
		uint8_t Point;
	};

	enum class PlayerAction
	{
		NoAction,
		MoveUp, 
		MoveDown, 
		MoveLeft, 
		MoveRight
	};

	SnakeEngine(TileRepresentations boardRepresentation, uint8_t boardWidth, uint8_t boardHeight);
	~SnakeEngine();
	void SetupBoard();
	void RenderFrame(PlayerAction action = PlayerAction::NoAction);
	uint8_t** GetBoard();
	uint8_t GetWidth();
	uint8_t GetHeight();
	uint16_t GetScore();
	bool IsGameOver();

private:
	struct Coordinate
	{
		uint8_t x;
		uint8_t y;
	};
	Coordinate getRandomCoordinate();

	struct Player
	{
	public:
		uint16_t Length;
		PlayerAction PreviousAction;
		uint16_t Score;
		std::vector<Coordinate> BodyPositions;
	private:
		void moveForward()
		{

		}
	};
	void clearBoard();
	void setTile(Coordinate position, uint8_t object);
	void setPoint(Coordinate position);
	void setHead(Coordinate position);
	void setBody(Coordinate position);
	void clearTile(Coordinate position);
	void movePlayer(PlayerAction action);
	uint8_t getTile(Coordinate position);
	void gameOver();
	void spawnPoint();
	void renderPlayer();

	const TileRepresentations m_boardVisuals;
	const uint8_t m_width;
	const uint8_t m_height;
	uint8_t** m_ppBoard; 
	const uint16_t m_boardSz;
	const Coordinate m_startPos;
	Player m_player;
	bool m_gameOver;
	Coordinate m_point;
};

#endif
