#include "WinMain.h"

//Additional include files
#include "Engine.h"


#ifndef _STRING_H
#include "string.h"
#endif
#ifndef _IOSTREAM_H
#include "iostream.h"
#endif
#ifndef _DELETEMACROS_H
#include "deletemacros.h"
#endif

#if defined(DEBUG) | defined(_DEBUG)
int _tmain(int argc, char*argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	//Logger::Log("Starting the program");

	//Run WinMain Function
	WinMain((HINSTANCE)GetModuleHandle(NULL), 0, 0, SW_SHOW);


}
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

#if defined (DEBUG) | defined(_DEBUG)
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	//Enable run-time memory leak cheak for debug builds
	/*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(0);*/

#endif

	//Create the Engine
	Engine* pEngine = new Engine();

	//Kick off the game
	int result = pEngine->RunLoop();

	//Delete the engine
	delete pEngine;

	return result;

}
