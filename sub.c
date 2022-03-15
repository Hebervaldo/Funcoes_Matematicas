#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[])
{
    long double x = atof(argv[1]);
    long double y = atof(argv[2]);
    long double Resultado = x - y;

	FILE *cfPtr;

    switch (argc)
	{
	case 3:
		printf("%.100Lf\n", Resultado);

		cfPtr = fopen("sub.result", "w");
		fprintf(cfPtr, "%.100Lf\n", Resultado);
		fclose(cfPtr);
		break;
	default:
		printf("exp: numero invalido de argumentos.\n");
		break;
	}
}