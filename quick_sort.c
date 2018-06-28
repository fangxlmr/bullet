#include <stdio.h>

void qsort(int *, int, int);
int main (void) {
    int a[] = {5, 4, 3, 2, 1};
    int len = sizeof(a) / sizeof(int);

    qsort(a, 0, len - 1);
    for (int i = 0; i < len; ++i) {
        printf("%d, ", a[i]);
    }
    return 0;
}

/*
void quick_sort(int *v, int left, int right)
{
    int i, last;
    void swap(int *v, int i, int j);

    if (left >= right) {
        return;
    }
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if (v[i] < v[left]) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    quick_sort(v, left, last - 1);
    quick_sort(v, last + 1, right);
}


void swap(int *v, int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
*/

void qsort(int *nums, int left,int right){
    int i,j,pivot;

    if(left > right)
       return;

    pivot = nums[left]; //pivot中存的就是基准数
    i = left;
    j = right;
    while(i != j){
        //顺序很重要，要先从右边开始找
        while(nums[j] >= pivot && i < j)
            j--;
        //再找左边的
        while(nums[i] <= pivot && i < j)
            i++;
        //交换两个数在数组中的位置
        if(i < j){
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }
    //最终将基准数归位
    nums[left] = nums[i];
    nums[i] = pivot;

    qsort(nums, left,  i - 1);
    qsort(nums, i + 1, right);
}
