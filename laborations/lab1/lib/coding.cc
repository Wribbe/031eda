#include "coding.h"

unsigned char Coding::encode(unsigned char c)
  /* Encode a character and return its encoded form. */
{
  return c+1;
}

unsigned char Coding::decode(unsigned char c)
  /* Take a encoded character and return its decoded form. */
{
  return c-1;
}
