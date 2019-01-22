#include <stdio.h>

int main()
{
	printf("This goes to standard output.\n");
	
	fprintf(stdout, "This goes to standard output, too.\n");
	
	fprintf(stderr, "This goes to standard error.\n");
	
	return 0;
}
