#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
# define SIZE (256)
# define LOCATION  ("./")
# define DEBUG_SINGAL (0)

struct NodeStruct{
   unsigned int frequency;
   int value;
   char*	code;
   struct Node* left;
   struct Node*  right;
};
typedef struct NodeStruct Node;


typedef struct HeapStruct{
   int size;
   Node** lists;
} Heap;



//node nodes[SIZE] = {{-1,-1,NULL, NULL, NULL}};
Node nodes[SIZE] = {{0}};
//Heap heap ={0};

void testFileIO_9149(){
    FILE * fout = fopen("./testIn.bin", "w");  
    int i=0;
    for(; i<256;i++){
     	fputc( (unsigned char)i ,fout); 
    }
    fclose(fout);

    FILE * fin = fopen("./testIn.bin" , "rb");
    int byte = -1;
    while ( (byte = fgetc(fin)) != EOF ){
         printf("%d, ",byte);
    }
    fclose(fin);

}


void swap_9149(Node **node1 , Node **node2 /** debugging **/ ){
    Node* tmp = *node1; /** debugging **/
    *node1 = *node2;  /** debugging **/
    *node2 = tmp;  /** debugging **/
}

void doDownHeapfy_9149(Heap* heap, int parentIdx){
   int leftIdx =  -1; 
   int rightIdx = -1;
   int minIdx  = parentIdx;
   

    while(parentIdx <= ( heap->size /***debugging heap.size -> heap->size **/ -1)) {
          
        leftIdx = parentIdx *2 + 1; /** debugging for forgetting plus 1 **/
        rightIdx = leftIdx +1;

        if ( leftIdx <= (heap->size -1)   &&  heap->lists[leftIdx]->frequency < heap->lists[minIdx]->frequency ){
            minIdx = leftIdx;
        }
        
        if ( rightIdx <= (heap->size -1) && heap->lists[rightIdx]->frequency < heap->lists[minIdx]-> frequency ){
             minIdx = rightIdx;
        }

        if (minIdx != parentIdx){
            swap_9149( &heap->lists[minIdx] , &heap->lists[parentIdx]); 
            parentIdx = minIdx;
        }else{
            break;
        }

    }
}

void doUpHeapfy_9149(Heap* heap, int parentIdx){
     int minIdx = parentIdx;
     int leftIdx = -1;
     int rightIdx = -1;

     while( parentIdx >=0){
         leftIdx = parentIdx *2 +1;
         rightIdx = leftIdx +1;

         if (leftIdx < heap->size && heap->lists[leftIdx]->frequency < heap->lists[minIdx]->frequency){
            minIdx = leftIdx;
         }

         if (rightIdx < heap->size && heap->lists[rightIdx]->frequency < heap->lists[minIdx]->frequency){
             minIdx = rightIdx;
         }

         if (minIdx != parentIdx){
            swap_9149( &heap->lists[minIdx] , &heap->lists[parentIdx]); 
            parentIdx = (parentIdx -1 ) /2;
            minIdx = parentIdx;  /// key for debugging for a long time.
         }else{
            break;
         }

     }


}

Node* extractMin_9149(Heap* heap){
    if (heap->size <=0) return NULL;
    Node* returnNode  = heap->lists[0];
    heap->lists[0] = heap->lists[heap->size -1];
    heap->size = heap->size -1;
    doDownHeapfy_9149(heap, 0);
    return returnNode;

}

void addHeapNode_9149(Heap* heap, Node* newNode){
    heap->lists[ heap->size++] = newNode;
    int parentIdx = ((heap->size -1 ) -1) /2; 
    doUpHeapfy_9149(heap, parentIdx);
}

Heap* createHeap_9149(int size){
printf("Func #### createHeap()\n");
     Heap* heap = (Heap*) malloc(1 * sizeof(Heap *) );  
     heap->size = size;
     heap->lists = (Node **) malloc(size * sizeof(Node *));
      
     int i=0;
     for ( ; i< size;i++){
         heap->lists[i]=NULL;
     }

     int j=0;
     for ( i=0; (i< SIZE) && (j < heap->size);i++){  //debugging using || so stupid!!
        if (nodes[i].frequency ==0){
            continue;
        }
        heap->lists[j++] = &nodes[i];  // error --> debugging!!
        //printf("i=%d \n",i);
     }

      if (DEBUG_SINGAL)  printf("Should be the same. j=%d == heap.size =%d; \n",j , heap->size);

     if ( j  != heap->size){
         printf("heap can not be initialized successfully. \n");
         heap->size = 0;
         return heap;
     }

     if (DEBUG_SINGAL)  printf("Should be the same. j=%d == heap.size =%d; \n",(j-1) , heap->size);


     if (DEBUG_SINGAL){
        for ( i=0; i< heap->size;i++){
             printf("heap.lists[%d] value=%d,frequency=%llu,\n",i,heap->lists[i]->value /* error--> debugging */ , heap->lists[i]->frequency);
        }
        printf("#######  finishing heapfy!! \n");
     }


     int lastParentNode = ( (heap->size -1) -1 ) / 2;

     for ( ; lastParentNode >=0 ; lastParentNode--){
            doDownHeapfy_9149(heap , lastParentNode);
     }

     return heap;
      
}


