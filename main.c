#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

void SystickHandler(void);

/**
 * main.c
 */
int main(void)
{

    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_USE_OSC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    SysTickPeriodSet(16000000);
	SysTickEnable();
	SysTickIntEnable();
	SysTickIntRegister(&SystickHandler);

	//__asm("CPSIE I");
	while(1){
	    //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
	    __asm("WFI");

	}

}

void SystickHandler(void){
    int x = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1);

    if(x == 0){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    }else{
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
    }

    //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

}

