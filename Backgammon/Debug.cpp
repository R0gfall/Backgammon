#include "Debug.h"

HANDLE Debug::handle = GetStdHandle(STD_OUTPUT_HANDLE);
Window* Debug::_window = nullptr;
std::ofstream Debug::_outputFile;

void Debug::Initialize(Window* window, const std::string& outputFilename)
{
	_window = window;
	_outputFile.open(outputFilename);
	if (!_outputFile.is_open())
	{
		std::cout << "CANNOT OPEN OUTPUT LOG FILE\n";
	}
}
void Debug::Destroy()
{
	_outputFile.close();
}

void Debug::Log(const std::string& message)
{
	DisplayLog(LOG_PREFIX, message, ConsoleColor::WHITE);
}

void Debug::Log(const std::string& message, const std::string& from)
{
	DisplayLog(LOG_PREFIX, message, from, ConsoleColor::WHITE);
}

void Debug::LogInfo(const std::string& message)
{
	DisplayLog(LOG_INFO_PREFIX, message, ConsoleColor::CYAN);
}

void Debug::LogInfo(const std::string& message, const std::string& from)
{
	DisplayLog(LOG_INFO_PREFIX, message, from, ConsoleColor::CYAN);
}

void Debug::LogSuccess(const std::string& message)
{
	DisplayLog(LOG_INFO_PREFIX, message, ConsoleColor::GREEN);
}

void Debug::LogSuccess(const std::string& message, const std::string& from)
{
	DisplayLog(LOG_INFO_PREFIX, message, from, ConsoleColor::GREEN);
}

void Debug::LogWarning(const std::string& message)
{
	DisplayLog(LOG_WARNING_PREFIX, message, ConsoleColor::YELLOW);
}

void Debug::LogWarning(const std::string& message, const std::string& from)
{
	DisplayLog(LOG_WARNING_PREFIX, message, from, ConsoleColor::YELLOW);
}

void Debug::LogError(const std::string& message)
{
	DisplayLog(LOG_ERROR_PREFIX, message, ConsoleColor::RED);
}

void Debug::LogError(const std::string& message, const std::string& from)
{
	DisplayLog(LOG_ERROR_PREFIX, message, from, ConsoleColor::RED);
}

void Debug::DisplayLog(const std::string& prefix, const std::string& message, ConsoleColor color)
{
	SetConsoleTextAttribute(handle, (int)color);
	std::cout << prefix << ": " << message << "\n";
	_outputFile << prefix << ": " << message << "\n";
	SetConsoleTextAttribute(handle, (int)ConsoleColor::WHITE);
}

void Debug::DisplayLog(const std::string& prefix, const std::string& message, const std::string& from, ConsoleColor color)
{
	SetConsoleTextAttribute(handle, (int)color);
	std::cout << std::setiosflags(std::ios::left) << std::setw(DEBUG_LEFT_SIZE) << from << std::setiosflags(std::ios::left) << std::setw(DEBUG_TYPE_SIZE) << prefix << ": " << message << "\n";
	_outputFile << std::setiosflags(std::ios::left) << std::setw(DEBUG_LEFT_SIZE) << from << std::setiosflags(std::ios::left) << std::setw(DEBUG_TYPE_SIZE) << prefix << ": " << message << "\n";
	SetConsoleTextAttribute(handle, (int)ConsoleColor::WHITE);
}
