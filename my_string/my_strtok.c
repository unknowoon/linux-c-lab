#include "my_string.h"
#include <string.h>

char *gp = NULL;

char * my_strtok ( char * str, const char * d ) {

	int count = 1;
	char ret[count] = '\0';

	//char *pos = str;
	while (*str) {
		//if (strrchr(d, (int) *pos)) {
		if (strrchr(d, (int) *str)) {
			if (count > 1) {
				gp = str;
				return &ret;
				}
			//pos = *str++;
			*str++;
			continue;
		} else {
			count++;
			ret[count-1] = *pos++;
		}
		*str++;
	}
	return NULL;
	
}

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;
}
