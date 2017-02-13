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