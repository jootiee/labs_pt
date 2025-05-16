#ifndef SORTS_H
#define SORTS_H

#include <algorithm>

/**
 * Select sort
 * @param a array to sort
 * @param size size of the array
 */
template <class T>
void selectSort(T a[], size_t size)
{
    long i, j, k;
    T x;
    for (i = 0; i < size - 1; i++)
    {
        k = i;
        x = a[i];
        for (j = i + 1; j < size; j++) // loop for searching minimal element
            if (a[j] < x)
                k = j;
        x = a[j]; // k - minimal element index
        a[k] = a[i];
        a[i] = x; // swap minimal element and a[i]
    }
}

/**
 * Building pyramid
 * @param k start index
 * @param n end index
 */
template <class T>
void downHeap(T a[], long k, long n)
{
    T new_elem;
    long child;
    new_elem = a[k];

    while (k <= n / 2)
    {
        child = 2 * k;
        if (child < n && a[child] < a[child + 1])
            child++;

        if (new_elem >= a[child])
            break;

        a[k] = a[child];
        k = child;
    }
    a[k] = new_elem;
}

/**
 * Heap sort
 * @param a array to sort
 * @param size size of the array
 */
template <class T>
void heapSort(T a[], size_t size)
{
    long i;
    T temp;

    for (i = size / 2 - 1; i >= 0; i--)
        downHeap(a, i, size - 1);

    for (i = size - 1; i > 0; i--)
    {
        std::swap(a[i], a[0]);
        downHeap(a, 0, i - 1);
    }
}

/**
 * Merging two sorted arrays
 * @param a array to sort
 * @param low start index
 * @param mid middle index
 * @param high end index
 */
template <class T>
void merge(T a[], long low, long mid, long high)
{
    T *b = new T[high + 1 - low];
    long h, i, j, k;
    h = low;
    i = 0;
    j = mid + 1;
    while ((h <= mid) && (j <= high))
    {
        if (a[h] <= a[j])
        {
            b[i] = a[h];
            h++;
        }

        else
        {
            b[i] = a[j];
            j++;
        }
        i++;
    }

    if (h > mid)
    {
        for (k = j; k <= high; k++)
        {
            b[i] = a[k];
            i++;
        }
    }

    else
    {
        for (k = h; k <= mid; k++)
        {
            b[i] = a[k];
            i++;
        }
    }

    for (k = 0; k <= high - low; k++)
        a[k + low] = b[k];

    delete[] b;
}


/**
 * Merge sort
 * @param a array to sort
 * @param low start index
 * @param high end index
 */
template <class T>
void mergeSort(T a[], long low, long high)
{
    long mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

/**
 * Standard sort
 * @param a array to sort
 * @param size size of the array
 */
template <class T>
void standartSort(T *a, size_t size)
{
    std::sort(a, a + size);
}

#endif