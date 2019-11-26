Tiny BME280
===========
The Bosch BME280 is the perfect sensor for a home weather station as it provides temperature, pressure, and humidity in a single device. This is an interface to allow you to use the sensor from an ATtiny processor such as the ATtiny85.

For information about using this library see [ATtiny85 Weather Station](http://www.plasticki.com/show?2F5D).

 

#### Introduction

The Bosch BME280 is a relatively low cost sensor which measures three environmental variables in a single device: temperature, pressure, and humidity. It's available on a breakout board from Adafruit, Sparkfun, or Chinese suppliers such as AliExpress and Banggood. Some boards, such as Adafruit's, support either 5V or 3.3V operation, so check carefully before buying if this is important to you.

The downside with this sensor is that you have to do quite a bit of calculation to get the final readings; it's not just a case of reading the values from the device via I2C or SPI, as with some other sensors. Both Adafruit and Sparkfun provide a library to interface to the sensor, but unfortunately these don't seem to work on ATtiny processors, such as the ATtiny85, so I set about writing my own Tiny BME280 library. I've only supported the I2C interface as it is the most useful one on ATtiny devices with a limited number of pins.

As with the other libraries my library uses the calculations from the BME280 datasheet, and I checked that it gives identical readings to the Sparkfun one. The only difference was with the pressure reading; Bosch gives two versions of the calculation, one using 64-bit integers and one using 32-bit integers. Sparkfun use the 64-bit version and I used the 32-bit version, but this resulted in a difference of under 1 part in 10000. I haven't provided altitude or dew point calculations.

This library is also compatible with the Bosch BMP280, a similar sensor that provides just temperature and pressure. If you use this sensor you'll get zero humidity readings.

#### Routines

The library provides the following routines:

**BME280setI2Caddress(address)** - specifies the I2C address. This should be called before **BME280setup()**. You don't need to call this if you are using the default I2C address, 0x77.

**BME280setup()** - sets up the BME280 into its normal measurement mode, with no upsampling, and reads the fixed calibrations from the sensor. You should call this in setup().

**BME280temperature()** - gives the temperature as a signed 32-bit integer in °C with a resolution of 0.01°C. So an output value of “5123” equals 51.23°C.

**BME280pressure()** - gives the pressure in Pa as an unsigned 32-bit integer, so an output value of “96386” equals 96386 Pa, or 963.86 hPa.

**BME280humidity()** - gives the humidity in %RH with a resolution of 0.01%RH, so an output value of “4653” represents 46.53 %RH.

#### Altitude

To add altitude use this routine:

    // Altitude in metres
    float BME280altitude (float referencePressure) {
      return ((float)-45846.2)*(pow(((float)BME280pressure()/(float)referencePressure), 0.190263) - (float)1);
    }

where **referencePressure** is the pressure in Pa at zero altitude; for example, 101325.0.
