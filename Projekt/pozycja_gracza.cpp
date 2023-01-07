#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <math.h>
#include "pozycja_gracza.h"


using namespace sf;
using namespace std;



void sprawdz_pozycje(RectangleShape & player, int pozycja, int &IdleAnim, int &delay, float &hp)
{
if(hp > 0)
{
    if(!isAnyKeyPressed() && delay >= 15)
        {
            if(pozycja == 1)
            {
                player.setTextureRect(IntRect(IdleAnim*69,960,69,96));
            }
            if(pozycja == 2)
            {
                player.setTextureRect(IntRect(IdleAnim*69,0,69,96));
            }
            if(pozycja == 3)
            {
                player.setTextureRect(IntRect(IdleAnim*69,480,69,96));
            }
            if(pozycja == 4)
            {
                player.setTextureRect(IntRect(IdleAnim*69,96,69,96));
            }

++IdleAnim;
if(IdleAnim == 9)
{
    IdleAnim = 0;
}
delay = 1;
}
}
}
