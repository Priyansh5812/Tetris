#include "Block.h"
#include "Grid.h"
#include "GameManager.h"

Block::Block() : id(0)
{		
	std::cout << "Base class constructor called" << std::endl;
	this->cellSize = 30;
	this->rotationState = 0;
	this-> rowOffset = 0;
	this-> colOffset = 0;
	this->colors = GetCellColors();
}

int Block::GetBlockId()
{
	return this->id;
}

void Block::Draw(const float& additionalColumnOffset, const float& additionalRowoffset) 
{
	std::vector<Position> tiles = cells[rotationState];
	
	for (int i = 0; i < cells[rotationState].size(); i++)
	{
		DrawRectangle(cellSize* (tiles[i].column + this-> colOffset+additionalColumnOffset), cellSize*(tiles[i].row + this->rowOffset+additionalRowoffset), cellSize-2 , cellSize-2, GetCellColors()[id]);
	}
}

void Block::MoveBlockLeft()
{	
	// Check for Block Collisions
	for (auto i : cells[rotationState])
	{
		if (CheckCollision({ i.row + this->rowOffset, i.column + this->colOffset -1 }))
		{
			return;
		}
	}

	this->UpdateBlockPositionBy(0, -1);
	BoundaryCheckResult res = IsUnderBoundary();
	if (!res.isUnderBoundary)
	{
		this->UpdateBlockPositionBy(res.rowValidation, res.columnValidation);
	}
}

void Block::MoveBlockRight()
{	
	// Check for Block Collisions
	for (auto i : cells[rotationState])
	{
		if (CheckCollision({ i.row + this->rowOffset, i.column + this->colOffset + 1}))
		{
			return;
		}
	}


	this->UpdateBlockPositionBy(0, 1);
	BoundaryCheckResult res = IsUnderBoundary();	
	if (!res.isUnderBoundary)
	{
		this->UpdateBlockPositionBy(res.rowValidation, res.columnValidation);
	}
}

void Block::MoveBlockDown()
{	

	// Check for Block Collisions
	for (auto i : cells[rotationState])
	{
		if (CheckCollision({ i.row + this->rowOffset + 1, i.column+ this->colOffset}))
		{	
			if (!GameManager::GetInstance()->GetGridRef()->IsRowEmpty(1))
			{
				GameManager::GetInstance()->SetGameOver();
				return;
			}
			GameManager::GetInstance()->GetNewBlock();
			GameManager::GetInstance()->GetGridRef()->RowCompletionCheck();		
			return;
		}
	}
	
	
	

	this->UpdateBlockPositionBy(1, 0);

	// Since we are moving in downward direction only, therefore moving block down will boundary check for best valid position in bottom direction (Though the function checks for all 4 corners)
	BoundaryCheckResult res = IsUnderBoundary(); 
	if (!res.isUnderBoundary)
	{
		this->UpdateBlockPositionBy(res.rowValidation, res.columnValidation);
		GameManager::GetInstance()->GetNewBlock();
		GameManager::GetInstance()->GetGridRef()->RowCompletionCheck();
	}
}

void Block::InitiateGridChange()
{	
	
	std::vector<Position> tiles = this->cells[rotationState];

	// Overwrite the grid map with data of the Block Data.
	for (auto i : tiles)
	{	
		GameManager::GetInstance()->GetGridRef()->UpdateGrid(i.row + this-> rowOffset, i.column + this->colOffset, this->id);

		// Displaying the Changed Grid
		//GameManager::GetInstance()->GetGridRef()->Print();
	}

}




void Block::Rotate()
{	
	int maxRotationStates = this->cells.size();
	int temp_RotationState = (rotationState + 1) % maxRotationStates;
	for (auto i : cells[temp_RotationState])
	{
		if (CheckCollision({i.row + this->rowOffset, i.column + this->colOffset}))
		{   
			return;
		}
	}

	rotationState = ++rotationState % maxRotationStates;

	BoundaryCheckResult res = IsUnderBoundary();
	if (!res.isUnderBoundary)
	{
		this->UpdateBlockPositionBy(res.rowValidation, res.columnValidation);
	}

}

void Block::UpdateBlockPositionBy(const int8_t rows, const int8_t cols)
{	
	this->rowOffset += rows;
	this->colOffset += cols;

}

void Block::UpdateBlockPositionTo(const int8_t rows, const int8_t cols)
{
	this->rowOffset = rows;
	this->colOffset = cols;
}

BoundaryCheckResult Block::IsUnderBoundary()
{	
	BoundaryCheckResult res;
	int8_t ColumnOffset = 0;	
	int8_t RowOffset = 0;	

	// Check for the block which crossed the boundary farthest
	for (auto pos : cells[rotationState])
	{	
		// Checkin for Columns
		// Across the Left Boundary
		if (pos.column + this->colOffset < 0)
		{	
			int8_t t = pos.column + this->colOffset;	
			ColumnOffset = std::min(t , ColumnOffset);
			res.isUnderBoundary = false;
		}

		// Across the right Boundary
		if	(pos.column + this->colOffset > Grid::numCols - 1)
		{
			int8_t t = pos.column + this->colOffset;
			ColumnOffset = std::max(t, ColumnOffset);
			res.isUnderBoundary = false;
		}

		// Checkin for Rows
		// Across the Top Boundary
		if (pos.row + this->rowOffset < 0)
		{
			int8_t t = pos.row + this->rowOffset;
			RowOffset = std::min(t, RowOffset);
			res.isUnderBoundary = false;
		}
		// Across the Bottom Boundary
		if( pos.row + this->rowOffset > Grid::numRows - 1)
		{
			int8_t t = pos.row + this->rowOffset;
			RowOffset = std::max(t, RowOffset);
			res.isUnderBoundary = false;
		}
	}

	// if Block has crossed the boundary, calculate the Validation Moves by row and column for keep the Block under boundary
	if (!res.isUnderBoundary)
	{	
		if (ColumnOffset < 0)
		{
			ColumnOffset = -1 * ColumnOffset;
		}
		else if (ColumnOffset > Grid::numCols - 1)
		{
			ColumnOffset = (Grid::numCols - 1) - ColumnOffset;
		}

		if (RowOffset < 0)	
		{
			RowOffset = -1 * RowOffset;	
		}
		else if (RowOffset > Grid::numRows - 1)	
		{
			RowOffset = (Grid::numRows - 1) - RowOffset;
		}

		res.columnValidation = ColumnOffset;
		res.rowValidation = RowOffset;

	}
	return res;
}

bool Block::CheckCollision(Position position)
{
	
	int gridId = GameManager::GetInstance()->GetGridRef()->GetCellIndex(position.row, position.column);	// Get the color Index at the required slot

	if (gridId == -1) // Grid Id is -1 outside its bounds
	{
		std::cout << "ERROR: Invalid Row-Column Index while checking collision" << std::endl;
		return false; // Skipping Collision Check
	}

	if (gridId != 0) //Grid Id is 0 for unoccupied cells
	{
		return true;
	}

	if (gridId == this->id) // If grid id is similar to the currentBlock's...
	{
		for (auto i : cells[rotationState]) // Check whether that cell exists in that block
		{
			if ((i.row + this->rowOffset, i.column + this->colOffset) != (position.row, position.column)) // If it doesn't then we have a collision from similar block used in past
			{
				return true;
			}
		}
	}
	else
	{	
		if (gridId != 0)
		{
			return true;
		}
	}



	return false;
}
