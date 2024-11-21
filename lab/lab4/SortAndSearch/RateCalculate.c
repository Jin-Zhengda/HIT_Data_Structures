#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int checkIfRateAvailable(double x, double y, int t, double rate) {
   double r1 = 1+rate, r2 = 1;
   while(t>=2) {
       r2 += r1;
       r1 *= (1+rate);
       t--;
   }
   return x*r1 < y*r2;
}

double BinarySearch(double x, double y, int t, double lo, double hi) {
   while (hi - lo > 1e-7) {
       double mid = (lo + hi) / 2;
       if (checkIfRateAvailable(x, y, t, mid)) {
           lo = mid;
       } else {
           hi = mid;
       }
   }
   return lo;
}

double searchProperRate(double x, double y, int t) {
   double r = 1;
   double lo = 0;
   double hi = r * 2;
   r = BinarySearch(x, y, t, lo, hi);
   return r;
}


int main(int argc, char *argv[]) {
   double rate;
   int N, X, Y, T;
   // I/O parts, do not modify
   scanf("%d", &N);
   for (int loop = 0; loop<N; loop++) {
       scanf("%d%d%d", &X,&Y,&T);
       rate = searchProperRate((double)X, (double)Y, T);
       printf("%.2f%%\n", 100 * rate);
   }
   return 0;
}