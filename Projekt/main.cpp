/**
 * @mainpage
 * Strona zawiera dokumentacje gry <b><i>ATAK ZOMBIE </b></i>
 **/
/**
 *  @file main.c
 *  @brief Glówny plik programu
 **/



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <sstream>
#include "pozycja_gracza.h"
#include "isAnyKeyPressed.h"
#include "wybor_postaci_z_menu.h"
#include "cale_menu_lewy_klik.h"

using namespace sf;
using namespace std;

int bitmapa = 0; ///< Zmienna przechowuje stan aktualnej bitmapy
int done = 0; ///< Zmienna odpowiadajaca za wybor postaci
const unsigned WINDOW_WIDTH = 1366; ///< Zmienna przechowuje dlugosc mapy
const unsigned WINDOW_HEIGHT = 768; ///< Zmienna przechowuje szerokosc mapy
int pozycja = 0; ///< Zmienna przechowuje aktualna pozycje gracza
int delay = 0; ///< Zmienna pozwalajaca na opoznienie aktualnie wykonywanej tekstury
int IdleAnim = 0; ///< Zmienna pozwalajaca na wyswietlenie tekstury w zaleznosci od pozycji gracza
bool czy_strzela = false; ///< Zmienna okreslajaca czy gracz wykonuje strzal
float ziara = 0; ///< Zmienna pozwalajaca na wykonanie tekstury strzalu
int czas_respu_zombie=10000; ///< Zmienna przechowujaca opoznienie dla pojawienia sie zombie
float hp=10; ///< Zmienna przechowujaca poziom zdrowia lucznika
float hp_berserker=7; ///< Zmienna przechowujaca poziom zdrowia berserkera
int score = 0; ///< Zmienna przechowujaca zdobyte punkty przez gracza
int poziom = 1; ///< Zmienna przechowujaca aktualny poziom gry
bool wykonaj = false; ///< Zmienna pozwalajaca na wyswietlenie tekstury umierania playera
int ziara4 = 0; ///< Zmienna pozwalajaca na wykonanie tekstury umierania
int delay2 = 0; ///< Zmienna pozwalajaca na opoznienie aktualnie wykonywanej tekstury
int kontroluj_strzal = 0; ///< Zmienna pozwalajaca na zablokowaniu dublowania sie strzal w tym samym wektorze, sprawdzanie pozycji gracza, sprawdzanie ktorej metody ma uzyc z klasy
vector <zombie> wektor_zombie; ///< Wektor przechowujacy zombie


/*!
 * @brief Funkcja sprawdzajaca kolizje strzaly
 * @param strzalka - obiekt klasy strzal, tworzy strzale
 */