Node* builtHuffmanTree_9149(Heap* heap){
     printf("Func #### builtHuffmanTree()\n");
    Node *left = NULL;
    Node *right =NULL;     
    
    while( heap->size > 1){
         // printf("heap->size=%d, \n",heap->size);
         left = extractMin_9149(heap); 
         right = extractMin_9149(heap);
         // printf("extract two, heap->size=%d, \n",heap->size);
         // fflush(stdout);
         Node* newNode = (Node *) malloc(1 * sizeof(Node /***debugging not sizeof(Node*) **/)  );
         // printf("@@@@ \n");
         // fflush(stdout);
         newNode->left = left;
         newNode->right = right;
         newNode->frequency = left->frequency + right->frequency;
         newNode->value = -1;
         // printf("start addheapNode\n");
         addHeapNode_9149(heap, newNode);
         // printf("finish addheapNode\n");
    }

    Node* returnNode = extractMin_9149(heap);
    return returnNode;
}

char *stringConcat_9149(char *str1, char *str2) {

    int length=strlen(str1)+strlen(str2)+1;
    char *result = (char*)malloc(sizeof(char) * length);

    strcpy(result, str1);
    strcat(result, str2);

    return result;
}


void preorderTraversal_9149(Node * node, char * codes){
     //printf("Func #### preorderTraversal()--assign leaf codes.\n");
    if (codes != NULL){
        node->code = codes;
    }
    
    char* new = NULL;
    if (node->left != NULL){
        if (codes == NULL){
            new = "0";
        }else{
          new = stringConcat_9149(codes, "0");
        } 
        preorderTraversal_9149(node->left, new );
    }

    if (node->right !=NULL){
        if (codes == NULL){
            new = "1";
        }else{
           new = stringConcat_9149(codes, "1");
        }
        preorderTraversal_9149(node->right , new );
    }
}



 void inorderTraversalPirntOut_9149(Node * node){
      if (node == NULL){
         return;
      }
      printf(" freq=%lld, value=%d, code=%s, left=%p-isNull=%d, right=%p-isNull=%d \n",node->frequency, node->value, node->code, node->left, node->right,(node->left ==NULL), (node->right==NULL));  
      inorderTraversalPirntOut_9149(node->left );
      inorderTraversalPirntOut_9149(node->right);
 }






 unsigned int  readHeaderInfo_9149(FILE *file, int * size){
    printf("Func #### readHeaderInfo()\n");
    char len[5];  /** debugging char len* ---> segment fault**/
    char equal=0;
    char semicolon=0;
  
  
    fread( len, sizeof(char), 5, file );
    fread( size, sizeof(int), 1, file);
    fread( &semicolon, sizeof(char) , 1 , file);

    printf(" len=%s, size=%d, semicolon=%c, \n",len,*size,semicolon );

    int count = *size;
    
    int i=0;
    char byte=0;  // debugging take a long long time , byte -128  ~  +127, unsigned char ：  0  ~ 255
    unsigned int frequency = 0;
    for ( ;i< count  ;i++){    // debugging (*size)  so stupid!!!
        //printf("i:%d; ",i);
        fflush(stdout);
        fread(&byte, sizeof(char), 1, file);
        fread(&equal, sizeof(char), 1, file);
        fread(&frequency, sizeof(unsigned int) ,1,file);
        fread(&semicolon, sizeof(char), 1, file);
        nodes[(unsigned char)byte].frequency= frequency;
        nodes[(unsigned char)byte].value = (unsigned char)byte; // debugging for a long time for judge is leaf or not.
        if (DEBUG_SINGAL) printf("i:%d, nodes[ byte%d] , eaual:%c , frequency:%u , semicolon:%c  \n",i,(unsigned char) byte, equal, frequency , semicolon);
      
    }

    fseek(file,0, SEEK_CUR);

    unsigned int headerSize = 0;
    headerSize = ftell(file);

    return headerSize;

}


unsigned int  writeHeaderInfo_9149(FILE *file, int size ){
    printf("Func #### writeHeaderInfo()\n");
    char len[]="len=\0";
    char equal= '=';
    char semicolon= ';';
    fwrite( len, sizeof(char), 5, file);   //5 bytes
    fwrite(&size, sizeof(int) , 1 , file); //4 bytes
    fwrite( &semicolon , sizeof(char), 1, file); // 1 bytes
    
    int i=0;
    for (;size >0 && i<(SIZE)  ;i++){
        if (nodes[i].frequency ==0 ){
            continue;
        }
        fwrite(&i, sizeof(char), 1, file); // 1 byte
        fwrite(&equal, sizeof(char), 1, file);  // 1 byte
        fwrite(&nodes[i].frequency, sizeof(unsigned int) ,1,file); //4bytes
        fwrite(&semicolon, sizeof(char), 1, file); // 1byte
        --size;
    }
    
    fseek(file,0, SEEK_CUR);
    unsigned int headerSize = 0;
    headerSize = ftell(file);

    return headerSize;
    /// (5+4+1) + N *(1+1+4+1)
    ///  10 + (N * 7) 

}

int cutString_9149(char* src, int start, int len){
    int length = strlen(src);

    // printf("cutString 1, len=%d\n",length);
    fflush(stdout);

    if (len <0){
        len = length - start;
    } 
    if ( (start + len) > length){
          len = length - start;
    } 
    // printf("cutString 2\n");
    fflush(stdout); 

    memmove(src+start, src+(start+len) , (length - len +1) );
     
    //printf("cutString 3\n");
    fflush(stdout);
    return len;
}

