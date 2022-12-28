#include <SFML/Graphics.hpp>
#include <iostream>
//#include <Animation.h>
#include <windows.h>
#include <math.h>

using namespace sf;
using namespace std;

class strzal
{
    public:
    Texture *strzala;
    Sprite shape;
    float szybkosc_lotu_strzaly;
    int dmg;

    strzal(Texture *strzala, float szybkosc_lotu_strzaly, int dmg)
    {
        this->strzala=strzala;
        this->szybkosc_lotu_strzaly=szybkosc_lotu_strzaly;
        this->dmg=dmg;
        this->shape.setTexture(*strzala);
    }


};

void dodaj_strzale(strzal strzalka, vector <strzal> &wektor_strzal, RectangleShape & player);
void dodaj_strzale_lewo(strzal strzalka, vector <strzal> &wektor_strzal_1, RectangleShape & player);
void dodaj_strzale_dol(strzal strzalka, vector <strzal> &wektor_strzal_dol, RectangleShape & player);
void dodaj_strzale_gora(strzal strzalka, vector <strzal> &wektor_strzal_gora, RectangleShape & player);
void narysuj_strzale(vector <strzal> &wektor_strzal, RenderWindow & window);
void narysuj_strzale_lewo(vector <strzal> &wektor_strzal_1, RenderWindow & window);
void narysuj_strzale_dol(vector <strzal> &wektor_strzal_dol, RenderWindow & window);
void narysuj_strzale_gora(vector <strzal> &wektor_strzal_gora, RenderWindow & window);
