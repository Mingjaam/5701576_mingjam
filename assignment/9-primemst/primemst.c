#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000
#define FALSE 0
#define TRUE 1

int parent[MAX_VERTICES];
int key[MAX_VERTICES];
int visited[MAX_VERTICES];

// 간선 정보를 저장하는 구조체
struct Edge {
	int start, end, weight;
};

// 그래프를 나타내는 구조체
typedef struct GraphType {
	int n;
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

typedef struct MinHeap {
    int size;
    int capacity;
    struct Edge* array;
} MinHeap;


// 그래프를 초기화하는 함수
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// edge를 그래프에 삽입하는 함수
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// edge를 가중치에 따라 비교하는 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	if (x->weight == y->weight) {
		return (x->start - y->start);
	}
	return (x->weight - y->weight);
}

// 최소 힙을 생성하는 함수
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Edge*)malloc(capacity * sizeof(struct Edge));
    return minHeap;
}

// 두 edge를 교환하는 함수
void swapEdge(struct Edge* a, struct Edge* b) {
    struct Edge t = *a;
    *a = *b;
    *b = t;
}

// 최소 힙을 유지하기 위한 함수
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].weight < minHeap->array[smallest].weight)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].weight < minHeap->array[smallest].weight)
        smallest = right;

    if (smallest != idx) {
        swapEdge(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 최소 힙이 비어있는지 확인하는 함수
int isMinHeapEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

// 최소 힙에서 최소 edge를 추출하는 함수
struct Edge extractMin(MinHeap* minHeap) {
    if (isMinHeapEmpty(minHeap))
        return (struct Edge){-1, -1, -1};

    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    struct Edge root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

// 최소 힙에 edge를 삽입하는 함수
void insertMinHeap(MinHeap* minHeap, struct Edge edge) {
    if (minHeap->size == minHeap->capacity) {
        printf("MinHeap is full\n");
        return;
    }

    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i] = edge;

    while (i != 0 && minHeap->array[(i - 1) / 2].weight > minHeap->array[i].weight) {
        swapEdge(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 그래프에 edge를 생성하는 함수
void generateGraph(GraphType* g) {
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}
// 프림 알고리즘을 구현하는 함수
void FindPrimMST(GraphType* g, int start) {
    // 최소 힙 생성
    MinHeap* minHeap = createMinHeap(g->n);
    printf("Prime MST Algorithm\n");
    printf("정점 %d 추가\n", start);
    // 모든 정점을 방문하지 않은 상태로 초기화
    for (int i = 1; i <= MAX_VERTICES; i++) {
        visited[i] = FALSE;
        key[i] = INF;
        parent[i] = -1;
    }

    // 시작 정점의 가중치를 0으로 설정
    key[start] = 0;
    // 시작 정점의 간선을 힙에 삽입
    struct Edge startEdge = {start, start, 0};
    insertMinHeap(minHeap, startEdge);

    while (!isMinHeapEmpty(minHeap)) {
        // 최소 힙에서 최소 가중치의 간선을 추출
        struct Edge minEdge = extractMin(minHeap);
        int end = minEdge.end;

        // 이미 방문한 정점은 건너뜀
        if (visited[end]) continue;
        visited[end] = TRUE;

        // 시작 정점이 아니면 정점 추가 출력
        if (end != start) {
            printf("정점 %d 추가\n",end);
        }

        // 인접한 정점들을 확인
        for (int i = 0; i < g->n; i++) {
            if (g->edges[i].start == end && !visited[g->edges[i].end] && g->edges[i].weight < key[g->edges[i].end]) {
                // 인접한 정점을 방문하지 않았고, 가중치가 더 작으면 업데이트
                parent[g->edges[i].end] = end;
                key[g->edges[i].end] = g->edges[i].weight;
                // 새로운 간선을 힙에 삽입
                struct Edge newEdge = {end, g->edges[i].end, g->edges[i].weight};
                insertMinHeap(minHeap, newEdge);
            }
        }
    }
    // 최소 힙 메모리 해제
    free(minHeap->array);
    free(minHeap);
}

// 메인 함수
int main(void)
{
	GraphType *g;
	g = (GraphType *)malloc(sizeof(GraphType));
	if (g == NULL) {
		fprintf(stderr, "메모리 할당 오류\n");
		return 1;
	}
	graph_init(g);
	generateGraph(g);
    FindPrimMST(g, 1);

    free(g);
    return 0;
}
