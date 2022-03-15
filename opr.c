#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define CONSTANTE_TIPO_NUMERO_DIGITOS "%.18Lf\n"
#define TIPO_OPERACAO_GENERICA "opr"
#define TIPO_OPERACAO_ADICAO "add"
#define TIPO_OPERACAO_SUBTRACAO "sub"
#define TIPO_OPERACAO_MULTIPLICACAO "mul"
#define TIPO_OPERACAO_DIVISAO "div"

int strContains(char* string, char* toFind)
{
    int slen = strlen(string);
    int tFlen = strlen(toFind);
    int found = 0;

    if(slen >= tFlen)
    {
        for(int s=0, t=0; s<slen; s++)
        {
            do
			{
                if(string[s] == toFind[t])
                {
                    if(++found == tFlen) 
					{
						return 1;
					}
                    s++;
                    t++;
                }
                else
				{
					s -= found;
					found=0;
					t=0;
				}

              }
			  while(found);
        }
        return 0;
    }
    else 
	{
		return -1;
	}
}

long double mtdOperarAdicao(long double x, long double y)
{
	return x + y;
}

long double mtdOperarSubtracao(long double x, long double y)
{
	return x - y;
}

long double mtdOperarMultiplicacao(long double x, long double y)
{
	return x * y;
}

long double mtdOperarDivisao(long double x, long double y)
{
	return x / y;
}

long double mtdOperarGenerico(char operador, long double x, long double y)
{
	long double Resultado = 0;

	switch (operador)
	{
		case '+':
			Resultado = mtdOperarAdicao(x, y);
		break;
		case '-':
			Resultado = mtdOperarSubtracao(x, y);
		break;
		case '*':
			Resultado = mtdOperarMultiplicacao(x, y);
		break;
		case '/':
			Resultado = mtdOperarDivisao(x, y);
		break;
	}

	return Resultado;
}

char *mtdDefinirOperacao(char *Entrada)
{
	char *Retorno;

	if (strContains(Entrada, TIPO_OPERACAO_GENERICA))
	{
		Retorno = TIPO_OPERACAO_GENERICA;
	}

	if (strContains(Entrada, TIPO_OPERACAO_ADICAO))
	{
		Retorno = TIPO_OPERACAO_ADICAO;
	}

	if (strContains(Entrada, TIPO_OPERACAO_SUBTRACAO))
	{
		Retorno = TIPO_OPERACAO_SUBTRACAO;
	}

	if (strContains(Entrada, TIPO_OPERACAO_MULTIPLICACAO))
	{
		Retorno = TIPO_OPERACAO_MULTIPLICACAO;
	}

	if (strContains(Entrada, TIPO_OPERACAO_DIVISAO))
	{
		Retorno = TIPO_OPERACAO_DIVISAO;
	}

	return Retorno;
}

long double mtdResultadoOperacao(char *operacao, char operador, long double x, long double y)
{
	long double Retorno;

	if (operacao == TIPO_OPERACAO_GENERICA)
	{
		Retorno = mtdOperarGenerico(operador, x, y);
	}

	if (operacao == TIPO_OPERACAO_ADICAO)
	{
		Retorno = mtdOperarAdicao(x, y);
	}

	if (operacao == TIPO_OPERACAO_SUBTRACAO)
	{
		Retorno = mtdOperarSubtracao(x, y);
	}

	if (operacao == TIPO_OPERACAO_MULTIPLICACAO)
	{
		Retorno = mtdOperarMultiplicacao(x, y);
	}

	if (operacao == TIPO_OPERACAO_DIVISAO)
	{
		Retorno = mtdOperarDivisao(x, y);
	}

	return Retorno;
}

