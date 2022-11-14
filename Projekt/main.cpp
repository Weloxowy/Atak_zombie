#include <SFML/Graphics.hpp>
#include <iostream>
//#include <Animation.h>
#include <windows.h>
#include <math.h>

using namespace sf;
using namespace std;
int bitmapa = 0;
int done = 0; // wybor postaci
const unsigned WINDOW_WIDTH = 1366; // na podstawie koordynatow naszej mapy ustawiamy kolizje
const unsigned WINDOW_HEIGHT = 768; // na podstawie koordynatow naszej mapy ustawiamy kolizje
int pozycja = 0;
int delay = 1;
int IdleAnim = 0;
bool czy_strzela = false;
float ziara = 0;


bool isAnyKeyPressed()
	{
		for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
		{
			if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
				return true;
		}
		return false;

	}





int main() {
    RenderWindow window(VideoMode(1366, 768), "SFML!", Style::Close);
    window.setFramerateLimit(60);
    //lucznik
    RectangleShape player(Vector2f(69.0f, 96.0f));
    player.setPosition(500.0f,350.0f);

    RectangleShape chooseplayer1(Vector2f(274.0f, 343.0f));
    chooseplayer1.setPosition(940.0f,136.0f);

    Texture chooseplayer1_texture;
    chooseplayer1_texture.loadFromFile("menuanima.png");


    RectangleShape chooseplayer2(Vector2f(274.0f, 343.0f));
    chooseplayer2.setPosition(256.0f, 137.0f);

    Texture chooseplayer2_texture;
    chooseplayer2_texture.loadFromFile("menuanima.png");

    RectangleShape player2(Vector2f(100.0f, 100.0f));
    player2.setPosition(100.0f,100.0f);

    Texture player1Texture;
    player1Texture.loadFromFile("cat.png");

    Texture player2Texture;
    player2Texture.loadFromFile("lucznik.png");

    player.setTextureRect(IntRect(0,0,69,96));
    chooseplayer1.setTextureRect(IntRect(0,0,260,349));





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





    while (window.isOpen())
    {
        delay++;
        if(czy_strzela == true)
        {
            ziara+=0.3;
        }
      //  deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        //NOWY KOX77

if (bitmapa == 1 && Mouse::getPosition(window).x  > 683 && Mouse::getPosition(window).y < 768){
    //cout<<"chujP";

        chooseplayer1.setTexture(&chooseplayer1_texture);

        done = 3; // potrzebna zmienna do wyswietlenia postaci

    if(!isAnyKeyPressed() && delay >= 15)
    {
    chooseplayer1.setTextureRect(IntRect(IdleAnim*274,0,274,343));

   ++IdleAnim;
   if(IdleAnim == 10)
    {
    IdleAnim = 0;
    }
delay = 1;

    }
}

if (bitmapa == 1 && Mouse::getPosition(window).x  < 683 &&Mouse::getPosition(window).y < 768 ){
    //cout<<"chujP";

        chooseplayer2.setTexture(&chooseplayer2_texture);
        done = 4; // potrzebna zmienna do wyswietlenia postaci

    if(!isAnyKeyPressed() && delay >= 15)
    {
    chooseplayer2.setTextureRect(IntRect(IdleAnim*274,343,274,343));

   ++IdleAnim;
   if(IdleAnim == 10)
    {
    IdleAnim = 0;
    }
delay = 1;

    }


}






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
    if (bitmapa == 1 && Mouse::getPosition(window).x  <= 683 &&Mouse::getPosition(window).y < 768 ){
    cout<<"chujL";

}


    //przyciski w wyborze postaci - prowadzi do gry docelowej
    if(bitmapa == 1  && Mouse::getPosition(window).x > 220 && Mouse::getPosition(window).x < 521 && Mouse::getPosition(window).y >627 && Mouse::getPosition(window).y < 721 )
            {
                done = 1;
                bitmapa = 3;

                player2.setTexture(&player1Texture);
                //tu wybieramy postac wojownika???
                // zadeklarowac zmiennna postac, cos typu postac=0 - to wojownik, postac = 1 - to lucznik
                // nastepnie zrobic funkcje z parametrem aby sprawdzalo ktora postac wybralismy
                //cos typu tak jak w allegro
    } else if(bitmapa == 1  && Mouse::getPosition(window).x > 888 && Mouse::getPosition(window).x < 1161 && Mouse::getPosition(window).y >648 && Mouse::getPosition(window).y < 716 )
            {
                done = 2;
                bitmapa = 3;

                player.setTexture(&player2Texture);

                //tu wybieramy postac lucznika??
            }

    //wyjscie z gry

    if(bitmapa == 0 && Mouse::getPosition(window).x > 484 && Mouse::getPosition(window).x < 883 && Mouse::getPosition(window).y >631 && Mouse::getPosition(window).y < 730 )
    {

        return 0;

    }


    // zerknac na wychodzenie z instrukcji




    if(bitmapa == 2 && Mouse::getPosition(window).x > 523 && Mouse::getPosition(window).x < 848 && Mouse::getPosition(window).y >646 && Mouse::getPosition(window).y < 722 )
           {

            bitmapa = 0;
            Sleep(200);
            }


}



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

    if(Keyboard::isKeyPressed(Keyboard::Key::D))
    {
        pozycja = 2;
        int xTexture = 0;
        IdleAnim = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
       // cout << xTexture<< endl;

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
    if(Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        int xTexture = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
        player.setTextureRect(IntRect(xTexture,674,69,96));
        player.move(-0.0f,0.0f);
    }

    if(Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        int xTexture = 0;
        xTexture = (int)player.getPosition().x / 25 % 9;
        xTexture*=69;
        player.setTextureRect(IntRect(xTexture,192,69,96));
        player.move(0.0f,0.0f);


    }

    if((Keyboard::isKeyPressed(Keyboard::Key::Space) && delay >=20) || czy_strzela == true )
    {

        IdleAnim = 0;
        if(pozycja == 2)
        {
            if(ziara < 10)
        {
            czy_strzela = true;
            player.setTextureRect(IntRect(floor(ziara)*69,288,69,96));

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
            }
            if(ziara >= 10)
            {
                czy_strzela = false;
                ziara = 0;
            }
        }





    delay = 1;
        //
    }




    if(Keyboard::isKeyPressed(Keyboard::Key::A))
        player2.move(-1.5f,0.0f);
    if(Keyboard::isKeyPressed(Keyboard::Key::D))
        player2.move(1.5f,0.0f);
    if(Keyboard::isKeyPressed(Keyboard::Key::W))
        player2.move(0.0f,-1.5f);
    if(Keyboard::isKeyPressed(Keyboard::Key::S))
        player2.move(0.0f,1.5f);

        // KOLIZJA DLA LUCZNIKA //

        // lewa kolizja
        if(player.getPosition().x < 0.f)
            player.setPosition(0.f, player.getPosition().y);
        // gorna kolizja
        if(player.getPosition().y < 0.f)
            player.setPosition(player.getPosition().x,0.f);

        /*
        // kolizja lewych drzew
        if(player.getPosition().x < 381.f && player.getPosition().y < 436.f)
       {
            if(player.getPosition().x < 381.f)
            {
                player.setPosition(382.f, player.getPosition().y);
            }else
            if(player.getPosition().y < 436.f)
            {
                player.setPosition(player.getPosition().x, 437.f);
            }

        }

    */





        // prawa kolizja
        if(player.getPosition().x + player.getGlobalBounds().width > WINDOW_WIDTH)
            player.setPosition(WINDOW_WIDTH - player.getGlobalBounds().width, player.getPosition().y);
        // kolizja dolna
        if(player.getPosition().y + player.getGlobalBounds().height > WINDOW_HEIGHT)
            player.setPosition(player.getPosition().x, WINDOW_HEIGHT - player.getGlobalBounds().height);


    window.clear();
    //animation.Update(0,deltaTime);
//player.setTextureRect(animation.uvRect);
    if(bitmapa == 0)
    {
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
            if(done == 1)
            {
                window.draw(player2);
            }
            else if(done == 2)
            {

                window.draw(player);
            }


    }


    window.display();

    }

    return 0;
}
