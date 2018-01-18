#pragma once

#include <Arduino.h>

#include "NumeryPinow.hpp"
#include "PozostaleDefinicje.hpp"


/* Funkcja s�u��ca do przemieszczania silnik�w w poszczeg�lnych osiach. Silniki s� przesuwane z jednakow� pr�dko�ci�.
W przypadku naci�ni�cia kra�c�wki odpowiadaj�cej danemu silnikowi silnik przestaje porusza� si� w g�r�. */
void PrzemiescSilniki(int IloscKrokowX, int IloscKrokowY, int IloscKrokowZ, int Predkosc);