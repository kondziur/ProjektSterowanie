#pragma once

#include <Arduino.h>

#include "NumeryPinow.hpp"
#include "PozostaleDefinicje.hpp"


/* Funkcja s³u¿¹ca do przemieszczania silników w poszczególnych osiach. Silniki s¹ przesuwane z jednakow¹ prêdkoœci¹.
W przypadku naciœniêcia krañcówki odpowiadaj¹cej danemu silnikowi silnik przestaje poruszaæ siê w górê. */
void PrzemiescSilniki(int IloscKrokowX, int IloscKrokowY, int IloscKrokowZ);