int binaryStrToInt_9149(char * str){

     /*
     // slower method by calculation, not shift!!
     int unit = 1;
     int value = atoi(str);
     int result =0;
      
     int i=0; 
     while(value >0){
        result +=  (value % 10) * unit;
        unit *= 2;
        value /= 10; 
        //printf("i=%d, result=%d, unit=%d, value=%d, \n", i, result, unit, value);
     } 
     //printf("result=%d, \n", result);
     */

    
     // quick
    int i=0;
    int len = strlen(str);
    int result = 0;
    for( i=0; i<len; i++ ){
         result <<= 1; 
         if(str[i] == '1'){
            result |= 1;
        }   
    }
    //printf("result=%d, len=%d, %s\n",result,len,bits);
    

     return result;
}


char* intToString_9149(int value, char* str){
    sprintf(str,"%d",value);
}

void intToBinaryStr_9149(char * array, int num){

    /*
    /// slow way to convert int to binary array.
     char * returnStr = "";

     if (num ==0){
        return "0";
     }else if (num == 1){
        return "1";
     }
     
     //char valueStr[256];
     int value =0;
     while(num >0){
         value = num %2 ;
         num= num / 2;
         //intToString(value,valueStr);
         returnStr = stringConcat( (value ==0 ) ? "0" : "1" ,returnStr );
     } 
     
       no need to transfer to original codes. for validate original codes only.
     int len = strlen(returnStr);
     while(len <8){
        returnStr =stringConcat("0",returnStr);
        len = strlen(returnStr);
     } 
     */


     

     array[8]='\0';
     int i=0;

     for (i = 0; i < 8; ++i) {  
         array[7-i] = num & (1 << i) ? '1' : '0';
     }

    //printf("num=%d, array=%s#\n",num,array);
}

char* subString_9149(const char* src, unsigned int start, unsigned len){
     int length = strlen(src);
     if ( (start + len ) > len){
         len = length - start ;
     }
     char * result = (char*) malloc(  sizeof(char) * (len+1));
     strncpy(result, src+start, len);
     return result; 
}

unsigned char* intCharArrayToBinaryArray_9149(unsigned char * charArray, unsigned int dataSize ){
     printf("Func #### intCharArrayToBinaryArray()\n");
      unsigned int len = strlen(charArray);
      /** key for judge how much bits in the last bit **/
      unsigned int howManyLastBits = charArray[len-1];
      printf("howManyLastBits=%d, charArray len=%u, dataSize=%u\n",howManyLastBits, len,dataSize );

      if (len != dataSize){
        printf("Error Error Error Error ==>  charArray != dataSize \n");
        printf("Error Error Error Error ==>  charArray != dataSize \n");
      }

      unsigned char * returnBinaryArray = "";
      char * tmpChar = NULL;
      unsigned int i=0;
      for (;i<(dataSize-1);i++){
           
           ///tmpChar =intToBinaryStr( (unsigned char)charArray[i]);

           // debugging for alignments
           while( strlen(tmpChar) <8 ){
                tmpChar = stringConcat_9149("0",tmpChar );
           }

           //printf("charArray[%u]=%d -> %s \n",i ,(unsigned char)charArray[i], tmpChar );
           if (i == (len-2)){
             //  printf("#charArray[%u]=last bit -> orignal tmpChar=%s   ,",i,tmpChar);
               tmpChar = subString_9149(tmpChar, 0,howManyLastBits);
               //printf("#charArray[%u]=last bit -> updated tmpChar=%s   \n",i,tmpChar);
           }

           returnBinaryArray = stringConcat_9149(returnBinaryArray ,tmpChar );
      }
      return returnBinaryArray;
}





void test_String_9149(){
     // test 6
     int byte = -1;
    int size = 0;
     FILE * fin = fopen("./testIn.bin" , "rb");

    while ( (byte = fgetc(fin)) != EOF ){
         if (nodes[byte].frequency ==0 ){
            size++;
         }
         nodes[byte].value = byte;
         nodes[byte].frequency ++ ;
         printf("%d=%llu ; ",byte,nodes[byte].frequency);
    }

    FILE *fout=fopen("./data.bin.buff","wb"); //開啟檔案來寫

    fclose(fout);
    

    fin = fopen("./data.bin.buff" , "rb");
    int finSize =0;
    readHeaderInfo_9149(fin , &finSize);
    fclose(fin); 

     
   
     // test 5
     char * buff2="1111111";
     char *zero ="0";
     unsigned char encrptCodes2 =0;
     if ( strlen(buff2) != 0  ){
        while( strlen(buff2) <8){
             buff2 = stringConcat_9149(buff2, zero );
        } 
        encrptCodes2 = (unsigned char) binaryStrToInt_9149(buff2);
        printf("encrptCodes2=%d, buff2=%s, \n", encrptCodes2,buff2);
        fflush(stdout);
        cutString_9149(buff2,0,8);
     }


     // test1
    char *a1= "123456";
    char *a2;
    a2 = subString_9149(a1, 0,2);
    printf("a2=%s,\n",a2);       
  
     // test2
    char * str = "00000001";
     binaryStrToInt_9149(str);

     // test4
    char *a_1= "123456";
    char *b_1 ="abcdef";

    char* c_1 =stringConcat_9149(a_1,b_1);
    printf("c_1=%s, \n",c_1);

    int len = cutString_9149(c_1, 0,2);

    printf("a=%s, \n",c_1);


    // test 5
    int aa =56;
    char bb[3];
    intToString_9149(aa, bb);
    char * a ="1234";
    a = stringConcat_9149(a, "78");
    printf("a=%s, ",a);
    

   char *b = NULL;
  // b= intToBinaryStr(2);
   printf("2=%s###\n",b);

    int i=0;
    
    for (;i<256;i++){
         //b = intToBinaryStr(i);
         printf("%d=%s,\n",i,b);
         fflush(stdout);
    }

}



