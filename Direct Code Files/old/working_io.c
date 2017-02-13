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
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
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
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOA, &GPIO_InitStructure);


     /*This code needs to be compiled with high speed optimization option.  */
  while (1)
  {
    //0x1 is PC0, 0x2 is PC1, 0x4 is PC2, x8 pc3, x10 pc4 good, etc. 
    /* Set Specified bits on Port*/
 //   GPIOC->BSRR = 0x0010;
    /* Reset ALL bits on Port */
 //   GPIOC->BRR = BSRR_VAL;
      Delay(60000);
    GPIOA->BSRR = 0x0001;
    /* Reset ALL bits on Port */
    GPIOA->BRR = BSRR_VAL;
    Delay(60000);      
    GPIOA->BSRR = 0x0002;
    /* Reset ALL bits on Port */
    GPIOA->BRR = BSRR_VAL;
    Delay(60000);
    GPIOA->BSRR = 0x0004;
    /* Reset ALL bits on Port */
    GPIOA->BRR = BSRR_VAL;
    Delay(60000);
    GPIOA->BSRR = 0x0008;
    /* Reset ALL bits on Port */
    GPIOA->BRR = BSRR_VAL;
    Delay(60000);
    GPIOA->BSRR = 0x0010;
    /* Reset ALL bits on Port */
    GPIOA->BRR = BSRR_VAL;
    Delay(60000);
    GPIOA->BSRR = 0x0020;
    /* Reset ALL bits on Port */
    GPIOA->BRR = BSRR_VAL;
    Delay(60000);
    GPIOA->BSRR = 0x0040;
    /* Reset ALL bits on Port */
    GPIOA->BRR = BSRR_VAL;
    Delay(60000);
    /* Set Specified bits on Port*/
 //   GPIOC->BSRR = 0x0082;
    /* Reset ALL bits on Port */
//    GPIOC->BRR = BSRR_VAL;
      Delay(60000);
    /* Set Specified bits on Port*/
//    GPIOC->BSRR = 0x0104;
    /* Reset ALL bits on Port */
 //   GPIOC->BRR = BSRR_VAL;
      Delay(60000);
    /* Set Specified bits on Port */
//    GPIOC->BSRR = 0x0208;
    /* Reset ALL bits on Port */
//    GPIOC->BRR = BSRR_VAL;    
      Delay(60000);
//    GPIOC->BSRR = 0x0000;
    /* Reset ALL bits on Port */
//    GPIOC->BRR = BSRR_VAL;    
//      Delay(60000);
 //   /* Set PC8 and PC9 */
 //   GPIOC->BSRR = BSRR_VAL;
 //   /* Reset PC8 and PC9 */
 //   Delay(75000);
 //   GPIOC->BRR = BSRR_VAL;
 //   Delay(6000000);
        /* Set PC8 and PC9 */
 //   GPIOA->BSRR = BSRR_VAL;
    /* Reset PC8 and PC9 */
 //   GPIOA->BRR = BSRR_VAL;
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
