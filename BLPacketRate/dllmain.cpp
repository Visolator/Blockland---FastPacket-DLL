// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <stdio.h>
//#include <cstdlib>
#include "detours/detours.h"
#include "torque.hpp"

typedef char(*NetConnection__getFinishedInitialGhostFn)(int* wat);
MologieDetours::Detour<NetConnection__getFinishedInitialGhostFn>* Detour__getFinishedInitialGhost = NULL;

char Hooked__getFinishedInitialGhost(int* wat)
{
	return 0;
}

bool init()
{
	if (!torque_init())
		return false;

	//1997 - 005CA5F0, 1986 - 005CA5D0
	Detour__getFinishedInitialGhost = new MologieDetours::Detour<NetConnection__getFinishedInitialGhostFn>((NetConnection__getFinishedInitialGhostFn)0x5CA650, Hooked__getFinishedInitialGhost);
	if (!Detour__getFinishedInitialGhost)
	{
		Printf("  Oh no.. ghost failed to init..");
		return false;
	}

	Printf("PacketRate.dll | Loaded successfully");

	return true;
}

bool deinit()
{
	if (Detour__getFinishedInitialGhost != NULL)
	{
		delete Detour__getFinishedInitialGhost;
	}

	return true;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
		case DLL_PROCESS_ATTACH:
			return (BOOL)init();

		case DLL_PROCESS_DETACH:
			return (BOOL)deinit();
			break;
    }

    return TRUE;
}

extern "C" void __declspec(dllexport) __cdecl placeholder(void) { }
