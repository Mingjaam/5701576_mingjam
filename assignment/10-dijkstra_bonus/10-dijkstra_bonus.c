#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode heap[MAX_VERTICES];
    int size;
} Heap;

typedef struct Edge {
    int vertex;
    int weight;
    struct Edge* next;
} Edge;

typedef struct GraphTypeList {
    int n;
    Edge* adj_list[MAX_VERTICES];
} GraphTypeList;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int foundorder[MAX_VERTICES];

// 그래프 초기화 함수: 인접 행렬 그래프의 모든 가중치를 INF로 초기화
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->weight[i][j] = INF;
        }
    }
}

// 간선 추가 함수: 인접 행렬에 양방향 간선 추가
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start-1][end-1] = weight;
    g->weight[end-1][start-1] = weight;
}

// 현재 상태 출력 함수: 각 정점까지의 거리와 방문 여부를 출력
void print_status(GraphType* g) {
    printf("Distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf("* ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nFound: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

// 최소 거리 정점 선택 함수: 방문하지 않은 정점 중 최소 거리를 가진 정점 반환
int choose(int distance[], int n, int found[]) {
    int min = INF;
    int minpos = -1;
    
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 다익스트라 최단경로 함수 (인접 행렬 버전)
void shortest_path(GraphType* g, int start) {
    int visit_count = 0;
    
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    
    found[start] = TRUE;
    distance[start] = 0;
    foundorder[visit_count++] = start + 1;
    
    print_status(g);
    
    for (int w = 0; w < g->n; w++) {
        if (!found[w]) {
            distance[w] = g->weight[start][w];
        }
    }
    
    int u = choose(distance, g->n, found);
    found[u] = TRUE;
    foundorder[visit_count++] = u + 1;
    print_status(g);
    
    for (int i = 0; i < g->n-2; i++) {
        for (int w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }
        
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        foundorder[visit_count++] = u + 1;
        print_status(g);
    }
}

// 최소 힙 초기화 함수
void init_heap(Heap* h) {
    h->size = 0;
}

// 최소 힙 삽입 함수: 새로운 정점과 거리를 힙에 삽입
void insert_min_heap(Heap* h, int vertex, int key) {
    int i = ++(h->size);
    
    while (i != 1 && key < h->heap[i/2].distance) {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    
    h->heap[i].vertex = vertex;
    h->heap[i].distance = key;
}

// 최소 힙 삭제 함수: 최소 거리를 가진 정점을 힙에서 제거하고 반환
HeapNode delete_min_heap(Heap* h) {
    int parent = 1, child = 2;
    HeapNode item = h->heap[1];
    HeapNode temp = h->heap[(h->size)--];
    
    while (child <= h->size) {
        if (child < h->size && h->heap[child].distance > h->heap[child+1].distance)
            child++;
        if (temp.distance <= h->heap[child].distance)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 연결 리스트 그래프 초기화 함수
void init_graph_list(GraphTypeList* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++)
        g->adj_list[i] = NULL;
}

// 연결 리스트에 간선 추가 함수: 양방향 간선 추가
void insert_edge_list(GraphTypeList* g, int start, int end, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->vertex = end-1;
    edge->weight = weight;
    edge->next = g->adj_list[start-1];
    g->adj_list[start-1] = edge;
    
    edge = (Edge*)malloc(sizeof(Edge));
    edge->vertex = start-1;
    edge->weight = weight;
    edge->next = g->adj_list[end-1];
    g->adj_list[end-1] = edge;
}

// 다익스트라 최단경로 함수 (연결 리스트 + 힙 버전)
void shortest_path_list(GraphTypeList* g, int start) {
    Heap heap;
    init_heap(&heap);
    int visit_count = 0;
    
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    
    found[start] = TRUE;
    distance[start] = 0;
    insert_min_heap(&heap, start, distance[start]);
    foundorder[visit_count++] = start + 1;
    print_status((GraphType*)g);
    
    while (heap.size > 0) {
        HeapNode u = delete_min_heap(&heap);
        int current = u.vertex;
        
        if (found[current] && current != start) continue;
        
        if (current != start) {
            found[current] = TRUE;
            foundorder[visit_count++] = current + 1;
            print_status((GraphType*)g);
        }
        
        for (Edge* e = g->adj_list[current]; e != NULL; e = e->next) {
            int next = e->vertex;
            if (!found[next]) {
                if (distance[current] + e->weight < distance[next]) {
                    distance[next] = distance[current] + e->weight;
                    insert_min_heap(&heap, next, distance[next]);
                }
            }
        }
    }
}

// 그래프 생성 함수: 인접 행렬과 연결 리스트 그래프에 동일한 간선들을 추가
void generate_graph(GraphType* g1, GraphTypeList* g2) {
    // 간선 정보를 저장할 배열
    struct {
        int start, end, weight;
    } edges[] = {
        {1, 7, 12}, {1, 6, 11}, {1, 2, 3},
        {2, 3, 5},  {2, 4, 4},  {2, 5, 1},
        {2, 6, 7},  {2, 7, 8},  {3, 4, 2},
        {3, 7, 6},  {3, 8, 5},  {4, 5, 13},
        {4, 8, 14}, {4, 10, 16},{5, 6, 9},
        {5, 9, 18}, {5, 10, 17},{7, 8, 13},
        {8, 10, 15},{9, 10, 10}
    };
    
    // 그래프 초기화
    init_graph(g1, 10);
    init_graph_list(g2, 10);
    
    // 간선 추가
    for (int i = 0; i < sizeof(edges)/sizeof(edges[0]); i++) {
        insert_edge(g1, edges[i].start, edges[i].end, edges[i].weight);
        insert_edge_list(g2, edges[i].start, edges[i].end, edges[i].weight);
    }
}



int main(void) {
    GraphType g1;
    GraphTypeList g2;
    
    generate_graph(&g1, &g2);
    
    printf("=================================================\n");
    printf("1. 인접 행렬을 이용한 구현\n");
    printf("=================================================\n");
    shortest_path(&g1, 0);
    
    printf("\n방문 순서 (인접 행렬): ");
    for (int i = 0; i < g1.n; i++) {
        printf("%d ", foundorder[i]);
    }
    printf("\n\n");
    
    // 전역 변수 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF;
        found[i] = FALSE;
        foundorder[i] = 0;
    }
    
    printf("=================================================\n");
    printf("2. 연결리스트와 힙을 이용한 구현 (보너스)\n");
    printf("=================================================\n");
    shortest_path_list(&g2, 0);
    
    printf("\n방문 순서 (연결리스트): ");
    for (int i = 0; i < g2.n; i++) {
        printf("%d ", foundorder[i]);
    }
    printf("\n");
    
    return 0;
}
