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
}model_st_t; model_st_t model_st; model_st_t* m=&model_st;
/*=====================================================================================================*/
void main(){
	/*Utworzenie pliku na wyniki*/
	FILE * fp;
	fp = fopen("dane.txt", "w+");

	/*Czas symulacji*/
	int t[1000]; for(int i = 0; i<1000; i++){t[i]=i;}

	/*Zależności:*/
	typedef struct{
	float dT = abs(abs(m->Tw) - abs(m->Tz));	 /*Różnica temperatur => [ K ]*/
	float Ptot = m->U * m->Pow * (m->Tw - m->Tz);/*Strumień ciepła => [ W ]*/
	float ZS = m->Pg / m->C; 					 /*Zysk/Strata liczone w stopniach => [ K = *C ]*/
	float R = m->U^(-1);						 /*Opór temperaturowy budynku => [ (m^2 * K)/W ]*/
	}model_wew_st_t; model_wew_st_t model_wew_st; model_wew_st_t* m_wew=&model_wew_st;

	/*Symulacja*/
	float Pb = 1;
	/*Pętla główna*/
	for(int i = 0; i<1000; i++)/* t */{

		/* G == 1 : (1) */
		/* Ustalenie różnicy temperatur i ilości uciekającego ciepła */
		/* Włączenie grzałki -> P(t) = Pb*exp(t/(R*C)) */
		/* Nagrzewanie się grzałki */
		/* Nagrzewanie budynku grzałką */
		/* => (1)/(2) */
		/*  */
		/**/
		/*  */
		/* G != 1 : (2) */
		/* Ustalenie różnicy temperatur i ilości uciekającego ciepła */
		/* Wyłączenie grzałki -> P(t) = Pb*exp(-t/(R*C)) (???) */
		/* Ochładzanie się grzałki */
		/* Ochładzanie budynku */
		/* =? (1)/(2) */

	//if(m->G){fprintf(fp,"%d\n", 1);}else{fprintf(fp,"%d\n", 1);}
	}
	fclose(fp);
	//system("gnuplot rysowanie.gp -p");
}


