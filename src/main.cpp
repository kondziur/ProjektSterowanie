#include <Arduino.h>
int buttonX;
int buttonY;
int buttonZ;
int a, kroki = 0;
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
        a = Serial.parseInt();
        if (a > 0)
        {
            kroki = a;
        }
    }

    // put your main code here, to run repeatedly:
    buttonX = digitalRead(esX);
    buttonY = digitalRead(esY);
    buttonZ = digitalRead(esZ);
    // Serial.print("End stop XYZ values: ");

    // Serial.print(buttonX);
    // Serial.print(buttonY);
    // Serial.print(buttonZ);
    // Serial.print("\r\n");

    if (buttonX == 0 && kroki > 0)
    {
        digitalWrite(X_STEP_PIN, LOW);
    }
    if (buttonY == 0 && kroki > 0)
    {
        digitalWrite(Y_STEP_PIN, LOW);
    }
    if (buttonZ == 0 && kroki > 0)
    {
        digitalWrite(Z_STEP_PIN, LOW);
    }

    if (kroki > 0)
        kroki--;
    delayMicroseconds(speed);
    digitalWrite(X_STEP_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, HIGH);
    digitalWrite(Z_STEP_PIN, HIGH);
    delayMicroseconds(speed);
}