unsigned char * loadFile_9149(const char *path, unsigned int * fileSize ){

   FILE *fp;
   fp = fopen(path,"rb");

   if (fp == NULL){
       printf("[Error][loadFile] Cannot get file=%s.\n",path);
       fflush(stdout);
   }

   fseek(fp,0, SEEK_END);
   unsigned int totalSize = ftell(fp);
   rewind(fp);
   unsigned int dataSize = totalSize/ sizeof(unsigned char);

   unsigned char *data = (unsigned char*)malloc(dataSize * sizeof(unsigned char));



   if (data == NULL){
       printf("[Error][loadFile] Cannot malloc memory, file=%s.\n",path);
       fflush(stdout);
   }

   size_t readResultSize  = fread(&data[0], sizeof(unsigned char) ,dataSize, fp);
   *fileSize = readResultSize;



   fclose(fp);


    
    printf("[loadFile] file=%s, totalSize=%u, dataSize(by unsigned char) =%u, fileSize=%u, readResultSize=%u\n",path,totalSize,dataSize,fileSize, readResultSize);
    fflush(stdout);
    


    return data;


}



unsigned char * decode_9149( Node* huffmanTree ,unsigned char* binaryCodes, unsigned int * decodeSize){
        printf("Func #### decode()\n");
      printf("strlen(binaryCodes)=%u, decodeSize=%u \n",strlen(binaryCodes), *decodeSize);
     unsigned int i=0;
     Node* curr= huffmanTree ;
     unsigned char * returnArray= "";
     unsigned char  valueStr[2];

     *decodeSize=0;

    
     unsigned int j=0;
     for( i=0;i<= strlen(binaryCodes) ;i++){  // debugging not < is <= ,becasue last char need to be judged!!
          printf("i=%d, ",i);
         /// if (curr->right == NULL && curr->left == NULL){  //debugging for a long time, memory will not be initialized to be NULL;

        if (curr->value >=0 ){
             printf("leaf i=%d, ",i);
             printf("j=%d=> %d,%c; \n",++j, curr->value,curr->value);
             printf(" freq=%lld, value=%d, code=%s, left=%p-isNull=%d, right=%p-isNull=%d \n",curr->frequency, curr->value, curr->code, curr->left, curr->right,(curr->left ==NULL), (curr->right==NULL));  

             intToString_9149(curr->value, valueStr);

             printf("*** valueStr=%s, d=%d",valueStr,valueStr);
             returnArray = stringConcat_9149(returnArray, valueStr);
             (*decodeSize)++;
             cutString_9149(binaryCodes, 0,i );
              printf(", binaryCodes=%s \n",binaryCodes);
             i=-1;  // debugging for a long time !!!! i=0
             curr =  huffmanTree;
         }else{
              printf("nonleaf i=%d, ",i);
              //curr = (binaryCodes[i] - '0' ==0) ? curr->right : curr->left;
              if (binaryCodes[i] - '0' ==0) {
                   printf(" #0 ");
                   curr = curr->left;
              }else{
                    curr = curr->right;
                    printf(" #1 ");
              }

         }
     }
     return returnArray;
}


int writeDataWithBuffer_9149( unsigned char * data, int dataSize, FILE *fout){
    const unsigned  int BUFFER_SIZE = 512;
    unsigned int idx =0;
    int size= 0;
    int j=0;
    while( idx < dataSize){

         size = BUFFER_SIZE;  
         if (idx + BUFFER_SIZE > dataSize ){
              size = dataSize - idx;
         }
         fwrite( &data[idx], sizeof(unsigned char), size , fout);
         idx = idx + size;
         j++;
    }

    printf("write %d times with buffer_size=%d \n", j, BUFFER_SIZE);
    return 1;
}