bool kolizja_strzaly(strzal strzalka)
{
    if(strzalka.shape.getPosition().x >1366 || strzalka.shape.getPosition().y > 768 || strzalka.shape.getPosition().x < 0 || strzalka.shape.getPosition().y < 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

/**
 * @brief Klasa gracz
 * @param hpBarBack - wyswietlanie szarego paska hp
 * @param hpBarInside - wyswietlanie czerwonego paska hp
 * @param MAXhp_lucznik - maksymalny poziom zdrowia lucznika
 * @param MAXhp_berserker - maksymalny poziom zdrowia berserkera
 * @param width - szerokosc paska zdrowia
 * @param height - wysokosc paska zdrowia
 * @param hpBarMaxWidth - maksymalna szerokosc paska zdrowia
 */


class gracz
{
    public:
        sf::RectangleShape hpBarBack;
        sf::RectangleShape hpBarInside;
        float MAXhp_lucznik = 10;
        float MAXhp_berserker = 7;
        float width = 50.f;
        float hpBarMaxWidth = width;
        float height = 10.f;

/**
 *  @brief Funkcja wyswietlajaca dwa paski zdrowia gracza
 *  @param target - pozwala na wyswietlenie paskow zdrowia
 */


    void render_hp(sf::RenderTarget & target)
    {
        target.draw(hpBarBack);
        target.draw(hpBarInside);
    }

    /**
     *  @brief Funkcja pozwalajaca na ustawienie pozycji oraz kolorow paskow zdrowia
     *  @param player - ustawienie paskow zdrowia nad playerem
     */

    void initHP(RectangleShape & player)
    {
        hpBarBack.setSize(sf::Vector2f(width,height));
        hpBarBack.setFillColor(sf::Color(50,50,50,200));
        hpBarBack.setPosition(player.getPosition().x,player.getPosition().y - 35);

        hpBarInside.setSize(sf::Vector2f(width,height));
        hpBarInside.setFillColor(sf::Color(250,20,20,200));
        hpBarInside.setPosition(hpBarBack.getPosition());

    }

    /**
     *  @brief Funckja sprawdza i modyfikuje aktualny poziom zdrowia
     */

    void update_hp()
    {
        float procent = static_cast<float>(hp) / static_cast<float>(MAXhp_lucznik);
        hpBarInside.setSize(sf::Vector2f(static_cast<float>(std::floor(hpBarMaxWidth * procent)), hpBarInside.getSize().y));
    }
    /**
     *  @brief Funckja sprawdza i modyfikuje aktualny poziom zdrowia
     */
    void update_hp_berserker()
    {
        float procent = static_cast<float>(hp_berserker) / static_cast<float>(MAXhp_berserker);
        hpBarInside.setSize(sf::Vector2f(static_cast<float>(std::floor(hpBarMaxWidth * procent)), hpBarInside.getSize().y));
    }

    /**
     *  @brief Funckja sprawdza aktualna pozycje playera, i blokuje mu wyjscie poza mape
     *  @param player - sprawdza pozycje playera
     */
    void kolizja_ogolna(RectangleShape & player)
    {

        if(player.getPosition().x < 0.f)
            player.setPosition(0.f, player.getPosition().y);

        if(player.getPosition().y < 0.f)
            player.setPosition(player.getPosition().x,0.f);

        if(player.getPosition().x + player.getGlobalBounds().width > WINDOW_WIDTH)
            player.setPosition(WINDOW_WIDTH - player.getGlobalBounds().width, player.getPosition().y);

        if(player.getPosition().y + player.getGlobalBounds().height > WINDOW_HEIGHT)
            player.setPosition(player.getPosition().x, WINDOW_HEIGHT - player.getGlobalBounds().height);
    }
    /**
     * @brief Funckja pozwala na poruszanie sie w lewo lucznika (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */

    void poruszanie_lewo(RectangleShape & player)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::A))
        {
            IdleAnim = 0;
            pozycja = 1;
            int xTexture = 0;
            xTexture = (int)player.getPosition().x / 25 % 9;
            xTexture*=69;

            player.setTextureRect(IntRect(xTexture,672,69,96));
            player.move(-3.0f,0.0f);

            if(player.getPosition().x < 381.f && player.getPosition().y < 375.f)
                {
                player.setPosition(381.f, player.getPosition().y);
                }
            if(player.getPosition().x < 420.f && player.getPosition().y < 145.f)
                {
                player.setPosition(420.f, player.getPosition().y);
                }

            if((player.getPosition().x > 551.f && player.getPosition().y < 90.f) && (player.getPosition().x < 664.f && player.getPosition().y < 90.f))
                {
            player.setPosition(664.f, player.getPosition().y);
                }
            }
        }
        /**
     * @brief Funckja pozwala na poruszanie sie w lewo berserkera (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_lewo_berserker(RectangleShape & player)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::A))
        {
            IdleAnim = 0;
            pozycja = 1;
            int xTexture = 0;
            xTexture = (int)player.getPosition().x / 25 % 9;
            xTexture*=69;

            player.setTextureRect(IntRect(xTexture,672,69,96));
            player.move(-4.0f,0.0f);

            if(player.getPosition().x < 381.f && player.getPosition().y < 375.f)
                {
                player.setPosition(381.f, player.getPosition().y);
                }
            if(player.getPosition().x < 420.f && player.getPosition().y < 145.f)
                {
                player.setPosition(420.f, player.getPosition().y);
                }

            if((player.getPosition().x > 551.f && player.getPosition().y < 90.f) && (player.getPosition().x < 664.f && player.getPosition().y < 90.f))
                {
            player.setPosition(664.f, player.getPosition().y);
                }
            }
        }
    /**
     * @brief Funckja pozwala na poruszanie sie w prawo lucznika (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_prawo(RectangleShape & player)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::D))
    {
        pozycja = 2;
        int xTexture = 0;
        IdleAnim = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
        player.setTextureRect(IntRect(xTexture,192,69,96));
        player.move(3.0f,0.0f);
        if(player.getPosition().x > 765.f && player.getPosition().y >472.f)
        {
            player.setPosition(765.f, player.getPosition().y);
        }
        if(player.getPosition().x > 789.f && player.getPosition().y >354.f)
        {
            player.setPosition(789.f, player.getPosition().y);
        }
        if(player.getPosition().x > 809.f && player.getPosition().y >324.f)
        {
            player.setPosition(809.f, player.getPosition().y);
        }
        if(player.getPosition().x > 832.f && player.getPosition().y >308.f)
        {
            player.setPosition(832.f, player.getPosition().y);
        }
        if(player.getPosition().x > 878.f && player.getPosition().y >293.f)
        {
            player.setPosition(878.f, player.getPosition().y);
        }
        if(player.getPosition().x > 933.f && player.getPosition().y >178.f)
        {
            player.setPosition(933.f, player.getPosition().y);
        }
        if(player.getPosition().x > 947.f && player.getPosition().y >148.f)
        {
            player.setPosition(947.f, player.getPosition().y);
        }
        if(player.getPosition().x > 964.f && player.getPosition().y > -93.f)
        {
            player.setPosition(964.f, player.getPosition().y);
        }
        if((player.getPosition().x > 482.f && player.getPosition().y < 90.f) && (player.getPosition().x < 664.f && player.getPosition().y < 90.f))
        {
            player.setPosition(482.f, player.getPosition().y);
        }

    }
    }
    /**
     * @brief Funckja pozwala na poruszanie sie w prawo berserkera (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_prawo_berserker(RectangleShape & player)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::D))
    {
        pozycja = 2;
        int xTexture = 0;
        IdleAnim = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
        player.setTextureRect(IntRect(xTexture,192,69,96));
        player.move(4.0f,0.0f);
        //kolizje dla prawych drzew
        if(player.getPosition().x > 765.f && player.getPosition().y >472.f)
        {
            player.setPosition(765.f, player.getPosition().y);
        }
        if(player.getPosition().x > 789.f && player.getPosition().y >354.f)
        {
            player.setPosition(789.f, player.getPosition().y);
        }
        if(player.getPosition().x > 809.f && player.getPosition().y >324.f)
        {
            player.setPosition(809.f, player.getPosition().y);
        }
        if(player.getPosition().x > 832.f && player.getPosition().y >308.f)
        {
            player.setPosition(832.f, player.getPosition().y);
        }
        if(player.getPosition().x > 878.f && player.getPosition().y >293.f)
        {
            player.setPosition(878.f, player.getPosition().y);
        }
        if(player.getPosition().x > 933.f && player.getPosition().y >178.f)
        {
            player.setPosition(933.f, player.getPosition().y);
        }
        if(player.getPosition().x > 947.f && player.getPosition().y >148.f)
        {
            player.setPosition(947.f, player.getPosition().y);
        }
        if(player.getPosition().x > 964.f && player.getPosition().y > -93.f)
        {
            player.setPosition(964.f, player.getPosition().y);
        }
        if((player.getPosition().x > 482.f && player.getPosition().y < 90.f) && (player.getPosition().x < 664.f && player.getPosition().y < 90.f))
        {
            player.setPosition(482.f, player.getPosition().y);
        }

    }
    }
    /**
     * @brief Funckja pozwala na poruszanie sie w gore lucznika (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_gora(RectangleShape & player)
    {
      if(Keyboard::isKeyPressed(Keyboard::Key::W))
    {
        IdleAnim = 0;
        pozycja = 3;
        int yTexture = 0;
        yTexture = (int)player.getPosition().y / 25 % 9;
        yTexture*=69;

        player.setTextureRect(IntRect(yTexture,480,69,96));
        player.move(0.0f,-3.0f);
        if(player.getPosition().x < 381.f && player.getPosition().y < 375.f)
        {
            player.setPosition(player.getPosition().x, 375.f);
        }
        if(player.getPosition().x < 420.f && player.getPosition().y < 145.f)
        {
            player.setPosition(player.getPosition().x, 145.f);
        }

        if((player.getPosition().x > 482.f && player.getPosition().y < 90.f) && (player.getPosition().x < 664.f && player.getPosition().y < 90.f))
        {
            player.setPosition(player.getPosition().x, 90.f);
        }
    }
    }
    /**
     * @brief Funckja pozwala na poruszanie sie w gore berserkera (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_gora_berserker(RectangleShape & player)
    {
      if(Keyboard::isKeyPressed(Keyboard::Key::W))
    {
        IdleAnim = 0;
        pozycja = 3;
        int yTexture = 0;
        yTexture = (int)player.getPosition().y / 25 % 9;
        yTexture*=69;

        player.setTextureRect(IntRect(yTexture,480,69,96));
        player.move(0.0f,-4.0f);
        if(player.getPosition().x < 381.f && player.getPosition().y < 375.f)
        {
            player.setPosition(player.getPosition().x, 375.f);
        }
        if(player.getPosition().x < 420.f && player.getPosition().y < 145.f)
        {
            player.setPosition(player.getPosition().x, 145.f);
        }

        if((player.getPosition().x > 482.f && player.getPosition().y < 90.f) && (player.getPosition().x < 664.f && player.getPosition().y < 90.f))
        {
            player.setPosition(player.getPosition().x, 90.f);
        }
    }
    }
    /**
     * @brief Funckja pozwala na poruszanie sie w dol lucznika (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_dol(RectangleShape & player)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        IdleAnim = 0;
        pozycja = 4;

            int yTexture = 0;
        yTexture = (int)player.getPosition().y / 50 % 9;
        yTexture*=69;

        player.setTextureRect(IntRect(yTexture,96,69,96));
        player.move(0.0f,3.0f);


        if(player.getPosition().x > 765.f && player.getPosition().y >472.f)
        {
            player.setPosition(player.getPosition().x, 472.f);
        }
        if(player.getPosition().x > 789.f && player.getPosition().y >354.f)
        {
            player.setPosition(player.getPosition().x, 354.f);
        }
        if(player.getPosition().x > 809.f && player.getPosition().y >324.f)
        {
            player.setPosition(player.getPosition().x, 324.f);
        }
        if(player.getPosition().x > 832.f && player.getPosition().y >308.f)
        {
            player.setPosition(player.getPosition().x, 308.f);
        }
        if(player.getPosition().x > 878.f && player.getPosition().y >293.f)
        {
            player.setPosition(player.getPosition().x, 293.f);
        }
        if(player.getPosition().x > 933.f && player.getPosition().y >178.f)
        {
            player.setPosition(player.getPosition().x, 178.f);
        }
        if(player.getPosition().x > 947.f && player.getPosition().y >148.f)
        {
            player.setPosition(player.getPosition().x, 148.f);
        }
        if(player.getPosition().x > 964.f && player.getPosition().y > -93.f)
        {
            player.setPosition(player.getPosition().x, -93.f);
        }

    }
    }
    /**
     * @brief Funckja pozwala na poruszanie sie w dol berserkera (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_dol_berserker(RectangleShape & player)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        IdleAnim = 0;
        pozycja = 4;

            int yTexture = 0;
        yTexture = (int)player.getPosition().y / 50 % 9;
        yTexture*=69;

        player.setTextureRect(IntRect(yTexture,96,69,96));
        player.move(0.0f,4.0f);


        if(player.getPosition().x > 765.f && player.getPosition().y >472.f)
        {
            player.setPosition(player.getPosition().x, 472.f);
        }
        if(player.getPosition().x > 789.f && player.getPosition().y >354.f)
        {
            player.setPosition(player.getPosition().x, 354.f);
        }
        if(player.getPosition().x > 809.f && player.getPosition().y >324.f)
        {
            player.setPosition(player.getPosition().x, 324.f);
        }
        if(player.getPosition().x > 832.f && player.getPosition().y >308.f)
        {
            player.setPosition(player.getPosition().x, 308.f);
        }
        if(player.getPosition().x > 878.f && player.getPosition().y >293.f)
        {
            player.setPosition(player.getPosition().x, 293.f);
        }
        if(player.getPosition().x > 933.f && player.getPosition().y >178.f)
        {
            player.setPosition(player.getPosition().x, 178.f);
        }
        if(player.getPosition().x > 947.f && player.getPosition().y >148.f)
        {
            player.setPosition(player.getPosition().x, 148.f);
        }
        if(player.getPosition().x > 964.f && player.getPosition().y > -93.f)
        {
            player.setPosition(player.getPosition().x, -93.f);
        }

    }
    }
    /**
     * @brief Funckja pozwala na poruszanie sie na ukos lewo gracza (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_ukos_lewo(RectangleShape & player)
    {
        if((Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::W) )|| (Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::S)))
    {
        int xTexture = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
        player.setTextureRect(IntRect(xTexture,674,69,96));
        player.move(-0.0f,0.0f);
    }
    }
    /**
     * @brief Funckja pozwala na poruszanie sie na ukos prawo gracza (wraz  z kolizja), oraz wyswietla tekstury
     * @param player - sprawdza pozycje playera
     */
    void poruszanie_ukos_prawo(RectangleShape & player)
    {
        if((Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::W) )||( Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::S)))
    {
        int xTexture = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
        player.setTextureRect(IntRect(xTexture,192,69,96));
        player.move(0.0f,0.0f);


    }
    }
    /**
     * @brief Funckja pozwalajaca na strzelanie playera, wykonuje rowniez odpowiednie tekstury
     * @param player - nadaje playerowi odpowiednia teksture
     * @param strzalka_gora - tekstura dla strzaly w gore
     * @param strzalka1 - tekstura dla strzaly w prawo
     * @param strzalka_lewo - tekstura dla strzaly w lewo
     * @param strzalka_dol - tekstura dla strzaly w dol
     * @param wektor_strzal_1 - wektor strzal przechowujacy strzaly ktore leca w lewa strone
     * @param wektor_strzal - wektor strzal przechowujacy strzaly ktore leca w prawa strone
     * @param wektor_strzal_dol - wektor strzal przechowujacy strzaly ktore leca w dol
     * @param wektor_strzal_gora - wektor strzal przechowujacy strzaly ktore leca w gore
     * @param strzalka - obiekt klasy strzal, przechowuje strzale ktora leci w prawo
     * @param strzalka_lewoo - obiekt klasy strzal, przechowuje strzale ktora leci w lewo
     * @param strzalka_goraa - obiekt klasy strzal, przechowuje strzale ktora leci w gore
     * @param strzalka_doll - obiekt klasy strzal, przechowuje strzale ktora leci w dol
     */
    void strzelanie(RectangleShape & player, Texture & strzalka_gora, Texture & strzalka1, Texture & strzalka_lewo, Texture & strzalka_dol,
                     vector <strzal> &wektor_strzal_1, vector <strzal> &wektor_strzal, vector <strzal> &wektor_strzal_dol, vector <strzal> &wektor_strzal_gora,
                     strzal &strzalka, strzal &strzalka_lewoo, strzal &strzalka_goraa, strzal &strzalka_doll)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::Space) || czy_strzela == true )
    {
        IdleAnim = 0;

        if(pozycja == 2)
        {
            if(ziara < 10)
        {
            czy_strzela = true;
            player.setTextureRect(IntRect(floor(ziara)*69,288,69,96));
            if( ziara > 8.2 && ziara < 8.5 )
            {
                dodaj_strzale(strzalka,wektor_strzal,player);
            }

        }
        if(ziara >= 10)
        {
            czy_strzela = false;
            ziara = 0;
        }

        }
        else if(pozycja == 1)
        {
            if(ziara < 10)
        {
            czy_strzela = true;

            player.setTextureRect(IntRect(floor(ziara)*69,768,69,96));
            if( ziara > 8.2 && ziara < 8.5 )
            {
                dodaj_strzale_lewo(strzalka_lewoo,wektor_strzal_1,player);
            }


        }
        if(ziara >= 10)
        {
            czy_strzela = false;
            ziara = 0;
        }
        }
        else if(pozycja == 3)
        {
            if(ziara < 10)
            {
                czy_strzela = true;
                player.setTextureRect(IntRect(floor(ziara)*69,864,69,96));

                if( ziara > 8.2 && ziara < 8.5 )
            {
                dodaj_strzale_gora(strzalka_goraa,wektor_strzal_gora,player);
            }

            }
            if(ziara >= 10)
            {
                czy_strzela = false;
                ziara = 0;
            }

        }
        else if(pozycja == 4)
        {
            if(ziara < 10)
            {
                czy_strzela = true;
                player.setTextureRect(IntRect(floor(ziara)*69,576,69,96));
                if( ziara > 8.2 && ziara < 8.5 )
                    {
                    dodaj_strzale_dol(strzalka_doll,wektor_strzal_dol,player);
                    }
            }
            if(ziara >= 10)
            {
                czy_strzela = false;
                ziara = 0;
            }
        }
    }
    }


