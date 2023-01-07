#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <math.h>
#include "wybor_postaci_z_menu.h"



using namespace sf;
using namespace std;

/** @brief Deklaracja funkcji wybor postaci
 *
 * @param int bitmapa - zawiera id uzywanej bitmapy
 * @param RenderWindow &window - wskaünik na okno
 * @param RectangleShape & chooseplayer1 - wskaznik na 1 postac
 * @param RectangleShape & chooseplayer2 - wskaznik na 2 postac
 * @param Texture & chooseplayer1_texture - wskaznik na tekstury 1 postaci
 * @param Texture & chooseplayer2_texture - wskaznik na tekstury 1 postaci
 * @param int &IdleAnim - iterator animacji tekstur
 * @param int &done - zmienna przechowuje numer wybranej postaci
 * @param int &delay - opoznienie
 *
 */
void wybor_postaci(int bitmapa, RenderWindow & window, RectangleShape & chooseplayer1,RectangleShape & chooseplayer2, Texture & chooseplayer1_texture, Texture & chooseplayer2_texture, int &IdleAnim, int &delay, int &done)
{

/**< Wybor pierwszej postaci z menu */
if (bitmapa == 1 && Mouse::getPosition(window).x  > 683 && Mouse::getPosition(window).y < 768){

        chooseplayer1.setTexture(&chooseplayer1_texture);

        done = 3; /**< Zmienna do wyswietlenia danej postaci w main*/

    if(!isAnyKeyPressed() && delay >= 15) /**< Animacja mrugania w menu */
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

/**< Wybor drugiej postaci z menu */
if (bitmapa == 1 && Mouse::getPosition(window).x  < 683 &&Mouse::getPosition(window).y < 768 ){

        chooseplayer2.setTexture(&chooseplayer2_texture);
        done = 4; /**< Zmienna do wyswietlenia danej postaci w main*/


    if(!isAnyKeyPressed() && delay >= 15) /**< Animacja mrugania w menu */
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


