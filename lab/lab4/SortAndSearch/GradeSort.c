#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct student {
   int Code;
   int Score[5];
   double sum;
   int rank;
} Student;

typedef struct rank {
   int Rank;
   int Code;
} Rank;

Student Students[50];
Rank Ranks[50];

int Priority[5];
double Weight[5];
int N;


void CalcAndWriteRanks() {
   for (int i = 0; i < N; i++) {
       double sum = 0;
       for (int j = 0; j < 5; j++) {
           sum += Students[i].Score[j] * Weight[j];
       }
       Students[i].sum = sum;
   }
   for (int i = 0; i < N; i++) {
       double max = Students[i].sum;
       for (int j = i + 1; j < N; j++) {
           if (Students[j].sum > max) {
               max = Students[j].sum;
               Student temp = Students[i];
               Students[i] = Students[j];
               Students[j] = temp;
           }
       }
   }
   for (int i = 0; i < N; i++) {
       Students[i].rank = i + 1;
   }
   for (int i = 1; i < N; i++) {
       for (int j = i; j > 0; j--) {
           if (fabs(Students[j].sum - Students[j - 1].sum) < 1e-3) {
               int min;
               int count = 1;
               for (min = 0; min < 5; min++) {
                   if (Priority[min] == 1) {
                       break;
                   }
               }
               while (Students[j].Score[min] == Students[j - 1].Score[min] && count <= 5) {
                   count += 1;
                   for (int k = 0; k < 5; k++) {
                       if (Priority[k] == count) {
                           min = k;
                           break;
                       }
                   }

               }
               if (count == 6) {
                   if (Students[j].Code < Students[j - 1].Code) {
                       Students[j].rank = Students[j - 1].rank;
                       Student temp = Students[j];
                       Students[j] = Students[j - 1];
                       Students[j - 1] = temp;
                   } else {
                       Students[j].rank = Students[j - 1].rank;
                   }
               } else {
                   if (Students[j].Score[min] > Students[j - 1].Score[min]) {
                       Students[j].rank -= 1;
                       Students[j - 1].rank += 1;
                       Student temp = Students[j];
                       Students[j] = Students[j - 1];
                       Students[j - 1] = temp;
                   }
               }
           }
       }
   }
   for (int i = 0; i < N; i++) {
       Ranks[i].Code = Students[i].Code;
       Ranks[i].Rank = Students[i].rank;
   }
}

void PrintRanks() {
   for (int loop = 0; loop < N; loop++) {
       printf("%d %d\n", Ranks[loop].Rank, Ranks[loop].Code);
   }
}

int main(int argc, char *argv[]) {
   // Input part, do not modify
   scanf("%d", &N);
   for (int loop = 0; loop < 5; loop++) {
       scanf("%d", Priority + loop);
   }
   for (int loop = 0; loop < 5; loop++) {
       scanf("%lf", Weight + loop);
   }

   for (int loop = 0; loop < N; loop++) {
       scanf("%d", &Students[loop].Code);
       for (int j = 0; j < 5; j++) {
           scanf("%d", Students[loop].Score + j);
       }
   }
   // Main process part
   CalcAndWriteRanks();
   // Output part, do not modify
   PrintRanks();
   return 0;
}
