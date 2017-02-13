
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Delay(volatile long);
void Segment_flip(int, int);
void systick_counter();
void reset();
void count_up();
void count_down();
void pause();
void enter();
void num_in(int);
void blank();
int is_valid();
void push_new(int);
void push_update(int);
void update_all();
void force_current();
void preset(int,int,int,int,int,int);
void keypad();
void test_digit(int );
void clear_digit(int );
void test_digit(int);
void set_digit(int);
void set_zero(int);
void set_one(int);
void set_two(int);
void set_three(int);
void set_four(int);
void set_five(int);
void set_six(int);
void set_seven(int);
void set_eight(int);
void set_nine(int);
void up_zero(int);
void up_one(int);
void up_two(int);
void up_three(int);
void up_four(int);
void up_five(int);
void up_six(int);
void up_seven(int);
void up_eight(int);
void up_nine(int);
void down_zero(int);
void down_one(int);
void down_two(int);
void down_three(int);
void down_four(int);
void down_five(int);
void down_six(int);
void down_seven(int);
void down_eight(int);
void down_nine(int);

#endif /* __MAIN_H */
