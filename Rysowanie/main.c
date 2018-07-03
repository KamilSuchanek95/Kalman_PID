 #include <stdio.h>
 #include <stdlib.h>

int main()
{
printf("\n\r 1");
	int i;
	FILE * fp;
	fp = fopen("dane.txt", "w+");
	for(i = 0; i<1000; i++) 
	{
		int r = rand() % 20;
		fprintf(fp,"%u %u\n", i, r);
	}
		fclose(fp);
		system("gnuplot rysowanie.gp -p");
return 0;
}

