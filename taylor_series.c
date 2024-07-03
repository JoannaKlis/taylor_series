#pragma warning (disable: 4996) 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h> // typ bool
#include <float.h> // DBL_EPSILON


double oblicz_sume_szeregu(double x, int M, int *suma_wyrazow, bool *dokladnosc)
{
	*dokladnosc = false;
	double suma_szeregu = 1.0;
	double licznik = 1.0;
	double mianownik = 3.0;
	double skladnik = licznik / mianownik * x;

	for (int i = 1; i <= M; i++)
	{
		suma_szeregu += skladnik;
		*suma_wyrazow = i;

		licznik += 3;
		mianownik += 3;
		double nastepny_skladnik = skladnik * licznik / mianownik * x;
		skladnik = nastepny_skladnik;

		if (fabs(nastepny_skladnik) < DBL_EPSILON)
		{
			*dokladnosc = true;
			break;
		}
	}

	return suma_szeregu;
}

int main()
{
	double dolna_granica = -1.0;
	double gorna_granica = 1.0;
	double a, b;
	int czesci_przedzialu;
	int liczba_wyrazow_szeregu;

	bool czy_osiegnieto_dokladnosc;
	int liczba_sumowanych_wyrazow;

	printf("Podaj przedzial [a,b] znajdujacy sie w granicach (-1,1)\n");
	printf("Podaj poczatek przedzialu \"a\" : ");
	if (scanf("%lf", &a) != 1 || a <= dolna_granica || a >= gorna_granica)
	{
		printf("Nieprawdziwe dane lub wprowadzona liczba nie nalezy do (-1,1)!\n");
		return -1;
	}
	printf("Podaj koniec przedzialu \"b\" : ");
	if (scanf("%lf", &b) != 1 || b <= dolna_granica || b >= gorna_granica)
	{
		printf("Nieprawdziwe dane lub wprowadzona liczba nie nalezy do (-1,1)!\n");
		return -1;
	}
	if (b <= a) 
	{
		printf("Koniec przedzialu musi byc mniejszy niz poczatek przedzialu!\n");
		return 1;
	}
	printf("Wprowadz liczbe czesci przedzialu [a,b] : ");
	if (scanf("%d", &czesci_przedzialu) != 1 || czesci_przedzialu <= 0)
	{
		printf("Wprowadzona liczba nie jest calkowita lub dodatnia!\n");
		return -1;
	}

	printf("Wprowadz liczbe wyrazow szeregu : ");
	if (scanf("%d", &liczba_wyrazow_szeregu) != 1 || liczba_wyrazow_szeregu <= 0)
	{
		printf("Wprowadzona liczba nie jest calkowita lub dodatnia!\n");
		return -1;
	}

	FILE* wyniki = fopen("wyniki.txt", "w");
	if (wyniki == NULL)
	{
		printf("Blad otwarcia pliku do zapisu.\n");
		return -1;
	}


	double przeskok = (b - a) / czesci_przedzialu;

	fprintf(wyniki, "\tx\tf_szereg(x)\tf_scisle(x)\tliczba wyrazow szeregu\twarunek stopu\n");
	printf("\tx\tf_szereg(x)\tf_scisle(x)\tliczba wyrazow szeregu\twarunek stopu\n");

	for (double x = a; x <= b; x += przeskok)
	{
		if (x > -1 && x < 1)
		{
			double szereg = oblicz_sume_szeregu(x, liczba_wyrazow_szeregu, &liczba_sumowanych_wyrazow, &czy_osiegnieto_dokladnosc);
			double scisle = pow((1 + x), -1. / 3);

			fprintf(wyniki, "%lf\t%lf\t%lf\t%d\t\t\t%s\n", x, szereg, scisle, liczba_sumowanych_wyrazow, czy_osiegnieto_dokladnosc ? "tak" : "nie");
			printf("%lf\t%lf\t%lf\t%d\t\t\t%s\n", x, szereg, scisle, liczba_sumowanych_wyrazow, czy_osiegnieto_dokladnosc ? "tak" : "nie");
		}
	}

	fclose(wyniki);

	return 0;
}
