/*#include <SFML/Graphics.hpp>
#include <iostream>

#include <windows.h>
#include <math.h>


using namespace sf;
using namespace std;


class gracz
{
    public:

    void kolizja_ogolna(RectangleShape & player)
    {
        // lewa kolizja
        if(player.getPosition().x < 0.f)
            player.setPosition(0.f, player.getPosition().y);
        // gorna kolizja
        if(player.getPosition().y < 0.f)
            player.setPosition(player.getPosition().x,0.f);
         // prawa kolizja
        if(player.getPosition().x + player.getGlobalBounds().width > WINDOW_WIDTH)
            player.setPosition(WINDOW_WIDTH - player.getGlobalBounds().width, player.getPosition().y);
        // kolizja dolna
        if(player.getPosition().y + player.getGlobalBounds().height > WINDOW_HEIGHT)
            player.setPosition(player.getPosition().x, WINDOW_HEIGHT - player.getGlobalBounds().height);
    }
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

            //kolizje dla lewych drzew
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

        if((player.getPosition().x > 551.f && player.getPosition().y < 90.f) && (player.getPosition().x < 664.f && player.getPosition().y < 90.f))
        {
            player.setPosition(player.getPosition().x, 90.f);
        }
    }
    }
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
    void poruszanie_ukos_lewo(RectangleShape & player)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        int xTexture = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
        player.setTextureRect(IntRect(xTexture,674,69,96));
        player.move(-0.0f,0.0f);
    }
    }
    void poruszanie_ukos_prawo(RectangleShape & player)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        int xTexture = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
        player.setTextureRect(IntRect(xTexture,192,69,96));
        player.move(0.0f,0.0f);


    }
    }

    void strzelanie(RectangleShape & player, Texture & strzalka_gora, Texture & strzalka1, Texture & strzalka_lewo, Texture & strzalka_dol,
                     vector <strzal> &wektor_strzal_1, vector <strzal> &wektor_strzal, vector <strzal> &wektor_strzal_dol, vector <strzal> &wektor_strzal_gora,
                     strzal &strzalka, strzal &strzalka_lewoo, strzal &strzalka_goraa, strzal &strzalka_doll)
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::Space) || czy_strzela == true )
    {
                // strzela szybko, aby opoznic trzeba zastanowic sie nad delay
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


    void usun_strzale_z_pamieci(vector <strzal> &wektor_strzal)
    {
        for(int i = 0; i < wektor_strzal.size(); ++i)
        {
            if(kolizja_strzaly(wektor_strzal[i]))
            {
                wektor_strzal.erase(wektor_strzal.begin()+i);
            }
        }
        //sprawdzenie czy strzala wyleciala z pamieci
        //cout << wektor_strzal.size() << endl;
    }

};
*/
