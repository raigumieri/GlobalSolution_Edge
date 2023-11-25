#include <WiFi.h>
#include <PubSubClient.h>
#include "HX711.h"

//HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 4;
HX711 scale;

const int peso_med1 = 7; // 7g de cada comprimido aspirina

//defines:
#define TOPICO_SUBSCRIBE    "/TEF/hosp200/cmd"   //tópico MQTT de escuta
#define TOPICO_PUBLISH      "/TEF/hosp200/attrs" //tópico MQTT de envio de informações para Broker
#define TOPICO_PUBLISH_1    "/TEF/lamp200/attrs/p"    //Tópico MQTT dos dados de Umidade

#define ID_MQTT  "fiware_200" //id mqtt (para identificação de sessão)

// WIFI
const char* SSID = "Wokwi-GUEST"; // nome da rede WI-FI
const char* PASSWORD = ""; // Senha da rede WI-FI 
  
// MQTT
const char* BROKER_MQTT = "46.17.108.113"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT

// Saída Led
int D4 = 16;  // Led builtin do ESP32 (led na placa)

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
char EstadoSaida = '0';  //variável que armazena o estado atual da saída
  
//Prototipos
void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);
 
void setup() 
{
    //inicializações:
    InitOutput();
    initSerial();
    initWiFi();
    initMQTT();
    MQTT.publish(TOPICO_PUBLISH, "s|off");

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}
  
void initSerial() 
{
    Serial.begin(115200);
}
 

void initWiFi() 
{
    delay(10);
    Serial.println("------Conexão WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
     
    reconectWiFi();
}
  

void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT); 
    MQTT.setCallback(mqtt_callback); 
}
  
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
     
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);
    
    //Toma ação dependendo da string recebida:
    //verifica se deve colocar nivel alto de tensão na saída D0:
    if (msg.equals("hosp200@on|"))
    {
        digitalWrite(D4, HIGH);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída D0:
    if (msg.equals("hosp200@off|"))
    {
        digitalWrite(D4, LOW);
        EstadoSaida = '0';
    }
}
  
//Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
//        em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentativa de conexao em 2s");
            delay(2000);
        }
    }
}
  
//Função: reconecta-se ao WiFi
void reconectWiFi() 
{
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}
 
void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}


//Função: inicializa o output em nível lógico baixo
void InitOutput(void)
{
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
    pinMode(D4, OUTPUT);
    digitalWrite(D4, HIGH);
    
    boolean toggle = false;

    for(int i = 0; i <= 10; i++)
    {
        toggle = !toggle;
        digitalWrite(D4,toggle);
        delay(200);           
    }

    digitalWrite(D4, LOW);
}
 
 
//Programa Principal
void loop() 
{   
    const int potPin = 34;
    
    char msgBuffer[4];
    //garante funcionamento das conexões WiFi e ao broker MQTT
    VerificaConexoesWiFIEMQTT();


    //HX711
      if (scale.is_ready()) {
      long reading = scale.read();
      long peso = reading * 2.38095238095;
      long comprimidos_1 = peso / peso_med1;

      int p = comprimidos_1;
      dtostrf(p, 4, 2, msgBuffer);
      MQTT.publish(TOPICO_PUBLISH_1,msgBuffer);

      Serial.println("---------------------------------------");
      Serial.print("|Leitura HX711: ");
      Serial.print(peso);
      Serial.println("g                 |");
      Serial.print("|Quantidade disponível: ");
      Serial.print(comprimidos_1);
      Serial.println(" unidades  |");
      Serial.println("---------------------------------------");


    } else {
      Serial.println("HX711 não encontrado.");
    }
    
    delay(1000);
    
    //keep-alive da comunicação com broker MQTT
    MQTT.loop();
}