/**
 *  @brief Funkcja usuwajaca strzaly z pamieci
 *  @param wektor_strzal - wektor przechowujacy strzaly
 */


    void usun_strzale_z_pamieci(vector <strzal> &wektor_strzal)
    {
        for(unsigned int i = 0; i < wektor_strzal.size(); ++i)
        {
            if(kolizja_strzaly(wektor_strzal[i]))
            {
                wektor_strzal.erase(wektor_strzal.begin()+i);
                break;
            }
        }
    }

};

/** @brief Funckja sprawdzajaca pozycje zombie, oraz ustawiajaca ich kolizje
 */
    void zombie_pozycja(){
    for(unsigned int i=0;i<wektor_zombie.size();i++){
        if(i==wektor_zombie.size()){
            break;
        }

        bool collision = false;
        for(unsigned int j=i+1;j<wektor_zombie.size();j++){
            if(wektor_zombie[i].shape.getGlobalBounds().intersects(wektor_zombie[j].shape.getGlobalBounds()) && wektor_zombie[j].atak == false){
                collision = true;
                break;
            }
        }
        wektor_zombie[i].zablokuj_ruszanie_sie = collision;
    }
}

/**
 *  @brief Funckaja pozwalajaca na wyswietlanie punktow w grze
 *  @param score - przechowuje ilosc zdobytych punktow
 *  @param tekscior - przechowuje czcionke do wyswietlania
 *  @param score_to_string - wyswietla zdobyte przez gracza punkty
 *  @param poziomek - przechowuje czcionke do wyswietlenia
 *  @param poziom - przechowuje aktualny poziom gry
 *  @param poziom_to_string - wyswietla aktualny poziom gry
 */

