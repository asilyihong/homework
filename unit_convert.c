#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

    if (argc != 2) {
	printf("ERROR: need a parameter.\n");
	printf("usage: %s <num>\n", argv[0]);
	return EXIT_FAILURE;
    }

    long size = atol(argv[1]);
    int index = 0;
    char **UNIT = (char**)malloc(sizeof (char*) * 5);
    UNIT[0] = "Byte";
    UNIT[1] = "KB";
    UNIT[2] = "MB";
    UNIT[3] = "GB";
    UNIT[4] = "TB";
    float result;
    const char *resultUnit;

    while (size >> 20) {
	index++;
	size = size >> 10;
    }

    if (size >> 10) {
	index++;
	result = (float)size / 1024.0;
    } else {
	result = size;
    }

    resultUnit = UNIT[index];
    
    printf("result: %.2f %s\n", result, resultUnit);

    free(UNIT);

    return EXIT_SUCCESS;
}
