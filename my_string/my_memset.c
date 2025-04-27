#include "my_string.h"
#include <string.h>

void *my_memset(void *s, int c, size_t n) {
    long count = (long) n;

    while(count --) {
        *(char *)s++ = c;
    }

    return s;
}

int main ()
{
  char str[] = "almost every programmer should know memset!";
  my_memset (str,'-',6);
  puts (str);
  return 0;
}