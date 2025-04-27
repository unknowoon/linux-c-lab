#include "my_string.h"
#include <string.h>

char *my_strcat(char *s, const char *ct) {
    char *ret = s;

    char *pc = s;
    while (*s++ != '\0') {
        pc = s;
    }
    while ((*pc++ = *ct++) != '\0') {}
    pc = NULL;

    return ret;
}

int main ()
{
  char str[80];
  strcpy (str,"these ");
  my_strcat (str,"strings ");
  my_strcat (str,"are ");
  my_strcat (str,"concatenated.");
  puts (str);
  return 0;
}