#include "ObslugaWejsciaSzeregowego.hpp"
#include "PrzemiescSilniki.hpp"
#include "Inicjalizuj.hpp"
/* -- Zmienne modu�owe -- */
// Zmienne do pobierania liczby krok�w od u�ytkownika
// Tablica przechowuj�ca zawarto�� bufora
static char ZawartoscBufora[ROZMIAR_BUFORA] = { 0 };
// Liczba okre�laj�ca ilo�� znak�w znajduj�cych si� w buforze (i jednocze�nie miejsce wstawienia nowego znaku)
static int ZajecieBufora = 0;

// Zmienne obs�uguj�ce kolejk� ruch�w pochodz�ce z g��wnego modu�u programu
// Tablica reprezentuj�ca kolejk� ruch�w prostoliniowych. Pierwszy indeks reprezentuje numer ruchu, a drugi - numer silnika, dla kt�rego ma by� wykonany ruch.
extern int Kolejka[ROZMIAR_KOLEJKI][3];
// Zmienna przechowuj�ca ilo�� ruch�w znajduj�cych si� aktualnie w kolejce;
extern int IloscRuchowWKolejce;
// Zmienna okre�laj�ca, czy kolejka ma by� wykonywana
extern bool WykonajKolejke;


/* -- Definicje funkcji -- */
/* Funkcja s�u��ca do obs�ugi portu szeregowego zgdnie ze specyfikacj� okre�lon� w pliku "Opis komunikacji.txt".
Pojedyncze wywo�anie funkcji spowoduje obs�u�enie wszelkich znak�w znajduj�cych si� w buforze portu szeregowego.*/
int ObsluzWejscieSzeregowe()
{
	/* - Zmienne - */
	char NowyZnak = 0;


	// Dop�ki w buforze portu s� dost�pne nowe znaki, pobieramy je i obs�ugujemy.
	while (Serial.available())
	{
		NowyZnak = Serial.read();
		ObsluzNowyZnak(NowyZnak);
	}
	return 0;
}



/* Funkcja s�u��ca do obs�ugi nowego pojedynczego znaku podanego na port szeregowy.*/
static int ObsluzNowyZnak(char NowyZnak)
{
	/* -- Czynno�ci wst�pne -- */
	// Je�li wype�niono bufor, a mimo to czekaj� nowe znaki, wysy�amy komunikat o b��dzie przez ��cze szeregowe oraz symulujemy czyszczenie bufora.
	if (ZajecieBufora >= ROZMIAR_BUFORA - 1)
	{
		Serial.print(KOMUNIKAT_PRZEPELNIENIA_BUFORA);
		ZajecieBufora = 0;
		return 1;
	}

	// // Je�li nowy znak jest liter� 'F', przechodzimy do wykonywania kolejki i usuwamy dotychczasow� zawarto�� bufora.
	// if (NowyZnak == 'F' || NowyZnak == 'f')
	// {
	// 	WykonajKolejke = true;
	// 	ZajecieBufora = 0;
	// 	return 2;
	// }


	/* -- Zmienne -- */
	// Liczba krok�w do wykonania przez poszczeg�lne silniki
	int KrokiX = 0;
	int KrokiY = 0;
	int KrokiZ = 0;


	/* -- Czynno�ci -- */
	// Dodajemy odczytany znak do bufora.
	ZawartoscBufora[ZajecieBufora++] = NowyZnak;

	// Je�li nowy znak jest znakiem nowej linii pr�bujemy odczyta� warto�ci krok�w z otrzymanego �a�cucha.
	if (NowyZnak == '\n')
	{
		// Je�li zako�czono �a�cuch bez znaku 'F' a kolejka jest przepe�niona, wysy�amy odpowiedni komunikat i czy�cimy bufor.
		if (IloscRuchowWKolejce > ROZMIAR_KOLEJKI)
		{
			ZajecieBufora = 0;
			Serial.print(KOMUNIKAT_PRZEPELNIENIA_KOLEJKI);
			return 3;
		}

		ZawartoscBufora[ZajecieBufora++] = 0;
		if (strcmp(ZawartoscBufora,"init\n") == 0)
		{
			ZajecieBufora = 0;
			Inicjalizuj();
			return 5;
		}

		int WynikDzialania = sscanf(ZawartoscBufora, "x %d y %d z %d", &KrokiX, &KrokiY, &KrokiZ);

		// W przypadku b��d�w czy�cimy bufor i wysy�amy odpowiedni komunikat
		if (WynikDzialania != 3)
		{
			Serial.print(KOMUNIKAT_NIEPOPRAWNEGO_LANCUCHA);
			ZajecieBufora = 0;
			return 4;
		}

		// Je�li wszystko posz�o dobrze, dodajemy nowe warto�ci krok�w do kolejki
		ZajecieBufora = 0;

		// W trybie debugowym dodatkowo zwracamy �a�cuch zawieraj�cy przyj�t� liczb� krok�w.
#ifdef TRYB_DEBUGOWY
		Serial.print("KrokiX = ");
		Serial.print(KrokiX);
		Serial.print(", KrokiY = ");
		Serial.print(KrokiY);
		Serial.print(", KrokiZ = ");
		Serial.print(KrokiZ);
		Serial.print("\n");
#endif

		PrzemiescSilniki(KrokiX, KrokiY, KrokiZ, 1000);
		return 0;
	}
	return 0;
}