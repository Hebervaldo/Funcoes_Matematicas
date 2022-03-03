#include <math.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/time.h>

#define err_c 1.0e-100
#define exp_c 2.718281828459045235360287471352662497757;

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

long double mtdCalcularLogaritmoNatural(long double x)
{
	long double Retorno = 0;

	FILE *cfPtr;

	int i = 0;
	int j = 1;
	int signal = 1;
    long double xn = x;
	long double r = x;
	long double m = x;
	long double oldr = 0;
	long double div = 1;
	long double exp = exp_c;
	long double err = mtdObterValorAbsoluto(r - oldr);

	mtdCronometroIniciar();

	if (x != 1)
	{
		while (mtdObterValorAbsoluto(xn) >= 1)
		{
			xn = xn / exp;
			i = i + 1;
		}

		xn = xn - 1;
		r = xn;
		m = xn;

		while (err > err_c)
		{
			m = m * xn;
			oldr = r;
			signal = signal * -1;
			div = div + 1;
			r = r + (signal * m / div);
			j = j + 1;
			err = mtdObterValorAbsoluto(r - oldr);
		}

		Retorno = (i + r);
	}
	else
	{
		j = 0;
		err = 0;
		Retorno = 0;
	}

	mtdCronometroParar();

	cfPtr = fopen("ln.loop", "w");
	fprintf(cfPtr, "%d\n", (j - 1));
	cfPtr = fopen("ln.erro", "w");
	fprintf(cfPtr, "%.100Lf\n", err);
	fclose(cfPtr);
	cfPtr = fopen("ln.time", "w");
	fprintf(cfPtr, "%ld us\n", mtdCronometroTempoDecorrido());

	return Retorno;
}

long double mtdCalcularLogaritmoNatural_n(long double x, int n)
{
	long double Retorno = 0;

	FILE *cfPtr;

	int i = 0;
	int signal = 1;
    long double xn = x;
	long double r = x;
	long double m = x;
	long double oldr = 0;
	long double div = 1;
	long double exp = exp_c;
	long double err = err_c;

	mtdCronometroIniciar();

	if (x != 1)
	{
		while (mtdObterValorAbsoluto(xn) >= 1)
		{
			xn = xn / exp;
			i = i + 1;
		}

		xn = xn - 1;
		r = xn;
		m = xn;

		for (int j = 2; j <= (n + 1); j++)
		{
			m = m * xn;
			oldr = r;
			signal = signal * -1;
			div = div + 1;
			r = r + (signal * m / div);
		}
	
		err = mtdObterValorAbsoluto((i + r) - mtdCalcularLogaritmoNatural(x));
		Retorno = (i + r);
	}
	else
	{
		err = 0;
		Retorno = 0;
	}

	mtdCronometroParar();

	cfPtr = fopen("ln.loop", "w");
	fprintf(cfPtr, "%d\n", n);
	cfPtr = fopen("ln.erro", "w");
	fprintf(cfPtr, "%.100Lf\n", err);
	cfPtr = fopen("ln.time", "w");
	fprintf(cfPtr, "%ld us\n", mtdCronometroTempoDecorrido());

	fclose(cfPtr);
	
	return Retorno;
}

int main(int argc, char *argv[])
{
	switch (argc)
	{
	case 2:
		printf("%.100Lf\n", mtdCalcularLogaritmoNatural(atof(argv[1])));
		break;
	case 3:
		printf("%.100Lf\n", mtdCalcularLogaritmoNatural_n(atof(argv[1]), atof(argv[2])));
		break;
	default:
		printf("ln: numero invalido de argumentos.\n");
		break;
	}

	printf("%.100f\n", log(atof(argv[1])));
}