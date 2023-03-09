//Declaração das constantes
const int pinoTrigger = 10;
const int pinoEcho = 9;
const int pinoBuzzer = 8;

//Declaração das variáveis
long duracao;
int distancia;
int distanciaDeSeguranca = 50;

void setup() {
  //Inicia monitor serial
  Serial.begin(9600);
  //Definição dos Pinos de entrada e saída
  pinMode(pinoTrigger, OUTPUT);
  pinMode(pinoEcho, INPUT);
  pinMode(pinoBuzzer, OUTPUT);
}

void loop() {
  //Define o pino Trigger como LOW (BAIXO) ou seja, desligado
  digitalWrite(pinoTrigger, LOW);
  //Aguarda 2 microssegundos para enviar o próximo comando 
  delayMicroseconds(2);
  //Define o pino Trigger como HIGH (ALTO) ou seja, ligado
  //Nesse caso é onde é feito o envio do sinal do sensor ultrassônio
  digitalWrite(pinoTrigger, HIGH);
  //Aguarda 10 microssegundos para enviar o próximo comando 
  delayMicroseconds(10);
  //Define o pino Trigger como LOW (BAIXO) ou seja, desligado
  digitalWrite(pinoTrigger, LOW);

  //Faz a medição de quanto tempo o sinal enviado pelo sensor demorou para refletir de volta após detectar o objeto.
  //Ou seja, mede o tempo que o sinal Echo (pinoEcho) ficou em nível HIGH (ALTO).
  duracao = pulseIn(pinoEcho, HIGH);

  /*
    Mede a distância em centímetros com base na duração calculada anteriormente.
    A velocidade do som no ar é de aproximadamente 340 metros por segundo, ou 0.034 centímetros por microssegundo. 
    A divisão por 2 é necessária porque o pulso deve ir e voltar do objeto para medir a distância. 
  */
  distancia = duracao * 0.034 / 2;

  //Mostra a distância em cm no Monitor Serial
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  //Valida se distância for menor (<) que a distância de segurança definida na variável distanciaDeSeguranca, nesse projeto é 50
  if (distancia < distanciaDeSeguranca) {
    //Se a condição for VERDADEIRO irá 
    //Define a frequencia do som emitido pelo buzzer
    int frequencia = 400;
    //Faz o mapeamento da distância medida pelo sensor para indicar a velocidade de bips do buzzer
    int tempoDelay = map(distancia, 0, distanciaDeSeguranca, 150, 400); 
    for (int i = 0; i < 3; i++) {
      //A função tone() é utilizada para ativar/ligar o buzzer, a frequência é indicada para definir o tom que irá emitir
      tone(pinoBuzzer, frequencia);
      //Faz o tempo de espera calculado acima
      delay(tempoDelay);
      //Desliga o buzzer
      noTone(pinoBuzzer);
      //Faz o tempo de espera calculado acima
      delay(tempoDelay);
    }
  } else {
      //Se a condição for FALSO irá
      //Desligar o buzzer
    noTone(pinoBuzzer);
  }
  delay(50);
}
