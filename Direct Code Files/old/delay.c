//function

void Delay(volatile long nCount) // VOLATILE is request for ATOLLIC v.3.1.0
{
/* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

//call
Delay(1000);