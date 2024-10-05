#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>
 
// Crear objeto de la clase
Adafruit_ADS1015 ads;
 
// Factor de escala. Por defecto el valor de referencia es 6,144V
// El factor de escala de esta referencia es de 0,1875mV
float factorEscala = 0.1875F;
 
void setup(void)
{
  Serial.begin(921600); //115200
  // Iniciar el ADS1015
  ads.begin();
  ads.setDataRate(RATE_ADS1015_3300SPS);
}
 
void loop(void)
{  
  // Obtener el diferencial
  short diferencia_0_1 = ads.readADC_Differential_0_1();
  
  // Convertir en voltios 
  float voltios = (diferencia_0_1 * factorEscala) / 1000.0;


  // Imprimir solo el valor de voltaje para el plotter
  Serial.println(voltios);

}
