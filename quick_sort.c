int a[101],n;//定义全局变量，这两个变量需要在子函数中使用
void quick_sort(int left,int right){

int i,j,t,pivot;
if(left > right)
   return;
                                
pivot = a[left]; //pivot中存的就是基准数
i = left;
j = right;
while(i != j){
    //顺序很重要，要先从右边开始找
    while(a[j] >= pivot && i < j)
        j--;
    //再找左边的
    while(a[i] <= pivot && i < j)
        i++;
    //交换两个数在数组中的位置
    if(i < j){
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}
//最终将基准数归位
a[left] = a[i];
a[i] = pivot;

quick_sort(left, i - 1);//继续处理左边的，这里是一个递归的过程
quick_sort(i + 1, right);//继续处理右边的 ，这里是一个递归的过程
}