#include <stdio.h>

void qsort (int v[], int left, int right);
void swap(int v[], int i, int j);

int main(int argc, char **argv) {
//    int a[]={12,42,54,3,5,32,61,24,31};
    int a[] = {7, 2, 3, 9, 5, 8, 10, 6, 4, 1};

    qsort(a, 0, 9);
    int i;  
    for(i=0; i<=9; i++) {  
	printf("%d\n",a[i]);  
    }
    return 0;
}

/* sqort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right) {
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)
	return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
	if (v[i] < v[left])
	    swap(v, ++last, i);
    swap (v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j) {
    int temp; 
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
