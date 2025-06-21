#pragma once
#include<iostream>
#include <Grid.h>
#include <Block.h>
#include <vector>
#include <random>
#include <UIManager.h>
#include <utility>
class InputManager
{

public:
	void PollEvents();
	void DetermineInput(int keyCode);

};



class GameManager
{
public:
	static GameManager* GetInstance();
	
	Grid* GetGridRef();
	Block& GetRandomBlock();	
	Block& GetCurrentBlock();
	void Update();
	void Cleanup();
	void MoveBlockDownByTime();
	void GetNewBlock();
	void ValidateRows();
	void SetGameOver();
	bool GetGameOver();
	Block* GetCachedBlock();
	UIManager& GetUIManager() ;
private:

	static GameManager* m_instance;
	GameManager(); // Constructor can't be accessed outside of the class
	GameManager(const GameManager&) = delete; // It can't be cloned
	void operator=(const GameManager&) = delete; // It can't be copied
	~GameManager();

	//------------------------------

	Grid* grid;
	std::vector<Block*> blocks;
	Block* previousBlock = NULL;
	Block* currentBlock = NULL;
	std::pair<Block*,int> cachedBlock;
	void CacheBlock();
	float blockMoveDownFrequency = 0.0f;
	float blockMoveDownFrequency_Bkp = 0.0f;
	bool isGameOver = false;
	void Draw();
	void RestoreBlock(Block& block);

	InputManager inputManager;
	UIManager uiManager;

};




