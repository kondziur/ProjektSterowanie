/* Modu³ realizuj¹cy obs³ugê wejœcia szeregowego*/

#pragma once

#include <Arduino.h>

#include "PozostaleDefinicje.hpp"


/* Funkcja s³u¿¹ca do obs³ugi portu szeregowego zgdnie ze specyfikacj¹ okreœlon¹ w pliku "Opis komunikacji.txt".
	Pojedyncze wywo³anie funkcji spowoduje obs³u¿enie wszelkich znaków znajduj¹cych siê w buforze portu szeregowego.*/
int ObsluzWejscieSzeregowe();


/* Funkcja s³u¿¹ca do obs³ugi nowego pojedynczego znaku podanego na port szeregowy.*/
static int ObsluzNowyZnak(char NowyZnak);