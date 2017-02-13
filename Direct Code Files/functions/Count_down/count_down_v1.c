void count_down()
{
    if (time[5] > 0)
    {
       time[5]--;
    }
    else
    {
      time[5] = 9;
      if(time[4] > 0)
      {
        time[4]--;
      }
      else
      {
        time[4] = 5;
        if(time[3] > 0)
        {
          time[3]--;
        }
        else
        {
          time[3] = 9;
          if(time[2] > 0)
          {
            time[2]--;
          }
          else
          {
            time[2] = 5;
            if((time[1] > 0) && (time[0] > 0))
            {
              time[1]--;
            }
            else if(time[0] < 1)
            {
              time[1] = 0;
              time[0] = 1;
            }
            else if((time[1] <2) && (time[0] == 1))
            {
              time[1]++;
            }
            else
            {
              time[1] = 0;
              time[0] = 0;
            }
          }
        }
      }
    }
    update(1);
//    printf("%i%i:%i%i:%i%i",hour_high,hour_low,min_high,min_low,sec_high,sec_low);
}