#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>
#include "strzelanie_player1.h"


using namespace sf;
using namespace std;

/**
 * @brief Klasa zombie
 * @param hpBarBack - wyswietlanie szarego paska hp
 * @param hpBarInside - wyswietlanie czerwonego paska hp
 * @param MAXhp_lucznik - maksymalny poziom zdrowia lucznika
 * @param MAXhp_berserker - maksymalny poziom zdrowia berserkera
 * @param width - szerokosc paska zdrowia
 * @param height - wysokosc paska zdrowia
 * @param hpBarMaxWidth - maksymalna szerokosc paska zdrowia
 * @param ziara2 - pozwala na wyswietlenie tekstury (animacji) potwora
 * @param ziara3 - pozwala na wyswietlenie tekstury (animacji) potwora
 * @param ziara4 - pozwala na wyswietlenie tekstury (animacji) potwora
 * @param czy_sie_respi - pozwala na sprawdzenie, czy potwor sie pojawil
 * @param atak - pozwala na sprawdzenie czy potwor zaatakowal gracza
 * @param zablokuj_ruszanie_sie - pozwala na zablokowanie potworow gdy na siebie nachodza
 * @param shape - pozwala na wyswietlenie tekstur
 * @param delay - pozwalajaca na opoznienie aktualnie wykonywanej tekstury
 * @param delay1 - pozwalajaca na opoznienie aktualnie wykonywanej tekstury
 * @param delay2 - pozwalajaca na opoznienie aktualnie wykonywanej tekstury
 * @param spr_pozycje_zombie - sprawdza aktualna pozycje zombie, w zaleznosci od pozycji wyswietla sie odpowiednia tekstura
 */

class zombie
{
public:

    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInside;
    float MAXhp = 3;
    float hp_zombie = 3;
    float width = 50.f;
    float hpBarMaxWidth = width;
    float height = 10.f;

    int ziara2 = 0;
    int ziara3 = 0;
    int ziara4 = 0;
    bool czy_sie_respi = true;
    bool atak = false;
    bool zablokuj_ruszanie_sie = false;

    Sprite shape;
    int delay=0;
    int delay1=0;
    int delay2=0;
    int spr_pozycje_zombie=0;





/**
 *  @brief Kontruktor klasy zombie.
 *  @param zombie_txt - pozwala na wyswietlenie tekstury zombie
 */
    zombie(Texture *zombie_txt)
    {
        shape.setTexture(*zombie_txt);
        shape.setTextureRect(IntRect(0,684,80,76));
    }
    /**
 *  @brief Funkcja wyswietlajaca dwa paski zdrowia zombie
 *  @param target - pozwala na wyswietlenie paskow zdrowia
 */
    void render_hp(sf::RenderTarget & target)
    {
        target.draw(hpBarBack);
        target.draw(hpBarInside);
    }

    /**
     *  @brief Funkcja pozwalajaca na ustawienie pozycji oraz kolorow paskow zdrowia
     */
    void initHP()
    {
        hpBarBack.setSize(sf::Vector2f(width,height));
        hpBarBack.setFillColor(sf::Color(50,50,50,200));
        hpBarBack.setPosition(shape.getPosition().x,shape.getPosition().y - 35);

        hpBarInside.setSize(sf::Vector2f(width,height));
        hpBarInside.setFillColor(sf::Color(250,20,20,200));
        hpBarInside.setPosition(hpBarBack.getPosition());
    }
    /**
     *  @brief Funckja sprawdza i modyfikuje aktualny poziom zdrowia
     */
    void update_hp()
    {

        float procent = static_cast<float>(hp_zombie) / static_cast<float>(MAXhp);
        hpBarInside.setSize(sf::Vector2f(static_cast<float>(std::floor(hpBarMaxWidth * procent)), hpBarInside.getSize().y));
    }


    /**
     *  @brief Funckja wyswietla animacje zombiego, ktory wstaje z Ziemii.
     *  @param score - W zaleznosci od zdobytych punktow, poziom zdrowia zombie sie zwieksza
     */

