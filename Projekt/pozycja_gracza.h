#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <math.h>
#include "isAnyKeyPressed.h"

using namespace sf;
using namespace std;

/** @brief Funkcja sprawdza aktualna pozycje gracza i kierunek w jakim jest on zwrocony aby dopasowac wlasciwa animacje
 *
 * @see void sprawdz_pozycje
 *
 */

void sprawdz_pozycje(RectangleShape & player, int pozycja, int &IdleAnim, int &dealy, float &hp);
