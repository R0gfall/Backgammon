#pragma once

#include <SFML/Graphics.hpp>

#include <iomanip>
#include <Windows.h>
#include <iostream>
#include <string>

#include "Window.h"

enum class ConsoleColor
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	PURPLE = 5,
	YELLOW = 6,
	WHITE = 7,
	GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_CYAN = 10,
	LIGHT_RED = 11,
	LIGHT_PURPLE = 12,
	LIGHT_YELLOW = 13,
	BRIGHT_WHITE = 14
};
const int DEBUG_LEFT_SIZE = 25;
const int DEBUG_TYPE_SIZE = 10;

const std::string LOG_PREFIX = "LOG";
const std::string LOG_INFO_PREFIX = "INFO";
const std::string LOG_WARNING_PREFIX = "WARNING";
const std::string LOG_ERROR_PREFIX = "ERROR";

//Класс для логов
class Debug
{
public:
	static void Initialize(Window* window);

	//Белое сообщение
	static void Log(const std::string& message);
	static void Log(const std::string& message, const std::string& from);
	//Голубое сообщение
	static void LogInfo(const std::string& message);
	static void LogInfo(const std::string& message, const std::string& from);
	//Желтое сообщение
	static void LogWarning(const std::string& message);
	static void LogWarning(const std::string& message, const std::string& from);
	//Красное сообщение
	static void LogError(const std::string& message);
	static void LogError(const std::string& message, const std::string& from);

private:
	static void DisplayLog(const std::string& prefix, const std::string& message, ConsoleColor color);
	static void DisplayLog(const std::string& prefix, const std::string& message, const std::string& from, ConsoleColor color);
	static HANDLE handle;

	static Window* _window;
};

