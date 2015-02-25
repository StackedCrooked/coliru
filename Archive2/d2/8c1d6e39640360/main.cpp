// sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <conio.h>
#include "ZT.h"



int WINAPI ZoneTriggerCallbackProc(int MessageType, ZT_TRIG_STRUCT *trigInfo)
{

	switch (MessageType) {

	case 0:		//Trig from a Zone Trigger hot spot
		printf("Got a trig from spot #%d : %s\r\n", trigInfo->SpotIndex, trigInfo->SpotName);
		break;

	case 1:		//Zone Trigger has started and is notifying us that it is ready
		printf("Zone Trigger issued a ready notification.\r\n");
		break;

	case 2:		//Zone Trigger is shutting down
		printf("Zone Trigger has left the building.\r\n");
		break;

	case 3:		//Hot spot scheme updated, you might want to re-enumerate the hot spots
		printf("Zone Trigger's hot spots have been updated.\r\n");
		break;


	}

	return 0;
}


int main(int argc, char* argv[])
{

    HMODULE hZT = LoadLibrary("ZTcom.dll");
	if (hZT == NULL) {
		printf("Can't load Zone Trigger interface, exiting...");
		_getch();
		return 0;
	}

	//Map all DLL functions...
	f_ZT_Init					ZT_Init				= (f_ZT_Init) GetProcAddress(hZT, "ZT_Init");
	f_ZT_GetVersion				ZT_GetVersion		= (f_ZT_GetVersion) GetProcAddress(hZT, "ZT_GetVersion");
	f_ZT_CleanUp				ZT_CleanUp			= (f_ZT_CleanUp) GetProcAddress(hZT, "ZT_CleanUp");
	f_ZT_ShutDown				ZT_ShutDown			= (f_ZT_ShutDown) GetProcAddress(hZT, "ZT_ShutDown");
	f_ZT_SetCallbackProc 		ZT_SetCallbackProc 	= (f_ZT_SetCallbackProc) GetProcAddress(hZT, "ZT_SetCallbackProc");
	f_ZT_EnableTriggers 		ZT_EnableTriggers	= (f_ZT_EnableTriggers) GetProcAddress(hZT, "ZT_EnableTriggers");
	f_ZT_EnumerateHotSpots 		ZT_EnumerateHotSpots= (f_ZT_EnumerateHotSpots) GetProcAddress(hZT, "ZT_EnumerateHotSpots"); 
	f_ZT_GetSpotType			ZT_GetSpotType		= (f_ZT_GetSpotType) GetProcAddress(hZT, "ZT_GetSpotType");
	f_ZT_GetCurrentPattern		ZT_GetCurrentPattern= (f_ZT_GetCurrentPattern) GetProcAddress(hZT, "ZT_GetCurrentPattern");
	f_ZT_SetCurrentPattern		ZT_SetCurrentPattern= (f_ZT_SetCurrentPattern) GetProcAddress(hZT, "ZT_SetCurrentPattern");
	f_ZT_GetCurrentPercentage	ZT_GetCurrentPercentage= (f_ZT_GetCurrentPercentage) GetProcAddress(hZT, "ZT_GetCurrentPercentage");
	f_ZT_GetSensitivity 		ZT_GetSensitivity	= (f_ZT_GetSensitivity) GetProcAddress(hZT, "ZT_GetSensitivity");
	f_ZT_SetSensitivity 		ZT_SetSensitivity	= (f_ZT_SetSensitivity) GetProcAddress(hZT, "ZT_SetSensitivity");
	f_ZT_TakePicture			ZT_TakePicture		= (f_ZT_TakePicture) GetProcAddress(hZT, "ZT_TakePicture");
	f_ZT_RecordStart			ZT_RecordStart		= (f_ZT_RecordStart) GetProcAddress(hZT, "ZT_RecordStart");
	f_ZT_RecordStop				ZT_RecordStop		= (f_ZT_RecordStop) GetProcAddress(hZT, "ZT_RecordStop");

	int check;

	check = ZT_Init();
		//If check == 0, we are connected to Zone Trigger
		//Otherwise, dont' despair, maybe this application has started before Zone Trigger, and ZT will be started soon.
		//If ZT starts later, it will issue a notification using the ZoneTriggerCallbackProc, so listen for that.

	DWORD version = ZT_GetVersion();	

	ZT_SetCallbackProc(ZoneTriggerCallbackProc);
		//Listen to what ZT has to say, if you care.
		//All triggers will come in the ZoneTriggerCallbackProc, and also various status messages.


	//Enumerate current spots in Zone Trigger
	int i=0;
	char SpotName[32];
	int SpotType;
	check = ZT_EnumerateHotSpots(i, SpotName, &SpotType);
	while (check == 0) {
		float sensitivity = ZT_GetSensitivity(i);
		printf("Zone Trigger spot: %s   Sensitivity: %0.1f%%\r\n", SpotName, sensitivity*100);
		check = ZT_EnumerateHotSpots(++i, SpotName, &SpotType);
	}


	//check = ZT_EnableTriggers(true);


	char path[256];

	//check = ZT_TakePicture(0, path);

/*
	check = ZT_RecordStart(0, path);
	if (check == 0) printf("Started recording in file %s\r\n", path);
	Sleep(5000);
	ZT_RecordStop(0);
*/

	//Main loop. Wait for messages from Zone Trigger to the ZoneTriggerCallbackProc
	printf("Press any key to exit\r\n");
	MSG msg = {0};
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
		if (_kbhit() != 0) break;
	}

	//check = ZT_ShutDown();


	ZT_CleanUp();


	printf("Done.");

	return 0;
}