void decodeAndSaveFile_9149( Node* huffmanTree ,unsigned char* data, unsigned int dataSize, FILE * fout  ){
     printf("Func #### decodeAndSaveFile()\n");
      
     unsigned int i=0;
     unsigned int j=0;
     Node* curr= huffmanTree ;
     

    const int BUFFER_SIZE =1024;
    unsigned char *buffer = malloc( sizeof( unsigned char ) * BUFFER_SIZE );
    memset( buffer, 0, sizeof( unsigned char ) * BUFFER_SIZE );
    int curr_idx = 0;

    char array[9];
    int value=-1;
    int num=0;
    unsigned char lastBits = (unsigned char) data[dataSize -1];
    printf("lastBits=%d, dataSize=%u\n",lastBits,dataSize);

     for( i=0;i< (dataSize-1) ;i++){  
          // printf("%u, ",i);
          //fflush(stdout);
          value = (unsigned char) data[i];
          
          intToBinaryStr_9149(array,value);
          if (DEBUG_SINGAL) printf("i[%u]=%d, array=%s# \n" ,i,value,array);

         /// if (curr->right == NULL && curr->left == NULL){  //debugging for a long time, memory will not be initialized to be NULL;
         for (j=0;j<strlen(array);j++){
                
                 if( i == (dataSize-2)){
                    if (j >= lastBits){
                        break; // for aligments to get total 8 bits in last byte.
                    }
                 }                   

                 if (curr_idx == BUFFER_SIZE){
                      fwrite( &buffer[0], sizeof(unsigned char), BUFFER_SIZE , fout);
                       memset( buffer, 0, sizeof( unsigned char ) * BUFFER_SIZE );
                       curr_idx=0;
                 }

                if (curr->value >=0 ){
                     
                     if (DEBUG_SINGAL)  printf("num=%d=> %d,%c; \n",num++, curr->value,curr->value);
                     
                     buffer[curr_idx++]=curr->value;
                     curr =  huffmanTree;
                 }

                    
                if (array[j] - '0' ==0) {
                    if (DEBUG_SINGAL)  printf(" #0 ");
                    curr = curr->left;
                }else{
                    curr = curr->right;
                    if (DEBUG_SINGAL)  printf(" #1 ");
                }

                 
          } //j
     }//i 
 

     // for last bit
     if (curr->value >=0 ){                     
         if (DEBUG_SINGAL)  printf("\nlast bits, num=%d=> %d,%c; \n",num++, curr->value,curr->value);            
         buffer[curr_idx++]=curr->value;
         curr =  huffmanTree;
    }
     

     if (curr_idx >=0){  // debugging for last step to check leaf node.
         fwrite( &buffer[0], sizeof(unsigned char), curr_idx , fout);
     }

     if (buffer != NULL){
        free(buffer);
        buffer = NULL;
     }

}



void initNodes_9149(){
     printf("Func #### initNodes()\n");
    int i=0;
    for( ; i< (SIZE) ;i++){
        nodes[i].frequency =  0;
        nodes[i].value = -1;
        nodes[i].code = NULL;
        nodes[i].left = NULL;
        nodes[i].right = NULL;
        //printf("###nodes[%d].frequency=%u, nodes[%d].value=%d! \n",i, nodes[i].frequency ,i, nodes[i].value );
    }
}

int decodeMain_9149(int argc, char* argv[]){
    printf("Func #### decodeMain()\n");
    int size=0;
    initNodes_9149();
    
    char* inputFile = stringConcat_9149(LOCATION, argv[1] );
    printf("inputFile=%s\n",inputFile);
             
   

    FILE * fin = fopen(inputFile , "rb");
    unsigned int  headerSize = readHeaderInfo_9149(fin, &size);
    printf("### header Size = %u, nodes size=%d \n", headerSize, size);
     
    fseek(fin,0, SEEK_END);
    unsigned int totalSize = ftell(fin);
    int dataSizeWithoutHeader = (totalSize - headerSize);
    printf("### totalSize =%u, data Size without header=%d\n",totalSize, dataSizeWithoutHeader );
    
    fseek(fin, headerSize, SEEK_SET);
    unsigned int currIdx = ftell(fin);
    printf("### currIdx = %u \n", currIdx);

    unsigned int dataSize = dataSizeWithoutHeader/ sizeof(unsigned char);
 
    printf("*without header -> s_data=%u# \n",dataSize );
    unsigned char *data = (unsigned char*)malloc(dataSize * sizeof(unsigned char));


    size_t readResultSize  = fread(&data[0], sizeof(unsigned char) ,dataSize, fin);
    fclose(fin);



    Heap* heap = createHeap_9149(size);

    if (DEBUG_SINGAL){
        printf("@@ heap->size=%d, \n", heap->size );
        int i=0;
        for ( i=0; i< heap->size;i++){
            printf("heap.lists[%d] value=%d,frequency=%u,\n",i,heap->lists[i]->value /* error--> debugging */ , heap->lists[i]->frequency);
        }
        
        printf("####### \n");
        for (i=0;i<SIZE;i++){
            if (nodes[i].frequency ==0){
                continue;
            }
           printf("i=%d, value:%d,frequency:%u;  ", i, nodes[i].value, nodes[i].frequency);
        }
        printf("\n");
        printf("heap->size=%d, \n", heap->size );
        printf("####### huffmanTree #### \n");
    }

    if (heap->size ==0){
        printf("Error heap size is not be zero!! \n");
        return 1;
    }

    Node* huffmanTree = builtHuffmanTree_9149(heap);
    printf("### Assign leaf code by preorderTraversal() ");
    preorderTraversal_9149(huffmanTree, NULL);

    if (DEBUG_SINGAL){

        

         unsigned int x =0;
         for ( x=0; x< SIZE;x++){
            if (nodes[x].frequency <=0){
                continue;
            }
            printf("lists[%u] value=%d,frequency=%u, code=%s\n",x, nodes[x].value , nodes[x].frequency,nodes[x].code);
        }
         inorderTraversalPirntOut_9149(huffmanTree); 
    }
    
    
    

     int decodeSize =0;
     //unsigned char *s = decode(huffmanTree , binaryArray, &decodeSize);
     
     

     int fileNameLen = strlen(inputFile);
     int ext_idx = -1;
     for (;fileNameLen>=0; fileNameLen--){
        if ( inputFile[fileNameLen] == '.'){
            ext_idx = fileNameLen;
            printf("ext_idx=%d\n",ext_idx);
            break;
        }
     }

     char * outputFile = subString_9149(inputFile,0,ext_idx);
     //outputFile = stringConcat_9149(outputFile,".copy2");
     printf(" outputFile=%s \n", outputFile);    
     FILE * fout = fopen(outputFile , "wb");
     //size_t writeResultSize  = fwrite(&s[0], sizeof(unsigned char) ,decodeSize, fout);
     decodeAndSaveFile_9149(huffmanTree , data, dataSize, fout);
     

     
     fclose(fout);

     
     remove(inputFile);
     printf("@@@  delete inputFile=%s\n",inputFile);


    /*
    len = strlen(data); 
    i=0;
    for( ;i<len; i++){
        data[i];
    }
    */
    ///printf("End \n", s);

    return 1;
}




