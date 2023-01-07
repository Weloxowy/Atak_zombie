#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include "cale_menu_lewy_klik.h"
#include "isAnyKeyPressed.h"

using namespace sf;
using namespace std;


void laduj_zombie(int &czas_respu, zombie zombi, vector <zombie> &zombie_wektor, int &score)
{
    czas_respu++;
    if(czas_respu > 200)
    {
        int losuj_3, losuj_4, losuj_5;
        srand (time(NULL));
        losuj_3 = rand() % 3+1;
        losuj_4 = rand() % 4+1;
        losuj_5 = rand() % 5+1;
        if(score >=0 && score < 10)
        {
            switch(losuj_3)
            {
        case 1: //resp krzak
        zombi.shape.setPosition(434.0f,503.0f);
            break;
        case 2: //lewy dolny rog
        zombi.shape.setPosition(326.0f,679.0f);
            break;
        case 3: // prawy gorny rog
        zombi.shape.setPosition(951.0f,63.0f);
            break;
        }
        }
         if(score >= 10 && score < 20)
        {
            switch(losuj_4)
            {
            case 1: //resp krzak
        zombi.shape.setPosition(434.0f,503.0f);
            break;
        case 2: //lewy dolny rog
        zombi.shape.setPosition(326.0f,679.0f);
            break;
        case 3: // prawy gorny rog
        zombi.shape.setPosition(951.0f,63.0f);
            break;
        case 4: //drzewa po lewej
        zombi.shape.setPosition(103.0f,483.0f);
            break;
            }
        }
        if(score >= 20)
        {
            switch(losuj_5)
            {
            case 1: //resp krzak
        zombi.shape.setPosition(434.0f,503.0f);
            break;
        case 2: //lewy dolny rog
        zombi.shape.setPosition(326.0f,679.0f);
            break;
        case 3: // prawy gorny rog
        zombi.shape.setPosition(951.0f,63.0f);
            break;
        case 4: //drzewa po lewej
        zombi.shape.setPosition(103.0f,483.0f);
            break;
        case 5: //drzewa po lewej
        zombi.shape.setPosition(103.0f,483.0f);
            break;
        }
        }





        zombie_wektor.insert(zombie_wektor.begin(),zombi);
        czas_respu=0;
    }

}

void przyjmowanie_strzal(vector <zombie> &zombie_wektor,vector <strzal> &wektor_strzal, int &score){

    for(int i=0;i<zombie_wektor.size();i++){
        for(int j=0; j<wektor_strzal.size();j++){
            if(zombie_wektor[i].shape.getGlobalBounds().intersects(wektor_strzal[j].shape.getGlobalBounds())){

                zombie_wektor[i].hp_zombie--;
                if(zombie_wektor[i].hp_zombie <= 0)
                {
                    zombie_wektor.erase(zombie_wektor.begin()+i);
                    score++;
                }
                wektor_strzal.erase(wektor_strzal.begin()+j);
                break;
            }

        }

    }

}



void cale_menu(int & bitmapa, RenderWindow & window, int &done, RectangleShape & player, RectangleShape & player2, Texture & player1Texture, Texture & player2Texture, int &IdleAnim)
{
//    zombie zom;

if(Mouse::isButtonPressed(Mouse::Left))
{


    //window potrzebne, od tego zaleza kordy mapki (zaczynaja sie wtedy od 0.0)
 //  cout << Mouse::getPosition(window).x << " " <<Mouse::getPosition(window).y << endl;
 // przycisk start

    if(bitmapa == 0 && Mouse::getPosition(window).x > 483 && Mouse::getPosition(window).x < 882 && Mouse::getPosition(window).y >349 && Mouse::getPosition(window).y < 448 )
    {
        bitmapa = 1;



    }
    // przycisk instrukcji
 if(bitmapa == 0 && Mouse::getPosition(window).x > 483 && Mouse::getPosition(window).x < 882 && Mouse::getPosition(window).y >490 && Mouse::getPosition(window).y < 589 )
    {
        bitmapa = 2;



    }


    //przyciski w wyborze postaci - prowadzi do gry docelowej
    if(bitmapa == 1  && Mouse::getPosition(window).x > 220 && Mouse::getPosition(window).x < 521 && Mouse::getPosition(window).y >627 && Mouse::getPosition(window).y < 721 )
            {
                //ninja
                done = 1;
                bitmapa = 3;

                player2.setTexture(&player1Texture);
    } else if(bitmapa == 1  && Mouse::getPosition(window).x > 888 && Mouse::getPosition(window).x < 1161 && Mouse::getPosition(window).y >648 && Mouse::getPosition(window).y < 716 )
            {
                done = 2;
                bitmapa = 3;

                player.setTexture(&player2Texture);
                //zomb.setTexture(&zombiee);
                //zom.laduj_zombie(zomb,zombiee);
               // zom.laduj_teksture_zombie(zomb,IdleAnim);
                //IdleAnim++;


                //tu wybieramy postac lucznika??
            }

    //wyjscie z gry

    if(bitmapa == 0 && Mouse::getPosition(window).x > 484 && Mouse::getPosition(window).x < 883 && Mouse::getPosition(window).y >631 && Mouse::getPosition(window).y < 730 )
    {
        window.close();
      //  return 0;
      // ZROBIC INNE WYCHODZENIE Z GRY!!!

    }


    // zerknac na wychodzenie z instrukcji




    if(bitmapa == 2 && Mouse::getPosition(window).x > 480 && Mouse::getPosition(window).x < 891 && Mouse::getPosition(window).y >616 && Mouse::getPosition(window).y < 712 )
           {
            Sleep(200);
            bitmapa = 0;

            }


}
}
