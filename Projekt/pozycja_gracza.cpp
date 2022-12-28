#include <SFML/Graphics.hpp>
#include <iostream>
//#include <Animation.h>
#include <windows.h>
#include <math.h>
#include "pozycja_gracza.h"


using namespace sf;
using namespace std;



void sprawdz_pozycje(RectangleShape & player, int pozycja, int &IdleAnim, int &delay)
{

	    if(!isAnyKeyPressed() && delay >= 15)
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

/*
    //cout << "x: " << player.getPosition().x << " oraz y: " << player.getPosition().y << endl;

    if((zombie.getPosition().x - player.getPosition().x) < 0)
    {
        //prawo
        int xTexture = 0;
        //IdleAnim = 0;
        xTexture = (int)zombie.getPosition().x / 25 % 9;
        xTexture*=80;
        zombie.setTextureRect(IntRect(xTexture,304,80,76));
        zombie.move(1.0f,0.0f);
    }
    else if((zombie.getPosition().x + player.getPosition().x) > 0)
    {
        //lewo
        int xTexture = 0;
      //  IdleAnim = 0;
        xTexture = (int)zombie.getPosition().x / 25 % 9;
        xTexture*=80;
        zombie.setTextureRect(IntRect(xTexture,152,80,76));
        zombie.move(-1.0f,0.0f);
    }
     if((zombie.getPosition().y - player.getPosition().y) < 0)
    {
        //dol
      //  IdleAnim = 0;
        int yTexture = 0;
        yTexture = (int)zombie.getPosition().y / 25 % 9;
        yTexture*=80;

        zombie.setTextureRect(IntRect(yTexture,228,80,76));
        zombie.move(0.0f,1.0f);
    }
    else if((zombie.getPosition().y - player.getPosition().y) > 0)
    {
        //gora
       // IdleAnim = 0;
        int yTexture = 0;
        yTexture = (int)zombie.getPosition().y / 25 % 9;
        yTexture*=80;

        zombie.setTextureRect(IntRect(yTexture,76,80,76));
        zombie.move(0.0f,-1.0f);
    }
*/


/*
    if(player.getPosition().x + player.getGlobalBounds().width == zombie.getPosition().x )
    {
        cout << "chuj" << endl;
    }
    */
    /*
    if(((zombie.getPosition().y - player.getPosition().y) < 0) && ((zombie.getPosition().x + player.getPosition().x) > 0) || ((zombie.getPosition().x + player.getPosition().x) > 0) && ((zombie.getPosition().y - player.getPosition().y) > 0))
    {
        // lewo dol/gora
        int xTexture = 0;
        IdleAnim = 0;
        xTexture = (int)zombie.getPosition().x / 25 % 9;
        xTexture*=80;
        zombie.setTextureRect(IntRect(xTexture,152,80,76));
        zombie.move(0.0f,0.0f);
    }
    if(((zombie.getPosition().y - player.getPosition().y) < 0) && ((zombie.getPosition().x - player.getPosition().x) < 0) || ((zombie.getPosition().y - player.getPosition().y) > 0) && ((zombie.getPosition().x - player.getPosition().x) < 0))
    {
        //prawo dol/gora
        int xTexture = 0;
        IdleAnim = 0;
        xTexture = (int)zombie.getPosition().x / 25 % 9;
        xTexture*=80;
        zombie.setTextureRect(IntRect(xTexture,304,80,76));
        zombie.move(0.0f,0.0f);
    }

*/
}
