#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Budynek posiada pojemność cieplną -> ilość ciepła potrzebna by zmienić temperaturę wewnątrz o stopień*/
/*C [ J/K = (W*s)/K]*/
/**/
/*Moc grzałki jest stała, podlega załączeniu.*/
/*Wyłączenie spowoduje spadek generowanego przezeń strumienia ciepła [J]*/
/*Zależność opisująca spadek mocy grzałki o wartości początkowej P0:*/
/*P(t) = P0 * exp(t/(R*C)) */

/*=====================================================================================================*/
/*Parametry początkowe:*/
typedef struct{
	float Tw = 25;   /*Temperatura wewnętrzna budynku => [ *C ]*/
	float Tz = -5;   /*Temperatura na zewnątrz budynku => [ *C ]*/
	float C = 83150; /*Pojemność cieplna budynku => [ J/K = (W*s)/K ]*/
	int G = 1;       /*Włączenie grzałki 0/1 => [ boolean ]*/
	float Pg = 80000;/*Moc grzałki => [ W ]*/
	float Pow = 400; /*Powierzchnia umowna budynku => [ m^2 ]*/
	float U = 0.085; /*Przenikalność temperaturowa budynku => [ W/(m^2 * K) ]*/
}model_st_t;
model_st_t model_st;
model_st_t* m = &model_st;
/*=====================================================================================================*/
void main(){
	/*Utworzenie pliku na wyniki*/
	FILE * fp;
	fp = fopen("dane.txt", "w+");

	/* Zmienne */
	float Zs; /* Zysk temperatury wewnętrznej z grzałki */
	float dT; /* Różnica temperatur */
	float Ptot; /* Strumień ciepła do zewnątrz */
	float P = 1; /* Aktualne ciepło grzałki */

	/*Pętla główna*/
	for(int i = 0; i<1000; i++)/* t */
	{

		if(i>500){m->G=0;};

		if(m->G == 1)/* Włączenie grzałki -> P(t) = Pb*exp(t/(R*C)) */
		{
			if (P >= m->Pg){/*Wartość już nie rośnie*/}else{P = m->Pg * exp(-i/exp(1));}/* Nagrzewanie grzałki */
			dT = abs(m->Tw - m->Tz); /* Ustalenie różnicy temperatur */
			Ptot = m->U * m->Pow * (m->Tw - m->Tz);/* Ciepło uchodzące z budynku */
			Zs = (P-Ptot) / m->C;		/* temperatura zapewniona przez ciepło grzałki */
			m->Tw = m->Tw + Zs; /* Zmiana temperatury wewnątrz */
		}
		else/* G != 1 */
		{
			if (P <= 0.1){/*Wartość już nie maleje*/}else{P = m->Pg *(1 - exp(-i/exp(1)));}/* Ochładzanie grzałki */
			dT = abs(m->Tw - m->Tz); /* Ustalenie różnicy temperatur */
			Ptot = m->U * m->Pow * (m->Tw - m->Tz);/* Ciepło uchodzące z budynku */
			Zs = (P-Ptot) / m->C;		/* temperatura zapewniona przez ciepło grzałki */
			m->Tw = m->Tw + Zs; /* Zmiana temperatury wewnątrz */
		}
	//if(m->G){fprintf(fp,"%d\n", 1);}else{fprintf(fp,"%d\n", 1);}
		fprint(fp, "%d %d\n",i, m->Tw);
	}
	fclose(fp);
	system("gnuplot Rysowanie.gp -p");
}



