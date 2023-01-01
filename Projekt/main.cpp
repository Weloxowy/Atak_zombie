#include <SFML/Graphics.hpp>
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
#include "klasa_postac.h"

using namespace sf;
using namespace std;
int bitmapa = 0;
int done = 0; // wybor postaci
const unsigned WINDOW_WIDTH = 1366; // na podstawie koordynatow naszej mapy ustawiamy kolizje
const unsigned WINDOW_HEIGHT = 768; // na podstawie koordynatow naszej mapy ustawiamy kolizje
int pozycja = 0;
int delay = 0;
int IdleAnim = 0;
bool czy_strzela = false;
float ziara = 0;
int czas_strzaly = 0;
int czas_respu_zombie=10000;
float hp=1000;
int score = 0;
int poziom = 1;
bool powtorz = false;
vector <zombie> wektor_zombie;



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

class gracz
{
    public:
        sf::RectangleShape hpBarBack;
        sf::RectangleShape hpBarInside;
        //float hp;
        ///POPRAWIC HP ZEBY BYLO MODYFIKOWANE W KLASIE!
        float MAXhp = 10;
        float width = 50.f;
        float hpBarMaxWidth = width;
        float height = 10.f;
        float x = 1250.f;
        float y = 20.f;



    void render_hp(sf::RenderTarget & target)
    {
        target.draw(hpBarBack);
        target.draw(hpBarInside);
    }

    void initHP(RectangleShape & player)
    {
        //szary pasek hp
        hpBarBack.setSize(sf::Vector2f(width,height));
        hpBarBack.setFillColor(sf::Color(50,50,50,200));
        hpBarBack.setPosition(player.getPosition().x,player.getPosition().y - 35);

        //czerwony pasek hp
        hpBarInside.setSize(sf::Vector2f(width,height));
        hpBarInside.setFillColor(sf::Color(250,20,20,200));
        hpBarInside.setPosition(hpBarBack.getPosition());

    }
    void update_hp()
    {
        float procent = static_cast<float>(hp) / static_cast<float>(MAXhp);
        hpBarInside.setSize(sf::Vector2f(static_cast<float>(std::floor(hpBarMaxWidth * procent)), hpBarInside.getSize().y));
    }

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
                break;
            }
        }
        //sprawdzenie czy strzala wyleciala z pamieci
        //cout << wektor_strzal.size() << endl;
    }

};


    void zombie_pozycja(){
    for(int i=0;i<wektor_zombie.size();i++){
        if(i==wektor_zombie.size()){
            break;
        }

        bool collision = false;
        for(int j=i+1;j<wektor_zombie.size();j++){
            if(wektor_zombie[i].shape.getGlobalBounds().intersects(wektor_zombie[j].shape.getGlobalBounds()) && wektor_zombie[j].atak == false){
                collision = true;
                break;
            }
        }
        wektor_zombie[i].zablokuj_ruszanie_sie = collision;
    }
}


