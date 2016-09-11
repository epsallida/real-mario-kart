#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

boolean banana1Enabled = false;
boolean banana2Enabled = false;
boolean shellEnabled = false;

// TSL2561
/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.

   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground

   I2C Address
   ===========
   The address will be different depending on whether you leave
   the ADDR pin floating (addr 0x39), or tie it to ground or vcc.
   The default addess is 0x39, which assumes the ADDR pin is floating
   (not connected to anything).  If you set the ADDR pin high
   or low, use TSL2561_ADDR_HIGH (0x49) or TSL2561_ADDR_LOW
   (0x29) respectively.

   History
   =======
   2013/JAN/31  - First version (KTOWN)
*/

Adafruit_TSL2561_Unified tsl1 = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 1);
Adafruit_TSL2561_Unified tsl2 = Adafruit_TSL2561_Unified(TSL2561_ADDR_HIGH, 2);
Adafruit_TSL2561_Unified tsl3 = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 3);



// NEOPIXEL
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      100

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
int delayval = 500; // delay for half a second




/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensor1Details(void)
{
  sensor_t sensor1;
  tsl1.getSensor(&sensor1);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor1.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor1.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor1.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor1.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor1.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor1.resolution); Serial.println(" lux");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displaySensor2Details(void)
{
  sensor_t sensor2;
  tsl2.getSensor(&sensor2);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor2.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor2.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor2.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor2.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor2.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor2.resolution); Serial.println(" lux");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displaySensor3Details(void)
{
  sensor_t sensor3;
  tsl2.getSensor(&sensor3);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor3.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor3.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor3.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor3.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor3.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor3.resolution); Serial.println(" lux");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2561
*/
/**************************************************************************/
void configureSensor(void)
{
  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl1.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  tsl2.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  tsl3.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */


  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  tsl1.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  tsl2.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  tsl3.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */

  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

  /* Update these values depending on what you've set above! */
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
}

void configureNeoPixel(void)
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Light Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if (!tsl1.begin() || !tsl2.begin() || !tsl3.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.print("Ooops, one or more TSL2561 not detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  /* Display some basic information on this sensor */
  displaySensor1Details();
  displaySensor2Details();
  displaySensor3Details();

  /* Setup the sensor gain and integration time */
  configureSensor();

  configureNeoPixel();


  /* We're ready to go! */
  Serial.println("Ready to go");

}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event1;
  tsl1.getEvent(&event1);

  /* Get a new sensor event */
  sensors_event_t event2;
  tsl2.getEvent(&event2);

  /* Get a new sensor event */
  sensors_event_t event3;
  tsl3.getEvent(&event3);

  /* Display the results (light is measured in lux) */
  if (event1.light)
  {
    Serial.print(event1.light); Serial.println(" lux in sensor 1");
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }
  //delay(250);

  /* Display the results (light is measured in lux) */
  if (event2.light)
  {
    Serial.print(event2.light); Serial.println(" lux in sensor 2");
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }
  //delay(250);

  /* Display the results (light is measured in lux) */
  if (event3.light)
  {
    Serial.print(event3.light); Serial.println(" lux in sensor 3");
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }
  //delay(250);

  //banana 1
  if (event1.light > 150) {
    if (!banana1Enabled) {
      for (int i = 5; i > 0; i--) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 0, 0));
      }
      banana1Enabled = true;
      delay(250);

    } else {
      for (int i = 5; i > 0; i--) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0));
      }
      banana1Enabled = false;
    }
  }

  // banana 2
  if (event2.light > 150) {
    if (!banana2Enabled) {
      for (int i = 11; i > 6; i--) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 0, 0));
      }
      banana2Enabled = true;
      delay(250);

    } else {
      for (int i = 11; i > 6; i--) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0));
      }
      banana2Enabled = false;
    }
  }

  // shell
  if (event3.light > 150) {
    if (!shellEnabled) {
      for (int i = 80; i > 11; i--) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 0, 0));
      }

      shellEnabled = true;
      delay(250);

    } else {
      for (int i = 80; i > 11; i--) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0));
      }
      shellEnabled = false;
      delay(250);

    }
  }

  pixels.show(); // This sends the updated pixel color to the hardware.
  //delay(50000);

}