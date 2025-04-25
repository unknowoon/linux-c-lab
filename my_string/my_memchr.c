#include "my_string.h"
#include <string.h>

/*
 * Description of K&R: return pointer to first occurrence of character c in cs,
 * or NULL if not present amonth the first n characters.
 */
void *my_memchr (const void *cs, int c, size_t n) {
	void *ret = NULL;
	char cc = (char) c;
	long count = (long) n;
	char *pc = (char *)cs;
	
	while (count--) {
		char *pos = &(*pc++);
		if (*pos == cc) {
			return pos;
		}
	}
	return NULL;
}

int main ()
{
  char * pch;
  char str[] = "Example string";
  pch = (char*) my_memchr (str, 'p', strlen(str));
  if (pch!=NULL)
    printf ("'p' found at position %d.\n", pch-str+1);
  else
    printf ("'p' not found.\n");
  return 0;
}
