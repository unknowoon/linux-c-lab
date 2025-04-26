#include "my_string.h"
#include <string.h>

void *my_memmove(void *s, const void *ct, size_t n) {

    long size = (long) n;
    char buf[size+1];

    char *cs = (char *) s;
    char *cct = (char *) ct;

    for (int i = 0; i < size; i++) {
      buf[i] = cct[i];
    }
    buf[size] = 0;

    for (int i = 0 ; i < size; i++) {
      cs[i] = buf[i] ;
    }

    return s;
}


int main ()
{
  char str[] = "memmove can be very useful......";
  my_memmove (str+20,str+15,11);
  puts (str);
  return 0;
}