#include "UIManager.h"
#include "GameManager.h"

UIManager::UIManager() : mainFont(LoadFontEx("Assets/Fonts/Satoshi-Variable.ttf", 64, 0, 0)), score(0)
{
	LoadFonts();
	SetScoreStat();
}


void UIManager::Draw()
{	
	if (!wasFontLoadingSuccess)
		return;
	this->DrawStats();
	Block* cachedBlock = GameManager::GetInstance()->GetCachedBlock();
	if (cachedBlock != nullptr)
	{	
		switch (cachedBlock->GetBlockId())
		{
			case 3: // I Block
				cachedBlock->Draw(8.5f, 9.8f);
				break;
			case 4:// O Block
				cachedBlock->Draw(8.5f, 9.2f);
				break;
			default: // Other Blocks
				cachedBlock->Draw(8.9f, 9.1f);
				break;
		}

	}
}

void UIManager::LoadFonts()
{
	wasFontLoadingSuccess = IsFontValid(mainFont);

	if (wasFontLoadingSuccess)
		SetTextureFilter(mainFont.texture, TEXTURE_FILTER_BILINEAR);
}

void UIManager::DrawStats()
{	
	// Score Title Draw
	DrawTextEx(mainFont, "Score", { 355,15 }, 45, 0.5f, WHITE);
	DrawRectangleRounded({ 320 , 60, 170, 60 }, 1.0f, 6, lightBlue);
	DrawTextEx(mainFont, &scoreText[0], { 335 , 69 }, 40, 0.5f, WHITE);
	DrawTextEx(mainFont, "Next", {360,200}, 45, 0.5f, WHITE);
	DrawRectangleRounded({ 320 , 250, 170, 120 }, 0.25f, 6, lightBlue);
	

	if(GameManager::GetInstance()->GetGameOver())
		DrawTextEx(mainFont, "GAME OVER", { 330, 470 }, 30, 0.5f, WHITE);
	
}

#pragma region Stat Modifiers
void UIManager::AddScore(int score)
{	
	
	this->score += score;
	std::cout << "Score Updated After : " << this->score  << std::endl;
	// Update the score stat once score gets updated
	SetScoreStat();
}

void UIManager::SetScoreStat()
{	
	std::cout << "Score Updated Before : " << this->scoreText << std::endl;
	std::string t_score = std::to_string(score);
	scoreText = "";
	for (int i = 0; i < 6 - t_score.length(); i++)
	{
		scoreText += "0";
	}

	scoreText += t_score;
	std::cout << "Score Updated After : " << this->scoreText << std::endl;
}
#pragma endregion