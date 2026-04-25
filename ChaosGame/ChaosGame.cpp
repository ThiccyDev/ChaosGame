// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

void GeneratePoint(vector<Vector2f>&, vector<Vector2f>&);

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;
	
	bool pointsSetUp = false;

	srand(time(0));

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && !pointsSetUp)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
					{
						///fourth click
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						pointsSetUp = true;
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (pointsSetUp)
		{
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
			
			GeneratePoint(vertices, points);
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}
		///TODO:  Draw points
		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(points[i].x, points[i].y));
			rect.setFillColor(Color::Red);
			window.draw(rect);
		}
		window.display();
	}
}

void GeneratePoint(vector<Vector2f>& vertices, vector<Vector2f>& points)
{
	/* 1. Get random triangle point.
	*  2. Find midpoint between selectedPoint and triangle point.
	*  3. Add a new point there.
	*  4. Set selectedPoint to the newPoint.
	*/

	Vector2f randomPoint = vertices.at(rand() % 3);

	// find midpoint
	Vector2f midPoint = Vector2f(randomPoint.x / 2.0f + points.at(points.size() - 1).x / 2.0f, randomPoint.y / 2.0f + points.at(points.size() - 1).y / 2.0f);

	points.push_back(midPoint);
}