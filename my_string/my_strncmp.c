#include "my_string.h"
#include <string.h>

int my_strncmp ( const char * str1, const char * str2, size_t num ) {
	while ((long) num--) {
		int b1 = (int) *str1++;
		int b2 = (int) *str2++;

		if (b1 < b2) {
			return -1;
		} else if (b1 > b2) {
			return 1;
		}
	}

	return 0;
}

int main ()
{
  char str[][5] = { "R2D2" , "C3PO" , "R2A6" };
  int n;
  puts ("Looking for R2 astromech droids...");
  for (n=0 ; n<3 ; n++)
    if (my_strncmp (str[n],"R2xx",2) == 0)
    {
      printf ("found %s\n",str[n]);
    }
  return 0;
}
