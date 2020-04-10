#include "detours/detours.h"
#include "torque.hpp"

BLFUNC(int, , NetConnection__getFinishedInitialGhost, DWORD* obj)
MologieDetours::Detour<NetConnection__getFinishedInitialGhostFn>* Detour_NetConnection__getFinishedInitialGhost = NULL;

int Hooked__getFinishedInitialGhost(DWORD* obj)
{
	return 1;
}

bool init()
{
	if (!torque_init())
		return false;

	//2000 - 005CA650, 1986 - 005CA5D0
	//NetConnection__getFinishedInitialGhost = (NetConnection__getFinishedInitialGhostFn)ScanFunc("\x8A\x81\xA8\x01\x00\x00", "xxxxxx"); // found wrong sig? got the same address as the patch before..

	NetConnection__getFinishedInitialGhost = (NetConnection__getFinishedInitialGhostFn)0x5CA650;
	Detour_NetConnection__getFinishedInitialGhost = new MologieDetours::Detour<NetConnection__getFinishedInitialGhostFn>(NetConnection__getFinishedInitialGhost, Hooked__getFinishedInitialGhost);
	if (NetConnection__getFinishedInitialGhost == 0 || !NetConnection__getFinishedInitialGhost)
	{
		delete Detour_NetConnection__getFinishedInitialGhost;
		Printf("PacketRate.dll | Loaded unsuccessfully (unable to resolve)");
		return false;
	}

	Printf("PacketRate.dll | Loaded successfully");

	return true;
}

bool deinit()
{
	if (Detour_NetConnection__getFinishedInitialGhost != NULL)
	{
		delete Detour_NetConnection__getFinishedInitialGhost;
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