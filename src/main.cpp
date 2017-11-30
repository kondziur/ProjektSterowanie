#include <Arduino.h>
#include <string.h>
// Zmienne do pobierania liczby kroków od użytkownika

String a;
char b;

// Zmienne przechowujące stan krańcówek
int buttonX;
int buttonY;
int buttonZ;
// Zmienne przechowujące ilosc pozostalych krokow
int KrokiX = 0;
int KrokiY = 0;
int KrokiZ = 0;

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

void setup()
{
    Serial.begin(9600);
    //WYŁĄCZNIKI KRAŃCOWE
    // krańcówka X
    pinMode(esX, INPUT);
    digitalWrite(esX, HIGH);

    //krańcówka Y
    pinMode(esY, INPUT);
    digitalWrite(esY, HIGH);

    //krańcówka Z
    pinMode(esZ, INPUT);
    digitalWrite(esZ, HIGH);

    //krańcówka dodatkowa
    pinMode(esADD, INPUT);
    digitalWrite(esADD, HIGH);

    //STEROWANIE SILNIKAMI KROKOWYMI
    pinMode(X_DIR_PIN, OUTPUT);
    digitalWrite(X_DIR_PIN, LOW);
    pinMode(X_ENABLE_PIN, OUTPUT);
    digitalWrite(X_ENABLE_PIN, LOW);
    pinMode(X_CS_PIN, OUTPUT);
    digitalWrite(X_CS_PIN, HIGH);
    pinMode(X_STEP_PIN, OUTPUT);

    pinMode(Y_DIR_PIN, OUTPUT);
    digitalWrite(Y_DIR_PIN, LOW);
    pinMode(Y_ENABLE_PIN, OUTPUT);
    digitalWrite(Y_ENABLE_PIN, LOW);
    pinMode(Y_CS_PIN, OUTPUT);
    digitalWrite(Y_CS_PIN, HIGH);
    pinMode(Y_STEP_PIN, OUTPUT);

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

    while (Serial.available())
    {
        b = Serial.read();
        a = a + b;
        if (b == '\n')
        {
            sscanf(a.c_str(), "x %d y %d z %d", &KrokiX, &KrokiY, &KrokiZ);

            Serial.print("KrokiX = ");
            Serial.print(KrokiX);
            Serial.print(", KrokiY = ");
            Serial.print(KrokiY);
            Serial.print(", KrokiZ = ");
            Serial.print(KrokiZ);
            Serial.print("\n");
            a = String("");
            break;
        }
    }
    // Niezaleznie od wartosci krokow silniki zawsze ida w gore
        if (KrokiX < 0)
        {
            KrokiX *= -1;
            digitalWrite(X_DIR_PIN,HIGH);
        }
        else
        {
            digitalWrite(X_DIR_PIN,LOW);
        }
        if (KrokiY < 0)
        {
            KrokiY *= -1;
            digitalWrite(Y_DIR_PIN,HIGH);
        }
                else
        {
            digitalWrite(Y_DIR_PIN,LOW);
        }
        if (KrokiZ < 0)
        {
            KrokiZ *= -1;
            digitalWrite(Z_DIR_PIN,HIGH);
        }
                else
        {
            digitalWrite(Z_DIR_PIN,LOW);
        }

    buttonX = digitalRead(esX);
    buttonY = digitalRead(esY);
    buttonZ = digitalRead(esZ);

    if (buttonX == 0 && KrokiX > 0)
    {
        digitalWrite(X_STEP_PIN, HIGH);
        KrokiX--;
    }
    if (buttonY == 0 && KrokiY > 0)
    {
        digitalWrite(Y_STEP_PIN, HIGH);
        KrokiY--;
    }
    if (buttonZ == 0 && KrokiZ > 0)
    {
        digitalWrite(Z_STEP_PIN, HIGH);
        KrokiZ--;
    }

    if (buttonX == 1 && digitalRead(X_DIR_PIN) == LOW)
    {
        KrokiX = 0;
    }
    if (buttonY == 1 && digitalRead(Y_DIR_PIN) == LOW)
    {
        KrokiY = 0;
    }
    if (buttonZ == 1 && digitalRead(Z_DIR_PIN) == LOW)
    {
        KrokiZ = 0;
    }

    delayMicroseconds(speed);
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    digitalWrite(Z_STEP_PIN, LOW);
    delayMicroseconds(speed);
}