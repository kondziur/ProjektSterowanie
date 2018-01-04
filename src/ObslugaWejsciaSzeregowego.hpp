/* Modu� realizuj�cy obs�ug� wej�cia szeregowego*/

#pragma once

#include <Arduino.h>

#include "PozostaleDefinicje.hpp"


/* Funkcja s�u��ca do obs�ugi portu szeregowego zgdnie ze specyfikacj� okre�lon� w pliku "Opis komunikacji.txt".
	Pojedyncze wywo�anie funkcji spowoduje obs�u�enie wszelkich znak�w znajduj�cych si� w buforze portu szeregowego.*/
int ObsluzWejscieSzeregowe();


/* Funkcja s�u��ca do obs�ugi nowego pojedynczego znaku podanego na port szeregowy.*/
static int ObsluzNowyZnak(char NowyZnak);