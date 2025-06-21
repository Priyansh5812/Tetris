#pragma once
#include <raylib.h>
#include "GameManager.h"
int main()
{	
	Color BGColor = { 44, 44, 127, 255 };

	InitWindow(500, 620, "Tetris");
	SetTargetFPS(120);

	GameManager* mgr = GameManager::GetInstance();
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BGColor);
		mgr->Update();	
		EndDrawing();
	}

	CloseWindow();
	
	GameManager::GetInstance()->Cleanup();

	return 0;
}
// GameManager::blocks was getting erased from begining upon getting a random block
