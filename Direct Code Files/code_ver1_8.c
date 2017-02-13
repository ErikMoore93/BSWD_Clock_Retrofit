/**
  ******************************************************************************
  * @file    IO_Toggle/main.c 
  * @author  Erik Moore, BSWD Clcok Retrofit Team 2014-2015
  * @contact Erikmoore93@yahoo.com
  * @version V1.5.0
  * @date    1-January-2015
  * @brief   Main program body
  ******************************************************************************

  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stdio.h"
/* Private define ------------------------------------------------------------*/
#define BSRR_VAL        0x0300

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef        GPIO_InitStructure;
              /* time[0]   time[1]  time[2]  time[3] time[4]  time[5]*/
int  time[6]; /* Hour_high Hour_low Min_high Min_low Sec_high Sec_low*/
int  update[6];
int  change[6]; //check for if change has occured since update
int  key;
int  backup_key;
int  stored_key;
int  key_changed;
int  cont;
int  paused;
long counter;

/* Private function prototypes -----------------------------------------------*/
void Delay(volatile long);
void Segment_flip(int, int);
void reset();
void count_up();
void count_down();
void pause();
void enter();
void blank();
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

/* Private functions ---------------------------------------------------------*/

/*Turn on/off a specific pin*/
/*Takes the pin, and puts it on the specified latch*/
/* Seconds_low   on enable 1  (16),    off enable 2  (32)   */
/* Seconds_high  on enable 3  (64),    off enable 4  (128)  */
/* Minutes_low   on enable 5  (256),   off enable 6  (512)  */
/*  ---> Min_low moved to        1 ,                    2   */
/* Minutes_high  on enable 7  (1024),  off enable 8  (2048) */
/* Hours_low     on enable 9  (4096),  off enable 10 (8192) */
/* Hours_high    on enable 11 (16384), off enable 12 (32768)*/

/* Pin layout for segments */
/*  11111   */
/* 6     2  */
/* 6     2  */
/*  77777   */
/* 5     3  */
/* 5     3  */
/*  44444   */
/* 1 is 2, 2 is 4, 3 is 8, 4 is 16, 5 is 32, 6 is 64, 7 is 128 */

/*  -----      -----      -----       -----       -----        -----    */
/* |     |    |     |    |     |     |     |     |     |      |     |   */
/* |     |    |     |    |     |     |     |     |     |      |     |   */
/*  -----      -----      -----       -----       -----        -----    */
/* |     |    |     |    |     |     |     |     |     |      |     |   */
/* |     |    |     |    |     |     |     |     |     |      |     |   */
/*  -----      -----      -----       -----       -----        -----    */
/* Hours_high Hours_low Minutes_high Mintues_low Seconds_high Seconds_low  */
/* On  latches:                                                            */
/* Enable_1   Enable_3  Enable_5     Enable_7    Enable_9     Enable_11    */
/* Off latches:                                                            */
/* Enable_2   Enable_4  Enable_6     Enable_8    Enable_10    Enable_12    */

void Delay(volatile long nCount) // VOLATILE is request for ATOLLIC v.3.1.0
{//75000 is about 20ms
/* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

void Segment_flip_new(int pin, int latch)
{
    int flip_delay  = 360000;
    int clock_delay = 5000;
    //needs to set bus    
    GPIOA->BSRR = pin;    /* Set PA1 for setting segment*/
    GPIOA->BRR = BSRR_VAL;
    //Enable clock
    GPIOB->BSRR = latch;    /* Clock on PB4 */
    GPIOB->BRR = BSRR_VAL;
    //wait short time
    Delay(clock_delay);       /* Wait for flip */    
    //Disable clock
    GPIOB->BSRR = BSRR_VAL;
    GPIOB->BRR = latch;     /* Clear latch*/    
    //clear bus
    GPIOA->BSRR = BSRR_VAL;  /* clear PA1*/
    GPIOA->BRR = pin;
    //wait short time
    Delay(flip_delay);     
    //Enable clock
//    GPIOB->BSRR = latch;    /* Clock on PB4 */
//    GPIOB->BRR = BSRR_VAL;
    //wait short time
//    Delay(clock_delay);     
    //disable clock
//    GPIOB->BSRR = BSRR_VAL;
//    GPIOB->BRR = latch;     /* Clear latch*/   
    //Delay(clock_delay);      
}

