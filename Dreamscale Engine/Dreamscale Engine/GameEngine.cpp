#include "GameEngine.h"

using namespace dse;

GameEngine::GameEngine() :
	m_tmx(new TmxHandler())
{
	std::cout << "class:	GameEngine:	Constructed!" << std::endl;
}

void dse::GameEngine::Update()
{
	bool mouse_inside_a_window = false;

	m_window.create(sf::VideoMode(1024, 768), "DreamScale Engine");

	while (m_window.isOpen())
	{
		sf::Event event;
		// Poll events for this window
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					m_tmx->ResetVector();
					m_tmx->LoadMap(m_tmx->map_vector[m_tmx->GetTmxNames()[0]]);
					m_tmx->LoadObjects(*m_tmx->map_vector[m_tmx->GetTmxNames()[0]]);
					
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					m_tmx->ResetVector();
					m_tmx->LoadMap(m_tmx->map_vector[m_tmx->GetTmxNames()[1]]);
					m_tmx->LoadObjects(*m_tmx->map_vector[m_tmx->GetTmxNames()[1]]);
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					//LuaTester.StartLuaScript();
				}
			}
			if (event.type == sf::Event::MouseEntered)
				mouse_inside_a_window = true;
			if (event.type == sf::Event::MouseLeft)
				mouse_inside_a_window = false;
		}

		m_window.clear();

		m_tmx->RefreshObjects();
		
		m_obj_handler.Update();
		m_obj_handler.DrawObjects(m_window);
		m_tmx->DrawMap(m_window);
		m_tmx->DrawObjects(m_window);

		m_window.display();
	}
}

TmxHandler* dse::GameEngine::GetTmxHandler() const
{
	return m_tmx;
}

GameEngine::~GameEngine()
{
	std::cout << "class:	GameEngine:	Destructed!" << std::endl;
}