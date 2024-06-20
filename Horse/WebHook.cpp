#include "WebHook.h"

#include<Windows.h>
#include<iostream>

std::string url = "https://discord.com/api/webhooks/1252099548902326312/TLIyiStHyc-HbAjp5RV3xHviZFigY3Sk0uK1hHYqmMLot4TtRpSlqQN2M9PytwZriKO_";
const std::string cmd_1 = "curl -i -H \"Accept: application/json\" -H \"Content-Type:application/json\" -X POST --data \"{";
const std::string closeline = "}\" ";

namespace webhookPrefix
{
    std::string contentPre = "\\\"content\\\": \\\"";
    std::string usernamePre = "\\\"username\\\": \\\"";
    std::string embedPre = "\\\"embeds\\\": [{";
    std::string embedSuf = "}]";

    std::string bodySuf = "\\\""; // would look smt like contentPre + content + bodySuf

    struct
    {
        std::string titlePre = "\\\"title\\\": \\\"";
        std::string textPre = "\\\"description\\\": \\\"";
        std::string colorPre = "\\\"color\\\": \\\"";
        std::string authorPre = "\\\"author\\\": {";
        std::string authorSuf = "}";

        struct
        {
            std::string namePre = "\\\"name\\\": \\\"";
            std::string imagePre = "\\\"icon_url\\\": \\\"";
        }author;

    }embed;
}


int sendWebHook(std::string name, std::string msg,std::string title,std::string color,std::string embedMsg)
{
    std::string username = webhookPrefix::usernamePre + name + webhookPrefix::bodySuf;
    std::string content = webhookPrefix::contentPre + msg + webhookPrefix::bodySuf;
    
    std::string newTitle = webhookPrefix::embed.titlePre + title + webhookPrefix::bodySuf;
    std::string description = webhookPrefix::embed.textPre + embedMsg + webhookPrefix::bodySuf;
    std::string newColor = webhookPrefix::embed.colorPre + color + webhookPrefix::bodySuf;

    std::string author = webhookPrefix::embed.authorPre + webhookPrefix::embed.author.namePre + "Hacky Hook Service" + webhookPrefix::bodySuf + ", " + webhookPrefix::embed.author.imagePre + "https://discohook.org/static/discord-avatar.png" + webhookPrefix::bodySuf + webhookPrefix::embed.authorSuf;

    std::string embedsettings = newTitle + ", " + description + ", " + newColor + ", " + author;
    std::string embeds = webhookPrefix::embedPre + embedsettings + webhookPrefix::embedSuf;

    std::string body;
    body = username + ", " + content + ", " + embeds;

    std::string command = cmd_1 + body + closeline + url;
    std::cout << command;

    command.insert(0, "/C ");

    SHELLEXECUTEINFOA ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "cmd.exe";
    ShExecInfo.lpParameters = command.c_str();
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;

    if (ShellExecuteExA(&ShExecInfo) == FALSE)
        return -1;

    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    DWORD rv;
    GetExitCodeProcess(ShExecInfo.hProcess, &rv);
    CloseHandle(ShExecInfo.hProcess);

    return rv;
}