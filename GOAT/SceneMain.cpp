#include "SceneMain.h"
#include "Input.h"

SceneMain::SceneMain():
	m_pInput(nullptr)
{
}

SceneMain::~SceneMain()
{
	delete m_pInput;
}

void SceneMain::Init()
{
	m_pInput = new Input;
	m_pInput->Init();
}

void SceneMain::Update()
{
	m_pInput->Update();
}

void SceneMain::Draw()
{
	m_pInput->Draw();
}
