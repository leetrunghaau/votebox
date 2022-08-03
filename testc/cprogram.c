#include <stdio.h>
#include <string.h>

#include <stdlib.h>

int main()
{
   const char *hexstring = "ab";
   int number = (int)strtol(hexstring, NULL, 16);
   printf("The number(unsigned long integer) is %lu\n", number);

   return (0);
}
