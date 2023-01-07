/** \file strzelanie_player1.h
 * Plik zrodlowy dla pliku naglowkowego strzelanie_player1.h
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "strzelanie_player1.h"
#include <vector>
#include <math.h>


using namespace sf;
using namespace std;




/**
 * @brief Tworzy strzale lecaca w prawo
 * @param strzal strzalka - wywolanie klasy strzal
 * @param vector <strzal> &wektor_strzal - wywolanie wektora przechowujacego strzaly
 * @param RectangleShape & player - wskaznik na postac
 *
 */

void dodaj_strzale(strzal strzalka, vector <strzal> &wektor_strzal, RectangleShape & player)
{

    strzalka.shape.setPosition(player.getPosition().x, player.getPosition().y+player.getGlobalBounds().height/2-10);
    wektor_strzal.push_back(strzalka);


}

/**
 * @brief Tworzy strzale lecaca w lewo
 * @param strzal strzalka - wywolanie klasy strzal
 * @param vector <strzal> &wektor_strzal - wywolanie wektora przechowujacego strzaly
 * @param RectangleShape & player - wskaznik na postac
 *
 */
void dodaj_strzale_lewo(strzal strzalka, vector <strzal> &wektor_strzal_1, RectangleShape & player)
{

    strzalka.shape.setPosition(player.getPosition().x, player.getPosition().y+player.getGlobalBounds().height/2-10);
    wektor_strzal_1.push_back(strzalka);
}

/**
 * @brief Tworzy strzale lecaca w dol
 * @param strzal strzalka - wywolanie klasy strzal
 * @param vector <strzal> &wektor_strzal - wywolanie wektora przechowujacego strzaly
 * @param RectangleShape & player - wskaznik na postac
 *
 */
void dodaj_strzale_dol(strzal strzalka, vector <strzal> &wektor_strzal_dol, RectangleShape & player)
{

    strzalka.shape.setPosition(player.getPosition().x+player.getGlobalBounds().width/2-20, player.getPosition().y+player.getGlobalBounds().height/2+10);
    wektor_strzal_dol.push_back(strzalka);
}

/**
 * @brief Tworzy strzale lecaca w gora
 * @param strzal strzalka - wywolanie klasy strzal
 * @param vector <strzal> &wektor_strzal - wywolanie wektora przechowujacego strzaly
 * @param RectangleShape & player - wskaznik na postac
 *
 */
void dodaj_strzale_gora(strzal strzalka, vector <strzal> &wektor_strzal_gora, RectangleShape & player)
{

    strzalka.shape.setPosition(player.getPosition().x+player.getGlobalBounds().width/2-20, player.getPosition().y+player.getGlobalBounds().height/2-69);
    wektor_strzal_gora.push_back(strzalka);
}

/**
 * @brief Naklada teksture na strzale lecaca w prawo
 * @param strzal strzalka - wywolanie klasy strzal
 * @param vector <strzal> &wektor_strzal - wywolanie wektora przechowujacego strzaly
 * @param RectangleShape & player - wskaznik na postac
 *
 */
void narysuj_strzale(vector <strzal> &wektor_strzal, RenderWindow & window)
{
    for(int i = 0; i < wektor_strzal.size(); ++i)
    {
        wektor_strzal[i].shape.move(5.5f,0.0f);
        window.draw(wektor_strzal[i].shape);
    }
}

/**
 * @brief Naklada teksture na strzale lecaca w lewo
 * @param strzal strzalka - wywolanie klasy strzal
 * @param vector <strzal> &wektor_strzal - wywolanie wektora przechowujacego strzaly
 * @param RectangleShape & player - wskaznik na postac
 *
 */
void narysuj_strzale_lewo(vector <strzal> &wektor_strzal_1, RenderWindow & window)
{
    for(int i = 0; i < wektor_strzal_1.size(); ++i)
    {
        wektor_strzal_1[i].shape.move(-5.5f,0.0f);
        window.draw(wektor_strzal_1[i].shape);
    }
}

/**
 * @brief Naklada teksture na strzale lecaca w dol
 * @param strzal strzalka - wywolanie klasy strzal
 * @param vector <strzal> &wektor_strzal - wywolanie wektora przechowujacego strzaly
 * @param RectangleShape & player - wskaznik na postac
 *
 */
void narysuj_strzale_dol(vector <strzal> &wektor_strzal_dol, RenderWindow & window)
{
    for(int i = 0; i < wektor_strzal_dol.size(); ++i)
    {
        wektor_strzal_dol[i].shape.move(0.0f,5.5f);
        window.draw(wektor_strzal_dol[i].shape);
    }
}

/**
 * @brief Naklada teksture na strzale lecaca w gore
 * @param strzal strzalka - wywolanie klasy strzal
 * @param vector <strzal> &wektor_strzal - wywolanie wektora przechowujacego strzaly
 * @param RectangleShape & player - wskaznik na postac
 *
 */
void narysuj_strzale_gora(vector <strzal> &wektor_strzal_gora, RenderWindow & window)
{
    for(int i = 0; i < wektor_strzal_gora.size(); ++i)
    {
        wektor_strzal_gora[i].shape.move(0.0f,-5.5f);
        window.draw(wektor_strzal_gora[i].shape);
    }
}


