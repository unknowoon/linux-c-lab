#include "my_string.h"
#include <string.h>

const char *my_strpbrk(const char *str1, const char* str2) {
	char *pos1 = str1;
	while (*pos1) {
		char *pos2 = str2;
		while (*pos2) {
			if (*pos1==*pos2) {
				return pos1;
			}
			*pos2++;
		}
		*pos1++;
	}
	return NULL;
}

int main ()
{
  char str[] = "This is a sample string";
  char key[] = "aeiou";
  char * pch;
  printf ("Vowels in '%s': ",str);
  pch = strpbrk (str, key);
  while (pch != NULL)
  {
    printf ("%c " , *pch);
    pch = my_strpbrk (pch+1,key);
  }
  printf ("\n");
  return 0;
}
