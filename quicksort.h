using namespace std;

void swap(int *a, int *b){
        if (*a != *b){
                *a ^= *b;
                *b ^= *a;
                *a ^= *b;
        }
}

int partition(int array[], int left, int right, int pivot){
        int newPivot = left;
        for (int i=left; i<right;i++){
                if (array[i] < array[pivot]){
                        swap(&array[i], &array[newPivot]);
                        newPivot++;
                }
        }
        swap(&array[newPivot], &array[pivot]);
        return newPivot;
}

void quicksort(int array[], int left, int right){
        if (left < right){
                int pivot = right;
                int newPivot = partition(array, left, right, pivot);

                quicksort(array, left, newPivot-1);

                quicksort(array, newPivot+1, right);
        }
}

void printArray(int array[], int length){
        for (int i=0;i<length;i++){
                cout<<array[i]<<",";
        }
        cout<<endl;
}

