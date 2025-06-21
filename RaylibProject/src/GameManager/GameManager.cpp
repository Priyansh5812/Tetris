#include "GameManager.h"

#pragma once
#include "Blocks.cpp"
GameManager::GameManager()	
{	
	// Initializing grid reference
	this->grid = new Grid();



	// Initializing the blocks	
	blocks = { new IBlock(), new JBlock(), new LBlock(), new OBlock(), new SBlock(), new TBlock(), new ZBlock()};
	cachedBlock = std::make_pair(nullptr, -1);
	inputManager = InputManager();	
	uiManager = UIManager();
	GetNewBlock();

	blockMoveDownFrequency = 1.0f; // secs
	blockMoveDownFrequency_Bkp = blockMoveDownFrequency;
}


Grid* GameManager::GetGridRef()
{
	return grid;
}


Block& GameManager::GetRandomBlock()
{	
	Block* block = NULL;
	if (cachedBlock.first != nullptr)
	{
		block = cachedBlock.first;
		
	}
	else
	{
		int randomIndex = rand() % blocks.size();
		block = blocks[randomIndex];
		blocks.erase(blocks.begin() + randomIndex);
	}

	CacheBlock();

	return *block;

}

void GameManager::CacheBlock()
{	
	// Clear the memory from last cache
	cachedBlock.first = nullptr;
	cachedBlock.second = -1;

	// Get the block
	cachedBlock.second = rand() % blocks.size();
	cachedBlock.first = blocks[cachedBlock.second];

	// Remove the block from the blocks array
	blocks.erase(blocks.begin() + cachedBlock.second);

	std::cout << "Block Cached : " << cachedBlock.first->GetBlockId() << std::endl;
}


Block& GameManager::GetCurrentBlock()
{
	return *currentBlock;
}

void GameManager::Draw()
{	
	this->grid->Draw();
	this->currentBlock->Draw(0.5f, 0.5f);
	this->uiManager.Draw();

}

void GameManager::Update()
{	
	if(!isGameOver)
		MoveBlockDownByTime();

	inputManager.PollEvents();
	this->Draw();
}



void GameManager::MoveBlockDownByTime()
{	
	blockMoveDownFrequency -= GetFrameTime();

	if (blockMoveDownFrequency <= 0.0f)
	{
		this->currentBlock->MoveBlockDown();
		blockMoveDownFrequency = blockMoveDownFrequency_Bkp;
	}
}

void GameManager::GetNewBlock()
{	
	std::cout << "New Block Retrived" << std::endl;
	Block* prevBlock = currentBlock;
	srand(time(0)); // seeding random number generation
	currentBlock = &GetRandomBlock();
	
	if(prevBlock)
	{	
		prevBlock->InitiateGridChange();
		RestoreBlock(*prevBlock);
		prevBlock = NULL;
	}
}

void GameManager::RestoreBlock(Block& block)
{
	block.ResetBlock();
	blocks.push_back(&block);
}

void GameManager::ValidateRows()
{
	int rowNo = Grid::numRows - 1;
	int i;
	int j = i = -1;
	bool anyRowFilled = false;	
	while (rowNo <= 0)
	{	
		bool isEmptyRow = false;
		int colNo = Grid::numCols - 1;
		rowNo--;
	}

}

void GameManager::SetGameOver()
{	
	std::cout << "Game Over !!!" << std::endl;
	this->isGameOver = true;
}

bool GameManager::GetGameOver()
{
	return this->isGameOver;
}

 Block* GameManager::GetCachedBlock()	
{	
	return cachedBlock.first;
}

 UIManager& GameManager::GetUIManager() 
 {		
	 return this->uiManager;
 }
	

#pragma region Singleton

GameManager* GameManager::m_instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (GameManager::m_instance == nullptr)
	{
		GameManager::m_instance = new GameManager();
	}
	return GameManager::m_instance;
}


void GameManager::Cleanup()
{
	free(cachedBlock.first);
	free(grid);
	free(previousBlock);
	free(currentBlock);
	free(GameManager::m_instance);
	std::cout << "Resources released by GameManager" << std::endl;
}


GameManager::~GameManager()
{
	// release any allocated resources here.
	std::cout << "Resources released by GameManager" << std::endl;
}
#pragma endregion



#pragma region InputManager

void InputManager::PollEvents()
{	
	 if(!GameManager::GetInstance()->GetGameOver())
		DetermineInput(GetKeyPressed());	
}


void InputManager::DetermineInput(int keyCode)
{
	switch (keyCode)
	{
	case KEY_LEFT:	
		GameManager::GetInstance()->GetCurrentBlock().MoveBlockLeft();
		break;
	
	case KEY_RIGHT:	
		GameManager::GetInstance()->GetCurrentBlock().MoveBlockRight();
		break;
	
	case KEY_DOWN :
		GameManager::GetInstance()->GetCurrentBlock().MoveBlockDown();	
		break;

	case KEY_UP:
		GameManager::GetInstance()->GetCurrentBlock().Rotate();
		break;
	default:

		break;
	}
}


#pragma endregion