int main(int argc, char *argv[])
{
    long double x = 0;
    long double y = 0;
    long double Resultado = 0;

	FILE *cfPtr;

	char *comando;
	comando = argv[0];
	char *operacao = mtdDefinirOperacao(comando);
	char operador;

    switch (argc)
	{
		case 1:
			if (operacao == TIPO_OPERACAO_GENERICA)
			{
				cfPtr = fopen("opr.input", "r");
			}
			if (operacao == TIPO_OPERACAO_ADICAO)
			{
				cfPtr = fopen("add.input", "r");
			}
			if (operacao == TIPO_OPERACAO_SUBTRACAO)
			{
				cfPtr = fopen("sub.input", "r");
			}
			if (operacao == TIPO_OPERACAO_MULTIPLICACAO)
			{
				cfPtr = fopen("mul.input", "r");
			}
			if (operacao == TIPO_OPERACAO_DIVISAO)
			{
				cfPtr = fopen("div.input", "r");
			}

			fscanf(cfPtr, "%Lf", &x);
			if (operacao == TIPO_OPERACAO_GENERICA)
			{
				fscanf(cfPtr, "%s", &operador);
			}
			fscanf(cfPtr, "%Lf", &y);
		break;
		case 2:
		{
			char *chr = argv[1];
			int cchr = 0;
			char *xc;
			char *yc;

			int pix = 0;
			int piy = 0;

			int bx = 0;
			int by = 0;

			int cx = 0;
			int cy = 0;

			while (bx != -1 && by != -1)
			{
				if (chr[cchr] == '(')
				{
					bx = 1;	
					by = 0;
					pix = cchr + 1;
				}

				if (bx == 1 && by == 0)
				{
					cx = cx + 1;
				}

				if (chr[cchr] == ',' || chr[cchr] == '+' || chr[cchr] == '-' || chr[cchr] == '*' || chr[cchr] == '/')
				{
					bx = 0;
					by = 1;
					piy = cchr + 1;
					cx = cx - 1;
					if(chr[cchr] != ',')
					{
						operador = chr[cchr];
					}
				}

				if (bx == 0 && by == 1)
				{
					cy = cy + 1;
				}

				if (chr[cchr] == ')')
				{
					bx = -1;
					by = -1;
					cy = cy - 1;
				}

				cchr = cchr + 1;
			}

			xc = (char *)malloc((cx + 1) * sizeof(char));
			yc = (char *)malloc((cy + 1) * sizeof(char));

			int j = 0;
			int k = 0;

			for (int i = 0; i < cchr; i++)
			{
				if (i >= pix && i < pix + cx - 1)
				{
					xc[j] = chr[i];
					j = j + 1;
				}
				
				if (i >= piy && i < piy + cy - 1)
				{
					yc[k] = chr[i]; 
					k = k + 1;
				}
			}

			x = atof(xc);
			y = atof(yc);
		}
		break;
		case 3:
			x = atof(argv[1]);
			y = atof(argv[2]);
		break;
		case 4:
			x = atof(argv[1]);
			operador = argv[2][0];
			y = atof(argv[3]);
		break;
		default:
			printf("%s: numero invalido de argumentos.\n", operacao);
			return 0;
		break;
	}

	Resultado = mtdResultadoOperacao(operacao, operador, x, y);

	if (operacao == TIPO_OPERACAO_GENERICA)
	{
		printf("(Operacao: %c)\t", operador);
	}
	printf(CONSTANTE_TIPO_NUMERO_DIGITOS, Resultado);

	if (operacao == TIPO_OPERACAO_GENERICA)
	{
		cfPtr = fopen("opr.result", "w");
	}
	if (operacao == TIPO_OPERACAO_ADICAO)
	{
		cfPtr = fopen("add.result", "w");
	}
	if (operacao == TIPO_OPERACAO_SUBTRACAO)
	{
		cfPtr = fopen("sub.result", "w");
	}
	if (operacao == TIPO_OPERACAO_MULTIPLICACAO)
	{
		cfPtr = fopen("mul.result", "w");
	}
	if (operacao == TIPO_OPERACAO_DIVISAO)
	{
		cfPtr = fopen("div.result", "w");
	}

	fprintf(cfPtr, CONSTANTE_TIPO_NUMERO_DIGITOS, Resultado);

    fclose(cfPtr);
}