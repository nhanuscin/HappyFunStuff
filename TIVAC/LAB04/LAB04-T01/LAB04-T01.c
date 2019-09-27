#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

int main(void)
{
    uint32_t ui32Period;
    //Set Clock to 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //Enable PortF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    //Enable Timer0A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    //Set timer to 10Hz 43% duty cycle
    ui32Period =  (43*SysCtlClockGet()/10) / 100;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);
    //Enable timer interrupt
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    TimerEnable(TIMER0_BASE, TIMER_A);

    while(1)
    {
    }
}

void Timer0IntHandler(void)
{
    uint32_t ui32Period2;
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Read the current state of the GPIO pin and
    // write back the opposite state
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
    {
        //Turn off LED and set 57% duty cycle
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        ui32Period2 =  (57*SysCtlClockGet()/10) / 100;
        TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period2 -1);
    }
    else
    {
        //Turn on LED and set 43% duty cycle
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
        ui32Period2 =  (43*SysCtlClockGet()/10) / 100;
        TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period2 -1);
    }
}