void convert_score(int &score, Text &tekscior, stringstream &score_to_string,Text &poziomek, int &poziom, stringstream &poziom_to_string)
{
    score_to_string.str("");
    poziom_to_string.str("");
    score_to_string << "Punkty: " << score;
    poziom_to_string << "Poziom: " << poziom;
    tekscior.setString(score_to_string.str());
    poziomek.setString(poziom_to_string.str());
    if(score >= 0 && score < 10)
    {
        poziom = 1;
    }
    else if(score >=10 && score < 20)
    {
        poziom = 2;
    }
    else if(score >= 20)
    {
        poziom = 3;
    }
}

/**
 *  @brief Funckja wyswietlajaca wszystkie punkty ktore zdobyl gracz
 *  @param score - przechwytuje wszystkie zdobyte punkty przez gracza
 *  @param end_score - tekst do wyswietlenia
 *  @param endzik_score - wyswietla na ostatnim ekranie ostateczna ilosc zdobytych punktow
 */

void ostateczne_punkty(int &score, Text &end_score, stringstream &endzik_score)
{

    endzik_score.str("");
    endzik_score << "Uzyskana ilosc punktow: " << score;
    end_score.setString(endzik_score.str());


}

/**
 *  @brief Funkcja sprawdza czy poziom zdrowia gracza jest rowne zero, jesli tak to wyswietla okno przegrania gry
 *  @param player - pozwala wyswietlic tekstura gracza
 *  @param window - wyswietla na ekranie odpowiednie tekstury
 */


