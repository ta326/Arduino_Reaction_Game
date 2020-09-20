#ifndef __UTILS_H__
#define __UTILS_H__

void LED_Initialize(void);
void LEDRed_Toggle (void);
void LEDBlue_Toggle (void);
void LEDGreen_Toggle (void);
void LEDRed_On (void);
void LEDGreen_On (void);
void LEDBlue_On (void);
void LEDTeal_On(void);
void LEDPurple_On(void);
void LEDWhite_On(void);
void LEDYellow_On(void);
void LED_Off (void);
void LEDRed_Blink(void);
void LEDBlue_Blink(void);
int LEDRed_Blink_num(int num);
int LEDBlue_Blink_num(int num);
void delay (void);
int multi_delay(int num);
int var_delay(int num);
void switch_setup(void);
void game_break (void);
void check_led(int arr[], int total, int num);
typedef struct {
	unsigned int sec;
	unsigned int msec;
} realtime_t;
//realtime_t start = {0,0} ;
//realtime_t current_time ={0,0};
#endif
