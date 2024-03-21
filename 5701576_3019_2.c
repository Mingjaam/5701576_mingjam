#include <stdio.h>
#include <time.h>

// �ݺ����� ����Ͽ� �ŵ������� ����ϴ� �Լ�
// a: ��
// b: ����
double power_iter(double a, double b);

// ��������� �ŵ������� ����ϴ� �Լ�
// a: ��
// b: ����
double power_rec(double a, double b);

int main(void) {
    clock_t start, stop;

    start = clock();
    double result_iter = power_iter(13, 21); // �ݺ����� ����Ͽ� �ŵ����� ���
    stop = clock();
    printf(" %.0f,   �ð�: %f ��\n", result_iter, (double)(stop - start) / CLOCKS_PER_SEC);

    start = clock();
    double result_rec = power_rec(13, 21); // ��������� �ŵ����� ���
    stop = clock();
    printf("%.0f,   �ð�: %f ��\n", result_rec, (double)(stop - start) / CLOCKS_PER_SEC);

    return 0;
}

// �ݺ����� ����Ͽ� �ŵ������� ����ϴ� �Լ�
double power_iter(double a, double b) {
    double result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

// ��������� �ŵ������� ����ϴ� �Լ�
double power_rec(double a, double b) {
    if (b == 0) {
        return 1;
    }
    else {
        return a * power_rec(a, b - 1);
    }
}
