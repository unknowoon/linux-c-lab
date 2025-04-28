#include "my_string.h"
#include <string.h>

char *my_strstr(char  *str1, const char *str2) {
	while (*str1) {
		char *pos = str1;
		char *ret = pos;
		char *buf = str2;
		long lenth = (long) strlen(str2);

		while (*buf) {
			if (*pos++ != *buf++) {
				ret = NULL;
				break;
			}
		}
		if (*buf == '\0') {
			return ret; 
		}
		*str1++;
	}

	return NULL;
}

int main ()
{
  char str[] ="This is a simple string";
  char * pch;
  pch = my_strstr (str,"simple");
  if (pch != NULL)
    strncpy (pch,"sample",6);
  puts (str);
  return 0;
}
