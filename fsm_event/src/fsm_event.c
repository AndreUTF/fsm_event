#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com apenas 8 estados e 1 evento temporal que alterna entre eles
// Seleção por evento

//Estado_0 - 000
//Estado_1 - 001
//Estado_2 - 011
//Estado_3 - 010
//Estado_4 - 110
//Estado_5 - 111
//Estado_6 - 101
//Estado_7 - 100

typedef enum {Estado_0, Estado_1, Estado_2, Estado_3, Estado_4, Estado_5, Estado_6, Estado_7, Estado_8} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static state_t Estado = Estado_0; // estado inicial da MEF
  LEDInit(LED1); //LED1 represnta o bit 0 da sequência de 3 bits
  LEDInit(LED2); //LED2 represnta o bit 1 da sequência de 3 bits
  LEDInit(LED3); //LED3 represnta o bit 2 da sequência de 3 bits
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    switch(Estado){
    case Estado_0: //Estado_0 - 000
      LEDOff(LED1);
      LEDOff(LED2);
      LEDOff(LED3);
      if(Evento){
        Evento = 0;
        Estado = Estado_1;
      }
      break;
    case Estado_1: //Estado_1 - 001
      LEDOn(LED1);
      LEDOff(LED2);
      LEDOff(LED3);
      if(Evento){
        Evento = 0;
        Estado = Estado_2;
      }
      break;
    case Estado_2: //Estado_2 - 011
      LEDOn(LED1);
      LEDOn(LED2);
      LEDOff(LED3);
      if(Evento){
        Evento = 0;
        Estado = Estado_3;
      }
      break; 
    case Estado_3: //Estado_3 - 010
      LEDOff(LED1);
      LEDOn(LED2);
      LEDOff(LED3);
      if(Evento){
        Evento = 0;
        Estado = Estado_4;
      }
      break; 
    case Estado_4: //Estado_4 - 110
      LEDOff(LED1);
      LEDOn(LED2);
      LEDOn(LED3);
      if(Evento){
        Evento = 0;
        Estado = Estado_5;
      }
      break;
    case Estado_5: //Estado_5 - 111
      LEDOn(LED1);
      LEDOn(LED2);
      LEDOn(LED3);
      if(Evento){
        Evento = 0;
        Estado = Estado_6;
      }
      break;
    case Estado_6: //Estado_6 - 101
      LEDOn(LED1);
      LEDOff(LED2);
      LEDOn(LED3);
      if(Evento){
        Evento = 0;
        Estado = Estado_7;
      }
      break;
    case Estado_7: //Estado_7 - 100
      LEDOff(LED1);
      LEDOff(LED2);
      LEDOn(LED3);
      if(Evento){
        Evento = 0;
        Estado = Estado_0;
      }
      break;
    }
  } // while
} // main
