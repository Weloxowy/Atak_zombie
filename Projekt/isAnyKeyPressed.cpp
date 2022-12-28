#include <SFML/Graphics.hpp>
#include <iostream>
//#include <Animation.h>
#include <windows.h>
#include <math.h>
#include "isAnyKeyPressed.h"

using namespace sf;
using namespace std;

bool isAnyKeyPressed()
	{
		for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
		{
			if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
				return true;
		}
		return false;

	}

