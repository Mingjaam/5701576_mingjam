#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEGREE 101 //�ְ� ������ 101������ �����Ͽ� ����

// ���׽��� ����ü�� ����
typedef struct polynomial {
    int degree;         // �ְ� ����
    float coef[MAX_DEGREE];  // ������� �迭
} polynomial;

// �Լ� ����
void print_polynomial(polynomial p);
polynomial poly_mult(polynomial A, polynomial B);

// �־��� �� ���׽�
polynomial a = { 6, {7,0,0,5,9,0,1} };
polynomial b = { 3, {5,2,1,10} };

int main(void) {
    // �־��� ���׽� ���
    print_polynomial(a);
    print_polynomial(b);
    printf("--------------------------------------------------------------------------------\n");

    // ���׽� ����
    polynomial c = poly_mult(a, b);
    print_polynomial(c);

    return 0;
}

// ���׽��� ����ϴ� �Լ�
void print_polynomial(polynomial p) {
    for (int i = p.degree; i > 0; i--) {
        printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
    }
    printf("%3.1f\n", p.coef[p.degree]);
}


// �� ���׽��� ���ϴ� �Լ�
polynomial poly_mult(polynomial A, polynomial B) {
    polynomial C; // ��� ���׽�
    memset(C.coef, 0, sizeof(float) * MAX_DEGREE); // C �迭�� 0���� �ʱ�ȭ

    C.degree = A.degree + B.degree; // C �� �ְ� ����

    for (int i = 0; i <= A.degree; i++) {
        for (int j = 0; j <= B.degree; j++) {
            C.coef[i + j] += A.coef[i] * B.coef[j];
        }
    }
    return C;
}
