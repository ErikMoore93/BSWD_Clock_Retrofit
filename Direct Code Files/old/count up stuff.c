/**
  ******************************************************************************
  * @file    IO_Toggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/** @addtogroup STM32F0_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BSRR_VAL        0x0300

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef        GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


void Delay(volatile long nCount) // VOLATILE is request for ATOLLIC v.3.1.0
{//75000 is about 20ms
/* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

/*Turn on/off a specific pin*/
/*Takes the pin, and puts it on the specified latch*/
/* Seconds_low   on enable 1  (16),    off enable 2  (32)   */
/* Seconds_high  on enable 3  (64),    off enable 4  (128)  */
/* Minutes_low   on enable 5  (256),   off enable 6  (512)  */
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
void Segment_flip(int pin, int latch)
{
    int time_delay = 170000;
    //needs to set bus    
    GPIOA->BSRR = pin;    /* Set PA1 for setting segment*/
    GPIOA->BRR = BSRR_VAL;
    //Enable clock
    GPIOB->BSRR = latch;    /* Clock on PB4 */
    GPIOB->BRR = BSRR_VAL;
    //wait short time
    Delay(time_delay);       /* Wait for flip */    
    //Disable clock
    GPIOB->BSRR = BSRR_VAL;
    GPIOB->BRR = latch;     /* Clear latch*/    
    //clear bus
    GPIOA->BSRR = BSRR_VAL;  /* clear PA1*/
    GPIOA->BRR = pin;
    //wait short time
    Delay(time_delay);     
    //Enable clock
    GPIOB->BSRR = latch;    /* Clock on PB4 */
    GPIOB->BRR = BSRR_VAL;
    //wait short time
    Delay(time_delay);     
    //disable clock
    GPIOB->BSRR = BSRR_VAL;
    GPIOB->BRR = latch;     /* Clear latch*/   
    Delay(time_delay);    
}

/* Calling this function sets all digits to Zero*/
void reset() 
{
    int pin = 2;
    int latch = 16;
    
    for(int lpos = 0; lpos <6;lpos++) /* Walks through on latches*/
    {
        for(int ppos = 0; ppos <6;ppos++) /* Walks through pins */
        {
           Segment_flip(pin, latch);
           pin *= 2;   /* moves to the next pin posisiton*/
        }
        latch *= 4;   /* moves to the next on latch */
        pin = 2;
    }
    
    pin = 128;
    latch = 32;
    for (int lpos =0; lpos <6; lpos++) /*Walks through off latches */
    {
        Segment_flip(pin,latch); /* turns segment 7 off on all digits */
        latch *= 4;
    }

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

void clear_digit(int off_latch) //clears digit
{
    Segment_flip(2,off_latch);
    Segment_flip(4,off_latch);
    Segment_flip(8,off_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch);  
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

void set_zero(int on_latch)
{
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
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,on_latch);
    Segment_flip(8,on_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch); 
}

void up_one(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(2,  off_latch);
    Segment_flip(16, off_latch);
    Segment_flip(32, off_latch);
    Segment_flip(64, off_latch);
    Segment_flip(128,off_latch);  
}

void up_two(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(8,off_latch);
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(128,on_latch);  
}

void up_three(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(8,on_latch);
    Segment_flip(32,off_latch);  
}

void up_four(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(2,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,on_latch);  
}

void up_five(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,off_latch);
    Segment_flip(16,on_latch);
}

void up_six(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(32,on_latch);
}

void up_seven(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch);  
}

void up_eight(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(64,on_latch);
    Segment_flip(128,on_latch);  
}

void up_nine(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
}

void up_zero(int on_latch);
{
    int off_latch = on_latch * 2;
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(128,off_latch);  
}



/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
 // int time_delay = 6000000;
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
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOA, &GPIO_InitStructure);


     /*This code needs to be compiled with high speed optimization option.  */
  reset();
  while (1)
  {
    /*0x1 is PC0, 0x2 is PC1, 0x4 is PC2, x8 pc3, x10 pc4 good, etc. */
    //needs to set bus
    //Enable clock
    //wait short time
    //Disable clock
    //clear bus
    //wait short time
    //Enable clock
    //wait short time
    //disable clock
    //0 is 1,1 is 2, 2 is 4, 3 is 8, 4 is 16, 5 is 32, 6 is 64, 7 is 128,
    //8 is , 9 is, 10 is, 11 is, 12 is
    //Segment_on(pin #, latch #)
//    set_digit();
//    reset();
//    clear_digit();
//    reset();
//    clear_digit(32);
    Delay(8000000);
    up_zero(16);
    Delay(8000000);
    up_one(16);
    Delay(8000000);
    up_two(16);
    Delay(8000000);
    up_three(16);
    Delay(8000000);
    up_four(16);
    Delay(8000000);
    up_five(16);
    Delay(8000000);
    up_six(16);
    Delay(8000000);
    up_seven(16);
    Delay(8000000);
    up_eight(16);
    Delay(8000000);
    up_nine(16);
    Delay(8000000);

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

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
