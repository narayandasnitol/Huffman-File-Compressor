#include <stdio.h>
#include <stdlib.h>

struct code{
    int value[200];
    int length;
    char ch;
} mycode[256];


struct node{
    char data;
    int freq;
    struct node *left;
    struct node *right;
};


struct node* p_queue[1000000];
int size = 0;

void push(struct node *n)
{
    p_queue[size] = n;
    size++;
}

struct node *pop()
{
    int min = 999999999;
    int min_index = 0;

    for(int index = 0; index < size; index++)
    {
        if(p_queue[index]->freq < min)
        {
            min = p_queue[index]->freq;
            min_index = index;
        }
    }
    struct node* to_ret = p_queue[min_index];
    for(int i = min_index+1; i < size; i++)
    {
        p_queue[i-1] = p_queue[i];
    }
    size--;
    return to_ret;
}



bool isEmpty()
{
    return size==0;
}

void printArr(int code[], int top, int n){
    mycode[n].length=top;

    for(int i = 0; i < top; i++){

    mycode[n].value[i] = code[i];

    //printf("%d", mycode[n].value[i]);

    }
}
//int count1=0;
void saveCodes(struct node* root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        saveCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        saveCodes(root->right, arr, top + 1);
    }
    if (root->left == NULL && root -> right == NULL )
    {
        int n = root->data;

        mycode[n].ch=root->data;
       //printf("\n%c: ", root->data);
       //printf("\n%c: ", n);

       printArr(arr, top, n);
       //count1++;
    }


    }
int main()
{
    printf("\t\t\t\t\t****SD LAB Project****\n\n\n");
    printf("Project Name: \t'File Compressor'\n");
    printf("Project Member:\t1)Narayan Das Nitol(15.02.04.025)\n\t\t2)Jannatun Naeem Muna(15.02.04.005)\n");

    int freq[256], choice;

    FILE *input_file = fopen("test.txt","r");
    FILE *fp = fopen("test.txt", "r");
    FILE *fp2 = fopen("test.txt", "r");
    FILE *fp3 = fopen("compressed.txt", "w");
    FILE *fp4 = fopen("encode_code.txt", "w");
    FILE *fp5 = fopen("encode_code.txt", "r");
    FILE *fp6 = fopen("Decompressed.txt", "w");

    printf("\n\nPress: \n\t1)Encode\n\t2)Decode\n");
    printf("\nChoice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {

        printf("\n\t\t\t\t\tEncoding");
        printf("\n\n\n\t\t");

        for(int ld=0;ld<60;ld++)
        {
            for(int wt=0;wt<100000000;wt++);   // ANIMATION
            printf("%c",219);
        }

    if(!input_file)
    {
        printf("Cannot open File!\n");
        exit(0);
    }

    /******************************** Frequency ************************************/

    for(int i = 0; i < 256; i++)
    {
        freq[i] = 0;
    }

    char ch;
    while(!feof(input_file))
    {
        fscanf(input_file, "%c",&ch);
        freq[ch]++;
    }

    /********************************************************************************/



    /********************************* Priority Queue and Tree Building ***************************/

    int count =0;
    for(int i = 0; i < 256; i++)
    {
        if(freq[i]!= 0){
                count++;
            struct node *d = (struct node *)malloc(sizeof(struct node));
            d->data = i;
            d->freq = freq[i];
            d->left = d->right = NULL;

            push(d);
        }
    }

    /***********************************************************************************************/


    /****************************** Tree Implementation ******************************************/


    for(int i =0; i< size; i++){
       // printf("%c -> %d\n",p_queue[i]->data,p_queue[i]->freq);
    }


    while(size != 1){
        struct node *left = pop();
        struct node *right = pop();
        struct node *root = (struct node *)malloc(sizeof(struct node));
        root->left = left;
        root -> right = right;
        root ->data = '$';
        root ->freq = left -> freq + right -> freq;
        push(root);
    }
    struct node * root = pop();

//    printf("\n%d\n",root->freq);

    int arr[200], top = 0;

    saveCodes(root,arr,top);

    //printf("\n\n\n");



    /********************************************************************************************/




    /*************************************** Encoding *********************************************/


    char ch2;
    while(!feof(fp2))
    {
        ch2= getc(fp2);

       // printf("%c", ch2);
    }
    printf("\n\n");

    char ch1;
    char save =0;
    int position = 7;

    while(!feof(fp))
    {
        //fscanf(fp, "%c",&ch1);
        ch1= getc(fp);

        int ch2 = ch1;

        int l = mycode[ch2].length;

        if(ch1 == mycode[ch2].ch)
        {
            //printf("\n%c: ", ch1);
            for(int j=0; j<l; j++)
            {
               // printf("%d",mycode[ch2].value[j]);

                save |= (mycode[ch].value[j] <<position);
                position--;

                if(position <0){
                   fprintf(fp3,"%c", save);
                   save =0;
                   position = 7;
                }

                fprintf(fp4,"%d", mycode[ch2].value[j]);
            }
        }

        //printf("\n%d ", ch2);
    }

    if(save != 7)
    {
        fprintf(fp3,"%c", save);
    }

    fclose(fp3);

      printf("\n\n\n\t\t\t\tSuccessfully Encoded !!! \n\n\n");
    }

    if(choice == 2)
    {

        //printf("\nNot yet done  !!!\n\n");


        char sc, myarr[20], myarr1[20];

        while(!feof(fp5))
        {
            int va=0;
            sc = getc(fp5);

            for(int x=0; x<256; x++){

                if(mycode[x].length==0)
                    continue;

                    if(mycode[x].value[va] != sc)
                        continue;


                        for(int y=0; y<mycode[x].length; y++){

                                myarr[y]=mycode[x].value[y];
                                myarr1[y]= sc;
                                sc = getc(fp5);
                    }
                    int flag = 0;

                    for(int z=0; z<mycode[x].length; z++){

                        if(myarr[z] == myarr1[z])
                            continue;
                        else
                        {
                            flag = 1;
                            break;

                        }
                        if(flag = 0)
                            printf("%c", mycode[x].ch);

                    }

            }
        }
    }







    /* char ch3;
    int z, le;
    char myarr[100], myarr1[100];

    while(!feof(fp5))
    {
        ch3=getc(fp5);
        printf("%c", ch3);

        if(ch3 == ' ')
            continue;

        else{

        printf("Found\n");
        //printf("%c", ch3);
           le = 0, z=0;

            myarr[z]=ch3;
            ch3=getc(fp5);
            z++;
            le++;
        } */

        //printf("%c ", mycode[x].ch);

         /*int flag;
        for(int ab=0; ab<z; ab++){

            for(int x = 1; x<256; x++){

                flag = 0;
                if(mycode[x].length==0)
                    continue;

                    for(int c=0; c<mycode[x].length; c++){

                        myarr1[c]=mycode[x].value[c];

                        if(myarr[c]==myarr1[c])
                            continue;
                        else{
                            flag = 1;
                            break;
                        }
                        //if(flag == 0)
                            //printf("%c", mycode[x].ch);
                    }
                }

            } */


    //fclose(fp5);

    /*for(int x=1; x<256; x++){
            if(mycode[x].length==0)
                continue;
        printf("%d\n", mycode[x].length);
    } */






    return 0;
}
