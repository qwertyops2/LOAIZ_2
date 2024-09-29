#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

const int size[] = { 1000, 100000 };
int k = 0;
double vremya[24];

void zaparr(int* a, int* b, int* c, int* d, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        a[i] = rand() % 1000;
        b[i] = i;
        c[i] = size - i;
        if (i < (size / 2)) { d[i] = i; }
        else { d[i] = size - i - 1; }
    }

}

void kopirka(int* a, int* b, int* c, int size)
{
    for (int i = 0; i < size; i++) {
        b[i] = a[i];
        c[i] = a[i];
    }
}

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;
    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (j - left < right - i) {
        if (left < j) qs(items, left, j);
        left = i;
    }
    else {
        if (i < right) qs(items, i, right);
        right = j;
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void schetShell(int* a, int* k, int size)
{
    clock_t start = clock();
    shell(a, size);
    clock_t end = clock();
    vremya[*k] = ((double)(end - start) / CLOCKS_PER_SEC);
    (*k)++;
}

void schetQs(int* a, int* k, int size)
{
    clock_t start = clock();
    qs(a, 0, size - 1);
    clock_t end = clock();
    vremya[*k] = ((double)(end - start) / CLOCKS_PER_SEC);
    (*k)++;
}

void schetQsort(int* a, int* k, int size)
{
    clock_t start = clock();
    qsort(a, size, sizeof(int), compare);
    clock_t end = clock();
    vremya[*k] = ((double)(end - start) / CLOCKS_PER_SEC);
    (*k)++;
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(NULL));
    for (int d = 0; d < 2; d++)
    {
        int* randarr1 = (int*)malloc(size[d] * sizeof(int)), * randarr2 = (int*)malloc(size[d] * sizeof(int)), * randarr3 = (int*)malloc(size[d] * sizeof(int));
        int* vozrast1 = (int*)malloc(size[d] * sizeof(int)), * vozrast2 = (int*)malloc(size[d] * sizeof(int)), * vozrast3 = (int*)malloc(size[d] * sizeof(int));
        int* ubiv1 = (int*)malloc(size[d] * sizeof(int)), * ubiv2 = (int*)malloc(size[d] * sizeof(int)), * ubiv3 = (int*)malloc(size[d] * sizeof(int));
        int* vozubiv1 = (int*)malloc(size[d] * sizeof(int)), * vozubiv2 = (int*)malloc(size[d] * sizeof(int)), * vozubiv3 = (int*)malloc(size[d] * sizeof(int));

        zaparr(randarr1, vozrast1, ubiv1, vozubiv1, size[d]);

        kopirka(randarr1, randarr2, randarr3, size[d]);
        kopirka(vozrast1, vozrast2, vozrast3, size[d]);
        kopirka(ubiv1, ubiv2, ubiv3, size[d]);
        kopirka(vozubiv1, vozubiv2, vozubiv3, size[d]);

        schetShell(randarr1, &k, size[d]);
        schetShell(vozrast1, &k, size[d]);
        schetShell(ubiv1, &k, size[d]);
        schetShell(vozubiv1, &k, size[d]);

        schetQs(randarr2, &k, size[d]);
        schetQs(vozrast2, &k, size[d]);
        schetQs(ubiv2, &k, size[d]);
        schetQs(vozubiv2, &k, size[d]);

        schetQsort(randarr3, &k, size[d]);
        schetQsort(vozrast3, &k, size[d]);
        schetQsort(ubiv3, &k, size[d]);
        schetQsort(vozubiv3, &k, size[d]);

        printf("Размер массивов %d:\n", size[d]);
        printf("       |  rand |  voz  |  ub   |  vu   |\n-----------------------------------------\n");
        printf(" shell | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n", vremya[0 + 12 * d], vremya[1 + 12 * d], vremya[2 + 12 * d], vremya[3 + 12 * d]);
        printf("   qs  | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n", vremya[4 + 12 * d], vremya[5 + 12 * d], vremya[6 + 12 * d], vremya[7 + 12 * d]);
        printf(" qsort | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n\n", vremya[8 + 12 * d], vremya[9 + 12 * d], vremya[10 + 12 * d], vremya[11 + 12 * d]);

        free(randarr1);
        free(randarr2);
        free(randarr3);
        free(vozrast1);
        free(vozrast2);
        free(vozrast3);
        free(ubiv1);
        free(ubiv2);
        free(ubiv3);
        free(vozubiv1);
        free(vozubiv2);
        free(vozubiv3);
    }

    printf("Разность 100000 и 1000:\n");
    printf("       |  rand |  voz  |  ub   |  vu   |\n-----------------------------------------\n");
    printf(" shell | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n", vremya[12] - vremya[0], vremya[13] - vremya[1], vremya[14] - vremya[2], vremya[15] - vremya[3]);
    printf("   qs  | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n", vremya[16] - vremya[4], vremya[17] - vremya[5], vremya[18] - vremya[6], vremya[19] - vremya[7]);
    printf(" qsort | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n\n", vremya[20] - vremya[8], vremya[21] - vremya[9], vremya[22] - vremya[10], vremya[23] - vremya[11]);

    return 0;
}
