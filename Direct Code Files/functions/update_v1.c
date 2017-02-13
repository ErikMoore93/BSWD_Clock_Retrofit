void update(int dir)//updates clock, 0 up, 1 down, 2 force set
{
    int latch = 16;
    if (dir == 0)
    {
      for(int pos =0;pos<6;pos++)
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
        latch *= 4;
      }
    }
    else if (dir == 1)
    {
      for(int pos =0;pos<6;pos++)
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
        latch *= 4;
      }
    }
    else if (dir == 2)
    {
      for(int pos =0;pos<6;pos++)
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
        latch *= 4;
      }
    }
    
    
}