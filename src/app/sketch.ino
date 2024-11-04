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

  delay(10000);
}

void checarNivelAgua() {
  int distancia = ultrasonic.read();
  Serial.print("A distância de líquidos nos reservatórios de água: ");
  Serial.println(distancia);

  if(nivelAgua < aguaNecessaria) {
    desativarIrrigacao();
  } else {
    ativarIrrigacao();
  }
}

void desativarIrrigacao() {
  Serial.println("Desativando a irrigação...");
}

void ativarIrrigacao() {
  Serial.println("Ativando a irrigação...");
}

void checarClima() {
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if(isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao ler o DHT.");
  }

  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Umidade: ");
  Serial.println(umidade);

  if(umidade < umidadeIdeal || temperatura > temperaturaIdeal) {
    Serial.println("A umidade ou a temperatura não está ideal!");
    ativarIrrigacao();
  } else {
    Serial.println("A umidade ou a temperatura está ideal.");
    desativarIrrigacao();
  }
}

void detectarInvasao() {
  boolean presencaDetectada = digitalRead(PIRDPino);

  if(presencaDetectada == true) {
    Serial.println("Invasão detectada! Ativando alarmes de segurança...");
  } else {
    Serial.println("Nenhuma invasão detectada.");
  }
}

void luminosidadeRecebida() {
  int intensidadeLuz = analogRead(DOPino); 

  if(luminosidadeIdeal < intensidadeLuz) {
    Serial.println("A luminosidade está baixa, a irrigação irá ser ativa...");
    ativarIrrigacao();
  } else {
    Serial.println("A luminosidade está ideal.");
    desativarIrrigacao();
  }
}
