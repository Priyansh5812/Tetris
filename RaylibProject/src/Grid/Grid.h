#pragma once
#include <iostream>
#include <unordered_map>
#include "raylib.h"
class Grid
{
public :
	Grid();
	void InitializeGrid();
	void Print();
	void Draw();
	int GetCellIndex(int row, int column);
	void UpdateGrid(int8_t row, int8_t column, int8_t id);
	void RowCompletionCheck();
	bool IsRowEmpty(int row);
	bool IsRowFilled(int row);
    bool IsCellEmpty(int row, int column);
	static const __int8 numRows = 20;
	static const __int8 numCols = 10;
	static const __int8 cellSize = 30;
	static const __int8 cellPadding = 2;


private:
		void ClearAndDescendRows(int& firstNonEmptyRowIndex);
		void ClearRow(int rowNo);
		void DescendRows(int bottomRow, int topRow);
		//-----------------------------------

		int grid[Grid::numRows][Grid::numCols];

		//-----------------------------------

		void DrawBackground();
};

