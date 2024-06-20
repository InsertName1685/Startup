#pragma once
#include<Windows.h>
#include<string>
#include<lmcons.h>

bool isUserAdmin();

std::string WindowUser();
std::string real_ip();
std::string getHwid();
std::string ComputerName();
std::string CompileInfo();