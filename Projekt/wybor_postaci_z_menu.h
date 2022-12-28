#include <SFML/Graphics.hpp>
#include <iostream>
//#include <Animation.h>
#include <windows.h>
#include <math.h>
#include "isAnyKeyPressed.h"

using namespace sf;
using namespace std;



void wybor_postaci(int bitmapa, RenderWindow & window, RectangleShape & chooseplayer1,RectangleShape & chooseplayer2, Texture & chooseplayer1_texture, Texture & chooseplayer2_texture, int &IdleAnim, int &delay, int &done);
