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
}