void Clear_latch(int latch)
{
    GPIOA->BSRR = BSRR_VAL;  /* clear PA1*/
   /* GPIOA->BRR = 2;
    GPIOA->BRR = 4;
    GPIOA->BRR = 8;
    GPIOA->BRR = 16;
    GPIOA->BRR = 32;
    GPIOA->BRR = 64;
    GPIOA->BRR = 128;*/
   // Delay(5000);
    GPIOB->BSRR = BSRR_VAL;
    GPIOB->BRR = latch;     /* Clear latch*/   
}

/*Segment_flip is the root level flip routine*/
void Segment_flip(int pin, int latch)
{
    int flip_delay  = 400000;
    int clock_delay = 3000;
    //needs to set bus    
    GPIOA->BSRR = pin;    /* Set PA1 for setting segment*/
    GPIOA->BRR = BSRR_VAL;
    //Enable clock
    GPIOB->BSRR = latch;    /* Clock on PB4 */
    GPIOB->BRR = BSRR_VAL;
    //wait short time
    Delay(clock_delay);       /* Wait for flip */    
    //Disable clock
    GPIOB->BSRR = BSRR_VAL;
    GPIOB->BRR = latch;     /* Clear latch*/    
    //clear bus
    GPIOA->BSRR = BSRR_VAL;  /* clear PA1*/
    GPIOA->BRR = pin;
    //wait short time
    Delay(flip_delay);     
    //Enable clock
    GPIOB->BSRR = latch;    /* Clock on PB4 */
    GPIOB->BRR = BSRR_VAL;
    //wait short time
    Delay(clock_delay);     
    //disable clock
    GPIOB->BSRR = BSRR_VAL;
    GPIOB->BRR = latch;     /* Clear latch*/   
    //Delay(clock_delay);      
}

/* Calling this function sets all digits to Zero*/
void reset() 
{
    int latch = 16;
    for(int lpos = 0;lpos <6;lpos++)
    {
        set_zero(latch);
        latch *= 4;
        time[lpos] = 0;
    }
    counter = 0;
}

void count_up() //Tested correctly, with cheat
{
    if (time[5] < 9)
    {
       time[5]++;
       update[5] = 1;
    }
    else
    {
      time[5] = 0;
      update[5] = 1;
      if(time[4] < 5)
      {
        time[4]++;
        update[4] = 1;
      }
      else
      {
        time[4] = 0;
        update[4] = 1;
        if(time[3]<9)
        {
          time[3]++;
          update[3] = 1;
        }
        else
        {
          time[3] = 0;
          update[3] = 1;
          if(time[2]<5)
          {
            time[2]++;
            update[2] = 1;
          }
          else
          {
            time[2] = 0;
            update[2] = 1;
            if((time[1] < 9) && (time[0] < 1))
            {
              time[1]++;
              update[1] = 1;
            }
            else if(time[0] < 1)
            {
              time[1] = 0;
              update[1] = 1;
              time[0] = 1;
              update[0] = 1;
            }
            else if((time[1] <2) && (time[0] == 1))
            {
              time[1]++;
              update[1] = 1;
            }
            else
            {
              time[1] = 0;
              update[1] = 1;
              time[0] = 0;
              update[0] = 1;
            }
          }
        }
      }
    }
    push_update(0);
}

void count_down() //Seems to be working properly
{
    if (time[5] > 0)
    {
       time[5]--;
       update[5] = 1;
    }
    else
    {
      if(time[4] > 0)
      {
        time[4]--;
        update[5] = 1;
        time[5] = 9;
        update[4] = 1;
      }
      else
      {
        if(time[3] > 0)
        {
          time[3]--;
          update[3] = 1;
          time[4] = 5;
          update[4] = 1;
          time[5] = 9;
          update[5] = 1;
        }
        else
        {
          
          if(time[2] > 0)
          {
            time[2]--;
            update[2] = 1;
            time[3] = 9;
            update[3] = 1;
            time[4] = 5;
            update[4] = 1;
            time[5] = 9;
            update[5] = 1;
          }
          else
          {
            
            if(time[1] > 0)
            {
              time[1]--;
              update[1] = 1;
              time[2] = 5;
              update[2] = 1;
              time[3] = 9;
              update[3] = 1;
              time[4] = 5;
              update[4] = 1;
              time[5] = 9;
              update[5] = 1;
            }
            else if(time[0] > 0)
            {
              time[0]--;
              update[0] = 1;
              time[1] = 9;
              update[1] = 1;
              time[2] = 5;
              update[2] = 1;
              time[3] = 9;
              update[3] = 1;
              time[4] = 5;
              update[4] = 1;
              time[5] = 9;
              update[5] = 1;
            }
            else
            {
              //buzzer();
            }
          }
        }
      }
    }
    push_update(1);
}

