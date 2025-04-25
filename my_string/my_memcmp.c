#include "my_string.h"

int my_memcmp(const void *cs, const void *ct, size_t n) {

	long length = (long) n;
	char *pcs = (char *)cs;
	char *pct = (char *)ct;

	while(length--) {
		int b1 = (int) * pcs++;
		int b2 = (int) * pct++;

		if (b1 < b2) {
			return -1;
		} else if (b1 > b2) {
			return 1;
		}
	}
	return 0;
}

int main ()
{
  char buffer1[] = "DWgaOtP12df0";
  char buffer2[] = "DWGAOTP12DF0";

  int n;

  n=my_memcmp ( buffer1, buffer2, sizeof(buffer1) );

  if (n>0) printf ("'%s' is greater than '%s'.\n",buffer1,buffer2);
  else if (n<0) printf ("'%s' is less than '%s'.\n",buffer1,buffer2);
  else printf ("'%s' is the same as '%s'.\n",buffer1,buffer2);

  return 0;
}
