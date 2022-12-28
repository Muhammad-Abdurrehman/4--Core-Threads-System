#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#define MAX_THREAD 4

int size;
int *arr;

void merge(int l, int m, int r)
{
int i, j, k;
int n1 = m - l + 1;
int n2 = r - m;
int L[n1], R[n2];

for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

i = 0;
j = 0;
k = l;
while (i < n1 && j < n2)
{
    if (L[i] <= R[j])
    {
        arr[k] = L[i];
        i++;
    }
else
    {
        arr[k] = R[j];
        j++;
    }
    k++;
}

while (i < n1)
{
    arr[k] = L[i];
    i++;
    k++;
}

while (j < n2)
{
    arr[k] = R[j];
    j++;
    k++;
}
}

void mergeSort(int l, int r)
{
if (l < r)
{
int m = l + (r - l) / 2;

    mergeSort(l, m);
    mergeSort(m + 1, r);

    merge(l, m, r);
}
}

void *thread_merge_sort(void *arg)
{
int thread_part = size / MAX_THREAD;
intptr_t l = (intptr_t)arg;
int r = l + thread_part;
mergeSort(l, r);
}

int main()
{
printf("Enter the size of the array: ");
scanf("%d", &size);

arr = (int *)malloc(size * sizeof(int));

printf("Enter the elements of the array: ");
for (int i = 0; i < size; i++)
    scanf("%d", &arr[i]);

pthread_t threads[MAX_THREAD];

for (int i = 0; i < MAX_THREAD; i++)
{
    int *arg = (int *)malloc(sizeof(*arg));
    *arg = i * (size / MAX_THREAD);
    pthread_create(&threads[i], NULL, thread_merge_sort, (void *)arg);
}

for (int i = 0; i < MAX_THREAD; i++)
    pthread_join(threads[i], NULL);
merge(0, size / 2, size - 1);

printf("Sorted array: ");
for (int i = 0;i < size; i++)
printf("%d ", arr[i]);

return 0;
}