void pause()
{
  if(paused == 0)
  {
    stored_key = backup_key;
    cont = 0;
    paused = 1;
  }
  else
  {
    key = stored_key;
    cont = 1;
    paused = 0;
  }
}
void blank()
{
   clear_digit(16);
   clear_digit(64);
   clear_digit(256);
   clear_digit(1024);
   clear_digit(4096);
   clear_digit(16384);
}
void enter()
{
  int num = 0;
  int next_num = 0;
  int new_num = 0;
  while(num != 6)
  {
    GPIOA->BSRR = GPIO_Pin_9;//set bit as high
    GPIOA->BRR = GPIO_Pin_10;//set bit as low
    GPIOA->BRR = GPIO_Pin_11;//set bit as low
    GPIOA->BRR = GPIO_Pin_12;//set bit as low
    {
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) //Clear Entry
      {
        next_num = 11;
        new_num = 1;
      }
    }
    GPIOA->BRR = GPIO_Pin_9;//set bit as high
    GPIOA->BSRR = GPIO_Pin_10;//set bit as low
    GPIOA->BRR = GPIO_Pin_11;//set bit as low
    GPIOA->BRR = GPIO_Pin_12;//set bit as low
    {
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)) //7
      {
        next_num = 7;
        new_num = 1;
      }
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)) //4
      {
        next_num = 4;
        new_num = 1;
       
      }
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) //1
      {
        next_num = 1;
        new_num = 1;
      }
    }
    GPIOA->BRR = GPIO_Pin_9;//set bit as high
    GPIOA->BRR = GPIO_Pin_10;//set bit as low
    GPIOA->BSRR = GPIO_Pin_11;//set bit as low
    GPIOA->BRR = GPIO_Pin_12;//set bit as low
    {
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)) //8
      {
        next_num = 8;
        new_num = 1;
      }
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)) //5
      {
        next_num = 5;
        new_num = 1;
      }
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) //2
      {
        next_num = 2;
        new_num = 1;
      }
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)) //0
      {
        next_num = 0;
        new_num = 1;
      }
    }
    GPIOA->BRR = GPIO_Pin_9;//set bit as high
    GPIOA->BRR = GPIO_Pin_10;//set bit as low
    GPIOA->BRR = GPIO_Pin_11;//set bit as low
    GPIOA->BSRR = GPIO_Pin_12;//set bit as low
    {
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)) //9
      {
        next_num = 9;
        new_num = 1;
      }
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)) //6
      {
        next_num = 6;
        new_num = 1;
      }
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) //3
      {
        next_num = 3;
        new_num = 1;
      }
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)) //Enter
      {
        next_num = 12;
        new_num = 1;
      }
      if(new_num == 1)
      {
        switch(next_num)
        {
          case 11:  break; //Clear routine
          case 12:  break; //Enter routine
          default: push_new(next_num); num++; break;
        }
      }
      new_num = 0;
   }
  } 
}
void push_new(int next_num)
{
        //dum = count[0];
      time[0] = time[1];
      time[1] = time[2];
      time[2] = time[3];
      time[3] = time[4];
      time[4] = time[5];
      time[5] = next_num;
      force_current();
}
void push_update(int dir)//updates clock, 0 up, 1 down, 2 force set
{
    int latch = 16;
    if (dir == 0)
    {
      for(int pos =5;pos>=0;pos--)
      {
        if(update[pos] == 1)
        {
          switch(time[pos])
          {
            case 0: up_zero(latch);  break;
            case 1: up_one(latch);   break;
            case 2: up_two(latch);   break;
            case 3: up_three(latch); break;
            case 4: up_four(latch);  break;
            case 5: up_five(latch);  break;
            case 6: up_six(latch);   break;
            case 7: up_seven(latch); break;
            case 8: up_eight(latch); break;
            case 9: up_nine(latch);  break;
            default: break;
          }
          update[pos] = 0;
        }
        latch *= 4;
      }
    }
    else if (dir == 1)
    {
      for(int pos =5;pos>=0;pos--)
      {
        if(update[pos] == 1)
        {
          switch(time[pos])
          {
            case 0: down_zero(latch);  break;
            case 1: down_one(latch);   break;
            case 2: down_two(latch);   break;
            case 3: down_three(latch); break;
            case 4: down_four(latch);  break;
            case 5: down_five(latch);  break;
            case 6: down_six(latch);   break;
            case 7: down_seven(latch); break;
            case 8: down_eight(latch); break;
            case 9: down_nine(latch);  break;
            default: break;
          }
          update[pos] = 0;
        }
        latch *= 4;
      }
    }
    else if (dir == 2)
    {
      for(int pos =5;pos>=0;pos--)
      {
        if(update[pos] == 1)
        {
          switch(time[pos])
          {
            case 0: set_zero(latch);  break;
            case 1: set_one(latch);   break;
            case 2: set_two(latch);   break;
            case 3: set_three(latch); break;
            case 4: set_four(latch);  break;
            case 5: set_five(latch);  break;
            case 6: set_six(latch);   break;
            case 7: set_seven(latch); break;
            case 8: set_eight(latch); break;
            case 9: set_nine(latch);  break;
            default: break;
          }
          update[pos] = 0;
        }
        latch *= 4;
      }
    }
    
    
}
void update_all()
{
    update[0] = 1;
    update[1] = 1;
    update[2] = 1;
    update[3] = 1;
    update[4] = 1;
    update[5] = 1;
}

