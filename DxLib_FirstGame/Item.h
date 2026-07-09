#pragma once

class Item
{
public:
	Item();
	~Item();

	void Init();
	void End();
	void Update();
	void Draw();

	//使用するグラフィックのハンドルを受けとる
	void SetHandle(int handle) { m_graph = handle; }

	//このアイテムが存在するか
	bool IsExist() const { return m_isExist; }

	float GetColCenterX() const { return m_x; }
	float GetColCenterY() const { return m_y; }
	float GetRadius()const { return 20; }

	//プレイヤーと当たった時の処理
	void OnHit();

private:
	//グラフィックハンドル
	int m_graph;

	//位置情報
	int m_x;
	int m_y;
	//アニメーション関連
	int m_animFrame;

	//存在しているか
	bool m_isExist;

};

