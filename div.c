#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[])
{
    long double x = atof(argv[1]);
    long double y = atof(argv[2]);
    long double Resultado = x / y;

	FILE *cfPtr;

    switch (argc)
	{
	case 1:
        FILE *cfPtr;
        cfPtr = fopen("div.input", "r");
        fscanf(cfPtr, "%d", &numEscondida);

        fclose(cfPtr);
    break;
	case 3:
        double x = atof(argv[1]);
        double y = atof(argv[2]);

		printf("%.100Lf\n", Resultado);

		cfPtr = fopen("div.result", "w");
		fprintf(cfPtr, "%.100Lf\n", Resultado);
		fclose(cfPtr);
		break;
	default:
		printf("exp: numero invalido de argumentos.\n");
		break;
	}
}