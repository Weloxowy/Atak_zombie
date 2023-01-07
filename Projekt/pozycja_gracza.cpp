/** \file pozycja_gracza.h
 * Plik zrodlowy dla pliku naglowkowego pozycja_gracza.h
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <math.h>
#include "pozycja_gracza.h"


using namespace sf;
using namespace std;


/** @brief Funkcja sprawdza aktualna pozycje gracza i kierunek w jakim jest on zwrocony aby dopasowac wlasciwa animacje
 *
 * @param RectangleShape & player - wskaznik na postac
 * @param int pozycja - kierunek zwrotu gracza: 1 = lewo, 2 = prawo, 3 = gora , 4 = dol
 * @param int &IdleAnim - iterator animacji tekstur
 * @param int &delay - opoznienie
 * @param float &hp - aktualne zdrowie postaci
 *
 */

void sprawdz_pozycje(RectangleShape & player, int pozycja, int &IdleAnim, int &delay, float &hp)
{
if(hp > 0)
{
    if(!isAnyKeyPressed() && delay >= 15) /**< Sprawdza czy gracz nie strzela lub nie idzie i zyje */
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
