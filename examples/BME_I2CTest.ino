/*
  Tiny BME280 Library
  https://github.com/technoblogy/tiny-bme280
  Example to print out environmental data (temperature, pressure, humidity) once per second.

  Created by Max Kendall
  Modified 20 January 2024
  Library by Technoblogy

  Connections:
  BME --- MCU
  VCC to 3v3
  GND to GND
  SDA to A4
  SCL to A5

  Set your Serial monitor to 9600 baud and click the magnifiying glass icon on the top-right.
*/

#include <TinyBME280.h>

void setup() {
  // Runs once at start or board reset

  // Uncomment to change address. Default is 0x77
  //BME280setI2Caddress(address)

  // Begin the I2C connection with BME280
  BME280setup();

  // Begin Serial monitor output for debugging
  Serial.begin(9600);

  Serial.println("BME280 Interface Example.");
}

void loop() {
  // Runs forever after setup

  // Gives the temperature as a signed 32-bit integer in °C with a resolution of 0.01°C. So an output value of “5123” equals 51.23°C.
  float temp = BME280temperature() / 100;

  // Pives the pressure in Pa as an unsigned 32-bit integer, so an output value of “96386” equals 96386 Pa, or 963.86 hPa.
  float press = BME280pressure() / 100;

  // Gives the humidity in %RH with a resolution of 0.01% RH, so an output value of “4653” represents 46.53 %RH.
  float humid = BME280humidity() / 100;


  // Print the data to Serial output!
  Serial.print("Temperature: ");
  Serial.print(temp);

  Serial.print("Pressure: ");
  Serial.println(press);

  Serial.print("Humidity: ");
  Serial.print(humid);

  delay(1000);
}