    void respienie_zombie(int &score)
    {
            if(czy_sie_respi == true)
            {
                if(score >= 5 && score < 10)
                    {
                        hp_zombie  = 4;
                        MAXhp  = 4;
                    }
                else if(score >= 10 && score < 20)
                {
                    hp_zombie  = 5;
                        MAXhp  = 5;
                }
                else if(score >=20)
                {
                    hp_zombie  = 6;
                        MAXhp  = 6;
                }
                if(ziara2 < 6)
                {
                    if(delay >= 20)
                    {
                       shape.setTextureRect(IntRect(ziara2*80,684,80,76));
                        ziara2++;
                       delay=0;
                    }
                    else
                    {
                        delay++;
                    }
                }
                else
                {
                    czy_sie_respi = false;
                    shape.setTextureRect(IntRect(0,0,80,76));
                }
            }
}

    /**
     *  @brief Funckja pozwala na poruszanie sie zombi. Dodalismy rowniez kolizje dla zombie.
     *  @param player - pobieramy sobie playera aby zombie znalazl do gracza najktotsza droge
     */
    void poruszanie(RectangleShape & player)
    {
        if(czy_sie_respi == false && atak == false && zablokuj_ruszanie_sie == false)
        {
            if((shape.getPosition().x - player.getPosition().x) < 0)
        {
        int xTexture = 0;
        spr_pozycje_zombie=0;
        xTexture = (int)shape.getPosition().x / 25 % 9;
        xTexture*=80;
        shape.setTextureRect(IntRect(xTexture,304,80,76));
        shape.move(1.0f,0.0f);

        if(shape.getPosition().x > 765.f && shape.getPosition().y >472.f)
        {
            shape.setPosition(765.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 789.f && shape.getPosition().y >354.f)
        {
            shape.setPosition(789.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 809.f && shape.getPosition().y >324.f)
        {
            shape.setPosition(809.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 832.f && shape.getPosition().y >308.f)
        {
            shape.setPosition(832.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 878.f && shape.getPosition().y >293.f)
        {
            shape.setPosition(878.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 933.f && shape.getPosition().y >178.f)
        {
            shape.setPosition(933.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 947.f && shape.getPosition().y >148.f)
        {
            shape.setPosition(947.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 964.f && shape.getPosition().y > -93.f)
        {
            shape.setPosition(964.f, shape.getPosition().y);
        }
        if((shape.getPosition().x > 482.f && shape.getPosition().y < 90.f) && (shape.getPosition().x < 664.f && shape.getPosition().y < 90.f))
        {
            shape.setPosition(482.f, shape.getPosition().y);
        }if(shape.getPosition().x > 765.f && shape.getPosition().y >472.f)
        {
            shape.setPosition(765.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 789.f && shape.getPosition().y >354.f)
        {
            shape.setPosition(789.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 809.f && shape.getPosition().y >324.f)
        {
            shape.setPosition(809.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 832.f && shape.getPosition().y >308.f)
        {
            shape.setPosition(832.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 878.f && shape.getPosition().y >293.f)
        {
            shape.setPosition(878.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 933.f && shape.getPosition().y >178.f)
        {
            shape.setPosition(933.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 947.f && shape.getPosition().y >148.f)
        {
            shape.setPosition(947.f, shape.getPosition().y);
        }
        if(shape.getPosition().x > 964.f && shape.getPosition().y > -93.f)
        {
            shape.setPosition(964.f, shape.getPosition().y);
        }
        if((shape.getPosition().x > 482.f && shape.getPosition().y < 90.f) && (shape.getPosition().x < 664.f && shape.getPosition().y < 90.f))
        {
            shape.setPosition(482.f, shape.getPosition().y);
        }
    }
    else if((shape.getPosition().x + player.getPosition().x) > 0)
    {
        int xTexture = 0;
        spr_pozycje_zombie=1; //lewo
        xTexture = (int)shape.getPosition().x / 25 % 9;
        xTexture*=80;
        shape.setTextureRect(IntRect(xTexture,152,80,76));
        shape.move(-1.0f,0.0f);
        if(shape.getPosition().x < 381.f && shape.getPosition().y < 375.f)
                {
                shape.setPosition(381.f, shape.getPosition().y);
                }
            if(shape.getPosition().x < 420.f && shape.getPosition().y < 145.f)
                {
                shape.setPosition(420.f, shape.getPosition().y);
                }

            if((shape.getPosition().x > 551.f && shape.getPosition().y < 90.f) && (shape.getPosition().x < 664.f && shape.getPosition().y < 90.f))
                {
            shape.setPosition(664.f, shape.getPosition().y);
                }
    }
     if((shape.getPosition().y - player.getPosition().y) < 0)
    {
        int yTexture = 0;
        spr_pozycje_zombie=2;
        yTexture = (int)shape.getPosition().y / 25 % 9;
        yTexture*=80;
        shape.setTextureRect(IntRect(yTexture,228,80,76));
        shape.move(0.0f,1.0f);
    }
    else if((shape.getPosition().y - player.getPosition().y) > 0)
    {
        int yTexture = 0;
        spr_pozycje_zombie=3;
        yTexture = (int)shape.getPosition().y / 25 % 9;
        yTexture*=80;
        shape.setTextureRect(IntRect(yTexture,76,80,76));
        shape.move(0.0f,-1.0f);

        if(shape.getPosition().x < 381.f && shape.getPosition().y < 375.f)
        {
            shape.setPosition(shape.getPosition().x, 375.f);
        }
        if(shape.getPosition().x < 420.f && shape.getPosition().y < 145.f)
        {
            shape.setPosition(shape.getPosition().x, 145.f);
        }

        if((shape.getPosition().x > 482.f && shape.getPosition().y < 90.f) && (shape.getPosition().x < 664.f && shape.getPosition().y < 90.f))
        {
            shape.setPosition(shape.getPosition().x, 90.f);
        }
    }
        }

    }

    /**
     *  @brief Funckja pokazuje animacje ataku zombie na gracza.
     *  @param player - sprawdzamy czy zombie wchodzi w interakcje z playerem
     *  @param hp - pobieramy poziom zdrowia gracza, po ataku zombie na gracza poziom zdrowia sie zmiejsza
     */
    void bitka(RectangleShape & player, float &hp)
    {
        if(shape.getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            if(atak == false)
            {
                atak = true;
            }

        }
        if(atak == true)
            {

                if(ziara3 < 13)
                {
                    if(delay1 >= 5)
                    {
                        if(spr_pozycje_zombie == 0)//bitka prawo
                        {
                            shape.setTextureRect(IntRect(ziara3*80,608,80,76));
                            ziara3++;
                            delay1=0;
                        }
                        else if(spr_pozycje_zombie == 1) //bitka lewo
                        {
                            shape.setTextureRect(IntRect(ziara3*80,456,80,76));
                            ziara3++;
                            delay1=0;
                        }
                        else if(spr_pozycje_zombie == 2) // bitka dol
                        {
                            shape.setTextureRect(IntRect(ziara3*80,532,80,76));
                            ziara3++;
                            delay1=0;
                        }
                        else if(spr_pozycje_zombie == 3) //bitka gora
                        {
                            shape.setTextureRect(IntRect(ziara3*80,380,80,76));
                            ziara3++;
                            delay1=0;
                        }

                        if(ziara3 == 8 && hp>0)
                        {
                            hp-=1;
                        }


                    }
                    else
                    {
                        delay1++;
                        delay2++;
                    }

                }
                else
                {
                    atak = false;
                    ziara3=0;
                    shape.setTextureRect(IntRect(0,0,80,76));

                }

            }
    }
};

void cale_menu(int & bitmapa, RenderWindow & window, int &done, RectangleShape & player, RectangleShape & player2, Texture & player1Texture, Texture & player2Texture);
void laduj_zombie(int &czas_respu, zombie zombi, vector <zombie> &zombie_wektor, int &score);
void przyjmowanie_strzal(vector <zombie> &zombie_wektor,vector <strzal> &wektor_strzal,int &score);


