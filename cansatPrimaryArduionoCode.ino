#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>

byte NTCPin = A0;
#define SERIESRESISTOR 10000
#define NOMINAL_RESISTANCE 10000
#define NOMINAL_TEMPERATURE 21
#define BCOEFFICIENT 3950

float  Pressure1;
float  PressureValue;
float  Tc;
float  Tf;
float  num1;
float  num2;
float  num3;
float  num4;
float  num5;
float  Altitude;
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

float steinhart;
float ADCvalue;
float Resistance;
void Temperature() {
  
ADCvalue = analogRead(NTCPin);
//Serial.print("Analog value ");
//Serial.print(ADCvalue);
//Serial.print(" = ");
//convert value to resistance
Resistance = (1023 / ADCvalue) - 1;
Resistance = SERIESRESISTOR / Resistance;
//Serial.print(Resistance);
//Serial.println(" Ohm");

steinhart = Resistance / NOMINAL_RESISTANCE; // (R/Ro)
steinhart = log(steinhart); // ln(R/Ro)
steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
steinhart = 1.0 / steinhart; // Invert
steinhart -= 273.15; // convert to C
steinhart /=2;
//Serial.print("Temperature ");
//Serial.print(steinhart);
//Serial.println(" oC");
//delay(1000);
}

void Pressure() {
  PressureValue = analogRead(A1);
  Pressure1 = PressureValue / 1024 + 0.095;
  Pressure1 = Pressure1 / 0.0009;
  num1 = Pressure1 * 100;
  num2 = num1 / 101325;
  num3 = log10(num2) ;
  num4 = num3 / 5.25588;
  num5 = pow(10.0, num4) - 1;
  Altitude = num5 / 0.000035;


}

void Print_Results() {
  Serial.print("Temperature =  ");
  Serial.print(steinhart);
  Serial.print("C, Pressure =  ");
  Serial.print(Pressure1);
  Serial.print(", Altitude =  ");
  Serial.print(Altitude);
  Serial.println("m");

}

void setup()
{
  Pressure1 = 0;
  PressureValue = 0;
  Tc = 0;
  Tf = 0;
  num1 = 0;
  num2 = 0;
  num3 = 0;
  num4 = 0;
  num5 = 0;
  Altitude = 0;
  Serial.begin(9600);
}


void loop()
{
  Temperature();
  Pressure();
  Print_Results();
  delay(1000);

}
