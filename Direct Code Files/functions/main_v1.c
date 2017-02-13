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
//    count_up();
    Delay(6000000);
    up_one(16);
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
    Delay(6000000);
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