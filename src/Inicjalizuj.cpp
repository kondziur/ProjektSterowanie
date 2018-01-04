#include "Inicjalizuj.hpp"

void Inicjalizuj()
{
    bool StanKrancowkiX = digitalRead(KRANCOWKA_X);
    bool StanKrancowkiY = digitalRead(KRANCOWKA_Y);
    bool StanKrancowkiZ = digitalRead(KRANCOWKA_Z);

    while (StanKrancowkiX == 0 || StanKrancowkiY == 0 || StanKrancowkiZ == 0)
    {
        PrzemiescSilniki(100,100,100);

        StanKrancowkiX = digitalRead(KRANCOWKA_X);
        StanKrancowkiY = digitalRead(KRANCOWKA_Y);
        StanKrancowkiZ = digitalRead(KRANCOWKA_Z);
    }

    PrzemiescSilniki(OPAD,OPAD,OPAD);

    Serial.print("k\n");
}