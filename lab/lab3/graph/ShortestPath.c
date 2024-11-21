#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];

typedef struct {
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的名字
} Graph;

Graph createGraph(int n);

int isConnected(Graph g);

int Diameter(Graph g);

int Radius(Graph g);

int dijkstra(Graph g, int start, int end, int *path);

void printPath(int d, int *diameter_path, Graph g);

void DFS(Graph g, int i, int *visited, int *count);

int DFSTraverse(Graph g);

void floyd(Graph g, int **dist, int **path);


/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
}


/**
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param diameter_path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *diameter_path, Graph g) {
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s->", g.vertex[diameter_path[k]]);
        path_length += g.matrix[diameter_path[k]][diameter_path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[diameter_path[k]]);
}

int DFSTraverse(Graph g) {
    int visited[g.N];
    for (int i = 0; i < g.N; i++) {
        visited[i] = 0;
    }
    int count = 0;
    DFS(g, 0, visited, &count);
    if (count == g.N) {
        return 1;
    } else {
        return 0;
    }
}

void DFS(Graph g, int i, int *visited, int *count) {
    visited[i] = 1;
    *count += 1;
    for (int j = 0; j < g.N; j++) {
        if (g.matrix[i][j] != max_dis && g.matrix[i][j] != 0 && visited[j] != 1) {
            DFS(g, j, visited, count);
        }
    }
}

/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    return DFSTraverse(g);
}


/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path) {
    int s[g.N];
    int dist[g.N];
    for (int i = 0; i < g.N; i++) {
        s[i] = 0;
        dist[i] = g.matrix[start][i];
        if (g.matrix[start][i] == max_dis || g.matrix[start][i] == 0) {
            path[i] = -1;
        } else {
            path[i] = start;
        }
        s[start] = 1;
    }
    for (int i = 0; i < g.N; i++) {
        int min = max_dis;
        int u;
        for (int j = 0; j < g.N; j++) {
            if (s[j] != 1 && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        s[u] = 1;
        for (int j = 0; j < g.N; j++) {
            if (s[j] != 1 && dist[j] > dist[u] + g.matrix[u][j]) {
                dist[j] = dist[u] + g.matrix[u][j];
                path[j] = u;
            }
        }
    }
    int temp[g.N];
    int count = 1;
    temp[0] = end;
    for (int i = 1; i < g.N; i++) {
        int pre = temp[i - 1];
        if (pre == start) {
            break;
        }
        temp[i] = path[pre];
        count++;
    }

    for (int i = 0; i < count; i++) {
        path[i] = temp[count - i - 1];
    }
    return dist[end];
}


void floyd(Graph g, int **dist, int **path) {
    for (int i = 0; i < g.N; i++) {
        for (int j = 0; j < g.N; j++) {
            dist[i][j] = g.matrix[i][j];
            path[i][j] = -1;
        }
    }
    for (int k = 0; k < g.N; k++) {
        for (int i = 0; i < g.N; i++) {
            for (int j = 0; j < g.N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

/**
 * 计算图的直径。提示：Floyd算法
 * @param g 图
 * @return 直径的长度
 */
int Diameter(Graph g) {
    int **dist = (int **) malloc(sizeof(int *) * g.N);
    int **path = (int **) malloc(sizeof(int *) * g.N);
    for (int i = 0; i < g.N; i++) {
        dist[i] = (int *) malloc(sizeof(int) * g.N);
        path[i] = (int *) malloc(sizeof(int) * g.N);
    }
    floyd(g, dist, path);

    int eff[g.N];
    for (int i = 0; i < g.N; i++) {
        int eMax = 0;
        for (int j = 0; j < g.N; j++) {
            if (dist[i][j] > eMax) {
                eMax = dist[i][j];
            }
        }
        eff[i] = eMax;
    }

    int max = 0;
    for (int i = 0; i < g.N; i++) {
        if (eff[i] > max) {
            max = eff[i];
        }
    }
    return max;
}


/**
 * 计算图的半径
 * @param g 图
 * @return 半径长度
 */
int Radius(Graph g) {
    int **dist = (int **) malloc(sizeof(int *) * g.N);
    int **path = (int **) malloc(sizeof(int *) * g.N);
    for (int i = 0; i < g.N; i++) {
        dist[i] = (int *) malloc(sizeof(int) * g.N);
        path[i] = (int *) malloc(sizeof(int) * g.N);
    }
    floyd(g, dist, path);

    int eff[g.N];
    for (int i = 0; i < g.N; i++) {
        int eMax = 0;
        for (int j = 0; j < g.N; j++) {
            if (dist[i][j] > eMax) {
                eMax = dist[i][j];
            }
        }
        eff[i] = eMax;
    }

    int min = max_dis;
    for (int i = 0; i < g.N; i++) {
        if (eff[i] > 0 && eff[i] < min) {
            min = eff[i];
        }
    }
    return min;
}


int main() {
    int node_num;
    int edge_num;


    scanf("%d %d", &node_num, &edge_num);

    Graph g = createGraph(node_num);
    for (int i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }
    for (int i = 0; i < edge_num; i++) {
        int start_idx, end_idx, weight;
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }
    printf("connected: %d\n", isConnected(g));

    if (isConnected(g)) {
        int *short_path = (int *) malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 1, 3, short_path);
        printf("the minimum fare between 1 and 3: %d\n", dis);
        printPath(dis, short_path, g);
        free(short_path);
        int d = Diameter(g);
        printf("diameter:%d\n", d);

        int r = Radius(g);
        printf("radius:%d\n", r);
    }

    return 0;
}