#include <Arduino.h>

int cm = 0;
int cm1 = 0;
float leituraD;
float leituraE;
int sinalD = 4;
int sinalE = 7;

#define EN1 12
#define EN2 13
#define EN3 11
#define EN4 10

void readUltrasonicDistanceD()
{
  pinMode(sinalD, OUTPUT);
  digitalWrite(sinalD, LOW);
  delayMicroseconds(2);
  digitalWrite(sinalD, HIGH);
  delayMicroseconds(10);
  digitalWrite(sinalD, LOW);
  pinMode(sinalD, INPUT);

  leituraD = pulseIn(sinalD, HIGH);
}

void readUltrasonicDistanceE()
{
  pinMode(sinalE, OUTPUT);
  digitalWrite(sinalE, LOW);
  delayMicroseconds(2);
  digitalWrite(sinalE, HIGH);
  delayMicroseconds(10);
  digitalWrite(sinalE, LOW);
  pinMode(sinalE, INPUT);

  leituraE = pulseIn(sinalE, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, LOW);
}

void loop()
{
  readUltrasonicDistanceD();

  cm = 0.01723 * leituraD;

  Serial.print("Medicao Direita:  ");
  Serial.print(cm);
  Serial.println("cm");
  delay(1000);

  readUltrasonicDistanceE();

  cm1 = 0.01723 * leituraE;

  Serial.print("Medicao Esquerda:  ");
  Serial.print(cm1);
  Serial.println("cm");
  delay(1000);

  if (cm1 > 20 && cm > 20) // sem nenhuma parede dos lados > Fim do lbirinto motores parados
  {
    digitalWrite(EN1, 0);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 0);
    digitalWrite(EN4, 0);
  }
  else if (cm1 < 20 && cm > 20) // parede na esquerda
  {
    digitalWrite(EN1, 1);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 0);
    digitalWrite(EN4, 1);
    delay(1000);
    digitalWrite(EN1, 0);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 0);
    digitalWrite(EN4, 0);
    delay(1000);
    digitalWrite(EN1, 1);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 1);
    digitalWrite(EN4, 0);
    delay(1000);
    digitalWrite(EN1, 0);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 0);
    digitalWrite(EN4, 0);
    delay(1000);
  }
  else if (cm1 > 20 && cm < 20) // parede na direita
  {
    digitalWrite(EN1, 0);
    digitalWrite(EN2, 1);
    digitalWrite(EN3, 1);
    digitalWrite(EN4, 0);
    delay(1000);
    digitalWrite(EN1, 0);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 0);
    digitalWrite(EN4, 0);
    delay(1000);
    digitalWrite(EN1, 1);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 1);
    digitalWrite(EN4, 0);
    delay(1000);
    digitalWrite(EN1, 0);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 0);
    digitalWrite(EN4, 0);
    delay(1000);
  }
  else if (cm1 < 20 && cm < 20) // parede dos dois lados motores para frente
  {
    digitalWrite(EN1, 1);
    digitalWrite(EN2, 0);
    digitalWrite(EN3, 1);
    digitalWrite(EN4, 0);
    delay(2000);
  }
  
}