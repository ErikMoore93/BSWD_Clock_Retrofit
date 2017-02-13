void clear_digit(int off_latch) //clears digit
{
    Segment_flip(2,off_latch);
    Segment_flip(4,off_latch);
    Segment_flip(8,off_latch);
    Segment_flip(16,off_latch);
    Segment_flip(32,off_latch);
    Segment_flip(64,off_latch);
    Segment_flip(128,off_latch);
    Clear_latch(off_latch);
    
}