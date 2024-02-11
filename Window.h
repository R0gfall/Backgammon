#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include "GlobalDefinitions.h"

//Класс обертка для SFML окна
//Нужен для отрисовки объектов
class Window
{
public:
	//Конструктор
	Window(const std::string& window);
	//Деструктор
	~Window();

	void Update();

	void BeginDraw();
	void Draw(const sf::Drawable& drawable);
	void Draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type);
	void EndDraw();

	bool IsOpen();

	void Close();

	static Window* Instance() { return _instance; }

	sf::Window& GetSfWindow() { return _window; }

private:
	sf::RenderWindow _window;

	static Window* _instance;
};

