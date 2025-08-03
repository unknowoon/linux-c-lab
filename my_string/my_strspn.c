#include "my_string.h"
#include <string.h>

size_t my_strspn(const char *str1, const char *str2) {
	long count = 0;


	while (*str1) {
		int pos = (int) *str1++;
		char *buf = (char *)str2;
		while (*buf) {
			if (pos == (int) *buf++) {
				count++;
				break;
			}
		}
		if (*buf == '\0') {
			return (size_t) count;
		}
	}
	return (size_t) count;
}

int main ()
{
  int i;
  char strtext[] = "1t29th";
  char cset[] = "1234567890";

  i = my_strspn (strtext,cset);
  printf ("The initial number has %d digits.\n",i);
  return 0;
}
