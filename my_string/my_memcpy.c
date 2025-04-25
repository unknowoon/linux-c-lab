#include "my_string.h"
#include <string.h>

/*
 * copy n characters from ct to s, and return s.
 */
void *my_memcpy(void *s, const void *ct, size_t n) {
	void *ret = s;
	long size = (long) n;

	while(size--) {
		*(char *)s++ = *(char*)ct++ ;
	}

	return ret;
}

struct {
  char name[40];
  int age;
} person, person_copy;

int main ()
{
  char myname[] = "Pierre de Fermat";

  /* using memcpy to copy string: */
  my_memcpy ( person.name, myname, strlen(myname)+1 );
  person.age = 46;

  /* using memcpy to copy structure: */
  my_memcpy ( &person_copy, &person, sizeof(person) );

  printf ("person_copy: %s, %d \n", person_copy.name, person_copy.age );

  return 0;
}
