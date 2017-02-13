/* WARNING!:                                                                  */
/* the following functions labelled up_# count from the previous function     */
/* they assume that the previous function number is on a given digit          */
/* if the previous function number is not on the digit the display will       */
/* be off and unexpected characters will result                               */
/*       on_latch is the on_latch number corresponding to the desired digit   */
void up_one(int on_latch)
{
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
    int off_latch = on_latch * 2;
    Segment_flip(8,on_latch);
    Segment_flip(32,off_latch);  
   // Clear_latch(on_latch);
   // Clear_latch(off_latch);
}


void up_four(int on_latch)
{
    int off_latch = on_latch * 2;
    Segment_flip(2,off_latch);
    Segment_flip(16,off_latch);
    Segment_flip(64,on_latch);  
   // Clear_latch(on_latch);
   // Clear_latch(off_latch);
}

void up_five(int on_latch)
{
    int off_latch = on_latch * 2;
    Segment_flip(2,on_latch);
    Segment_flip(4,off_latch);
    Segment_flip(16,on_latch);
    //Clear_latch(on_latch);
    //Clear_latch(off_latch);
}

void up_six(int on_latch)
{
    //int off_latch = on_latch * 2;
    Segment_flip(32,on_latch);
  //  Clear_latch(on_latch);
 //   Clear_latch(off_latch);
}

void up_seven(int on_latch)
{
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
    int off_latch = on_latch * 2;
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}

void up_zero(int on_latch)
{
    int off_latch = on_latch * 2;
    Segment_flip(16,on_latch);
    Segment_flip(32,on_latch);
    Segment_flip(128,off_latch);  
  //  Clear_latch(on_latch);
  //  Clear_latch(off_latch);
}
/* NOTE: end of up only functions */