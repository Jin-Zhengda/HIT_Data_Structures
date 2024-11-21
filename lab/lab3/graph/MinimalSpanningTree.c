//#include <stdio.h>
//#include <stdlib.h>
//
//# define max_dis 100000
//
//typedef char vextype[20];
//
//typedef struct {
//    int N, E;//N是顶点数，E是边数
//    int **matrix;//储存邻接矩阵
//    vextype *vertex;//存储节点的名字
//} Graph;
//
//Graph createGraph(int n) {
//    int i, j;
//    Graph g;
//    g.N = n;
//    g.matrix = (int **) malloc(sizeof(int *) * g.N);
//    for (i = 0; i < n; i++) {
//        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
//    }
//    for (i = 0; i < g.N; i++) {
//        for (j = 0; j < g.N; j++) {
//            g.matrix[i][j] = max_dis;
//        }
//    }
//    for (i = 0; i < g.N; i++) {
//        g.matrix[i][i] = 0;
//    }
//    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
//    return g;
//}
//
//int Prim(Graph g) {
//    int lowCost[g.N];
//    int closeSt[g.N];
//    int i, j, k;
//    int min;
//    int sum = 0;
//    lowCost[0] = 0;
//    closeSt[0] = 0;
//    for (i = 1; i < g.N; i++) {
//        lowCost[i] = g.matrix[0][i];
//        closeSt[i] = 0;
//    }
//
//    for (i =1; i < g.N; i++) {
//        min = max_dis;
//        j = 0;
//        k = 0;
//        while (j < g.N) {
//            if (lowCost[j] != 0 && lowCost[j] < min) {
//                min = lowCost[j];
//                k = j;
//            }
//            j++;
//        }
//        sum += min;
//        lowCost[k] = 0;
//        for (j = 0; j < g.N; j++) {
//            if (lowCost[j] != 0 && g.matrix[k][j] < lowCost[j]) {
//                lowCost[j] = g.matrix[k][j];
//                closeSt[j] = k;
//            }
//        }
//    }
//    return sum;
//}
//
//int main() {
//    int node_num;
//    int edge_num;
//
//    scanf("%d %d", &node_num, &edge_num);
//
//    Graph g = createGraph(node_num);
//    for (int i = 0; i < node_num; i++) {
//        sprintf(g.vertex[i], "%d", i);
//    }
//    for (int i = 0; i < edge_num; i++) {
//        int start_idx, end_idx, weight;
//        scanf("%d %d %d", &start_idx, &end_idx, &weight);
//        g.matrix[start_idx][end_idx] = weight;
//        g.matrix[end_idx][start_idx] = weight;
//    }
//    printf("%d", Prim(g));
//}