#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "usb_msd.h"

/*
 * Orange LED blinker thread, times are in milliseconds.
 */
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(100);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(100);
  }
}

int main(void) {
  halInit();
  chSysInit();

  palSetPadMode(GPIOD, GPIOD_LED4, PAL_MODE_ALTERNATE(2));  /* Green.   */

  sdcStart(&SDCD1, NULL);
  sdcConnect(&SDCD1);

  //palSetPad(GPIOC, GPIOC_LED);

  USBMassStorageDriver UMSD1;
//  msdInit(&USBD1, &SDCD1, &UMSD1);

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  while (TRUE) {
    chThdSleepMilliseconds(1000);
  }
}
