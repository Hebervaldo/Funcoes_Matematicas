#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[])
{
    long double x = atof(argv[1]);
    long double invx = 1/x; 

    switch (argc)
	{
	case 2:
		printf("%.100Lf\n", invx);
		break;
	default:
		printf("exp: numero invalido de argumentos.\n");
		break;
	}

}