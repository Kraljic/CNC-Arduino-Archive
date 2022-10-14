
#ifndef config_h
#define config_h

#define INFO_LED 13

#define X_STEP 8
#define Y_STEP 6
#define X_DIR 9   // 
#define Y_DIR 7   // 

// PULLUP OTPORNICI
#define X_SENSOR A0
#define Y_SENSOR A1

// PWM PIN
#define Z_SERVO 12	


/*
 *	A4988 controler
 * 
 *  MS1 MS2 MS3     STEP:
 *   L   L   L    -> FULL 
 *   H   L   L    -> HALF 
 *   L   H   L    -> QUARTER 
 *   H   H   L    -> EIGHTH 
 *   H   H   H    -> SIXTEENTH 
 */
#define MS1 2
#define MS2 3
#define MS3 4

// NEGIRANO (LOW ZA SLEEP)
#define SLEEP 5

// CONTROL VAR
#define STEPS_PER_MM 5.011d
#define HOME_OFFSET 10 // n MM from (0, 0)

// SERIAL SPEED
#define BAUD_RATE 1200

#endif
