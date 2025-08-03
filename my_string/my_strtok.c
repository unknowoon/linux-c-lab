#include "my_string.h"
#include <string.h>

char *gp = NULL;

char * my_strtok ( char * str, const char * d ) {

	//printf("=== start ===\n");
	//printf("=== str: %s\n", str);
	//printf("=== gp: %s\n", gp);

	size_t count = 0;
	char *ret = malloc(count); 
	if (!ret) {
		return NULL;
	}

	//ret[0] = '\0';
	//printf("=== count: %d\n", count);
	//printf("=== ret: %s\n", ret);

	if (str == NULL && gp == NULL) {
		return NULL;
	}

	char *pos;
	if (str == NULL) {
		pos = gp;

	} else {
		pos = str;
	}
	//printf("=== pos: %s\n", pos);

	while (*pos) {
		//printf("=== strchr: %s\n", strchr(d, (int) *pos));
		//printf("=== count: %d\n", count);
		//printf("=== ret: %s\n", ret);
		if (strchr(d, (int) *pos)) {
			if (count > 0) {
				gp = pos;
				//printf("=== count if\n");
				//printf("=== ret: %s\n", ret);
				return ret;
			}
			*pos++;
			continue;
		} else {
			//printf("=== count else\n");
			count++;
			ret = realloc(ret, count);
			strncat(ret, pos, 1);
			//printf("=== pos: %c\n", pos);
			//printf("=== ret: %s\n", ret);
		}
		*pos++;
	}
	return NULL;
	
}

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = my_strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = my_strtok (NULL, " ,.-");
  }
  return 0;
}
