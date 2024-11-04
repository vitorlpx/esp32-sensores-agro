#include <DHT.h> // Biblioteca para o sensor DHT
#include <Ultrasonic.h> // Biblioteca para o sensor ultrassônico

// Definição dos pinos utilizados
#define ECHOPino 18
#define TRIGPino 5
#define DHTPino 13
#define DOPino 12
#define PIRDPino 17

// Definição do modelo do sensor DHT
#define modeloDHT DHT22

// Variáveis para o nível de água
float nivelAgua = 30.0;
float aguaNecessaria = 40.0;

// Valores ideais para umidade, temperatura, distância e luminosidade
int umidadeIdeal = 40;  
int temperaturaIdeal = 30;  
int limiteDistancia = 26;  
int luminosidadeIdeal = 30;  

// Inicialização dos sensores
DHT dht(DHTPino, modeloDHT);
Ultrasonic ultrasonic(TRIGPino, ECHOPino);

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  dht.begin(); // Inicializa o sensor DHT

  // Configura os pinos como entrada
  pinMode(DOPino, INPUT);
  pinMode(PIRDPino, INPUT);

  Serial.println("Sistema de monitoramento iniciado."); // Mensagem de inicialização
}

void loop() {
  detectarInvasao(); // Função para detectar invasão
  checarNivelAgua(); // Função para checar o nível de água
  checarClima(); // Função para checar o clima
  luminosidadeRecebida(); // Função para checar a luminosidade

  delay(10000); // Aguarda 10 segundos antes de repetir o loop
}

// Função para checar o nível de água
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

// Função para desativar a irrigação
void desativarIrrigacao() {
  Serial.println("Desativando a irrigação...");
}

// Função para ativar a irrigação
void ativarIrrigacao() {
  Serial.println("Ativando a irrigação...");
}

// Função para checar o clima
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

// Função para detectar invasão
void detectarInvasao() {
  boolean presencaDetectada = digitalRead(PIRDPino);

  if(presencaDetectada == true) {
    Serial.println("Invasão detectada! Ativando alarmes de segurança...");
  } else {
    Serial.println("Nenhuma invasão detectada.");
  }
}

// Função para verificar a luminosidade
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
