#include <SFML/Graphics.hpp>
#include <iostream>
//#include <Animation.h>
#include <windows.h>
#include <math.h>
#include "wybor_postaci_z_menu.h"



using namespace sf;
using namespace std;


void wybor_postaci(int bitmapa, RenderWindow & window, RectangleShape & chooseplayer1,RectangleShape & chooseplayer2, Texture & chooseplayer1_texture, Texture & chooseplayer2_texture, int &IdleAnim, int &delay, int &done)
{


if (bitmapa == 1 && Mouse::getPosition(window).x  > 683 && Mouse::getPosition(window).y < 768){

        chooseplayer1.setTexture(&chooseplayer1_texture);

        done = 3; // potrzebna zmienna do wyswietlenia postaci

    if(!isAnyKeyPressed() && delay >= 15)
    {
    chooseplayer1.setTextureRect(IntRect(IdleAnim*274,0,274,343));

   ++IdleAnim;
   if(IdleAnim == 10)
    {
    IdleAnim = 0;
    }
delay = 1;

    }
}

if (bitmapa == 1 && Mouse::getPosition(window).x  < 683 &&Mouse::getPosition(window).y < 768 ){
    //cout<<"chujL";

        chooseplayer2.setTexture(&chooseplayer2_texture);
        done = 4; // potrzebna zmienna do wyswietlenia postaci


    if(!isAnyKeyPressed() && delay >= 15)
    {
    chooseplayer2.setTextureRect(IntRect(IdleAnim*274,343,274,343));

   ++IdleAnim;
   if(IdleAnim == 10)
    {
    IdleAnim = 0;
    }
delay = 1;

    }


}

}


