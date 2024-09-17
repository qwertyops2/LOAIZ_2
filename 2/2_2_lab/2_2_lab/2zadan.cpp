#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int size = 100000;
int randarr1[size], randarr2[size], randarr3[size];
int vozrast1[size], vozrast2[size], vozrast3[size];
int ubiv1[size], ubiv2[size], ubiv3[size];
int vozubiv1[size], vozubiv2[size], vozubiv3[size];
int vremya[12];

void zaparr(int a[], int b[], int c[], int d[], int size)
{
    int i;
    srand(time(NULL));
    for (i=0; i < size; i++) {
        a[i] = rand() % 1000;
        b[i] = i;
        c[i] = size - i;
        if ((i) < (size / 2)) { d[i] = i; }
        else { d[i] = size - i - 1; }
    }

}

void print(int a[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
}

void kopirka(int a[], int b[], int c[], int size)
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

int main() {
    int k = 0;

    zaparr(&randarr1[size], &vozrast1[size], &ubiv1[size], &vozubiv1[size], size);

    kopirka(&randarr1[size], &randarr2[size], &randarr3[size], size);
    kopirka(&vozrast1[size], &vozrast2[size], &vozrast3[size], size);
    kopirka(&ubiv1[size], &ubiv2[size], &ubiv2[size], size);
    kopirka(&vozubiv1[size], &vozubiv2[size], &vozubiv3[size], size);

    clock_t start = clock();
    shell(randarr1, size);
    clock_t end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;
    
    start = clock();
    shell(vozrast1, size);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    start = clock();
    shell(ubiv1, size);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    start = clock();
    shell(vozubiv1, size);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    //----------------------------------

    start = clock();
    qs(randarr2, 0, size - 1);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    start = clock();
    qs(vozrast2, 0, size - 1);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    start = clock();
    qs(ubiv2, 0, size - 1);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    start = clock();
    qs(vozubiv2, 0, size - 1);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    //----------------------------------

    start = clock();
    qsort(randarr3, size, sizeof(int), compare);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    start = clock();
    qsort(vozrast3, size, sizeof(int), compare);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    start = clock();
    qsort(ubiv3, size, sizeof(int), compare);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;
    k++;

    start = clock();
    qsort(vozubiv3, size, sizeof(int), compare);
    end = clock();
    vremya[k] = (double)(end - start) / CLOCKS_PER_SEC;

    printf("       |  rand |  voz  |   ub  |   vu  |\n----------------------------\n");
    printf(" shell | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n----------------------------\n", vremya[0], vremya[1], vremya[2], vremya[3]);
    printf("   qs  | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n----------------------------\n", vremya[4], vremya[5], vremya[6], vremya[7]);
    printf(" qsort | %3.3lf | %3.3lf | %3.3lf | %3.3lf |\n----------------------------\n", vremya[8], vremya[9], vremya[10], vremya[11]);

    //print(&randarr1[size], size);
    //printf("\n");
    //print(&vozrast1[size], size);
    //printf("\n");
    //print(&ubiv1[size], size);
    //printf("\n");
    //print(&vozubiv1[size], size);
    //printf("\n");

    return 0;
}