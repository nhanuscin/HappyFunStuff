#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"


 //about 2ms at 40Mhz
#define time 28333

//PWM frequency in hz
uint32_t freq = 100000;

int main()
{

  //Set clock to 40Mhz
  SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

  uint32_t i;
  uint32_t Period;
  uint32_t dutyCycle;
  Period = SysCtlClockGet()/freq ;  //set period to 400
  dutyCycle = Period-2;

  //Configure PF1 as T0CCP1
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlDelay(3);
  GPIOPinConfigure(GPIO_PF1_T0CCP1);
  GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);



  //Configure timer 0 to split pair and timer B in PWM mode
  //Set period and starting duty cycle.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  SysCtlDelay(3);
  TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PWM);
  TimerLoadSet(TIMER0_BASE, TIMER_B, Period -1);
  TimerMatchSet(TIMER0_BASE, TIMER_B, dutyCycle); // PWM

  //Turn on timer0B
  TimerEnable(TIMER0_BASE, TIMER_B);

  //Start by rising Red LED
  for(i=Period-2; i > 40 ;i--){
    TimerMatchSet(TIMER0_BASE, TIMER_B, i);
    SysCtlDelay(time);
  }
  while(1)
  {
    //Red brightness goes down
    for(i=1; i < 360; i++){
      TimerMatchSet(TIMER0_BASE, TIMER_B, i);
      SysCtlDelay(time);
    }
    //Red brightness goes up
    for(i=Period-2; i > 40; i--){
      TimerMatchSet(TIMER0_BASE, TIMER_B, i);
      SysCtlDelay(time);
    }

  }

}