int encodeMain_9149(int argc, char* argv[]){
    
    printf("Func #### encodeMain()\n");
    int byte = -1;
    int size = 0;
    unsigned int i=0;
    unsigned int fileSize = 0;

    char* inputFile = stringConcat_9149(LOCATION, argv[1] );
    printf("inputFile=%s\n",inputFile);
             
    unsigned char* data = loadFile_9149(inputFile, &fileSize);
    

    printf("fileSize=%u, no use => strlen(data)=%u, sizeof(data)=%u \n",fileSize, strlen(data) , sizeof(data) );
    
    

    initNodes_9149(); 

    for( i=0;i< fileSize;i++ ){
        byte = (unsigned int) data[i];
        if (nodes[byte].frequency ==0 ){
             nodes[byte].value = byte;
            size++;
        }
        nodes[byte].frequency ++ ;
    }
    
    
    // int g=0;
    // for( i=0;i< fileSize;i++ ){         
          // if (nodes[i].frequency >0 ){
              // g++;
              // printf("node[%d].frequency=%u ;",i,nodes[i].frequency);
              // if(g %5 ==0){
                // printf("\n");
              // }
          // }
    // }
    

    Heap* heap = createHeap_9149(size);

   if (DEBUG_SINGAL){
 
        printf("@@ heap->size=%d, \n", heap->size );
        unsigned int x =0;
        for ( x=0; x< heap->size;x++){
            printf("heap.lists[%d] value=%d,frequency=%u,\n",x,heap->lists[x]->value /* error--> debugging */ , heap->lists[x]->frequency);
        }

        printf("####### \n");
        for (x=0;x<SIZE;x++){
            if (nodes[x].frequency ==0){
                continue;
            }
           printf("i=%d, value:%d,frequency:%u;  ", x, nodes[x].value, nodes[x].frequency);
        }
        printf("\n");
        printf("heap->size=%d, \n", heap->size );
        printf("####### huffmanTree #### \n");
    }

    Node* huffmanTree = builtHuffmanTree_9149(heap);
    printf("### Assign leaf code by preorderTraversal() ");
    preorderTraversal_9149(huffmanTree, NULL);


    if (DEBUG_SINGAL){
       


        unsigned int x =0;
        for ( x=0; x< SIZE;x++){
            if (nodes[x].frequency <=0){
                continue;
            }
            printf("lists[%d] value=%d,frequency=%u, code=%s\n",x, nodes[x].value , nodes[x].frequency,nodes[x].code);
        }
   
    }
    
    byte =-1;
    //fin = fopen("./testIn.bin" , "rb"); ''
    char* outputFile = stringConcat_9149(LOCATION, argv[1] );
    outputFile = stringConcat_9149(outputFile, ".huf" );
    printf("outputFile=%s\n",outputFile);
   
    FILE * fout = fopen(outputFile , "wb");
    unsigned int headerSize = writeHeaderInfo_9149( fout, size);
    fflush(stdout);
   
    printf("########### headerSize=%u \n",headerSize);


    char buff[9];
    buff[8]='\0';
    int buffIdx = 0;

    char * eightBits = NULL;
    int len = 0;
    unsigned char encrptCodes =0;
    char *zero ="0";
    i=1;
    //unsigned  int j=1;


    struct timeval tv, tv2;
    clock_t endTime;
    unsigned long long start_utime, end_utime;
    endTime =clock();
    gettimeofday(&tv, NULL);



    unsigned char * encodedData = (unsigned char*)malloc( (fileSize + 3000) * sizeof(unsigned char));

    //unsigned char encodedArray[fileSize + 3000];


    unsigned int encoidedSize = 0;

    char * logInfo = "";
    char  logInfoOne[256];
    char * originalData ="";

    
    /// char * logBuff = "";

    printf("fileSize=%u\n",fileSize);

    for( i=0;i< fileSize;i++ ){
           //printf("%u, ",i );
           //fflush(stdout); 
           byte = (unsigned char) data[i];
           if (nodes[byte].frequency == 0){
               printf("[Error]  byte=%d , frequency=%d \n",byte, nodes[byte].frequency ); 
           }
           //printf("i=%u, byte=%d , cocde=%12s, frequency=%u ,",i,byte,nodes[byte].code, nodes[byte].frequency ); 
            int j=0;
             ///logBuff = stringConcat(logBuff, nodes[byte].code);
           //printf("%u, nodes[byte].code=%s, byte=%d",i,nodes[byte].code, byte );
           //fflush(stdout); 
           for ( ; j<strlen(nodes[byte].code);j++ ){
                //printf("j=%d, ",j );
                //fflush(stdout); 
                buff[buffIdx++] = nodes[byte].code[j];
                
                //printf("1 " );
                //fflush(stdout); 
                if (buffIdx >=8){
                    encrptCodes = (unsigned char) binaryStrToInt_9149(buff);
                    if (DEBUG_SINGAL)  printf("encode i[%u]=%d \n",encoidedSize,encrptCodes);
                    encodedData[encoidedSize++] = encrptCodes;

                    buffIdx =0;
                }
           }
    }
  
  ///if (DEBUG_SINGAL)  printf("### logBuff=%s ,strlen(logBuff)=%u \n",logBuff ,strlen(logBuff));

 gettimeofday(&tv2, NULL);
    endTime =clock() - endTime ;

    start_utime = tv.tv_sec * 1000000 + tv.tv_usec;
    end_utime = tv2.tv_sec * 1000000 + tv2.tv_usec;
    printf("@@@@ Clock=%f sec. ,  Gettimeofday time = %llu.%03llu milisecond;  %llu.%06llu sec \n",((float)endTime) /CLOCKS_PER_SEC, (end_utime - start_utime)/1000, (end_utime - start_utime)%1000, (end_utime - start_utime)/1000000, (end_utime - start_utime)%1000000  );
    

 
     int lastBits = buffIdx;
    

    if ( lastBits != 0  ){
        
        if (lastBits == 8){
            printf("#### [Error] The lenght of Last bits  is 8.\n");
        }
        while( buffIdx <8){
             buff[buffIdx++] = '0';
        } 

       
        encrptCodes = (unsigned char) binaryStrToInt_9149(buff);
        encodedData[encoidedSize++] = encrptCodes;
        encodedData[encoidedSize++] = (unsigned char) lastBits; // key for alignments
    }else{
        encodedData[encoidedSize++] = (unsigned char)8; // key for alignments
    }
    
     // printf("%s", logInfo);
     printf("#### The lenght of Last bits  is %d. encoidedSize=%u \n",lastBits,encoidedSize);
     
    
    //printf("###Without involving last byte, origianl encoding len=%u encoding=%s,\n", strlen(originalData) , originalData);



    size_t readResultSize  = fwrite(&encodedData[0], sizeof(unsigned char) ,encoidedSize, fout);

    fseek(fout,0, SEEK_END);
    unsigned int totalSize = ftell(fout);

    printf("## Total encoidedSize=%u, headerSize=%u , (encoidedSize+headerSize)=%u, Encoding File size=%u  \n",encoidedSize, headerSize, (encoidedSize+ headerSize) , totalSize);
     
    fclose(fout);
   
    remove(inputFile);
    printf("@@@  delete inputFile=%s\n",inputFile);

    
    return 1;
}




