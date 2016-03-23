/* Alban Kraus
 *
 * (C) 2016 École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal -- Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX2
 * FRANCE
 *
 * This is free software. You can freely modify and/or distribute it
 * under the terms of the GNU General Public License version 3 or
 * above.
 *
 * This program dumps the sensor value.
 */

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

#define SENSOR_PIN         RPI_V2_GPIO_P1_12

int main()
{
  int retcode = EXIT_FAILURE;
    
  if(bcm2835_init())
  {
    unsigned char previous_level = HIGH, level;
    
    // Setup
    bcm2835_gpio_fsel(SENSOR_PIN, BCM2835_GPIO_FSEL_INPT);

    // Main loop
    while(1)
    {
      level = bcm2835_gpio_lev(SENSOR_PIN);
      fprintf(stderr, "%d", level);
      if(previous_level == HIGH && level == LOW)
      {
	printf("Detected!\n");
	system("raspistill --quality 50 --timeout 100 --encoding jpg --timestamp --output /home/pi/alban/intrusion_%d.jpg");
	previous_level = LOW;
      }
      else if(previous_level == LOW && level == HIGH)
	previous_level = HIGH;
      
      bcm2835_delay(100);
    }

    // Finalize
    bcm2835_close();
  }
  else
    fprintf(stderr, "Failed to initialize bcm2835. Are you running as root?\n");
    
  return retcode;
}

