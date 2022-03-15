#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[])
{
    long double x = atof(argv[1]);
    long double invx = 1/x;

	FILE *cfPtr;

    switch (argc)
	{
	case 2:
		printf("%.100Lf\n", invx);

		cfPtr = fopen("inv.result", "w");
		fprintf(cfPtr, "%.100Lf\n", invx);
		fclose(cfPtr);
		break;
	default:
		printf("exp: numero invalido de argumentos.\n");
		break;
	}

}