#include <Arduino.h>
#include <string.h>

#include "PrzemiescSilniki.hpp"
#include "ObslugaWejsciaSzeregowego.hpp"
#include "NumeryPinow.hpp"


/* -- Zmienne modu�owe -- */

// Zmienne obs�uguj�ce kolejk� ruch�w
// Tablica reprezentuj�ca kolejk� ruch�w prostoliniowych. Pierwszy indeks reprezentuje numer ruchu, a drugi - numer silnika, dla kt�rego ma by� wykonany ruch.
int Kolejka[ROZMIAR_KOLEJKI][3] = { 0 };
// Zmienna przechowuj�ca ilo�� ruch�w znajduj�cych si� aktualnie w kolejce;
int IloscRuchowWKolejce = 0;
// Zmienna okre�laj�ca, czy kolejka ma by� wykonywana
bool WykonajKolejke = false;

/* -- Funkcje -- */
void setup()
{
	/* Uruchomienie portu szeregowego */
	Serial.begin(115200);


	/* Konfiguracja pin�w */
	// Piny zwi�zane z kra�c�wkami
	// Kra�c�wka X
	pinMode(KRANCOWKA_X, INPUT);
	digitalWrite(KRANCOWKA_X, HIGH);

	// Kra�c�wka Y
	pinMode(KRANCOWKA_Y, INPUT);
	digitalWrite(KRANCOWKA_Y, HIGH);

	// Kra�c�wka Z
	pinMode(KRANCOWKA_Z, INPUT);
	digitalWrite(KRANCOWKA_Z, HIGH);

	// Dodatkowa kra�c�wka
	pinMode(KRANCOWKA_DOD, INPUT);
	digitalWrite(KRANCOWKA_DOD, HIGH);


	// Piny s�u��ce do sterowania silnikami krokowymi
	// Silnik X
	pinMode(X_DIR_PIN, OUTPUT);
	digitalWrite(X_DIR_PIN, LOW);
	pinMode(X_ENABLE_PIN, OUTPUT);
	digitalWrite(X_ENABLE_PIN, LOW);
	pinMode(X_CS_PIN, OUTPUT);
	digitalWrite(X_CS_PIN, HIGH);
	pinMode(X_STEP_PIN, OUTPUT);

	// Silnik Y
	pinMode(Y_DIR_PIN, OUTPUT);
	digitalWrite(Y_DIR_PIN, LOW);
	pinMode(Y_ENABLE_PIN, OUTPUT);
	digitalWrite(Y_ENABLE_PIN, LOW);
	pinMode(Y_CS_PIN, OUTPUT);
	digitalWrite(Y_CS_PIN, HIGH);
	pinMode(Y_STEP_PIN, OUTPUT);

	// Silnik Z
	pinMode(Z_DIR_PIN, OUTPUT);
	digitalWrite(Z_DIR_PIN, LOW);
	pinMode(Z_ENABLE_PIN, OUTPUT);
	digitalWrite(Z_ENABLE_PIN, LOW);
	pinMode(Z_CS_PIN, OUTPUT);
	digitalWrite(Z_CS_PIN, HIGH);
	pinMode(Z_STEP_PIN, OUTPUT);
}

void loop()
{
	ObsluzWejscieSzeregowe();
}