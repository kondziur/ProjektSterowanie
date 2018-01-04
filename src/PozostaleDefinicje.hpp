#pragma once


// Pr�dko�� zdefiniowana w krokach na sekund�
#define PREDKOSC 10

// Rozmiar bufora przechowuj�cego przechwycone znaki
#define ROZMIAR_BUFORA 51

// Rozmiar kolejki ruch�w
#define ROZMIAR_KOLEJKI 10

// Definicja umo�liwiaj�ca kompilacj� kodu odpowiedzialnego za debugowanie
// #define TRYB_DEBUGOWY

/* Definicje komunikat�w z b��dami wysy�anymi przez urz�dzenie */
#define KOMUNIKAT_WYKONANIA_KOLEJKI "Pomyslnie wykonano kolejke"
#define KOMUNIKAT_PRZEPELNIENIA_KOLEJKI "Przepelniono kolejke!"
#define KOMUNIKAT_NIEPOPRAWNEGO_LANCUCHA "Niepoprawny format lancucha wejsciowego!"
#define KOMUNIKAT_PRZEPELNIENIA_BUFORA "Przepelniono bufor!"