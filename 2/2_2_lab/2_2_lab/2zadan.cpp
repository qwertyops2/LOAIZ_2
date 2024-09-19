#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

const int size = 100000;
int randarr1[size], randarr2[size], randarr3[size];
int vozrast1[size], vozrast2[size], vozrast3[size];
int ubiv1[size], ubiv2[size], ubiv3[size];
int vozubiv1[size], vozubiv2[size], vozubiv3[size];
int k = 0;
double vremya[12];

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

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void schetShell(int* a, int* k)
{
    clock_t start = clock();
    shell(a, size);
    clock_t end = clock();
    vremya[*k] = ((double)(end - start) / CLOCKS_PER_SEC);
    (*k)++;
}

void schetQs(int* a, int* k)
{
    clock_t start = clock();
    qs(a, 0, size - 1);
    clock_t end = clock();
    vremya[*k] = ((double)(end - start) / CLOCKS_PER_SEC);
    (*k)++;
}

void schetQsort(int* a, int* k)
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

    zaparr(randarr1, vozrast1, ubiv1, vozubiv1, size);

    kopirka(&randarr1[size], &randarr2[size], &randarr3[size], size);
    kopirka(&vozrast1[size], &vozrast2[size], &vozrast3[size], size);
    kopirka(&ubiv1[size], &ubiv2[size], &ubiv3[size], size);
    kopirka(&vozubiv1[size], &vozubiv2[size], &vozubiv3[size], size);

    schetShell(randarr1, &k);
    schetShell(vozrast1, &k);
    schetShell(ubiv1, &k);
    schetShell(vozubiv1, &k);

    schetQs(randarr2, &k);
    schetQs(vozrast2, &k);
    schetQs(ubiv2, &k);
    schetQs(vozubiv2, &k);
    
    schetQsort(randarr3, &k);
    schetQsort(vozrast3, &k);
    schetQsort(ubiv3, &k);
    schetQsort(vozubiv3, &k);

    printf("       |  rand |  voz  |  ub   |  vu   |\n-----------------------------------------\n");
    printf(" shell | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n", vremya[0], vremya[1], vremya[2], vremya[3]);
    printf("   qs  | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n", vremya[4], vremya[5], vremya[6], vremya[7]);
    printf(" qsort | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n-----------------------------------------\n", vremya[8], vremya[9], vremya[10], vremya[11]);

    return 0;
}
