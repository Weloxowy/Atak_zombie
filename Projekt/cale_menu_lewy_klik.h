#include <SFML/Graphics.hpp>
#include <iostream>
//#include <Animation.h>
#include <windows.h>
#include <math.h>
#include <vector>
#include "strzelanie_player1.h"


using namespace sf;
using namespace std;



class zombie
{
public:

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
    bool wykonaj = false;
    int spr_pozycje_zombie=0;

        sf::RectangleShape hpBarBack;
        sf::RectangleShape hpBarInside;
        float MAXhp = 3;
        float hp_zombie = 3;
        float width = 50.f;
        float hpBarMaxWidth = width;
        float height = 10.f;
        float x = 1250.f;
        float y = 20.f;




    zombie(Texture *zombie_txt)
    {
        shape.setTexture(*zombie_txt);
        shape.setTextureRect(IntRect(0,684,80,76));
    }
    void render_hp(sf::RenderTarget & target)
    {
        target.draw(hpBarBack);
        target.draw(hpBarInside);
    }

    void initHP()
    {
        //szary pasek hp
        hpBarBack.setSize(sf::Vector2f(width,height));
        hpBarBack.setFillColor(sf::Color(50,50,50,200));
        hpBarBack.setPosition(shape.getPosition().x,shape.getPosition().y - 35);

        //czerwony pasek hp
        hpBarInside.setSize(sf::Vector2f(width,height));
        hpBarInside.setFillColor(sf::Color(250,20,20,200));
        hpBarInside.setPosition(hpBarBack.getPosition());

    }
    void update_hp()
    {
        float procent = static_cast<float>(hp_zombie) / static_cast<float>(MAXhp);
        hpBarInside.setSize(sf::Vector2f(static_cast<float>(std::floor(hpBarMaxWidth * procent)), hpBarInside.getSize().y));
    }

    void respienie_zombie()
    {
            if(czy_sie_respi == true)
            {
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

    void poruszanie(RectangleShape & player)
    {


        if(czy_sie_respi == false && atak == false && zablokuj_ruszanie_sie == false)
        {
            if((shape.getPosition().x - player.getPosition().x) < 0)
        {
        //prawo
        int xTexture = 0;
        spr_pozycje_zombie=0; //prawo
        //IdleAnim = 0;
        xTexture = (int)shape.getPosition().x / 25 % 9;
        xTexture*=80;
        shape.setTextureRect(IntRect(xTexture,304,80,76));
        shape.move(1.0f,0.0f);
    }
    else if((shape.getPosition().x + player.getPosition().x) > 0)
    {
        //lewo
        int xTexture = 0;
        spr_pozycje_zombie=1; //lewo
      //  IdleAnim = 0;
        xTexture = (int)shape.getPosition().x / 25 % 9;
        xTexture*=80;
        shape.setTextureRect(IntRect(xTexture,152,80,76));
        shape.move(-1.0f,0.0f);
    }
     if((shape.getPosition().y - player.getPosition().y) < 0)
    {
        //dol
      //  IdleAnim = 0;
        int yTexture = 0;
        spr_pozycje_zombie=2; //dol
        yTexture = (int)shape.getPosition().y / 25 % 9;
        yTexture*=80;

        shape.setTextureRect(IntRect(yTexture,228,80,76));
        shape.move(0.0f,1.0f);
    }
    else if((shape.getPosition().y - player.getPosition().y) > 0)
    {
        //gora
       // IdleAnim = 0;
        int yTexture = 0;
        spr_pozycje_zombie=3; //gora
        yTexture = (int)shape.getPosition().y / 25 % 9;
        yTexture*=80;

        shape.setTextureRect(IntRect(yTexture,76,80,76));
        shape.move(0.0f,-1.0f);
    }
        }

    }

    //zombie.setFillColor(); to na przyszlosc
    void bitka(RectangleShape & player, float &hp, sf::RenderWindow& window, bool powtorz, int &bitmapa, int &score)
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
                                while(hp <= 0)
                                {
                                    Texture gleba;
                                    gleba.loadFromFile("ded.png");
                                    Sprite dedzik;
                                    dedzik.setTexture(gleba);
                                    delay2++;
                                    window.clear(Color::Black);
                                    window.draw(dedzik);
                                    window.draw(player);
                                    sf::Vector2u windowSize = window.getSize();
                                    float x = (windowSize.x - player.getSize().x) / 2;
                                    float y = (windowSize.y - player.getSize().y) / 2;
                                    player.setPosition(x, y);
                                    player.setScale(2.0,2.0);

                                    // dolaczyc wyniki
                                    // dwa guziki (wyjscie i powrot do menu)
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

                                            }
                                            else
                                            {
                                               wykonaj = true;
                                            }
                                    }

                                    window.display();

                                        if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(window).x > 480 && Mouse::getPosition(window).x < 615 && Mouse::getPosition(window).y >615 && Mouse::getPosition(window).y <712)
                                        {
                                            Sleep(200);
                                            exit(0);
                                        }
                                        //dokonczyc wychodzenie

                                            /*
                                            Event event;
                                            if (event.type == Event::Closed)
                                                {
                                                    window.close();
                                                }
                                                */


                                }
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
//void sprawdz_zombie(vector <zombie> &wektor_zombie);

void cale_menu(int & bitmapa, RenderWindow & window, int &done, RectangleShape & player, RectangleShape & player2, Texture & player1Texture, Texture & player2Texture,int &IdleAnim);
void laduj_zombie(int &czas_respu, zombie zombi, vector <zombie> &zombie_wektor);
void przyjmowanie_strzal(vector <zombie> &zombie_wektor,vector <strzal> &wektor_strzal,int &score);