void force_current()
{   
   update_all();
   push_update(2);
}

void preset(int hh, int hl, int mh, int ml, int sh, int sl)
{
    time[0] = hh;
    time[1] = hl;
    time[2] = mh;
    time[3] = ml;
    time[4] = sh;
    time[5] = sl;
}
void keypad() /*Handles the keypad scan function and calls the appropiate function*/
{
  /*Keypad is set up in a row column grid pinout.*/
  /*This code is designed for the chronomix pro-control 234 keypad but */
  /*is easily adaptable to any common row column keypad                */
  /*         Column 0       Column 1      Column 2        Column 3     */
  /*Row 0|   Cycle A     |      [     |       ]       | clear Memory  |*/
  /*Row 1|   Cycle B     |      7     |       8       |      9        |*/
  /*Row 2| Review Memory |      4     |       5       |      6        |*/
  /*Row 3|  Clear Entry  |      1     |       2       |      3        |*/
  /*Row 4|      Up       |    Split   |       0       |    Enter      |*/
  /*Row 5|     Down      |    Blank   | Manual Signal | Manual Signal |*/
  /*Row 6|   Reset Alt   | Reset Prim |               |  Start/Stop   |*/
  
  /*Description of functions*/
  /*From start options are Reset Prim   --> Resets clock to 00:00.00*/
  /*                       Up           --> Puts clock into count up mode from current value*/
  /*                       Down         --> Puts clock into count down mode from current value*/
  /*                       # key, enter --> Sets value on LSD and shifts values up */
  /*                       Start/Stop   --> If nothing running, starts current mode (default up),
                                            otherwise stops current function with current values*/
  /*                       Blank        --> Clears clock face of any segments */
  
  
  GPIOA->BSRR = GPIO_Pin_9;//set bit as high
  GPIOA->BRR = GPIO_Pin_10;//set bit as low
  GPIOA->BRR = GPIO_Pin_11;//set bit as low
  GPIOA->BRR = GPIO_Pin_12;//set bit as low
  {
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))//Cycle A
    {
      key = 0;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)) //Cycle B
    {
      key = 1;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)) //Review Memory
    {
      key = 2;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) //Clear Entry
    {
      key = 3;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)) //Up
    {
      key = 4;
      key_changed = 1;
      cont = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)) //Down
    {
      key = 5;
      key_changed = 1;
      cont = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)) //Reset Alt
    {
      key = 6;
      key_changed = 1;
      cont = 1;
    }
  }
  GPIOA->BRR = GPIO_Pin_9;//set bit as high
  GPIOA->BSRR = GPIO_Pin_10;//set bit as low
  GPIOA->BRR = GPIO_Pin_11;//set bit as low
  GPIOA->BRR = GPIO_Pin_12;//set bit as low
  {
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))//[
    {
      key = 7;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)) //7
    {
      key = 8;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)) //4
    {
      key = 9;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) //1
    {
      key = 10;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)) //Split/Freeze
    {
      key = 11;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)) //Blank
    {
      key = 12;
      key_changed = 1;
      cont = 0;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)) //Reset Prim
    {
      key = 13;
      cont = 0;
      key_changed = 1;
    }
  }
  GPIOA->BRR = GPIO_Pin_9;//set bit as high
  GPIOA->BRR = GPIO_Pin_10;//set bit as low
  GPIOA->BSRR = GPIO_Pin_11;//set bit as low
  GPIOA->BRR = GPIO_Pin_12;//set bit as low
  {
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))//]
    {
      key = 14;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)) //8
    {
      key = 15;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)) //5
    {
      key = 16;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) //2
    {
      key = 17;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)) //0
    {
      key = 18;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)) //Manual Signal (left)
    {
      key = 19;
      key_changed = 1;
    }
  }
  GPIOA->BRR = GPIO_Pin_9;//set bit as high
  GPIOA->BRR = GPIO_Pin_10;//set bit as low
  GPIOA->BRR = GPIO_Pin_11;//set bit as low
  GPIOA->BSRR = GPIO_Pin_12;//set bit as low
  {
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))//Clear Memory
    {
      key = 21;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)) //9
    {
      key = 22;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)) //6
    {
      key = 23;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) //3
    {
      key = 24;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)) //Enter
    {
      key = 25;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)) //Manual Signal (right)
    {
      key = 26;
      key_changed = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)) //Start/Stop
    {
      key = 27;
      key_changed = 1;
    }
  }
  if(((counter >= 60000)&&(cont == 1))||((key_changed == 1)&&(counter >= 40000)))
  {
    switch(key)
    {
      case 0:  break;
      case 1:  break;
      case 2:  break;
      case 3:  break;
      case 4: count_up(); break; //Count Up Routine
      case 5: count_down(); break; //Count Down Routine
      case 6: force_current(); key = backup_key; break; //Reset to current
      case 7:  break;
      case 8:  break;
      case 9:  break;
      case 10:  break;
      case 11:  break;
      case 12: blank(); break; //Blank display
      case 13: reset(); break; //Reset to 00:00.00 state
      case 14:  break;
      case 15:  break;
      case 16:  break;
      case 17:  break;
      case 18:  break;
      case 19:  break;
      /*case 20:  break; Button 20 does not exist*/
      case 21:  break;
      case 22:  break;
      case 23:  break;
      case 24:  break;
      case 25: enter(); break; //Enter routine
      case 26:  break;
      case 27: pause(); break; //Starts/Stops current function
      default: break;
    }
    backup_key = key;
    key_changed = 0;
    counter = 0;
  }
  counter++;
}
void test_digit(int on_latch) //turns digit on and off
{
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch);
    
    Segment_flip(2,off_latch);
    Segment_flip(4,off_latch);
    Segment_flip(8,off_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch);  
}

