#include "Item.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	//グラフィックの切り取りサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//アニメーション関連の定義
	constexpr int kAnimNum = 17; //待機

	constexpr int kSingleAnimFrame = 4;	//アニメ1コマ


	constexpr int kAnimTotalFrame = kAnimNum * kSingleAnimFrame;
	//constexpr int kRunAnimTotalFrame = kRunAnimNum * kSingleAnimFrame;
}

Item::Item() :
	m_graph(-1),
	m_x(0.0f),
	m_y(0.0f),
	m_animFrame(0)
{
}

Item::~Item()
{
}

void Item::Init()
{
	m_graph = LoadGraph("image/Apple.png");
	//ランダムな位置に配置する
	m_x = GetRand(Game::kScreenWidth - kWidth);
	m_y = GetRand(Game::kScreenHeight - kHeight);

	//アニメーションが同期しないようにする
	m_animFrame = GetRand(kAnimTotalFrame - 1);

	//存在する状態から開始
	m_isExist = true;
}


void Item::End()
{
	DeleteGraph(m_graph);

}

void Item::Update()
{
	m_animFrame++;

}

void Item::Draw()
{
	int animNo = (m_animFrame % kAnimTotalFrame) / kSingleAnimFrame;
	//存在しないアイテムは描画しない
	if (!m_isExist)
	{
		return;
	}
	else
	{
		DrawRectGraph(m_x, m_y,
			animNo * kWidth, 0, kWidth, kHeight,
			m_graph, true);
	}
	DrawCircle(GetColCenterX(), GetColCenterY(), GetColor(255, 255, 255), false);

	

}

void Item::OnHit()
{
	m_isExist = false;
}
