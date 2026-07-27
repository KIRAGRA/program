#pragma once
#include "Vec2.h"
class Shot
{
public:
		Shot();
		virtual~Shot();

		void Init();
		void Update();
		void Draw();

public:
	void SetInfo(const Vec2& pos, bool isRight);

	Vec2 GetPos() const { return m_pos; }
private:
	int m_handle;//玉の画像
	Vec2 m_pos;//弾の位置
	Vec2 m_move;//移動量
};

