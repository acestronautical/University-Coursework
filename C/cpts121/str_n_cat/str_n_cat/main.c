#include <stdio.h>
#include <string.h>

int main(void)
{
	char dest[10] = { 'j','i','l','l' };
	char * src = "Jack";
	printf("%s\n", strncat(dest, src, 3));
	return 0;
}