int main(int argc, char* argv[]){
    
    
    if ( argc < 2) {
        printf("please key in your file.\n");
        return 1;
    }
    printf("argc=%d, argv[1]=%s", argc, argv[1]); 

    struct timeval tv, tv2;
    clock_t endTime;
    unsigned long long start_utime, end_utime;
    endTime =clock();
    gettimeofday(&tv, NULL);

    printf("argc=%d, argv=%s\n",argc,argv[0]);

    /*
    if (argc > 2){
        printf("##########  decodeMain()  ##########\n");
        decodeMain_9149(argc,argv);
         printf("##########  decodeMain()  ##########\n");
    }else{
        printf("##########  encodeMain()  ##########\n");
        encodeMain_9149(argc,argv);
         printf("##########  encodeMain()  ##########\n");
    }*/
    
      printf("##########  decodeMain()  ##########\n");
        decodeMain_9149(argc,argv);
         printf("##########  decodeMain()  ##########\n");

    gettimeofday(&tv2, NULL);
    endTime =clock() - endTime ;

    start_utime = tv.tv_sec * 1000000 + tv.tv_usec;
    end_utime = tv2.tv_sec * 1000000 + tv2.tv_usec;
    printf("Clock=%f sec. ,  Gettimeofday time = %llu.%03llu milisecond;  %llu.%06llu sec \n",((float)endTime) /CLOCKS_PER_SEC, (end_utime - start_utime)/1000, (end_utime - start_utime)%1000, (end_utime - start_utime)/1000000, (end_utime - start_utime)%1000000  );
    

}




