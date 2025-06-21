#include "Grid.h"
#include "Colors.h"
#include "GameManager.h"
Grid::Grid()
{	
	InitializeGrid();
}

void Grid::InitializeGrid()
{
	std::cout << "Initializing Grid" << std::endl;

	//Initializing the Array to be zero 
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grid[i][j] = 0;
		}

	}
}


void Grid::Print()
{
	for (int i = 0;i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}

}


void Grid::Draw()
{
	DrawBackground();	
}


void Grid::DrawBackground()
{
	for (int i = 0;i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			int cellValue = grid[i][j];
			DrawRectangle(cellSize * (j+0.5f), cellSize * (i+0.5f), cellSize - cellPadding, cellSize - cellPadding, GetCellColors()[cellValue]);
		}

	}
}

void Grid::UpdateGrid(int8_t row, int8_t column , int8_t id)
{
	this->grid[row][column] = id;
}

int Grid::GetCellIndex(int row, int column)
{
	if (row < 0 || row >= numRows)
		return -1;

	if (column < 0 || column >= numCols)
		return -1;

	return this->grid[row][column];
}

void Grid::RowCompletionCheck()
{
	int firstNonEmptyRowIndex = -1;	

	for (int i = 0; i < numRows; i++)
	{	
		if (!IsRowEmpty(i))
		{
			firstNonEmptyRowIndex = i;
			break;
		}
	}

	if (firstNonEmptyRowIndex != -1)
	{
		std::cout << "Row Completion Check Acted = " << firstNonEmptyRowIndex << std::endl;
		ClearAndDescendRows(firstNonEmptyRowIndex);
	}
	
}





void Grid::ClearAndDescendRows(int& firstNonEmptyRowIndex)
{	
	int tfner = firstNonEmptyRowIndex;
	for (int i = Grid::numRows - 1; i >= tfner; i--)
	{
		if (IsRowFilled(i))
		{	
			std::cout << "Filled Row detected = " << i << std::endl;
			GameManager::GetInstance()->GetUIManager().AddScore(10);
			ClearRow(i);	
			DescendRows(i - 1, tfner);
			//Clear the topmost row since that row was not cleared and shifted down
			ClearRow(tfner);	
			tfner++;
			i++; // Rechecking the same row (otherwise it will get skipped)	
			
		}
	}
}

void Grid::ClearRow(int RowNo)
{
	for (int i = 0; i < Grid::numCols; i++)
	{
		grid[RowNo][i] = 0;
	}
}

void Grid::DescendRows(int bottomRow, int topRow)
{
	int b = bottomRow;
	int t = topRow;

	while (b >= t)
	{	
		for (int i = 0; i < Grid::numCols; i++)
		{
			grid[b + 1][i] = grid[b][i];
		}
		b--;
	}
}



bool Grid::IsRowEmpty(int row)
{	
	bool isEmpty = true;
	for (int i = 0; i < numCols; i++)
	{
		isEmpty = (isEmpty && grid[row][i] == 0);
	}

	return isEmpty;
}

bool Grid::IsRowFilled(int row)
{
	bool isFilled = true;
	for (int i = 0; i < numCols; i++)
	{
		isFilled = (isFilled && grid[row][i] != 0);
	}
	return isFilled;	
}

