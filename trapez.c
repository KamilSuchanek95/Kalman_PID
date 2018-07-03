#include <stdio.h>
#define N 1000
int main(int t[], int x[])
{
int calka;
int in = sizeof(t)/sizeof(t[0]) - 1;

a = 0;
b = t[in];

 if (a > b) {
  i = a;
  a = b;
  b = i;
 }

 for (i = a; i < b; i += (b - a) / N) {
  y = x[i] * x[i] + 2 * x - 4;
  calka += y * (b - a) / N;
 }

return calka;
}


