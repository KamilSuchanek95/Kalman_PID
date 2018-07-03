#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
	/*Temperatura wewnętrzna*/
	float Tw=25;
	/*Temperatura zewnętrzna*/
	float Tz=15;
	/*Rezystancja cieplna ścian*/
	float Rc=100;
	/*Moc grzałki*/
	float Pg=0.6;
	/*Pojemność cieplna budynku*/
	float Cc=0.003;
	/*Aktywność grzałki*/
	int G = 1;
}model_st_t;

model_st_t model_st;
model_st_t* m=&model_st;

void main()
{
	/*Prąd uchodzący*/
	float Iout;
	/*Prąd kondensatora*/
	float Ic = 0;

	/*Utworzenie pliku na wyniki*/
	FILE * fp;
	fp = fopen("dane.txt", "w+");

	/*Symulacja*/
	if(m->G)//
	{
	/*Napięcie jako różnica temperatur*/
		float U = m->Tw - m->Tz;
													/*Zwiększenie temperatury o ładunek kondensatora*/
															m->Tw += m->Cc * U;
/*Prąd na zewnątrz - Uciekające ciepło*/
		Iout = U / m->Rc;
			/*Zapis do pliku*/
		fprintf(fp,"%d\n", Iout);
	}
	else
	{
	/*Napięcie jako różnica temperatur*/
		float U = m->Tw - m->Tz;
													/*Zmniejszenie temperatury pomieszczenia*/
															m->Tw -= m->Cc * m->Rc * Ic;
/*Początkowy prąd dla kondensatora bez zasilania*/

	/*Spadek prądu poprzez rozładowanie kondensatora*/
		Ic = Ic * exp(1 / (m->Rc * m->Cc));
		float Uc = m->Rc * Ic;
		Iout = Uc / m->Rc;
			/*Zapis do pliku*/
		fprintf(fp,"%d\n", Iout);
	}

	/*Rysowanie*/
	fclose(fp);
	system("gnuplot rysowanie.gp -p");
}
/**/
