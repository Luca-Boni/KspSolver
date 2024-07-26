#pragma once

#include <string>

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__) || defined(unix)

#define clearScreen() system("clear")

#endif // __APPLE__ || __linux__ || __unix__ || unix

#ifdef _WIN32

#include <windows.h>

#define clearScreen() system("cls")

#endif // _WIN32