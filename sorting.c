#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int size) 
{
    int x, y, aux;
    int flag = 1;
    for (x = 0 ; x < size - 1; x++)
    {
        for (y = 0 ; y < size - x - 1; y++)
        {
            if (arr[y] > arr[y+1])
            {
                aux      = arr[y];
                arr[y]   = arr[y+1];
                arr[y+1] = aux;
                flag     = 0;
            } 
        }
        if (flag) 
            break;
    }
}

void insertionSort(int arr[], int size) 
{
    int i, j, aux;
    for(i = 1; i < size; i++) 
    {
        aux = arr[i];
        for(j = i - 1; j >= 0 && aux < arr[j]; j--) 
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = aux;
    }
}

void selectionSort(int arr[], int size) 
{
    int i, j, position, aux;
    for(i = 0; i < size - 1; i++)
    {
        position = i;
        for(j = i + 1; j < size; j++)
        {
            if(arr[position] > arr[j])
                position = j;
        }
        if(position != i)
        {
            aux = arr[i];
            arr[i] = arr[position];
            arr[position]=aux;
        }
    }
}

/*
  Retirado de https://gist.github.com/olegon/27c2a880c9b932862e60ab5eb89be5b6
  Dado um vetor v e três inteiros i, m e f, sendo v[i..m] e v[m+1..f] vetores ordenados,
  coloca os elementos destes vetores, em ordem crescente, no vetor em v[i..f].
*/
void merge(int *v, int *c, int i, int m, int f) {
    int z,
    iv = i, ic = m + 1;

    // transfere os elementos de i a f para o array auxiliar
    for (z = i; z <= f; z++) 
        c[z] = v[z];

    z = i;

    // enquanto existirem elementos nas duas metades
    while (iv <= m && ic <= f) {
        if (c[iv] <= c[ic]) v[z++] = c[iv++];   // v[z] = c[iv] seguido de iv++ e z++
        else v[z++] = c[ic++];
    }

    // se restaram elementos na primeira metade, faça o append
    while (iv <= m) 
        v[z++] = c[iv++];

    // se restaram elementos na segunda metade, faça o append
    while (ic <= f) 
        v[z++] = c[ic++];
}

// ordena v[i...f] com o auxílio de c[]
void sort(int *v, int *c, int i, int f) {
    // Condição de parada
    if (i >= f) return;

    int m = (i + f) / 2; 

    sort(v, c, i, m);        
    sort(v, c, m + 1, f);

    // Se v[m] <= v[m + 1], então v[i..f] já está ordenado.
    if (v[m] <= v[m + 1]) return;

    merge(v, c, i, m, f);
}

// ordena arr[] de tamanho size
void mergeSort(int arr[], int size) {
    int *c = malloc(sizeof(int) * size);
    sort(arr, c, 0, size - 1);
    free(c);
}

void lomutoQuickSort_r(int arr[],int start,int end){
    if (start >= end) return;

    int pivot = arr[end];
    int swp;
    //set a pointer to divide array into two parts
    //one part is smaller than pivot and another larger
    int pointer = start;
    int i;
    for (i = start; i < end; i++) {
        if (arr[i] < pivot) {
            if (pointer != i) {
                //swap a[i] with a[pointer]
                //a[pointer] behind larger than pivot
                swp = arr[i];
                arr[i] = arr[pointer];
                arr[pointer] = swp;
            }
            pointer++;
        }
    }
    //swap back pivot to proper position
    swp = arr[end];
    arr[end] = arr[pointer];
    arr[pointer] = swp;
    lomutoQuickSort_r(arr, start, pointer - 1);
    lomutoQuickSort_r(arr, pointer + 1, end);
}

void lomutoQuickSort(int arr[], int size){
    lomutoQuickSort_r(arr, 0, size);
}

void hoareQuickSort_r(int arr[], int start, int end)
{
    int i = start, j = end, aux, m, x;
    m = (start + end) / 2;
    x = arr[m]; //pivot
    // Hoare’s Partition 
    while (i <= j)
    {
        if (arr[i] < x) i++; // até encontrar um valor maior ou igual o pivot
        else if (arr[j] > x) j--; // até encontrar um valor menor ou igual o pivot
        else {
            // troque os valores
            aux = arr[i];
            arr[i++] = arr[j];  
            arr[j--] = aux;
        }
    }

    if (start < j)
        hoareQuickSort_r(arr, start, j);
    if (end > i)
        hoareQuickSort_r(arr, i , end);
}

void hoareQuickSort(int arr[], int size){
    hoareQuickSort_r(arr, 0, size);
}

void showArray(int arr[], int size) 
{
    int x;
    for(x = 0; x < size; x++)
    {
        if (x % 20 == 0) 
            printf("\n");
        printf("%8d", arr[x]);
    }
}

void measureTime(int arr[], int size, void (*sortFunction)(int arr[], int)) 
{
    clock_t t;
    double time_taken;

    t = clock();
    sortFunction(arr, size);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("\nLevou %f segundos para ordenar", time_taken);
}

int *createRandomArray(int size) 
{
    int *array = (int*) malloc(size * sizeof(int));
    int i, r;
    for (i = 0; i < size; i++) 
    {
        r = rand() % 32768; // máximo para essa library é 32767
        array[i] = r;
    }
    return array;
}

int *createReverseArray(int size) 
{
    int *array = (int*) malloc(size * sizeof(int));
    int i, r;
    r = 0;
    for (i = size - 1; i >= 0; i--) 
    {
        array[i] = r;
        r++;
    }
    return array;
}

void menu() 
{
    int size, option, type, *array;
    start:
    do 
    {
        printf("\nEscolha o tamanho do array: \n");
        scanf("%d", &size); 
        while (getchar() != '\n');

    } while (size <= 0);

    do 
    {
        printf("\nEscolha o tipo do array: ");
        printf("\n1 - Aleatorio");
        printf("\n2 - Reverso\n");
        scanf("%d", &type);
        while (getchar() != '\n');

        switch (type)
        {
            case 1:
                array = createRandomArray(size);
                break;
            case 2:
                array = createReverseArray(size); 
                break;
            default:
                printf("\nIncorreto, tente novamente.\n");
        }
    } while (type < 1 || type > 2);

    do 
    {
        printf("\n\nEscolha: ");
        printf("\n1 - Mostrar o array");
        printf("\n2 - Bubble Sort");
        printf("\n3 - Insertion Sort");
        printf("\n4 - Selection Sort");
        printf("\n5 - Merge Sort");
        printf("\n6 - Quick Sort (Lomuto)");
        printf("\n7 - Quick Sort (Hoare)");
        printf("\n9 - Novo array");
        printf("\n0 - Sair\n\n");
        scanf("%d", &option); 
        while (getchar() != '\n');

        switch (option)
        {
            case 0:
                break;
            case 1:
                showArray(array, size);
                break;
            case 2:
                measureTime(array, size, bubbleSort);
                break;
            case 3:
                measureTime(array, size, insertionSort);
                break;
            case 4:
                measureTime(array, size, selectionSort);
                break;
            case 5:
                measureTime(array, size, mergeSort);
                break;
            case 6:
                measureTime(array, size - 1, lomutoQuickSort);
                break;
            case 7:
                measureTime(array, size - 1, hoareQuickSort);
                break;
            case 9: 
                free(array);
                goto start;    // evitar goto sempre que possível
            default:
                printf("\nIncorreto, tente novamente.");
                break;
        }
    } while (option != 0);
}

void main()
{
    menu();
}