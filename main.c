

// This code blinks the LED on the LPC11U35 quickstart board.
// It is an introduction to how this processor can be used in a
//  GCC based developmet environment with local libraries.
//
// It does not require any vendor locked libraries.


#include <type.h>
#include "LPC11Uxx.h"
#include <system_LPC11Uxx.h>
#include "gpio.h"

#define LED7_GPIO 0  // LED on GPIO 0,
#define LED7_BIT  7  // Pin 7.
#define LED_ON   1  // Level to set port to turn on led
#define LED_OFF  0  // Level to set port to turn off led

#define True 1
#define False 0
#define MSCOUNT_MAX 1000

// ISR based delay routine:
static __IO uint32_t TimingDelay;
static __IO uint8_t SystickEvt;  //Systick has occurred
void Delay_ms(uint32_t nTime);



int main(void) {

  uint32_t mscount=0;

  SystickEvt=False;
  
  GPIOInit();  // Initialize GPIO port.

  TimingDelay=0; //Initialize timer variable.

  GPIOSetDir(LED7_GPIO, LED7_BIT, 1 );   // Configure LED pin as output

  GPIOSetBitValue(LED7_GPIO, LED7_BIT, LED_OFF);

  //Configure systick timer for 1ms interrupts:
  if (SysTick_Config(SystemCoreClock/1000)){
    while (1); //If not successful, block here...
  }
  
  
  while (1) {

    if (SystickEvt==True){
      ++mscount;
      SystickEvt=False;
      if (mscount==MSCOUNT_MAX)
	mscount=0;
    }

    if (mscount<100){
    GPIOSetBitValue(LED7_GPIO, LED7_BIT, LED_ON); // Turn LED on
    }else if (mscount>=100 && mscount<200){
    GPIOSetBitValue(LED7_GPIO, LED7_BIT, LED_OFF);
    }else if (mscount>=200 && mscount<300){
    GPIOSetBitValue(LED7_GPIO, LED7_BIT, LED_ON);
    }else if (mscount>=300 && mscount<MSCOUNT_MAX){
    GPIOSetBitValue(LED7_GPIO, LED7_BIT, LED_OFF);
    }

    //    Delay_ms (100);

  }
}


//static __IO uint32_t TimingDelay;
/*
void Delay_ms( uint32_t nTime ){
  TimingDelay = nTime ;
  while ( TimingDelay != 0);
  }
*/

void SysTick_Handler (void){            // ISR
  //  if ( TimingDelay != 0x00)
  //    TimingDelay --;

  SystickEvt=True;
  //  GPIOSetBitValue(LED7_GPIO, LED7_BIT, LED_ON);

}
