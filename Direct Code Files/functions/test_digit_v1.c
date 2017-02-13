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
