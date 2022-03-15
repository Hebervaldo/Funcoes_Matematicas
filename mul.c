#include <stdio.h>
#include <stdlib.h> 

#define CONSTANTE_TIPO_NUMERO_DIGITOS "%.18Lf\n"

long double mtdOperarMultiplicacao(long double x, long double y)
{
	return x * y;
}

int main(int argc, char *argv[])
{
    long double x = 0;
    long double y = 0;
    long double Resultado = 0;

	FILE *cfPtr;

    switch (argc)
	{
	case 1:
        cfPtr = fopen("mul.input", "r");
        fscanf(cfPtr, "%Lf", &x);
        fscanf(cfPtr, "%Lf", &y);

		Resultado = mtdOperarMultiplicacao(x, y);

		printf(CONSTANTE_TIPO_NUMERO_DIGITOS, Resultado);

		cfPtr = fopen("mul.result", "w");
		fprintf(cfPtr, CONSTANTE_TIPO_NUMERO_DIGITOS, Resultado);
    break;
	case 3:
		cfPtr = fopen("mul.result", "w");
        x = atof(argv[1]);
        y = atof(argv[2]);

		Resultado = mtdOperarMultiplicacao(x, y);

		printf(CONSTANTE_TIPO_NUMERO_DIGITOS, Resultado);

		cfPtr = fopen("mul.result", "w");
		fprintf(cfPtr, CONSTANTE_TIPO_NUMERO_DIGITOS, Resultado);
	break;
	default:
		printf("mul: numero invalido de argumentos.\n");
	break;
	}

    fclose(cfPtr);
}