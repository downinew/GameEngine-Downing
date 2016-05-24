#include "Engine.h"

#include "System.h"
#include "Game.h"


#ifndef _DELETEMACROS_H
#include "deletemacros.h"
#endif

EngineState Engine::m_EngineState = EngineState::Invalid;

Engine::Engine()
{
	m_EngineState = EngineState::Constructing;
}


Engine::~Engine()
{
	m_EngineState = EngineState::Destroying;
}

#pragma region Public Methods
int Engine::RunLoop()
{
	Context context;

	if (!this->Initialize())
		return 0;

	srand(GetTickCount());

	MSG msg = {};

	m_EngineState = EngineState::Running;

	while (msg.message != WM_QUIT && m_EngineState == EngineState::Running)
	{
		//CheckResize();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		this->Update(context);
		this->Draw(context);
	}

	//Logger::Log("Ending the program");
	//Logger::WriteLogFile();

	if (!this->Shutdown())
		return 0;

	return msg.wParam;
}
#pragma endregion

#pragma region Private Methods
int Engine::Initialize()
{
	m_EngineState = EngineState::Initializing;

	Game* game = CreateGame();

	if (!game)
		return false;
	
	//Add some systems



	return true;
}
int Engine::Draw(const Context& context)
{
	return true;
}
int Engine::Update(const Context& context)
{
	return true;
}
int Engine::Shutdown()
{
	m_EngineState = EngineState::ShuttingDown;

	for (std::pair<SystemType, System*> psys : m_MapSystems)
	{
		//if (!psys.second->ShutDown())
		//{
		//	//Log::Logger("Failed to shutdown system" + psys->GetSystemType());
		//	continue;
		//}

		SafeDelete(psys.second);
	}

	return true;
}


//Add a core system to the engine
int Engine::AddSystem(System* psys)
{
	auto element = m_MapSystems.insert(std::make_pair(psys->GetType(), psys));
	if (element.second)
		return true;

	return false;
}


Game* Engine::CreateGame()
{
	if (!AddSystem(new Game(GameData())))
		return nullptr;
	
	Game* game = GetSystem<Game>(SystemType::Sys_Game);
	if (!game)
		return nullptr;

	/*if (!game->Initialize())
		return nullptr;*/

	return game;
}
#pragma endregion