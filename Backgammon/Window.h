#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include "GlobalDefinitions.h"

class Window
{
public:
	Window(const std::string& window);

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

