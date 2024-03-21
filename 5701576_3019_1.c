#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// �ݺ����� ����Ͽ� ���丮���� ����ϴ� �Լ�
// a: ����� ��
long factorial_iter(int a);

// ��������� ���丮���� ����ϴ� �Լ�
// a: ����� ��
long factorial_rec(int a);

int main(void) {
    clock_t start, stop;

    // �ݺ����� ����Ͽ� ���丮�� ���
    start = clock();
    long result_iter = factorial_iter(20);
    stop = clock();
    printf(" %ld, Elapsed time: %.6f seconds\n", result_iter, (double)(stop - start) / CLOCKS_PER_SEC);

    // ��������� ���丮�� ���
    start = clock();
    long result_rec = factorial_rec(20);
    stop = clock();
    printf("%ld, Elapsed time: %.6f seconds\n", result_rec, (double)(stop - start) / CLOCKS_PER_SEC);

    return 0;
}

// �ݺ����� ����Ͽ� ���丮���� ����ϴ� �Լ�
long factorial_iter(int a) {
    long i, fac = 1;
    // �ݺ����� ���� ���丮�� ���
    for (i = 2; i <= a; i++) {
        fac *= i;
    }
    return fac;
}

// ��������� ���丮���� ����ϴ� �Լ�
long factorial_rec(int a) {
    // ���� ����: a�� 1 ������ �� 1 ��ȯ
    if (a <= 1) {
        return 1;
    }
    else {
        // ��� ȣ���� ���� ���丮�� ���
        return a * factorial_rec(a - 1);
    }
}
