enum Estado_enum
{
  PARA,
  FRENTE,
  ROTACAO_DIREITA,
  ROTACAO_ESQUERDA
};
enum Sensores_enum
{
  NENHUM,
  SENSOR_DIREITO,
  SENSOR_ESQUERDO,
  AMBOS
};

int trigEsquerda = 7;
int echoEsquerda = 10;
// int trigcen = 5;
// int echocen = 6;
int trigDireita = 2;
int echoDireita = 4;
int distEsquerda, distDireita; /*distcen, */

void setup()
{

  pinMode(trigEsquerda, OUTPUT);
  // pinMode(trigcen, OUTPUT);
  pinMode(trigDireita, OUTPUT);
  pinMode(echoEsquerda, INPUT);
  // pinMode(echocen, INPUT);
  pinMode(echoDireita, INPUT);
  //pinMode(0, OUTPUT);
  //pinMode(1, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
}

void motores_para()
{
  digitalWrite(11, LOW);
  digitalWrite(5, LOW);
}

void motores_frente()
{
  digitalWrite(11, HIGH);
  digitalWrite(5, HIGH);
  delay(2000);
}

void motores_direito()
{
  digitalWrite(11, LOW);
  digitalWrite(5, HIGH);
  delay(1000);
}

void motores_esquerdo()
{
  digitalWrite(11, HIGH);
  digitalWrite(5, LOW);
  delay(1000);
}

void loop()
{
  maquina_estado_run(ler_IR());

  delay(10);
}

uint8_t estado = FRENTE;

void maquina_estado_run(uint8_t sensores)
{
  switch (estado)
  {
  case PARA:
    motores_para(); // desliga os dois motores
    break;

  case FRENTE:
    motores_frente(); // anda pra frente por 2s
    break;

  case ROTACAO_DIREITA:
    motores_direito(); // gira pra direita por 1s
    motores_frente();  // anda pra frente por 2s
    break;

  case ROTACAO_ESQUERDA:
    motores_esquerdo(); // gira pra esquerda por 1s
    motores_frente();   // anda pra frente por 2s
    break;
  }
}

uint8_t ler_IR()
{
  long duracaoEsquerda;
  long distanciaEsquerda;

  long duracaoDireita;
  long distanciaDireita;

  digitalWrite(trigEsquerda, LOW);
  delayMicroseconds(2);
  digitalWrite(trigEsquerda, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigEsquerda, LOW);
  duracaoEsquerda = pulseIn(echoEsquerda, HIGH);
  distanciaEsquerda = duracao / 58; // converte sensor para CM

  digitalWrite(trigDireita, LOW);
  delayMicroseconds(2);
  digitalWrite(trigDireita, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigDireita, LOW);
  duracaoDireita = pulseIn(echo, HIGH);
  distanciaDireita = duracao / 58; // converte sensor para CM

  if (distanciaEsquerda > 20 && distanciaDireita > 20) // sem nenhuma parede dos lados > Fim do lbirinto
  { 
    return NENHUM;
  }
  else if (distanciaEsquerda < 20 && distanciaDireita > 20) // parede na esquerda
  {
    return ROTACAO_DIREITA;
  }
  else if (distanciaEsquerda > 20 && distanciaDireita < 20) // parede na direita
  {
    return ROTACAO_ESQUERDA;
  }
  else if (distanciaEsquerda < 20 && distanciaDireita < 20) // parede dos dois lados
  {
    return AMBOS;
  }

  delay(500);
}
