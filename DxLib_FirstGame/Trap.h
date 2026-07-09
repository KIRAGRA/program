#pragma once
class Trap
{
public:
	Trap();
	~Trap();


	void Init();
	void End();
	void Update();
	void Draw();

	//使用するグラフィックの設定
	void SetHandle(int handle) { m_graphHandle = handle;  }

	//当たり判定実装用
	float GetColCenterX() const;
	float GetColCenterY() const;
	float GetRadius()const;

private:
	int m_graphHandle;

	//開始待ち
	int m_waitFrame;


	float m_x;
	float m_y;

	float m_vecX;
	float m_vecY;

	//回転速度
	double m_angle;

};