void convert_score(int &score, Text &tekscior, stringstream &score_to_string,Text &poziomek, int &poziom, stringstream &poziom_to_string)
{
    score_to_string.str("");
    poziom_to_string.str("");
    score_to_string << "Score: " << score;
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

int main() {

    RenderWindow window(VideoMode(1366, 768), "SFML!", Style::Close);
    window.setFramerateLimit(60);
    //lucznik
    RectangleShape player(Vector2f(69.0f, 96.0f));
    player.setPosition(500.0f,350.0f);


    Texture strzalka1;
    strzalka1.loadFromFile("lucznik.png");
    strzal strzalka(&strzalka1, 10, 5);
    vector<strzal> wektor_strzal;
    strzalka.shape.setTextureRect(IntRect(0,1056,44,10));


    Texture strzalka_lewo;
    strzalka_lewo.loadFromFile("lucznik.png");
    strzal strzalka_lewoo(&strzalka_lewo, 10, 5);
    vector<strzal> wektor_strzal_1;
    strzalka_lewoo.shape.setTextureRect(IntRect(46,1056,46,10));


    Texture strzalka_dol;
    strzalka_dol.loadFromFile("lucznik.png");
    strzal strzalka_doll(&strzalka_dol, 10, 5);
    vector<strzal> wektor_strzal_dol;
    strzalka_doll.shape.setTextureRect(IntRect(9,1066,9,46));

     Texture strzalka_gora;
    strzalka_gora.loadFromFile("lucznik.png");
    strzal strzalka_goraa(&strzalka_gora, 10, 5);
    vector<strzal> wektor_strzal_gora;
    strzalka_goraa.shape.setTextureRect(IntRect(0,1066,9,46));




    RectangleShape chooseplayer1(Vector2f(274.0f, 343.0f));
    chooseplayer1.setPosition(940.0f,136.0f);

    Texture chooseplayer1_texture;
    chooseplayer1_texture.loadFromFile("menuanima.png");

    RectangleShape chooseplayer2(Vector2f(274.0f, 343.0f));
    chooseplayer2.setPosition(256.0f, 137.0f);

    Texture chooseplayer2_texture;
    chooseplayer2_texture.loadFromFile("menuanima.png");


    //player 2
    RectangleShape player2(Vector2f(100.0f, 100.0f));
    player2.setPosition(100.0f,100.0f);

    Texture player1Texture;
    player1Texture.loadFromFile("cat.png");

    Texture player2Texture;
    player2Texture.loadFromFile("lucznik.png");

    player.setTextureRect(IntRect(0,0,69,96));
    chooseplayer1.setTextureRect(IntRect(0,0,260,349));


    Texture zombie_player;
    zombie_player.loadFromFile("zombie.png");

        zombie zombi(&zombie_player);


    Text tekscior;
    Font czcionka;
    czcionka.loadFromFile("czcionka.TTF");
    tekscior.setFont(czcionka);
    tekscior.setFillColor(Color::White);
    tekscior.setCharacterSize(50);
    tekscior.setPosition(1125.f,20.f);
    stringstream score_to_string;

    Text poziomek;
    poziomek.setFont(czcionka);
    poziomek.setFillColor(Color::White);
    poziomek.setCharacterSize(50);
    poziomek.setPosition(1125.f,60.f);
    stringstream poziom_to_string;

    //wladowac menu
    Texture menu;
    menu.loadFromFile("menu.png");
    Sprite sprajt;
    sprajt.setTexture(menu);

    //wybor postaci
    Texture wybor;
    wybor.loadFromFile("wybor.png");
    // Sprite moze byc jeden, ale mamy do wyboru duzo Texture (tyle ile sobie zadeklarujemy j.w)

    //wczytanie tekstury graficznej
    Texture instrukcja;
    instrukcja.loadFromFile("instrukcja_gotowa.png");

    //wczytanie mapy docelowej
    Texture mapadocelowa;
    mapadocelowa.loadFromFile("mapkadocelowa.png");


    chooseplayer2.setTextureRect(IntRect(0,343,274,343));
    chooseplayer1.setTextureRect(IntRect(0,0,274,343));


    while (window.isOpen())
    {
        delay++;
        czas_strzaly++;
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



wybor_postaci(bitmapa, window, chooseplayer1,chooseplayer2, chooseplayer1_texture, chooseplayer2_texture, IdleAnim, delay, done);
cale_menu(bitmapa,window,done,player,player2,player1Texture,player2Texture, IdleAnim);
sprawdz_pozycje(player, pozycja, IdleAnim, delay);


gracz lucznik;
lucznik.kolizja_ogolna(player);
lucznik.poruszanie_lewo(player);
lucznik.poruszanie_prawo(player);
lucznik.poruszanie_gora(player);
lucznik.poruszanie_dol(player);
lucznik.poruszanie_ukos_lewo(player);
lucznik.poruszanie_ukos_prawo(player);

lucznik.strzelanie(player, strzalka_gora, strzalka1, strzalka_lewo, strzalka_dol,
                   wektor_strzal_1, wektor_strzal, wektor_strzal_dol, wektor_strzal_gora,
                   strzalka, strzalka_lewoo, strzalka_goraa, strzalka_doll);

lucznik.usun_strzale_z_pamieci(wektor_strzal);
lucznik.usun_strzale_z_pamieci(wektor_strzal_1);
lucznik.usun_strzale_z_pamieci(wektor_strzal_dol);
lucznik.usun_strzale_z_pamieci(wektor_strzal_gora);

lucznik.initHP(player);
lucznik.update_hp();
convert_score(score,tekscior, score_to_string, poziomek, poziom, poziom_to_string);

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






    if(Keyboard::isKeyPressed(Keyboard::Key::A))
        player2.move(-1.5f,0.0f);
    if(Keyboard::isKeyPressed(Keyboard::Key::D))
        player2.move(1.5f,0.0f);
    if(Keyboard::isKeyPressed(Keyboard::Key::W))
        player2.move(0.0f,-1.5f);
    if(Keyboard::isKeyPressed(Keyboard::Key::S))
        player2.move(0.0f,1.5f);







    window.clear();
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
        window.draw(tekscior);
        window.draw(poziomek);


            if(done == 1)
            {
                window.draw(player2);
                    for(int i=0; i<wektor_zombie.size(); ++i)
                        {
                            window.draw(wektor_zombie[i].shape);
                        }
            }
            else if(done == 2)
            {

                przyjmowanie_strzal(wektor_zombie,wektor_strzal, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_1, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_dol, score);
                przyjmowanie_strzal(wektor_zombie,wektor_strzal_gora, score);
                window.draw(player);
                zombie_pozycja();
                    for(int i=0; i<wektor_zombie.size(); ++i)
                        {

                            wektor_zombie[i].respienie_zombie(score);
                            wektor_zombie[i].poruszanie(player);
                            wektor_zombie[i].bitka(player, hp, window, powtorz, bitmapa, score);
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
