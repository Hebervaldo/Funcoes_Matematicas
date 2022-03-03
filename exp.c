#include <math.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/time.h>

#define err_c 1.0e-100
#define exp_c 2.718281828459045235360287471352662497757

long tInicial, tFinal, tTempoDecorrido;

struct ut_tv
{
   int32_t tv_sec; /* Seconds */
   int32_t tv_usec; /* Microseconds */
}; /* Time entry was made */

struct timeval ut_tv; /* Time entry was made */
struct timeval tvInicial, tvFinal;

long mtdCronometroIniciar()
{
	gettimeofday(&tvInicial, NULL);

	tInicial = (tvInicial.tv_sec * 1e6) + (tvInicial.tv_usec);
	return tInicial;
}

long mtdCronometroParar()
{
	gettimeofday(&tvFinal, NULL);

	tFinal = (tvFinal.tv_sec * 1e6) + (tvFinal.tv_usec); 
	return tFinal;
}

long mtdCronometroTempoDecorrido()
{
	tTempoDecorrido = (tFinal - tInicial);
	return tTempoDecorrido;
}

long double mtdObterValorAbsoluto(long double x)
{
	long double Retorno = 0;

	if (x >= 0)
	{
		Retorno = x;
	}
	else
	{
		Retorno = -1 * x;
	}

	return Retorno;
}

long double mtdCalcularExponencial(long double x)
{
	long double Retorno = 0;

	FILE *cfPtr;

	int j = 1;
	long double oldr = 0;
	long double r = 1 + x;
	long double div = 1;
	long double m = x;
	long double err = mtdObterValorAbsoluto(r - oldr);

	mtdCronometroIniciar();

	if (x != 0)
	{
		while (err > err_c)
		{
			j = j + 1;
			div = div * j;
			m = m * x;
			oldr = r;
			r = r + (m / div);
			err = mtdObterValorAbsoluto(r - oldr);
		}

		Retorno = r;
	}
	else
	{
		j = 0;
		err = 0;
		Retorno = 1;
	}

	mtdCronometroParar();
	
	cfPtr = fopen("exp.loop", "w");
	fprintf(cfPtr, "%d\n", (j - 1));
	cfPtr = fopen("exp.error", "w");
	fprintf(cfPtr, "%.100Lf\n", err);
	cfPtr = fopen("exp.time", "w");
	fprintf(cfPtr, "%ld us\n", mtdCronometroTempoDecorrido());

	fclose(cfPtr);
	
	return Retorno;
}

long double mtdCalcularExponencial_n(long double x, int n)
{
	long double Retorno = 0;

	FILE *cfPtr;

	long double oldr = 0;
	long double r = 1 + x;
	long double div = 1;
	long double m = x;
	long double err = 0;

	mtdCronometroIniciar();

	if (x != 0)
	{
		for (int j = 2; j <= (n + 1); j++)
		{
			div = div * j;
			m = m * x;
			oldr = r;
			r = r + (m / div);
		}

		err = mtdObterValorAbsoluto(r - mtdCalcularExponencial(x));
		Retorno = r;
	}
	else
	{
		err = 0;
		Retorno = 1;
	}

	mtdCronometroParar();

	cfPtr = fopen("exp.loop", "w");
	fprintf(cfPtr, "%d\n", n);
	cfPtr = fopen("exp.erro", "w");
	fprintf(cfPtr, "%.100Lf\n", err);
	cfPtr = fopen("exp.time", "w");
	fprintf(cfPtr, "%ld us\n", mtdCronometroTempoDecorrido());

	fclose(cfPtr);
	
	return Retorno;
}

int main(int argc, char *argv[])
{
	switch (argc)
	{
	case 2:
		printf("%.100Lf\n", mtdCalcularExponencial(atof(argv[1])));
		break;
	case 3:
		printf("%.100Lf\n", mtdCalcularExponencial_n(atof(argv[1]), atof(argv[2])));
		break;
	default:
		printf("exp: numero invalido de argumentos.\n");
		break;
	}

	printf("%.100lf\n", exp(atof(argv[1])));
}