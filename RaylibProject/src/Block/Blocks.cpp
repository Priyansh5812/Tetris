#pragma once
#include "Position.h"
#include "Block.h"

class LBlock : public Block	
{
public:
	LBlock()  : Block()
	{	
		
		this->id = 1;
		//------------------------

		cells[0] = { Position(0,2), Position(1,0), Position(1,1), Position(1,2) };
		cells[1] = { Position(0,1), Position(1,1), Position(2,1), Position(2,2) };
		cells[2] = { Position(2,0), Position(1,0), Position(1,1), Position(1,2) };
		cells[3] = { Position(0,0), Position(0,1), Position(1,1), Position(2,1) };

		this->ResetBlock();

	}

	void ResetBlock() override
	{	
		
		this->rotationState = 0;
		this->UpdateBlockPositionTo(0, 3);
	}

};


class JBlock : public Block
{
public:
	JBlock() : Block()
	{	

		
		this->id = 2;
		
		//-------------------------------

		cells[0] = { Position(0,0), Position(1,0), Position(1,1), Position(1,2) };
		cells[1] = { Position(0,1), Position(0,2), Position(1,1), Position(2,1) };
		cells[2] = { Position(1,0), Position(1,1), Position(1,2), Position(2,2) };
		cells[3] = { Position(0,1), Position(1,1), Position(2,0), Position(2,1) };
		ResetBlock();
	}

	void ResetBlock() override
	{	
		this->rotationState = 0;		
		this->UpdateBlockPositionTo(0, 3);
	}
};


class IBlock : public Block
{
public:
	IBlock() : Block()
	{
		this->id = 3;

		//---------------------------

		cells[0] = { Position(1,0), Position(1,1), Position(1,2), Position(1,3) };
		cells[1] = { Position(0,2), Position(1,2), Position(2,2), Position(3,2) };

		//cells[2] = { Position(2,0), Position(2,1), Position(2,2), Position(2,3) };
		//cells[3] = { Position(0,1), Position(1,1), Position(2,1), Position(3,1) };
		
		ResetBlock();
	}

	void ResetBlock() override
	{	
		this->rotationState = 0;	
		UpdateBlockPositionTo(-1, 3);
	}
};

class OBlock : public Block
{
public:
	OBlock() : Block()
	{
		this->id = 4;

		//--------------------------

		cells[0] = { Position(0,0), Position(0,1), Position(1,0), Position(1,1) };
		//cells[3] = cells[2] = cells[1] = cells[0];
		this->ResetBlock();
	}

	void ResetBlock() override
	{	
		this->rotationState = 0;
		UpdateBlockPositionTo(0, 4);
	}
};

class SBlock : public Block
{
public:
	SBlock() : Block()
	{
		this->id = 5;

		//----------------------------

		cells[0] = { Position(0,1), Position(0,2), Position(1,0), Position(1,1) };
		cells[1] = { Position(0,1), Position(1,1), Position(1,2), Position(2,2) };
		cells[2] = { Position(1,1), Position(1,2), Position(2,0), Position(2,1) };
		cells[3] = { Position(0,0), Position(1,0), Position(1,1), Position(2,1) };
		this->ResetBlock();
	}

	void ResetBlock() override
	{	
		this->rotationState = 0;
		this->UpdateBlockPositionTo(0, 3);
	}

};

class TBlock : public Block
{
public:
	TBlock() : Block()
	{
		this->id = 6;

		//--------------------------

		cells[0] = { Position(0,1), Position(1,0), Position(1,1), Position(1,2) };
		cells[1] = { Position(0,1), Position(1,1), Position(1,2), Position(2,1) };
		cells[2] = { Position(1,0), Position(1,1), Position(1,2), Position(2,1) };
		cells[3] = { Position(0,1), Position(1,0), Position(1,1), Position(2,1) };
		this->ResetBlock();
	}

	void ResetBlock() override
	{	
		this->rotationState = 0;	
		this->UpdateBlockPositionTo(0, 3);
	}

};

class ZBlock : public Block
{
public:
	ZBlock() : Block()
	{
		this->id = 7;

		cells[0] = { Position(0,0), Position(0,1), Position(1,1), Position(1,2) };
		cells[1] = { Position(0,2), Position(1,1), Position(1,2), Position(2,1) };
		cells[2] = { Position(1,0), Position(1,1), Position(2,1), Position(2,2) };
		cells[3] = { Position(0,1), Position(1,0), Position(1,1), Position(2,0) };
		this->ResetBlock();
		
	}

	void ResetBlock() override
	{	
		this->rotationState = 0;
		this->UpdateBlockPositionTo(0, 3);
	}
};