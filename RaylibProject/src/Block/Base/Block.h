#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"
//#include "GameManager.h"


typedef struct BlockBoundaryCheckInfo
{
	bool isUnderBoundary = true;
	int8_t columnValidation = 0;
	int8_t rowValidation = 0;

} BoundaryCheckResult;



class Block
{
public:
	Block();
	int GetBlockId();
	void Draw(const float& additionalColumnOffset, const float& additionalRowOffset);
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	void Rotate();
	void InitiateGridChange();
	bool CheckCollision(Position position);
	virtual void ResetBlock() = 0;

	std::map<int, std::vector<Position>> cells;

	
protected:
	int id;
	void UpdateBlockPositionBy(const int8_t rows, const int8_t cols);
	void UpdateBlockPositionTo(const int8_t rows, const int8_t cols);
	BoundaryCheckResult IsUnderBoundary();		
	int8_t rotationState;
private:	
	int8_t cellSize;
	std::vector<Color> colors;	
	int8_t rowOffset;
	int8_t colOffset;

};

