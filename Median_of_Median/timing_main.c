#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NOT_FOUND  -99999999
#define debug 0
#define GROUP_SIZE 5
#define MAX_N  10000000



void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swapArray(int data[],int index1,int index2){
    int temp =0;
    temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

int selectK_ByQuicksortPartition(int data[],int start,int end,int k){
    # if debug
    printf("start=%d ,end=%d ,k=%d \n",start,end,k);
    # endif // debug

    if (start > end || k > (end - start +1) ) return NOT_FOUND;  // shit for debugging

    int pivotIndex = algoPartition(data,start,end);
    int pivotSequenceNo = pivotIndex - start +1;

    # if debug
       printf("start=%d ,end=%d ,k=%d ,pivotIndex=%d ,pivotSequenceNo=%d , =>",start,end,k,pivotIndex,pivotSequenceNo);
       int i=0;
       for (i=start;i<=end;i++){
            printf(" %d",data[i]);
       }
       printf("\n");
    # endif // debug

    if (k == pivotSequenceNo){

      return data[pivotIndex]; // shit for debugging
    }else if( k< pivotSequenceNo){
        return selectK_ByQuicksortPartition(data, start, pivotIndex -1, k );
    }else{
        return selectK_ByQuicksortPartition(data,pivotIndex+1,end, k - pivotSequenceNo  );
    }

}

int selectK_AfterSorting(int data[],int start,int end,int k){
    if (start > end || k > (end-start+1) ) {
        printf("selectK_AfterSorting s=%d, e=%d, k=%d \n",start,end,k);
        return NOT_FOUND;
    }

    quickSort(data,start,end);
    int kIndex = end-k +1;
    return data[kIndex];
}


int selectK_ByMedianOFMedian(int data[],int start,int end,int k){
    if (start > end || k >(end-start+1)  ) {
        printf("selectK_ByMedianOFMedian s=%d, e=%d, k=%d \n",start,end,k);
        return NOT_FOUND;
    }

    int median = findMedian(data,start,end);
    int medianIndex = findMedainIndexInArray(data,start,end,median);
     # if debug
      printf("  ##  1  ");
      printf("medianIndex=%d ,end=%d \n",medianIndex,end);
    # endif // debug
    swapArray(data,medianIndex,end); // because we assume that default pivot for partition is located in the rightest side.

     # if debug
    printf("start=%d ,end=%d ,k=%d ,median=%d, medianIndex=%d , ",start,end,k,median,medianIndex);
    int i=0;
    for (i=start;i<=end;i++){
        printf(" %d",data[i]);
    }
    printf("\n");
    # endif // debug

    medianIndex = algoPartition(data,start,end);
    # if debug
    printf("  ## 2  ");
    # endif // debug

    int medianIndexSequenceNo = end - medianIndex +1;

    # if debug
       printf("start=%d ,end=%d ,k=%d ,median=%d, medianIndex=%d ,medianIndexSequenceNo=%d , =>",start,end,k,median,medianIndex,medianIndexSequenceNo);
       for (i=start;i<=end;i++){
            printf(" %d",data[i]);
       }
       printf("\n");
    # endif // debug


    if (k== medianIndexSequenceNo){
        return data[medianIndex];
    }else if ( k > medianIndexSequenceNo){
        return selectK_ByMedianOFMedian(data,start,medianIndex -1,k-medianIndexSequenceNo);
    }else{
        return selectK_ByMedianOFMedian(data,medianIndex+1,end, k );
    }
}

int insertionSort(int data[],int start,int end){
    int i=start+1,j=NOT_FOUND;
    int value = NOT_FOUND;
    for (i;i<=end;i++){
        value = data[i];
        j=i-1;
        while(value < data[j]){
            data[j+1]= data[j];
            j--;
        }
        data[j+1]=value;// shit for debugging
    }
}

int findMedian(int data[],int start,int end){

   if (start <=0 && end<= 0){
        printf("findMedian start=%d, end=%d \n",start,end);
   }

   int medianNum = ( (end -start+1) + (GROUP_SIZE-1) )/ GROUP_SIZE;
   int median[medianNum];
   memset(median, NOT_FOUND,sizeof(median));

   int i=0;
   int s=0,e=0,m=0;
   for (i=0;i<medianNum;i++){
        s= (i* GROUP_SIZE)+start;
        e= (s+GROUP_SIZE -1);
        if (e >end){
            e=end;
        }
       insertionSort(data,s,e);
       m= (s+e)/2;
       median[i]=data[m];
   }

   # if debug
     printf("medianNum=%d \n",medianNum);
   # endif // debug
   if (medianNum ==1){
      # if debug
        printf("media=%d \n",median[0]);
      # endif // debug
       // for data size is less than and equals with 5.
       return median[0];
   }else{
       return findMedian(median,0,medianNum-1);
   }
}

int findMedainIndexInArray(int data[],int start,int end, int median){
    int i=start;
    for (i=start;i<=end;i++){
        # if debug
        printf("i=%d ,data[%d]=%d  ",i,i,data[i]);
        # endif // debug
        if (median ==data[i]){
            return i;
        }
    }
    return NOT_FOUND;
}



void quickSort(int data[],int start,int end){
    if (start >=end ) return;
    int pivotIndex = algoPartition(data,start,end);
    quickSort(data,start,pivotIndex-1);
    quickSort(data,pivotIndex+1,end);
}

int dsPartition(int data[],int start,int end){
    int i=0,j=end-1,pivot=data[end];

    while (1){
        while (data[i]<= pivot){
            i++;
        }
        while (data[j]> pivot){
            j--;
        }
           # if debug
             printf("i=%d,j=%d \n",i,j);
           # endif // debug
          if (i<j){
            swapArray(data,i,j);
          }else{
              break;
          }
          //swap(data[i],data[j]);
    }
    swapArray(data,i,end);
    //swap(data[i+1],data[end]);
    // return index for pivot's location in array.
    return i;
}

int algoPartition(int data[],int start,int end){
    int i=start-1, j=start, pivot=data[end];

    for (j=start;j< end ; j++){
        if (data[j]<= pivot){
                 # if debug
                printf("swapArray %d ,%d",data[i+1],data[j]);
                 # endif // debug
            swapArray(data, ++i,j);
        }
    }
    swapArray(data,++i,end);
    // return index for pivot's location in array.
    return i;
}



int testData1[MAX_N];
int testData2[MAX_N];
int sortData[MAX_N];

void resetTestData(){
    int i=0;
    for (i=0;i<MAX_N;i++){
        testData1[i]= 0;
        testData2[i]= 0;
        sortData[i]= 0;
    }
}

int checkRepted(int i, int series[],int temp){
    int j;
    for(j=0; j<i; j++){
        if(series[j]==temp)
        return 1;
    }
    return 0;
}


void randSerirs(int n){
    int i,seed;
    int series[n];
    seed = (unsigned)time(NULL); // 取得時間序列
    srand(seed); // 以時間序列當亂數種子
    for(i=0; i<n; i++){
        int temp=rand();
        /*check not repeated, repeated=1, else=0*/
        while(checkRepted(i, series, temp)){
           temp=rand();
        }
        testData1[i]=temp;
        testData2[i]= temp;
        sortData[i]=temp;
        //printf("%d=%d , ",i,temp);
    }
    printf("\n");
}



int main(){
    clock_t start, end;


    freopen("out.txt","w",stdout);
    //randGenerator2(30, 99);

    printf("RAND_MAX=%d\n", RAND_MAX);

    int n = 100000;
    n = 32000 ;
    n= 7000;
    int endIndex = n -1;
    start = clock();

    int aa= n;
    for (aa=n;aa<=32000; aa =aa+1000 ){

    resetTestData();
    randSerirs(aa);
    end = clock();
    double diff = end - start; // ms
    /*
    printf("### generate rand %lf  ms  \n" ,diff);
    printf("### %lf  sec \n", diff / CLOCKS_PER_SEC );


    insertionSort(sortData,0,endIndex);
    int j=0;

    printf("==============================================================\n");
    printf("==============================================================\n");
    printf("==============================================================\n");
    printf("Sort data: ");

    int x =1;
    for (j=endIndex ;j>=0;j--){
        printf("%d=%d , ",x++,sortData[j]);
    } # endif // debug
    */
    /*
    printf("\n");
    printf("==============================================================\n");
    printf("==============================================================\n");
    printf("==============================================================\n");
    */
    # if debug
    printf("1 endIndex=%d \n",endIndex);


    printf("2 \n");
    # endif

    start = clock();
    int k= 55;
    int value = selectK_ByMedianOFMedian(testData1, 0,endIndex ,k);
    # if debug
    printf("3 \n");
    # endif // debug
    end = clock();
    diff = end - start; // ms
    printf("### n=%d , k=%d , mOFm value=%d , %lf  ms  , ",aa ,k,value,diff);
    printf("mOFm= %lf  sec \n", diff / CLOCKS_PER_SEC );

    start = clock();
    value = 0; diff = 0; end =0;
    value = selectK_AfterSorting(testData2, 0, endIndex,k);
    end = clock();
    diff = end - start; // ms
    printf("### n=%d , k=%d , sorting value =%d , %lf  ms  , ",aa ,k,value ,diff);
    printf("sorting= %lf  sec \n", diff / CLOCKS_PER_SEC );

    }
}







int a[] = {1,11,5,12,4,3,9};
//int a[] = {3,1,3,2,4,5,6,3,7,10,3,8,9,11,3,4,21,3,3,3,3};

void resetArray(){
    a[0]= 1;
    a[1]=11;
    a[2]=5;
    a[3]=12;
    a[4]=4;
    a[5]=3;
    a[6]=9;
}



