#pragma once
#include "Character.h"

class Shot;

class Player : public Character
{
public:
	Player();
	virtual~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Shot* CreateShot();

private:
	void Move();

	void Jump();

};

