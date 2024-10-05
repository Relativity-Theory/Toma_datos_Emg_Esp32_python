#include <Arduino.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>
 
// Crear objeto de la clase para el ADS1115
Adafruit_ADS1115 ads;

// Factor de escala para el ADS1115 con referencia de 6,144V (por defecto 0.1875 mV)
float factorEscala = 0.1875F;

void setup(void)
{
  Serial.begin(921600);
  
  // Iniciar el ADS1115
  if (!ads.begin()) {
    Serial.println("Error al iniciar el ADS1115");
    while (1);
  }

  // Configurar la tasa de muestreo del ADS1115
  ads.setDataRate(RATE_ADS1115_860SPS);  // Máxima tasa de muestreo para ADS1115
}
 
void loop(void)
{  
  // Obtener el diferencial entre A0 y A1
  short diferencia_0_1 = ads.readADC_Differential_0_1();
  
  // Convertir a voltios
  float voltios = (diferencia_0_1 * factorEscala) / 1000.0;

  // Imprimir solo el valor de voltaje para el plotter
  Serial.println(voltios);


}

