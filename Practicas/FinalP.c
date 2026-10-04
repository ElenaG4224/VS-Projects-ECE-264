# include <stdio.h>

int main()
{
    return 0;
}

void swap (int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;

}


int select_sort(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        int small = i;
        for (int j = 0; j< size; j++)
        {
            if (arr[j] < arr[i])
            {
                small = j;
            }

        }
        if (small != i)
        {
            swap (&arr[i], &arr[small]);
        }

    }
}

void quick_sort ( int * arr, int first, int last) // recursive! first and last are indexes.
{
    int p = arr[first];
    int low = first + 1;
    int high = last;

    while (low < high) //while the indexes are not overlappping
    {
        while ((low < last) &&(arr[low] <= p)) //move low
        {
            low++;
        }
        while ((first < high) && (arr[high] > p)) //mive high
        {
            high--;
        }

        if (low < high) // swap if low and high havent crossed
        {
            swap(&arr[low], &arr[high]);
        }
    }

    if (p > arr[high]) //move pivot to be between lower and higher values (remember that low and high have switched)
    {
        swap(&arr[first], &arr[high]);
    }

    quick_sort(arr, first, high - 1); // recursive sort values less than/before pivot
    quick_sort(arr, low, last); //recursiveley sort values greater than/ after the pivot

    return;
}

void merge_sort (int arr[], int left, int right) //recursive! lefts and rights are indexes
{
    if (left < right)
    {
        int mid = (left + right) / 2; // find middle index
        merge_sort(arr, left, mid);//subdivide arrays to single elements
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right); //sort subdivisions as they join back
    }

}

void merge (int arr[], int left, int mid, int right) //recursive! lefts and rights are indexes
{
    int size = right - left + 1;
    int *temp = malloc(size * sizeof(int)); // allocate space for merged array
    //handle malloc failiure

    int i = left; //left subarray
    int j = mid+1; //right subarray
    int k = 0; //used for temp array

    while (i <= mid && j <= right) // sorts until one of the sub-arrays is finished, filling in temp
    {
        if(arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) //populates the rest of temp from the remaining subarray.(this will be sorted from a previous breakdown)
    {
        temp[k++] = arr[i++];
    }
    while (j <= right) // case for the other subarray being left over instead.
    {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) // move sorted array back into passed memory, free temp array
    {
        arr[i] = temp[k];
    }
    free(temp);

}