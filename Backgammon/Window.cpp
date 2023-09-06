#include "Window.h"

Window* Window::_instance = nullptr;

Window::Window(const std::string& windowName) : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), windowName, sf::Style::Close | sf::Style::Titlebar)
{
	if (_instance == nullptr)
	{
		_instance = this;
		return;
	}
	static_assert("Only one instance of window possible");
}

Window::~Window()
{

}

void Window::Update()
{
	sf::Event event;
	if (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			Close();
		}
	}
}

void Window::BeginDraw()
{
	_window.clear(sf::Color::Black);
}

void Window::Draw(const sf::Drawable& drawable)
{
	_window.draw(drawable);
}

void Window::Draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type)
{
	_window.draw(vertices, vertexCount, type);
}

void Window::EndDraw()
{
	_window.display();
}


bool Window::IsOpen()
{
	return _window.isOpen();
}

void Window::Close()
{
	_window.close();
}