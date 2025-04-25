#include "my_string.h"
#include <string.h>

/*
 * Descreption of K&R: copy at most n characters of string ct to s; return s. 
 * Pad with '\0'`s if ct has fewer than n characters. 
 */
char *my_strncpy(char *s, const char *t, size_t n) {

	char *ret = s;
	long size = (long) n;
	long count = 0;

	while (size) {
		if ((*s++ = *t++) == '\0') {
			break;
		}

	}
    return ret;
}

int main ()
{
  char str1[]= "To be or not to be";
  char str2[40];
  char str3[40];

  /* copy to sized buffer (overflow safe): */
  my_strncpy ( str2, str1, sizeof(str2) );

  /* partial copy (only 5 chars): */
  my_strncpy ( str3, str2, 5 );
  str3[5] = '\0';   /* null character manually added */

  puts (str1);
  puts (str2);
  puts (str3);

  return 0;
}
