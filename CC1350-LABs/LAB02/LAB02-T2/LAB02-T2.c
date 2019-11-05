/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/ADC.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header file */
#include "Board.h"

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* 1 second delay */
    uint32_t time = 1;
    uint16_t adcValue0 = 0;
    //uint32_t adcValue0MicroVolt;
    uint16_t threshold = 675;
    uint16_t trigger = 0;

    /* Call driver init functions */
    GPIO_init();
    ADC_init();
    // I2C_init();
    // SPI_init();
    // UART_init();
    // Watchdog_init();
    ADC_Handle adc;
    ADC_Params params;
    ADC_Params_init(&params);
    adc = ADC_open(Board_ADC0, &params);
    if (adc == NULL) {
        //Display_printf(display, 0, 0, "Error initializing ADC channel 0\n");
        while (1);
    }

    /* Configure the LED pin */
    GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    while (1) 
    {
        int_fast16_t res;
        res = ADC_convert(adc, &adcValue0);
        if (res == ADC_STATUS_SUCCESS) 
        {
            //Display_printf(displayHandle, 1, 0, "ADC Reading %d", adcValue0);
            if(adcValue0 >= threshold)
            {
                GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);
                trigger = 1;
            } 
            else
            {
                GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_OFF);
                trigger = 0;
            }
        }
    sleep(time);
    }
}
