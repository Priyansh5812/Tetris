#include <iostream>
#include <string>
#include <raylib.h>
#include <Colors.h>
#pragma once 

class UIManager
{
	
public :
	UIManager();
	void Draw();
	void AddScore(int value);
private:
	bool wasFontLoadingSuccess = false;
	void LoadFonts();
	void DrawStats();
	void SetScoreStat();
	long score;
	std::string scoreText;
	Font mainFont;


};


