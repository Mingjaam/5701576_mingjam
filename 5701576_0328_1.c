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
polynomial add_polynomial(polynomial A, polynomial B);
polynomial multiply_polynomial(polynomial A, polynomial B);

// �־��� �� ���׽�
polynomial a = { 5, {3.0, 6.0, 0.0, 0.0, 0.0, 10.0} };
polynomial b = { 4, {7.0, 0.0, 5.0, 0.0, 1.0} };

int main(void) {
    // �־��� ���׽� ���
    printf("Polynomial a           :");
    print_polynomial(a);
    printf("Polynomial b           :");
    print_polynomial(b);

    // ���׽� ����
    polynomial sum = add_polynomial(a, b);
    printf("Sum of polynomials     :");
    print_polynomial(sum);

    // ���׽� ����
    polynomial product = multiply_polynomial(a, b);
    printf("Product of polynomials :");
    print_polynomial(product);

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
polynomial add_polynomial(polynomial A, polynomial B) {
    polynomial C; //��� ���׽�
    memset(C.coef, 0, sizeof(float) * MAX_DEGREE); // C �迭�� 0���� �ʱ�ȭ

    int Apos = 0, Bpos = 0, Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;

    // C�� �ְ� ����
    C.degree = (A.degree > B.degree) ? A.degree : B.degree;

    while (Apos <= A.degree && Bpos <= B.degree) {
        if (degree_a > degree_b) {
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        else if (degree_a == degree_b) {
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degree_a--; degree_b--;
        }
        else {
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

// �� ���׽��� ���ϴ� �Լ�
polynomial multiply_polynomial(polynomial A, polynomial B) {
    polynomial D; // ��� ���׽�
    memset(D.coef, 0, sizeof(float) * MAX_DEGREE); // D �迭�� 0���� �ʱ�ȭ

    D.degree = A.degree + B.degree; // D �� �ְ� ����

    for (int i = 0; i <= A.degree; i++) {
        for (int j = 0; j <= B.degree; j++) {
            D.coef[i + j] += A.coef[i] * B.coef[j];
        }
    }
    return D;
}
