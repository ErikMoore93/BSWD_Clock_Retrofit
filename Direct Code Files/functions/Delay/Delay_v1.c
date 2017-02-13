void Delay(volatile long nCount) // VOLATILE is request for ATOLLIC v.3.1.0
{//75000 is about 20ms
/* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}