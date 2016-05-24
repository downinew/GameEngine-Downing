#ifndef _ENGINE_H
#define _ENGINE_H

#ifndef _WINDOWS_
	#include <Windows.h>
#endif

#ifndef _MAP_
	#include <map>
#endif

#ifndef _CONTEXT_H
#include "context.h"
#endif


//Forward Declaration
enum SystemType;

class Game;
class System;


enum EngineState
{
	Invalid,
	Constructing,
	Initializing,
	Running,
	ShuttingDown,
	Destroying
};



class Engine
{
public:
	Engine();
	~Engine();

	int RunLoop();

	//void* operator new(size_t size);
	//void operator delete(void* pDelete);


	static EngineState GetEngineState() { return m_EngineState; }

private:

	int Initialize();
	int Draw(const Context& context);
	int Update(const Context& context);
	int Shutdown();


	//Add a core system to the engine
	int AddSystem(System* psys);

	//Retrieve a core system from engine
	template<typename T>
	T* GetSystem(SystemType sysType)
	{
		T* psys = static_cast<T*>(m_MapSystems[sysType]);
		if (!psys)
		{
			//Logger::Log("System is not valid!");
			return nullptr;
		}
		return psys;
	}

	//Create the game instance 
	Game* CreateGame();

	std::map<SystemType, System*> m_MapSystems;
	static EngineState m_EngineState;


};

#endif