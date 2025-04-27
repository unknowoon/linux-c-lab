#include "my_string.h"
#include <string.h>

int strcmp ( const char * str1, const char * str2 ) {
    while (*str1) {
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
  char key[] = "apple";
  char buffer[80];
  do {
     printf ("Guess my favorite fruit? ");
     fflush (stdout);
     scanf ("%79s",buffer);
  } while (strcmp (key,buffer) != 0);
  puts ("Correct answer!");
  return 0;
}
