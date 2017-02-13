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