void clear_digit(int on_latch) //clears digit
{
    if(on_latch == 256)
    {
     on_latch = 1;
    }
    int off_latch = on_latch *2;
    Segment_flip(2,off_latch);
    Segment_flip(4,off_latch);
    Segment_flip(8,off_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch);
    Clear_latch(off_latch);
    
}

void set_digit(int on_latch) //sets digit
{
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch);  
}

/* NOTE: the following function set_# set that number onto the digit          */
/*       This is number is set regardless of the previous value on the digit  */
/*       on_latch is the on_latch number corresponding to the desired digit   */
void set_zero(int on_latch)
{
     if(on_latch == 256) //changed from PB8 and PB9 due to issues
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,off_latch); 
}

void set_one(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,off_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch);  
}

void set_two(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,off_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,on_latch); 
}

void set_three(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,on_latch); 
}

void set_four(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,off_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch); 
}

void set_five(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,off_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch); 
}

void set_six(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,off_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch); 
}

void set_seven(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch); 
}

void set_eight(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
   // int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch); 
}

void set_nine(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch); 
}
/* NOTE: end of set_# functions                                               */

/* WARNING!:                                                                  */
/* the following functions labelled up_# count from the previous function     */
/* they assume that the previous function number is on a given digit          */
/* if the previous function number is not on the digit the display will       */
/* be off and unexpected characters will result                               */
/*       on_latch is the on_latch number corresponding to the desired digit   */
void up_one(int on_latch)
{
   if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,  off_latch);
    Segment_flip(16, off_latch);
    Segment_flip(32, off_latch);
    Segment_flip(64, off_latch);
    Segment_flip(128,off_latch);
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void up_two(int on_latch)
{
   if(on_latch == 256)
   {
     on_latch = 1;
   }
     
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(8,off_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(128,on_latch);  
   // Clear_latch(on_latch);
   // Clear_latch(off_latch);
}

void up_three(int on_latch)
{
     if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(8,on_latch);
    Segment_flip(32,off_latch);  
   // Clear_latch(on_latch);
   // Clear_latch(off_latch);
}


void up_four(int on_latch)
{
     if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,off_latch);
    Segment_flip(16,off_latch);
    Segment_flip(64,on_latch);  
   // Clear_latch(on_latch);
   // Clear_latch(off_latch);
}

