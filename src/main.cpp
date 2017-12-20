#include <Arduino.h>
#include <string.h>

#define speed 1000

#define esX 2
#define esY 15
#define esZ 19
#define esADD 3

#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38
#define X_CS_PIN 53

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
#define Y_CS_PIN 49

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62
#define Z_CS_PIN 40

// Zmienne do pobierania liczby krok�w od u�ytkownika
String ZawartoscBufora;
char NowyZnak;

// Zmienne przechowuj�ce stan kra�c�wek
int buttonX;
int buttonY;
int buttonZ;

// Zmienne przechowuj�ce ilosc pozostalych krokow
int KrokiX = 0;
int KrokiY = 0;
int KrokiZ = 0;

void PrzemiescSilniki(int IloscKrokowX, int IloscKrokowY, int IloscKrokowZ);

void setup()
{
	/* Uruchomienie portu szeregowego */
	Serial.begin(9600);

	/* Konfiguracja pin�w */
	// Piny zwi�zane z kra�c�wkami
	// Kra�c�wka X
	pinMode(esX, INPUT);
	digitalWrite(esX, HIGH);

	// Kra�c�wka Y
	pinMode(esY, INPUT);
	digitalWrite(esY, HIGH);

	// Kra�c�wka Z
	pinMode(esZ, INPUT);
	digitalWrite(esZ, HIGH);

	// Dodatkowa kra�c�wka
	pinMode(esADD, INPUT);
	digitalWrite(esADD, HIGH);

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
	/* Wczytanie danych podanych na port szeregowy */
	while (Serial.available())
	{
		NowyZnak = Serial.read();
		ZawartoscBufora = ZawartoscBufora + NowyZnak;
		if (NowyZnak == '\n')
		{
			sscanf(ZawartoscBufora.c_str(), "x %d y %d z %d", &KrokiX, &KrokiY, &KrokiZ);

			Serial.print("KrokiX = ");
			Serial.print(KrokiX);
			Serial.print(", KrokiY = ");
			Serial.print(KrokiY);
			Serial.print(", KrokiZ = ");
			Serial.print(KrokiZ);
			Serial.print("\n");

			ZawartoscBufora = String("");

			PrzemiescSilniki(KrokiX, KrokiY, KrokiZ);
			// break;
		}
	}
}

void PrzemiescSilniki(int IloscKrokowX, int IloscKrokowY, int IloscKrokowZ)
{
	/* Realizacja ruchu */
	// - Dopasowanie kierunku ruchu do wartoci krok�w -
	// Silnik X
	if (IloscKrokowX < 0)
	{
		IloscKrokowX *= -1;
		digitalWrite(X_DIR_PIN, HIGH);
	}
	else
	{
		digitalWrite(X_DIR_PIN, LOW);
	}

	// Silnik Y
	if (IloscKrokowY < 0)
	{
		IloscKrokowY *= -1;
		digitalWrite(Y_DIR_PIN, HIGH);
	}
	else
	{
		digitalWrite(Y_DIR_PIN, LOW);
	}

	// Silnik Z
	if (IloscKrokowZ < 0)
	{
		IloscKrokowZ *= -1;
		digitalWrite(Z_DIR_PIN, HIGH);
	}
	else
	{
		digitalWrite(Z_DIR_PIN, LOW);
	}

	// - Pętla realizująca ruch -
	while (IloscKrokowX > 0 || IloscKrokowY > 0 || IloscKrokowZ > 0)
	{
		// Zabezpieczenie silników przed poruszeniem się przy wciniętych krańcówkach
		// Wczytanie wartoci pinów związanych z krańcówkami
		buttonX = digitalRead(esX);
		buttonY = digitalRead(esY);
		buttonZ = digitalRead(esZ);

		// Silnik X
		if (buttonX == 1 && digitalRead(X_DIR_PIN) == LOW)
		{
			IloscKrokowX = 0;
		}
		// Silnik Y
		if (buttonY == 1 && digitalRead(Y_DIR_PIN) == LOW)
		{
			IloscKrokowY = 0;
		}
		// Silnik Z
		if (buttonZ == 1 && digitalRead(Z_DIR_PIN) == LOW)
		{
			IloscKrokowZ = 0;
		}

		// Wystawienie jedynek na piny związane z poruszaniem silnikami
		// Silnik X
		if (IloscKrokowX > 0)
		{
			digitalWrite(X_STEP_PIN, HIGH);
			IloscKrokowX--;
		}
		// Silnik Y
		if (IloscKrokowY > 0)
		{
			digitalWrite(Y_STEP_PIN, HIGH);
			IloscKrokowY--;
		}
		// Silnik Z
		if (IloscKrokowZ > 0)
		{
			digitalWrite(Z_STEP_PIN, HIGH);
			IloscKrokowZ--;
		}
		// Opóźnienie

		delayMicroseconds(speed);

		// Wystawienie zer na piny związane z poruszaniem silnikami
		digitalWrite(X_STEP_PIN, LOW);
		digitalWrite(Y_STEP_PIN, LOW);
		digitalWrite(Z_STEP_PIN, LOW);
		// Opóźnienie
		delayMicroseconds(speed);
	}
	Serial.print("Zakonczono ruch.");
}
//komentarz