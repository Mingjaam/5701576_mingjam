#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

struct Stack {
    int data[MAX_VERTICES];
    int top;
};

struct Queue {
    int data[MAX_VERTICES];
    int front;
    int rear;
};

void enqueue(struct Queue* queue, int value) {
    queue->data[queue->rear++] = value;
}

int dequeue(struct Queue* queue) {
    return queue->data[queue->front++];
}


void push(struct Stack* stack, int value) {
    stack->data[++stack->top] = value;
}

int pop(struct Stack* stack) {
    return stack->data[stack->top--];
}

GraphMatType* createGraph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

void destroyGraph(GraphMatType* g) {
    free(g);
}

void initGraph(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

void insertVertex(GraphMatType* g, int v) {
    if (g->n + 1 > MAX_VERTICES) {
        printf("그래프 정점의 개수 초과\n");
        return;
    }
    g->n++;
}

void insertEdge(GraphMatType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        printf("그래프 정점의 개수 초과\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;  // 양방향 vertex 연결
}

void printGraph(GraphMatType* g) {
    for (int i = 0; i < g->n; i++) {
        printf("\n정점 %d의 인접 정점: ", i);
        for (int j = 0; j < g->n; j++) {
            printf("%d ", g->adj_mat[i][j]);
        }
    }
}
//그래프 생성
void generateGraph(GraphMatType* g) {
    int size = 11;
    int edge_size = 21;
    
    int node[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int edge[21][2] = {
        {0,2},{0,4},{0,5},{0,6},{0,9},
        {1,4},{1,5},{1,7},{1,10},
        {2,3},{2,4},
        {3,5},{3,4},
        {4,5},{4,6},{4,7},
        {6,8},{6,7},
        {7,10},
        {8,9},{8,10}
    };

    initGraph(g);
    // 정점 추가
    for (int i = 0; i < size; i++) {
        insertVertex(g, node[i]);
    }
    // vertex 연결
    for (int i = 0; i < edge_size; i++) {
        insertEdge(g, edge[i][0], edge[i][1]); 
    }
}

//깊이우선 탐색
void DFS(GraphMatType* g, int start, int target, int* count) {
    int visited[MAX_VERTICES] = {0};
    struct Stack stack;
    stack.top = -1;

    push(&stack, start);
    visited[start]++;

    while (stack.top >= 0) {
        int current = stack.data[stack.top];
        printf("%d ", current);
        (*count)++;

        // 목표 노드를 찾았을 경우
        if (current == target) {
            printf("\n탐색 성공 : %d\n", target);
            printf("방문한 노드의 수 : %d\n", *count);
            return;
        }

        // 다음 방문할 노드 찾기
        int next_node = -1;
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[current][i] && visited[i] == 0) {
                next_node = i;
                break;
            }
        }
        // 다음 방문할 노드가 있을 경우
        if (next_node != -1) {
            push(&stack, next_node);
            visited[next_node]++;
        } else {
            pop(&stack);
        }
    }

    printf("\n탐색 실패: %d를 찾지 못했습니다.\n", target);
}


//너비우선 탐색
void BFS(GraphMatType* g, int start, int target) {
    int visited[MAX_VERTICES] = {0};
    struct Queue queue;
    queue.front = 0;
    queue.rear = 0;
    int count = 0;

    enqueue(&queue, start);
    visited[start] = 1;
    printf("%d ", start);

    while (queue.front < queue.rear) {
        int current = dequeue(&queue);
        // 목표 노드를 찾았을 경우
        if (current == target) {
            printf("\n탐색 성공 : %d\n", target);
            printf("방문한 노드의 수 : %d\n", count);
            return;
        }

        // 인접한 노드들을 큐에 추가
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[current][i] && visited[i] == 0) {
                enqueue(&queue, i);
                visited[i] = 1;
                printf("%d ", i);
                count++;

                if (i == target) {
                    printf("\n탐색 성공 : %d\n", target);
                    printf("방문한 노드의 수 : %d\n", count);
                    return;
                }
            }
        }
    }

    printf("\n탐색 실패: %d를 찾지 못했습니다.\n", target);
    printf("방문한 노드의 수 : %d\n", count);
}

int main() {
    GraphMatType* g = createGraph();
    generateGraph(g);

    int start, target, count = 0;
    int choice;

    while (1) {
        printf("──────────────────────\n");
        printf("1 : 깊이 우선 탐색 \n");
        printf("2 : 너비 우선 탐색 \n");
        printf("3 : 종료           \n");
        printf("──────────────────────\n");
        printf("메뉴 입력 : ");
        scanf("%d", &choice);

        if (choice == 3) break;

        printf("시작 번호와 탐색할 값 입력 : ");
        scanf("%d %d", &start, &target);

        if (choice == 1) {
            DFS(g, start, target, &count);
            printf("\n");
        } else if (choice == 2) {
            BFS(g, start, target);
        }

        printf("\n");
    }

    destroyGraph(g);
    return 0;
}
