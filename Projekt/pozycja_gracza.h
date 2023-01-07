#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <math.h>
#include "isAnyKeyPressed.h"

using namespace sf;
using namespace std;

void sprawdz_pozycje(RectangleShape & player, int pozycja, int &IdleAnim, int &dealy, float &hp);
