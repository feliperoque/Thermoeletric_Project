/** 
  Autor: Felipe Roque de Albuquerque Neto;
  Instituição: Instituto Federal de Pernambuco - Recife;
  Título do Projeto: Desenvolvimento de um dispositivo inteligente de baixo custo para transporte de materiais biológicos, vacinas e remédios. ;
 */

#include <OneWire.h>
#include <DallasTemperature.h>

// CONFIG RELAY
const int peltier = 5;
const int fan = 4;

// LED CONFIGURATION
const int green_led = 8;
const int red_led = 10;

// CONFIG TEMPERATURE SENSORS
const int pin_data = 7;
OneWire oneWire(pin_data);
DallasTemperature sensor_ds18b20(&oneWire);
float intern_temperature;

// VARIABLES
float disrd_temperature = 4;

void setup() {

  Serial.begin(9600);      // Initializing Serial
  sensor_ds18b20.begin();  // Initializing Temperature Sensor

  // RELAY PINS
  pinMode(peltier, OUTPUT);
  pinMode(fan, OUTPUT);

  // LED PINS
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
}

void loop() {

  if (intern_temperature >= disrd_temperature) {
    digitalWrite(fan, LOW);         // Turn Fans On
    digitalWrite(peltier, LOW);     // Turn Peltier On
    digitalWrite(red_led, LOW);     // Turn Red Led Off
    digitalWrite(green_led, HIGH);  // Turn Green Led On

    sensor_ds18b20.requestTemperatures();  // Request Sensor Data
    intern_temperature = sensor_ds18b20.getTempCByIndex(0);

    int estadoAtual = 1;

    Serial.print(estadoAtual);
    Serial.print(" , ");
    Serial.print(intern_temperature);
    Serial.println(" ");
    
  }

  else if (intern_temperature <= disrd_temperature) {
    digitalWrite(fan, LOW);        // Turn Fans Off
    digitalWrite(peltier, HIGH);   // Turn Peltier Off
    digitalWrite(red_led, HIGH);   // Turn Red Led On
    digitalWrite(green_led, LOW);  // Turn Green Led Off

    sensor_ds18b20.requestTemperatures();  // Request Sensor Data
    intern_temperature = sensor_ds18b20.getTempCByIndex(0);

    int estadoAtual = 0;

    Serial.print(estadoAtual);
    Serial.print(" , ");
    Serial.print(intern_temperature);
    Serial.println(" ");
  }
}
