#include "my_string.h"
#include <string.h>

size_t my_strlen(const char *str) {
	long count = 0;
	while (*str++) {
		count += 1;
	}
	return count;
}

int main ()
{
  char szInput[256];
  printf ("Enter a sentence: ");
  fgets (szInput, 256, stdin);
  printf ("The sentence entered is %ld characters long.\n", my_strlen(szInput));
  return 0;
}
