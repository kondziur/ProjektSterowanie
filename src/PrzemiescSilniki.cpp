#include <PrzemiescSilniki.hpp>


/* Funkcja s�u��ca do przemieszczania silnik�w w poszczeg�lnych osiach. Silniki s� przesuwane z jednakow� pr�dko�ci�.
W przypadku naci�ni�cia kra�c�wki odpowiadaj�cej danemu silnikowi silnik przestaje porusza� si� w g�r�. */
void PrzemiescSilniki(int IloscKrokowX, int IloscKrokowY, int IloscKrokowZ, int Predkosc)
{
	/* -- Zmienne -- */
	// Czas brany pod uwag� przy op�nieniach
	unsigned int CzasOpoznienia = Predkosc;

	// Zmienne przechowuj�ce aktualny stan kra�c�wek
	bool StanKrancowkiX = true;
	bool StanKrancowkiY = true;
	bool StanKrancowkiZ = true;

	/* -- Czynno�ci -- */
	/* Realizacja ruchu */
	// - Dopasowanie kierunku ruchu do warto�ci krok�w -
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


	// - P�tla realizuj�ca ruch -
	while (IloscKrokowX > 0 || IloscKrokowY > 0 || IloscKrokowZ > 0)
	{
		// Zabezpieczenie silnik�w przed poruszeniem si� przy wci�ni�tych kra�c�wkach
		// Wczytanie warto�ci pin�w zwi�zanych z kra�c�wkami
		StanKrancowkiX = digitalRead(KRANCOWKA_X);
		StanKrancowkiY = digitalRead(KRANCOWKA_Y);
		StanKrancowkiZ = digitalRead(KRANCOWKA_Z);

		// Zerowanie krok�w dla poszczeg�lnych silnik�w gdy kra�c�wka jest wci�ni�ta i nakazano ruch w g�r�
		// Silnik X
		if (StanKrancowkiX == 1 && digitalRead(X_DIR_PIN) == LOW)
		{
			IloscKrokowX = 0;
		}
		// Silnik Y
		if (StanKrancowkiY == 1 && digitalRead(Y_DIR_PIN) == LOW)
		{
			IloscKrokowY = 0;
		}
		// Silnik Z
		if (StanKrancowkiZ == 1 && digitalRead(Z_DIR_PIN) == LOW)
		{
			IloscKrokowZ = 0;
		}

		// Wystawienie jedynek na piny zwi�zane z poruszaniem silnikami
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

		// Op�nienie
		delayMicroseconds(CzasOpoznienia);

		// Wystawienie zer na piny zwi�zane z poruszaniem silnikami
		digitalWrite(X_STEP_PIN, LOW);
		digitalWrite(Y_STEP_PIN, LOW);
		digitalWrite(Z_STEP_PIN, LOW);

		// Op�nienie
		delayMicroseconds(CzasOpoznienia);
	}
	Serial.print("1\n");
}