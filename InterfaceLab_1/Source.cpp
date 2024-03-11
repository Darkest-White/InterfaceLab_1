#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
	const int win_width = 1920;
	const int win_height = 1080;
	const float SIZE = 8;
	RenderWindow win(VideoMode(win_width, win_height), "Lab 1");

	RectangleShape shape(Vector2f(2 * SIZE, SIZE));
	shape.setFillColor(Color(105, 105, 105));
	shape.setPosition(200, 600);

	while (win.isOpen())
	{
		Vector2i mouse_pos = Mouse::getPosition(win);

		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
				win.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					if (shape.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
					{
						cout << "Pressed" << endl;
						Vector2i new_pos(win_width / 2, win_height / 2);
						Mouse::setPosition(new_pos);
					}
		}
		win.clear();
		win.draw(shape);
		win.display();
	}

	return 0;
}