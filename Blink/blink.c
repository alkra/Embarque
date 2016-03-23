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
 */

#include <bcm2835.h>
#include <stdlib.h>

#define PIN RPI_V2_GPIO_P1_07

int main()
{
    int retcode = EXIT_FAILURE;
    
    if(bcm2835_init())
    {
	// Setup
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
	
	// Blink
	while(1)
	{
	    bcm2835_gpio_write(PIN, HIGH);
	    bcm2835_delay(1000);
	    bcm2835_gpio_write(PIN, LOW);
	    bcm2835_delay(1000);
	}
	
	// Finalize
	bcm2835_close();
	retcode = EXIT_SUCCESS;
    }
    
    return retcode;
}
