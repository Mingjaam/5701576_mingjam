#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

// ���׽��� �� ���� ��Ÿ���� ����ü
struct term {
    float coef; // ���
    int expon;  // ����
};

// �Էµ� ���׽��� ��Ÿ���� �迭
struct term terms[MAX_TERMS] = { {4.0, 3}, {3.0, 2}, {2.0, 1}, {1.0, 0},
                                 {3.0, 2}, {2.0, 1}, {8.0, 0} };
int avail = 7; // ���׽��� ���� ���̸� ��Ÿ���� ����

// ���׽� ��� �Լ� ����
void print_poly(int s, int e);
// ���׽� ���� �Լ� ����
void poly_multiply(int As, int Ae, int Bs, int Be, int* Csp, int* Cep);


int main() {
    int As = 0, Ae = 3, Bs = 4, Be = 6, Cs, Ce;

    // �Էµ� ���׽� ���
    printf("A = ");
    print_poly(As, Ae);
    printf("B = ");
    print_poly(Bs, Be);

    // ���׽��� ���� ����
    poly_multiply(As, Ae, Bs, Be, &Cs, &Ce);
    printf("A * B = ");
    print_poly(Cs, Ce);

    return 0;
}

// ���׽� ���� �Լ�
void poly_multiply(int As, int Ae, int Bs, int Be, int* Csp, int* Cep) {
    struct term result[MAX_TERMS]; // ��� ���׽��� ������ �迭
    int avail_result = 0; // ��� ���׽��� ���� ���̸� ��Ÿ���� ����

    // ��� ���׽� ���
    for (int i = As; i <= Ae; i++) {
        for (int j = Bs; j <= Be; j++) {
            float coef = terms[i].coef * terms[j].coef; // ��� ����
            int expon = terms[i].expon + terms[j].expon; // ���� ��

            // ���� ������ ���� ���� ã�� ����� ����
            int found = 0;
            for (int k = 0; k < avail_result; k++) {
                if (result[k].expon == expon) {
                    result[k].coef += coef;
                    found = 1;
                    break;
                }
            }
            // ���� ������ ������ ���� ������ ��� ���׽Ŀ� �߰�
            if (!found) {
                result[avail_result].coef = coef;
                result[avail_result].expon = expon;
                avail_result++;
            }
        }
    }

    // ��� ���׽��� ���� ���׽Ŀ� ����
    *Csp = avail;
    for (int i = 0; i < avail_result; i++) {
        terms[avail].coef = result[i].coef;
        terms[avail].expon = result[i].expon;
        avail++;
    }
    *Cep = avail - 1;
}

// ���׽� ��� �Լ�
void print_poly(int s, int e) {
    for (int i = s; i < e; i++) {
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
    }
    printf("%3.1fx^%d\n", terms[e].coef, terms[e].expon);
}
