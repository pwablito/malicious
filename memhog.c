#include <stdlib.h>
#include <stdio.h>

int main() {
	unsigned int kb_allocated = 0;
	while (1)
	{
		malloc(1024);
		kb_allocated += 1;
		printf("Allocated %u kb\n", kb_allocated);
	}
	return 0;
}