int encodeMain_very_slow_9149(int argc, char* argv[]){
    
    printf("Func #### encodeMain()\n");
    int byte = -1;
    int size = 0;
    unsigned int i=0;
    
    //FILE * fin = fopen("./testIn.bin" , "rb");
    unsigned int fileSize = 0;
    //unsigned char* data = loadFile("./testIn.bin", &fileSize);
    //unsigned char* data = loadFile("./IMG_2047.JPG", &fileSize);
    unsigned char* data = loadFile_9149("./tmp_1.jpg", &fileSize);
    //unsigned char* data = loadFile("./f_1m.pdf", &fileSize);
    
    
    //fclose(fin); 

    printf("fileSize=%u, no use => strlen(data)=%u, sizeof(data)=%u \n",fileSize, strlen(data) , sizeof(data) );
    
    

    initNodes_9149(); 
    for( i=0;i< fileSize;i++ ){
        byte = (unsigned int) data[i];
        if (nodes[byte].frequency ==0 ){
             nodes[byte].value = byte;
            size++;
        }
        nodes[byte].frequency ++ ;
        //printf("node[%d].frequency=%u ; ",byte,nodes[byte].frequency);
    }
    
    
    // int g=0;
    // for( i=0;i< fileSize;i++ ){         
          // if (nodes[i].frequency >0 ){
              // g++;
              // printf("node[%d].frequency=%u ;",i,nodes[i].frequency);
              // if(g %5 ==0){
                // printf("\n");
              // }
          // }
    // }
    

    Heap* heap = createHeap_9149(size);
    printf("@@ heap->size=%d, \n", heap->size );
    
    for ( i=0; i< heap->size;i++){
        printf("heap.lists[%d] value=%d,frequency=%u,\n",i,heap->lists[i]->value /* error--> debugging */ , heap->lists[i]->frequency);
    }

    printf("####### \n");
    for (i=0;i<SIZE;i++){
        if (nodes[i].frequency ==0){
            continue;
        }
       printf("i=%d, value:%d,frequency:%u;  ", i, nodes[i].value, nodes[i].frequency);
    }
    printf("\n");
    printf("heap->size=%d, \n", heap->size );
    printf("####### huffmanTree #### \n");
    Node* huffmanTree = builtHuffmanTree_9149(heap);
    
   

    preorderTraversal_9149(huffmanTree, NULL);

    
    for ( i=0; i< SIZE;i++){
        if (nodes[i].frequency <=0){
            continue;
        }
        printf("lists[%d] value=%d,frequency=%u, code=%s\n",i, nodes[i].value , nodes[i].frequency,nodes[i].code);
    }
   

    
    byte =-1;
    //fin = fopen("./testIn.bin" , "rb"); 
    FILE * fout = fopen("./tmp_1.jpg.buff" , "wb");
    unsigned int headerSize = writeHeaderInfo_9149( fout, size);
    fflush(stdout);
   
    printf("########### headerSize=%u \n",headerSize);


    char * buff= "";
    char * eightBits = NULL;
    int len = 0;
    unsigned char encrptCodes =0;
    char *zero ="0";
    i=1;
    unsigned  int j=1;

    unsigned char * encodedData = (unsigned char*)malloc( (fileSize + 3000) * sizeof(unsigned char));
    unsigned int encoidedSize = 0;

    char * logInfo = "";
    char  logInfoOne[256];
    char * originalData ="";

    for( i=0;i< fileSize;i++ ){
           byte = (unsigned int) data[i];
           if (nodes[byte].frequency == 0){
               printf("[Error]  byte=%d , frequency=%d \n",byte, nodes[byte].frequency ); 
           }
           //printf("i=%u, byte=%d , cocde=%12s, frequency=%u ,",i,byte,nodes[byte].code, nodes[byte].frequency ); 
           buff = stringConcat_9149(buff, nodes[byte].code);
           //printf("i=%u, buff=%s \n",i,buff);
            fflush(stdout);
           len = strlen(buff);
           while (len >= 8 ){
               eightBits = subString_9149(buff, 0,8);
               
               // keeping original encoding for debugging.
               originalData = stringConcat_9149(originalData, eightBits);
             
               encrptCodes = (unsigned char) binaryStrToInt_9149(eightBits);
               //printf("## j=%u, eightBits=%s,encrptCodes=%d, \n",j,eightBits, encrptCodes); 
               //sprintf(logInfoOne,"j=%u, eightBits=%s,encrptCodes=%d, \n",j,eightBits, encrptCodes); 
               logInfo = stringConcat_9149(logInfo, logInfoOne);


               encodedData[encoidedSize++] = encrptCodes;
               cutString_9149(buff,0,8);
               //printf("i=%u, cut 0-7, buff=%s ,strlen(buff)=%u \n",i,buff ,strlen(buff));
               len = strlen(buff);
               j++;
           }
            //fflush(stdout);
    }
 
     int lastBits = strlen(buff);
    

    if ( lastBits != 0  ){
        int lastBits = strlen(buff);
        if (lastBits == 8){
            printf("#### [Error] The lenght of Last bits  is 8.\n");
        }
        while( strlen(buff) <8){
             buff = stringConcat_9149(buff, zero );
        } 

        // keeping original encoding for debugging.
        originalData = stringConcat_9149(originalData, buff);

        encrptCodes = (unsigned char) binaryStrToInt_9149(buff);
        //printf("## j=%d, last bit -> buff=%s,encrptCodes=%d, \n",j,buff, encrptCodes); 

        //sprintf(logInfoOne,"j=%u, eightBits=%s,encrptCodes=%d, \n",j,buff, encrptCodes); 
        logInfo = stringConcat_9149(logInfo, logInfoOne);


        encodedData[encoidedSize++] = encrptCodes;
        cutString_9149(buff,0,8);
        encodedData[encoidedSize++] = (unsigned char) lastBits; // key for alignments
    }else{
        encodedData[encoidedSize++] = (unsigned char)8; // key for alignments
    }
    
     // printf("%s", logInfo);
     printf("#### The lenght of Last bits  is %d. encoidedSize=%u \n",lastBits,encoidedSize);
     
    
    //printf("###Without involving last byte, origianl encoding len=%u encoding=%s,\n", strlen(originalData) , originalData);


    if ( strlen(buff) != 0  ){
        printf("### error ### strlen(buff) != 0  !!! \n");
    }

    size_t readResultSize  = fwrite(&encodedData[0], sizeof(unsigned char) ,encoidedSize, fout);

    fseek(fout,0, SEEK_END);
    unsigned int totalSize = ftell(fout);

    printf("Total encoidedSize=%u, headerSize=%u , (encoidedSize+headerSize)=%u, Encoding File size=%u  \n",encoidedSize, headerSize, (encoidedSize+ headerSize) , totalSize);
     



    fclose(fout);

    free(encodedData);
    
    return 1;
}