void hp_rowne_zero(RectangleShape &player, sf::RenderWindow& window)
{

    if(hp <= 0 || hp_berserker <= 0)
        {
            Text end_score;
            Font czcionka;
            czcionka.loadFromFile("czcionka.TTF");
            end_score.setFont(czcionka);
            end_score.setFillColor(Color::White);
            end_score.setCharacterSize(50);
            end_score.setPosition(400.f,250.f);
            stringstream endzik_score;
            ostateczne_punkty(score,end_score,endzik_score);
            wektor_zombie.clear();
            Texture gleba;
            gleba.loadFromFile("ded.png");
            Sprite dedzik;
            dedzik.setTexture(gleba);
            delay2++;
            window.draw(dedzik);
            window.draw(player);
            window.draw(end_score);
            sf::Vector2u windowSize = window.getSize();
            float x = (windowSize.x - player.getSize().x) / 2;
            float y = (windowSize.y - player.getSize().y) / 2;
            player.setPosition(x, y);
            player.setScale(2.0,2.0);
            window.display();
            if(wykonaj == false)
                {
                    if(ziara4 < 10)
                      {
                        if(delay2 >= 5)
                         {
                            player.setTextureRect(IntRect(ziara4*69,384,69,96));
                            ziara4++;
                            delay2=0;
                         }

                       } else
                          {
                            wykonaj = true;
                          }

                }
                        window.display();
            if(Keyboard::isKeyPressed(Keyboard::Key::Escape))
                {
                    window.close();
                }
        }
}

