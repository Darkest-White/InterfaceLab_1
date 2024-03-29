#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <fstream>
using namespace sf;
using namespace std;
using namespace chrono;

void random_rect(float radius, RectangleShape* rectangle) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.f, 2.f * 3.14);

	float angle = dis(gen);
	float x = radius * cos(angle);
	float y = radius * sin(angle);

	rectangle->setPosition(abs(x), abs(y));
}

int main()
{
	system("chcp 1251");
	system("cls");

	RenderWindow window(VideoMode(800, 700), "Lab 1", Style::Close);

	auto last_click_time = steady_clock::now();

	Vector2i pos = window.getPosition();
	pos.y += 32;

	bool IsClicked = 0;
	bool IsMoved = 0;

	float radius = 400;
	float size = 8;
	RectangleShape rectangle(Vector2f(2 * size, size));
	rectangle.setFillColor(Color(128, 128, 128));

	sf::CircleShape circle(radius);
	circle.setPointCount(200);
	circle.setFillColor(Color::Transparent);
	circle.setOutlineThickness(1);
	circle.setOutlineColor(Color::Red);
	circle.setPosition(0, 0);

	vector<float> dists = { 1, 20, 40, 60, 100, 150, 200, 250, 300, 350 };

	int current_dist = 0;
	int current_try = 0;

	int tries = 5;

	vector<float> med_nums;
	vector<vector<float>> med_nums2;
	med_nums.push_back(0);
	med_nums2.push_back(*new vector<float>);
	med_nums2.at(0).push_back(0);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (current_dist >= dists.size())
				window.close();
			else if (event.type == Event::KeyPressed and event.key.code == Keyboard::Space and not IsClicked and not IsMoved)
			{
				IsClicked = 1;

				pos = window.getPosition();
				pos.y += 30;
				pos.x += 8;
				Mouse::setPosition(pos);

				radius = dists.at(current_dist);
				circle.setRadius(radius);
				circle.setPosition(-radius, -radius);

				random_rect(radius, &rectangle);
			}
			else if (IsClicked and Mouse::getPosition() != pos and not IsMoved) 
			{
				IsMoved = 1;

				last_click_time = steady_clock::now();
			}
			else if (IsMoved == 1 and IsClicked and event.type == Event::MouseButtonPressed and rectangle.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			{
				auto current_time = steady_clock::now();
				auto time_since_last_click = duration_cast<nanoseconds>(current_time - last_click_time).count();

				cout << "�����: " << static_cast<float>(time_since_last_click) / 1e9 << " ������" << endl;

				last_click_time = current_time;

				if (current_try < tries - 1)
				{
					med_nums.at(current_dist) += static_cast<float>(time_since_last_click) / 1e9;
					current_try++;
				}
				else
				{
					med_nums.push_back(0);
					med_nums.at(current_dist) += static_cast<float>(time_since_last_click) / 1e9;
					med_nums.at(current_dist) /= 5;
					current_dist++;
					current_try = 0;
				}
				IsClicked = 0;
				IsMoved = 0;
			}
		}
		window.clear(Color::Black);
		if (IsClicked)
		{
			window.draw(rectangle);
			window.draw(circle);
		}
		window.display();
	}

	cout << "������� �������� ������� ����� ���������:" << endl;
	for (int i = 0; i < dists.size(); i++)
		cout << "��� �������� " << dists[i] << ": " << med_nums[i] << endl;

	ofstream outputFile("average_times.txt", ios::app);

	if (outputFile.is_open())
	{
		outputFile << "����� ������������: " << 1 << endl;
		outputFile << "������� �������� ������� ����� ���������:" << endl;

		// ������ ������� �������� � ����
		for (int i = 0; i < dists.size(); i++)
			outputFile << "��� �������� " << dists[i] << ": " << med_nums[i] << endl;

		outputFile.close();

		cout << "������ �� ������������ " << 1 << " ���� ��������� � ���� 'average_times.txt'" << endl;
	}
	else
	{
		cerr << "�� ������� ������� ���� ��� ������." << endl;
	}
	return 0;
}