#include "GameEngine.h"
#include "LuaBridge.h"

using namespace dse;

GameEngine::GameEngine() :
	m_tmx(new TmxHandler())
{
	std::cout << "class:	GameEngine:	Constructed!" << std::endl;
}

GameEngine::~GameEngine()
{
	std::cout << "class:	GameEngine:	Destructed!" << std::endl;
}

void dse::GameEngine::Update()
{
	dse::LuaBridge lua_bridge;
	lua_bridge.BindLua();
	m_tmx->ParseAllMaps();

	sf::Clock clock;
	const int NUM_FRAMES_PER_SECOND = 60;
	const float UPDATE_INTERVAL = 1.0f / (NUM_FRAMES_PER_SECOND);
	float current_time = 0.0f;

	bool mouse_inside_a_window = false;
	bool key_is_pressed = false;

	m_window.create(sf::VideoMode(1024, 768), "DreamScale Engine");

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();
		current_time += dt.asSeconds();

		sf::Event event;

		key_is_pressed = false;

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
					lua_bridge.StartLuaScript("test.lua");
				}
			}
			if (event.type == sf::Event::MouseEntered)
				mouse_inside_a_window = true;
			if (event.type == sf::Event::MouseLeft)
				mouse_inside_a_window = false;
		}

		if (current_time >= UPDATE_INTERVAL) //Update intervals
		{
			//Lua Scripts that updates movement
			//-_
			//lua_bridge.StartLuaScript("movement");
			m_test_object.SetSize(50, 50);
			m_test_object.SetPosition(m_position_temp++, m_position_temp++);

			current_time -= UPDATE_INTERVAL;
		}

		m_window.clear();

		m_tmx->RefreshObjects();
		
		m_tmx->DrawMap(m_window);
		m_tmx->DrawObjects(m_window);
		m_test_object.Draw(&m_window);

		m_window.display();
	}
}

TmxHandler* dse::GameEngine::GetTmxHandler() const
{
	return m_tmx;
}