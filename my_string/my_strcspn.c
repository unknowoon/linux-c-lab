#include "my_string.h"
#include <string.h>

size_t my_strcspn (const char *str1, const char *str2) {

	long ret = sizeof(str1);
	int count = 0;
	while (*str1) {
		char *b1 = &*str1++;
		char *b2 = str2;
		while (*b2) {
			if (*b1 == *b2++) {
				return (size_t) count;
			}
		}
		count += 1;
	}

	return ret;
}

int main ()
{
  char str[] = "fcba73";
  char keys[] = "1234567890";
  int i;
  i = my_strcspn (str,keys);
  printf ("The first number in str is at position %d.\n",i+1);
  return 0;
}
