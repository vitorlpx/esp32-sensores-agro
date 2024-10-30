#include <DHT.h>
#include <Ultrasonic.h>

#define ECHOPino 18
#define TRIGPino 5
#define DHTPino 13
#define DOPino 12
#define PIRDPino 17

#define modeloDHT DHT22

float nivelAgua = 30.0;
float aguaNecessaria = 40.0;

int umidadeIdeal = 40;  
int temperaturaIdeal = 30;  
int limiteDistancia = 26;  
int luminosidadeIdeal = 30;  

DHT dht(DHTPino, modeloDHT);
Ultrasonic ultrasonic(TRIGPino, ECHOPino);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(DOPino, INPUT);
  pinMode(PIRDPino, INPUT);

  Serial.println("Sistema de monitoramento iniciado.");
}

void loop() {
  detectarInvasao();
  checarNivelAgua();
  checarClima();
  luminosidadeRecebida();
}

void checarNivelAgua() {
}

void desativarIrrigacao() {
}

void ativarIrrigacao() {
}

void checarClima() {
}

void detectarInvasao() {
}

void luminosidadeRecebida() {
}