void up_five(int on_latch)
{
     if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,off_latch);
    Segment_flip(16,on_latch);
    //Clear_latch(on_latch);
    //Clear_latch(off_latch);
}

void up_six(int on_latch)
{
     if(on_latch == 256)
   {
     on_latch = 1;
   }
    //int off_latch = on_latch * 2;
    Segment_flip(32,on_latch);
  //  Clear_latch(on_latch);
 //   Clear_latch(off_latch);
}

void up_seven(int on_latch)
{
     if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(4,on_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch);  
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void up_eight(int on_latch)
{
     if(on_latch == 256)
   {
     on_latch = 1;
   }
    //int off_latch = on_latch * 2;
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch);  
  //  Clear_latch(on_latch);
 //   Clear_latch(off_latch);
}

void up_nine(int on_latch)
{
     if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void up_zero(int on_latch)
{
     if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(4,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(128,off_latch);  
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}
/* NOTE: end of up only functions */

/* WARNING!:                                                                  */
/* the following functions labelled down_# count from the previous function   */
/* they assume that the next function number is on a given digit              */
/* if the next function number is not on the digit the display will           */
/* be off and unexpected characters will result                               */
/*       on_latch is the on_latch number corresponding to the desired digit   */
void down_one(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,  off_latch);
    Segment_flip(8,  on_latch);
    Segment_flip(16, off_latch);
    Segment_flip(32, off_latch);
    Segment_flip(128,off_latch);  
    Clear_latch(on_latch);
    Clear_latch(off_latch);
}

void down_two(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(8,off_latch);
    Segment_flip(32,on_latch);
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void down_three(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(64,off_latch);  
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void down_four(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,off_latch);
    Segment_flip(4,on_latch);  
    Segment_flip(16,off_latch);
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void down_five(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(128,on_latch);
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void down_six(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(4,off_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch);  
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void down_seven(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch);  
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void down_eight(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    //int off_latch = on_latch * 2;
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
  //  Clear_latch(on_latch);
 //   Clear_latch(off_latch);
}

void down_nine(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    int off_latch = on_latch * 2;
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(128,on_latch);
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void down_zero(int on_latch)
{
       if(on_latch == 256)
   {
     on_latch = 1;
   }
    //int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);  
    Segment_flip(64,on_latch);
   // Clear_latch(on_latch);
   // Clear_latch(off_latch);
}
/* NOTE: end of down only functions */

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
  /* GPIOA Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  /* GPIOB Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); //Set A and B to outputs, with no pullup
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOC, &GPIO_InitStructure); //Set C to input, with pulldowns

  reset();
  reset();
 // preset(0,9,5,9,5,9);
 // force_current();
  while (1)
  {
    /*0x1 is PC0, 0x2 is PC1, 0x4 is PC2, x8 pc3, x10 pc4 good, etc. */
    //0 is 1,1 is 2, 2 is 4, 3 is 8, 4 is 16, 5 is 32, 6 is 64, 7 is 128,
    //8 is , 9 is, 10 is, 11 is, 12 is
    //Segment_on(pin #, latch #)
//    set_digit();
//    reset();
//    clear_digit();
//    reset();
//    clear_digit(32);
  //  count_up();
    //count_down();
    keypad();
    //Delay(6000000);
  /*  up_one(16);
    Delay(6000000);
    up_two(16);
    Delay(6000000);
    up_three(16);
    Delay(6000000);
    up_four(16);
    Delay(6000000);
    up_five(16);
    Delay(6000000);
    up_six(16);
    Delay(6000000);
    up_seven(16);
    Delay(6000000);
    up_eight(16);
    Delay(6000000);
    up_nine(16);
    Delay(6000000);
    up_zero(16);
    
    up_one(64);
    Delay(6000000);
    up_two(64);
    Delay(6000000);
    up_three(64);
    Delay(6000000);
    up_four(64);
    Delay(6000000);
    up_five(64);
    Delay(6000000);
    up_six(64);
    Delay(6000000);
    up_seven(64);
    Delay(6000000);
    up_eight(64);
    Delay(6000000);
    up_nine(64);
    Delay(6000000);
    up_zero(64);
    
    up_one(256);
    Delay(6000000);
    up_two(256);
    Delay(6000000);
    up_three(256);
    Delay(6000000);
    up_four(256);
    Delay(6000000);
    up_five(256);
    Delay(6000000);
    up_six(256);
    Delay(6000000);
    up_seven(256);
    Delay(6000000);
    up_eight(256);
    Delay(6000000);
    up_nine(256);
    Delay(6000000);
    up_zero(256);
    
    up_one(1024);
    Delay(6000000);
    up_two(1024);
    Delay(6000000);
    up_three(1024);
    Delay(6000000);
    up_four(1024);
    Delay(6000000);
    up_five(1024);
    Delay(6000000);
    up_six(1024);
    Delay(6000000);
    up_seven(1024);
    Delay(6000000);
    up_eight(1024);
    Delay(6000000);
    up_nine(1024);
    Delay(6000000);
    up_zero(1024);
    
        up_one(4096);
    Delay(6000000);
    up_two(4096);
    Delay(6000000);
    up_three(4096);
    Delay(6000000);
    up_four(4096);
    Delay(6000000);
    up_five(4096);
    Delay(6000000);
    up_six(4096);
    Delay(6000000);
    up_seven(4096);
    Delay(6000000);
    up_eight(4096);
    Delay(6000000);
    up_nine(4096);
    Delay(6000000);
    up_zero(4096);
    
    up_one(16384);
    Delay(6000000);
    up_two(16384);
    Delay(6000000);
    up_three(16384);
    Delay(6000000);
    up_four(16384);
    Delay(6000000);
    up_five(16384);
    Delay(6000000);
    up_six(16384);
    Delay(6000000);
    up_seven(16384);
    Delay(6000000);
    up_eight(16384);
    Delay(6000000);
    up_nine(16384);
    Delay(6000000);
    up_zero(16384);
    
    Delay(6000000);    
    down_nine(16);
    Delay(6000000);
    down_eight(16);
    Delay(6000000);
    down_seven(16);
    Delay(6000000);
    down_six(16);
    Delay(6000000);
    down_five(16);
    Delay(6000000);
    down_four(16);
    Delay(6000000);
    down_three(16);
    Delay(6000000);
    down_two(16);
    Delay(6000000);
    down_one(16);
    Delay(6000000);
    down_zero(16);
    Delay(6000000);

    down_nine(64);
    Delay(6000000);
    down_eight(64);
    Delay(6000000);
    down_seven(64);
    Delay(6000000);
    down_six(64);
    Delay(6000000);
    down_five(64);
    Delay(6000000);
    down_four(64);
    Delay(6000000);
    down_three(64);
    Delay(6000000);
    down_two(64);
    Delay(6000000);
    down_one(64);
    Delay(6000000);
    down_zero(64);
    Delay(6000000);*/
/*    Delay(600000);
    set_one(16);
    Delay(600000);
    set_two(16);
    Delay(600000);
    set_three(16);
    Delay(600000);
    set_four(16);
    Delay(600000);
    set_five(16);
    Delay(600000);
    set_six(16);
    Delay(600000);
    set_seven(16);
    Delay(600000);
    set_eight(16);
    Delay(600000);
    set_nine(16);
    Delay(600000);
    set_zero(16);
    Delay(600000);*/


  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
