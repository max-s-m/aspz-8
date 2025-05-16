#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int compare(const void *, const void *);
int sorted(int *, int);
void fill_sorted(int *, int);
void fill_reverse(int *, int);
void fill_rand(int *, int);
void test(const char *, void (*fill_func)(int*, int), int);

int main(){
    srand(time(NULL));
    int sizes[] = {100000, 500000, 1000000};
    int num_sizes = sizeof(sizes)/sizeof(sizes[0]);
    //тестування масивів різних розмірів та сортованості
    for(int i=0; i<num_sizes; i++){
        int n = sizes[i];
        test("Sorted", fill_sorted, n);
        test("Reversed", fill_reverse, n);
        test("Random", fill_rand, n);
    }
}
//порівняння для qsort
int compare(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}
//перевірка чи масив сортований
int sorted(int *arr, int n){
    for(int i=1; i<n; i++){
        if(arr[i-1] > arr[i]){
            return 0;
        }
    }
    return 1;
}
//заповнюється сортований масив
void fill_sorted(int *arr, int n){
    for(int i = 0; i < n; i++) arr[i] = i;
}
//сортований, але в спадаючому порядку
void fill_reverse(int *arr, int n){
    for(int i = 0; i < n; i++) arr[i] = n - i;
}
//рандомний масив
void fill_rand(int *arr, int n){
    for(int i = 0; i < n; i++) arr[i] = rand();
}
//перевірка правильності та швидкості роботи quick sort (qsort)
void test(const char *desc, void (*fill_func)(int*, int), int n) {
    int *arr = malloc(n * sizeof(int));
    fill_func(arr, n);
    //засікання часу сортування
    clock_t start = clock();
    qsort(arr, n, sizeof(int), compare);
    clock_t end = clock();
    //виведення даних
    double total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s,   n = %d,   time = %.3f sec,   sorted: %s\n", desc, n, total, sorted(arr, n) ? "yes" : "no");
    free(arr);
}



