
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO_Interface.h"

#define  FIRST_OUT  PINB4
#define  FIRST_IN   PIND2

#define  ROWS 4
#define  COLS 4
#define  NO_KEY  ','
u8 KEYPAD_GetEntry(void);



#endif /* KEYPAD_H_ */