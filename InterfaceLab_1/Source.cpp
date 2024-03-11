#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
	const int WIN_WIDTH = 1920;
	const int WIN_HEIGHT = 1080;
	const float SIZE = 8;
	RenderWindow win(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Lab 1");

	RectangleShape shape(Vector2f(2 * SIZE, SIZE));
	shape.setFillColor(Color(105, 105, 105));
	shape.setPosition(200, 600);

	int press_count = 0;

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
						press_count++;
						Vector2i new_pos(WIN_WIDTH / 2, WIN_HEIGHT / 2);
						Mouse::setPosition(new_pos);
					}

			if (press_count == 5)
			{

			}
		}

		win.clear();
		win.draw(shape);
		win.display();
	}

	return 0;
}