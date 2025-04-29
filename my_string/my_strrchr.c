#include "my_string.h"
#include <string.h>

char *my_strrchr (const char *str, int c) {
	long lenth = (long) strlen(str);
	while(lenth) {
		if (c == (int) *(str+lenth--)) {
			return (char *)str+lenth+1;
		}
	}
	return NULL;
}

int main ()
{
  char str[] = "This is a sample string";
  char * pch;
  pch=my_strrchr(str,'s');
  printf ("Last occurence of 's' found at %d \n",pch-str+1);
  return 0;
}
