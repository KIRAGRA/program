#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player();
	virtual~Player();

	void Init();
	void Update();
	void Draw();



};