int main() {

    ///< Stworzenie okna gry
    RenderWindow window(VideoMode(1366, 768), "SFML!", Style::Close);
    ///< Ustawienie ilosci FPS w grze
    window.setFramerateLimit(60);

    ///< Tworzenie wektora strzaly, ktora leci w prawa strone. £adowanie tekstury dla strzaly.
    Texture strzalka1;
    strzalka1.loadFromFile("lucznik.png");
    strzal strzalka(&strzalka1, 10, 5);
    vector<strzal> wektor_strzal;
    strzalka.shape.setTextureRect(IntRect(0,1056,44,10));

///< Tworzenie wektora strzaly, ktora leci w lewa strone. £adowanie tekstury dla strzaly.
    Texture strzalka_lewo;
    strzalka_lewo.loadFromFile("lucznik.png");
    strzal strzalka_lewoo(&strzalka_lewo, 10, 5);
    vector<strzal> wektor_strzal_1;
    strzalka_lewoo.shape.setTextureRect(IntRect(46,1056,46,10));

///< Tworzenie wektora strzaly, ktora leci w dol. £adowanie tekstury dla strzaly.
    Texture strzalka_dol;
    strzalka_dol.loadFromFile("lucznik.png");
    strzal strzalka_doll(&strzalka_dol, 10, 5);
    vector<strzal> wektor_strzal_dol;
    strzalka_doll.shape.setTextureRect(IntRect(9,1066,9,46));

///< Tworzenie wektora strzaly, ktora leci w gore. £adowanie tekstury dla strzaly.
     Texture strzalka_gora;
    strzalka_gora.loadFromFile("lucznik.png");
    strzal strzalka_goraa(&strzalka_gora, 10, 5);
    vector<strzal> wektor_strzal_gora;
    strzalka_goraa.shape.setTextureRect(IntRect(0,1066,9,46));

///< Stworzenie szurikena ktorym posluguje sie berserker. Szuriken porusza sie w prawo. Zaladowanie tekstury dla szurikena.
    Texture szuriken_prawo;
    szuriken_prawo.loadFromFile("berserker.png");
    strzal szuriken(&szuriken_prawo, 10, 5);
    szuriken.shape.setTextureRect(IntRect(33,1090,33,8));

///< Stworzenie szurikena ktorym posluguje sie berserker. Szuriken porusza sie w lewo. Zaladowanie tekstury dla szurikena.
    Texture szuriken_lewo;
    szuriken_lewo.loadFromFile("berserker.png");
    strzal szuriken_lewoo(&szuriken_lewo, 10, 5);
    szuriken_lewoo.shape.setTextureRect(IntRect(0,1090,33,8));

///< Stworzenie szurikena ktorym posluguje sie berserker. Szuriken porusza sie w dol. Zaladowanie tekstury dla szurikena.
    Texture szuriken_dol;
    szuriken_dol.loadFromFile("berserker.png");
    strzal szuriken_doll(&szuriken_dol, 10, 5);
    szuriken_doll.shape.setTextureRect(IntRect(0,1057,8,33));

    ///< Stworzenie szurikena ktorym posluguje sie berserker. Szuriken porusza sie w gore. Zaladowanie tekstury dla szurikena.
     Texture szuriken_gora;
    szuriken_gora.loadFromFile("berserker.png");
    strzal szuriken_goraa(&szuriken_gora, 10, 5);
    szuriken_goraa.shape.setTextureRect(IntRect(10,1057,8,33));

///< Stworzenie tekstur animacji dla wyboru postaci
    Texture chooseplayer1_texture;
    chooseplayer1_texture.loadFromFile("menuanima.png");

    Texture chooseplayer2_texture;
    chooseplayer2_texture.loadFromFile("menuanima.png");


///< Stworzenie i ustawienie tekstury dla gracza berserker
    RectangleShape player2(Vector2f(69.0f, 96.0f));
    player2.setPosition(500.0f,350.0f);

    Texture player1Texture;
    player1Texture.loadFromFile("berserker.png");

    RectangleShape chooseplayer2(Vector2f(274.0f, 343.0f));
    chooseplayer2.setPosition(256.0f, 137.0f);

    player2.setTextureRect(IntRect(0,0,69,96));

///< Stworzenie i ustawienie tekstury dla gracza lucznik
    RectangleShape player(Vector2f(69.0f, 96.0f));
    player.setPosition(500.0f,350.0f);

    Texture player2Texture;
    player2Texture.loadFromFile("lucznik.png");

    RectangleShape chooseplayer1(Vector2f(274.0f, 343.0f));
    chooseplayer1.setPosition(940.0f,136.0f);

    player.setTextureRect(IntRect(0,0,69,96));
    chooseplayer1.setTextureRect(IntRect(0,0,260,349));

///< Stworzenie tekstury dla zombie, oraz wywolanie metody zombie
    Texture zombie_player;
    zombie_player.loadFromFile("zombie.png");

    zombie zombi(&zombie_player);

    ///< Stworzenie czcionki do wyswietlania punktow w grze
    Text tekscior;
    Font czcionka;
    czcionka.loadFromFile("czcionka.TTF");
    tekscior.setFont(czcionka);
    tekscior.setFillColor(Color::White);
    tekscior.setCharacterSize(50);
    tekscior.setPosition(1125.f,20.f);
    stringstream score_to_string;

///< Stworzenie czcionki do wyswietlania poziomu w grze
    Text poziomek;
    poziomek.setFont(czcionka);
    poziomek.setFillColor(Color::White);
    poziomek.setCharacterSize(50);
    poziomek.setPosition(1125.f,60.f);
    stringstream poziom_to_string;

///< Stworzenie tekstury menu
    Texture menu;
    menu.loadFromFile("menu.png");
    Sprite sprajt;
    sprajt.setTexture(menu);

///< Stworzenie tekstury wyboru postaci
    Texture wybor;
    wybor.loadFromFile("wybor.png");

///< Stworzenie tesktury dla instruckji
    Texture instrukcja;
    instrukcja.loadFromFile("instrukcja_gotowa.png");

///< Stworzenie tekstury mapy docelowej
    Texture mapadocelowa;
    mapadocelowa.loadFromFile("mapkadocelowa.png");

///< Wyswietlenie postaci w wyborze postaci
    chooseplayer2.setTextureRect(IntRect(0,343,274,343));
    chooseplayer1.setTextureRect(IntRect(0,0,274,343));

///< Stworzenie muzyki w grze
    sf::Music music;
    if (!music.openFromFile("muzyka.ogg"))
        return -1;
    music.setVolume(25.f);
    music.play();

    while (window.isOpen())
    {
        delay++;
        if(czy_strzela == true)
        {
            ziara+=0.3;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

///< Wywolanie funkcji wybor postaci
wybor_postaci(bitmapa, window, chooseplayer1,chooseplayer2, chooseplayer1_texture, chooseplayer2_texture, IdleAnim, delay, done);
///< Wywolanie funkcji menu
cale_menu(bitmapa,window,done,player,player2,player1Texture,player2Texture);

///< Stworzenie obiektu klasy lucznik, wywolanie metod klasy
gracz lucznik;
lucznik.kolizja_ogolna(player);
lucznik.poruszanie_lewo(player);
lucznik.poruszanie_prawo(player);
lucznik.poruszanie_gora(player);
lucznik.poruszanie_dol(player);
lucznik.poruszanie_ukos_lewo(player);
lucznik.poruszanie_ukos_prawo(player);


///< Usuwanie strzal z pamieci
lucznik.usun_strzale_z_pamieci(wektor_strzal);
lucznik.usun_strzale_z_pamieci(wektor_strzal_1);
lucznik.usun_strzale_z_pamieci(wektor_strzal_dol);
lucznik.usun_strzale_z_pamieci(wektor_strzal_gora);


///< Stworzenie obiektu klasy berserk, wywolanie metod klasy
gracz berserker;
berserker.kolizja_ogolna(player2);
berserker.poruszanie_lewo_berserker(player2);
berserker.poruszanie_prawo_berserker(player2);
berserker.poruszanie_gora_berserker(player2);
berserker.poruszanie_dol_berserker(player2);
berserker.poruszanie_ukos_lewo(player2);
berserker.poruszanie_ukos_prawo(player2);

///< Usuwanie szurikenow z pamieci
berserker.usun_strzale_z_pamieci(wektor_strzal);
berserker.usun_strzale_z_pamieci(wektor_strzal_1);
berserker.usun_strzale_z_pamieci(wektor_strzal_dol);
berserker.usun_strzale_z_pamieci(wektor_strzal_gora);

///< Ten if pozwala nam na zablokowaniu dublowania sie strzal, hp gracza, oraz na wyswietlaniu tesktury umierania gracza
if(kontroluj_strzal == 0)
{
    berserker.strzelanie(player2, szuriken_gora, szuriken_prawo, szuriken_lewo, szuriken_dol,
                   wektor_strzal_1, wektor_strzal, wektor_strzal_dol, wektor_strzal_gora,
                   szuriken, szuriken_lewoo, szuriken_goraa, szuriken_doll);
                   berserker.initHP(player2);
                   berserker.update_hp_berserker();
                   sprawdz_pozycje(player2, pozycja, IdleAnim, delay, hp_berserker);


}
else if(kontroluj_strzal == 1)
{
    lucznik.strzelanie(player, strzalka_gora, strzalka1, strzalka_lewo, strzalka_dol,
                   wektor_strzal_1, wektor_strzal, wektor_strzal_dol, wektor_strzal_gora,
                   strzalka, strzalka_lewoo, strzalka_goraa, strzalka_doll);
                   lucznik.initHP(player);
                   lucznik.update_hp();
                   sprawdz_pozycje(player, pozycja, IdleAnim, delay, hp);
}

///< Wyswietla punkty w grze
convert_score(score,tekscior, score_to_string, poziomek, poziom, poziom_to_string);

///< W zaleznosci od zdobytych punktow, poziom gry sie zwieksza i tworzy sie wiecej potworow
if(score >= 0 && score < 10)
{
    if(wektor_zombie.size() < 3)
    {
        laduj_zombie(czas_respu_zombie, zombi, wektor_zombie, score);
    }
}
else if(score >= 10 && score < 20)
{
    if(wektor_zombie.size() <= 3)
    {
        laduj_zombie(czas_respu_zombie, zombi, wektor_zombie, score);
    }
}
else if(score >= 20)
{
   if(wektor_zombie.size() <= 4)
    {
        laduj_zombie(czas_respu_zombie, zombi, wektor_zombie, score);
    }
}

    window.clear();
    ///< W tych if'ach sprawdzamy w ktorym miejscu dokladnie jestesmy.
    if(bitmapa == 0)
    {
        wektor_zombie.clear();
        sprajt.setTexture(menu);
        window.draw(sprajt);
    }
    else if(bitmapa == 1)
    {
        sprajt.setTexture(wybor);
        window.draw(sprajt);
        if(done == 3)
            {
                window.draw(chooseplayer1);
            }
        if(done == 4)
            {
                window.draw(chooseplayer2);
            }
    } else if(bitmapa == 2)
    {
        sprajt.setTexture(instrukcja);
        window.draw(sprajt);
    }
    else if(bitmapa == 3)
    {
        sprajt.setTexture(mapadocelowa);
        window.draw(sprajt);
        lucznik.render_hp(window);
        berserker.render_hp(window);
        window.draw(tekscior);
        window.draw(poziomek);
        if(hp <= 0)
        hp_rowne_zero(player, window);

        if(hp_berserker<= 0)
        hp_rowne_zero(player2, window);

            if(done == 1)
            {
                kontroluj_strzal = 0; // zmienna potrzebna aby sie strzaly nie dublowaly
                przyjmowanie_strzal(wektor_zombie,wektor_strzal, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_1, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_dol, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_gora, score);
                window.draw(player2);
                zombie_pozycja();
                    for(unsigned int i=0; i<wektor_zombie.size(); ++i)
                        {
                            wektor_zombie[i].respienie_zombie(score);
                            wektor_zombie[i].poruszanie(player2);
                            wektor_zombie[i].bitka(player2, hp_berserker);
                            window.draw(wektor_zombie[i].shape);
                            wektor_zombie[i].render_hp(window);
                            wektor_zombie[i].initHP();
                            wektor_zombie[i].update_hp();
                        }
            }
            else if(done == 2)
            {
                kontroluj_strzal = 1;// zmienna potrzebna aby sie strzaly nie dublowaly
                przyjmowanie_strzal(wektor_zombie,wektor_strzal, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_1, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_dol, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_gora, score);
                window.draw(player);
                zombie_pozycja();
                    for(unsigned int i=0; i<wektor_zombie.size(); ++i)
                        {
                            wektor_zombie[i].respienie_zombie(score);
                            wektor_zombie[i].poruszanie(player);
                            wektor_zombie[i].bitka(player, hp);
                            window.draw(wektor_zombie[i].shape);
                            wektor_zombie[i].render_hp(window);
                            wektor_zombie[i].initHP();
                            wektor_zombie[i].update_hp();
                        }
            }
    }

      narysuj_strzale(wektor_strzal,window);
      narysuj_strzale_lewo(wektor_strzal_1,window);
      narysuj_strzale_dol(wektor_strzal_dol,window);
      narysuj_strzale_gora(wektor_strzal_gora,window);

    window.display();
    }
    return 0;
}
