#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>

Adafruit_ADS1015 ads;
const float multiplier = 3.0F;  // Multiplicador para ADS1015

void setup(void) {
  Serial.begin(230400);  // Inicia la comunicación serial a 230400 baudios
  if (!ads.begin()) {  // Verifica si el ADS1015 se inicializa correctamente
    Serial.println("No se pudo encontrar el ADS1015. Verifica la conexión.");
    while (1);  // Detiene el programa en caso de error
  }
  ads.setDataRate(RATE_ADS1015_3300SPS);  // Configura la tasa de muestreo más rápida disponible para el ADS1015
}

void loop(void) {
  int16_t adc0;  // Variable para almacenar el valor de ADC0
  float volts[1];  // Arreglo para almacenar el voltaje de ADC0

  // Leer el valor de ADC0 (canal 0)
  adc0 = ads.readADC_SingleEnded(0);
  
  // Convertir el valor de ADC a voltios y almacenarlo en el arreglo
  volts[0] = ads.computeVolts(adc0);

  // Enviar los datos por el puerto serie
 
  Serial.print(volts[0], 4);  // Imprimir voltaje con 4 decimales
  Serial.println(" V");

  delay(1000);  // Espera de 1 segundo entre cada lectura
}

