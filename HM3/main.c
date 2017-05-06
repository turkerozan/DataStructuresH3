#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 10
#define TOT 2414
#define MAX 2414
int isEdge(char *s1, char *s2);
void filladj(unsigned char **wordGraph, int total,char words[TOT][10]);
int findWord(char *needle,char words[TOT][10],int total);
int queue[MAX];
    int rear = -1;
    int front = -1;
int main()
{
    char words[TOT][10];
    int backqueue[MAX][2];
    FILE *input;
    int i = 0;
    int j = 0;
    int tmp1,tmp2;
    char needle[10];
    char needle2[10];
    int k;
    int choice;
    int total = 0;
    unsigned char **wordGraph;
    //declaring pointer for reading file
    input = fopen("kelime.txt","r");
    //error handling if open fails
    if(input == NULL ){
        printf("unable to open file\n");
        exit(1);
    }
    //for debug purpose
    else{
        printf("File opened successfully\n");
    }
    while(fgets(words[i], 10 , input)){
        words[i][strlen(words[i]) - 1] = '\0';
        i++;
    }
    total = i;
    fclose(input);

    //now we got total number of words before closing input
    /*for(i = 0; i < total; i++){
    printf("%d : %s\n",i, words[i]);}*/
    //We can allocate memory; NxN adjacent matrix
    wordGraph = malloc((total+1) * sizeof(unsigned char *));
    if(wordGraph == NULL){
        printf("Memory error \n");
        exit(1);
    }
    for(i = 0; i< total+1; i++){
        wordGraph[i] = malloc((total+1) * sizeof(unsigned char));
        if(wordGraph[i] == NULL ){
        printf("Memory error \n");
        exit(1);
        }
    }
    //For edges it should be 0 first
    for(i=0; i< total;i++){
        wordGraph[i][i]=0;
    }
    //Fill adj. Matrix with isEdge function
    //Because it is symmetrical, i-j = j-i on matrix
    filladj(wordGraph,total,words);
    //Menu implementation after all of work are done without errors
    do{
        do{
            printf("\n 1.Compare strings with id");
            printf("\n 2.Compare strings with input");
            printf("\n 3.Find Transaction between strings");
            printf("\n 4.Exit");
            scanf("%d",&choice);
            if(choice<1||choice>4)
                printf("\n Invalid choice ");
        }while(choice <1 || choice >4);
        switch(choice){
    case 1:
        printf("\n Please input id respectively");
        //Id means the position in array, if known
        printf("\n First ID : ");
        scanf("%d",&i);
        printf("\n Second ID : ");
        scanf("%d",&j);
        if(wordGraph[i][j]== 1){//if it is 1; then it means there is an connection
        printf("\n WORD %s and WORD %s has %d connection",words[i],words[j],wordGraph[i][j]);}
        else{
            printf("\n NO CONNECTION");
        }
        break;
    case 2:
        printf("\n Enter string 1 : ");
        scanf("%s",needle);
        i = findWord(needle,words,total);
        printf("\n Enter string 2 : ");
        scanf("%s", needle);
        j = findWord(needle,words,total);;
        //if any of the while go until end, it means that we cannot find the string
        if((i == total)||(j == total)){
            printf("\n String Not found ");
        }
        else{//else we found them and print positions and condition
            printf("\n positions %d :%d", i,j);
            if(wordGraph[i][j]== 1){
        printf("\n WORD %s and WORD %s has %d connection",words[i],words[j],wordGraph[i][j]);}
        else{
            printf("\n NO CONNECTION");
        }
        }
        break;
    case 3:
        printf("\n Start string :");
        scanf("%s",needle);
        printf("\n Stop string :");
        scanf("%s",needle2);
        i = 0;
        j = 0;
        tmp1 = 1;
        tmp2 = 1;
        while(i < total ){
            tmp1 = strcmp(words[i], needle);
            if(tmp1==0){
                break;
            }
            i++;
        }
        while(j < total ){
            tmp2 = strcmp(words[j], needle2);
            if(tmp2==0){
                break;
            }
            j++;
        }
        for(k=0;k<MAX;k++){
            backqueue[k][0] = 0;
            backqueue[k][1] = -1;
        }
        // i and j are positions of words.
        printf("First word pos : %d second word pos : %d \n",i,j);
        insert(i);
        backqueue[i][0] = 1;
        backqueue[i][1] = -2;
        int stop = 0;
        while((front - rear !=1) && (queue[front] != j)){
            stop = del();
            if(stop == j){
                printf("islem tamam \n");
            }
            else{
                printf("%s ->",words[stop]);
                for(k=0;k<total;k++){
                    if(wordGraph[stop][k]==1){
                           // printf("%s(%d) komsudur %s(%d)  ",words[stop],stop,words[k],k);
                           // printf("\n backqueue %d \n", backqueue[k][0]);
                        if(backqueue[k][0]!=1){
                            backqueue[k][0] = 1;
                            backqueue[k][1] = stop;
                            insert(k);
                        }
                    }
                }
                //printf("\n QUEUE \n");
                //display();
            }
        }
        if(queue[front] == j){
        printf("\n %s",words[j]);
        printf(" \n There is a path like : ");

        do{
        printf("%s->",words[j]);
            //printf("parent : %d %s ",backqueue[j][1], words[backqueue[j][1]]);
            j=backqueue[j][1];
        }while(backqueue[j][1]!=-2);

        }
        printf("%s",words[j]);
        front = -1;
        rear = -1;
        for(k=0;k<MAX;k++){
            backqueue[k][0]=0;
            backqueue[k][1]=-1;
        }
        break;
    default:
        printf("\n End of program");//Before end, do not forget to free our matrix
        for(i = 0; i < total +1; i++)
        free(wordGraph[i]);
	free(wordGraph);
        }
    }while(choice != 4);

    return 0;
}
int findWord(char *needle,char words[TOT][10],int total){
    int i = 0;
    int tmp = 1;
while(i < total ){
            tmp = strcmp(words[i], needle);
            if(tmp==0){
                return i;
            }
            i++;
        }
        return i;
}

void filladj(unsigned char **wordGraph, int total,char words[TOT][10]){
    int i,j,k;
for(i = 0; i < total ; i++){
        for(j = i+1; j<total ; j++){
                k = isEdge(words[i],words[j]);
            if( k == 1){//if k = 1; then it means only 1 difference occured
                wordGraph[i][j]=1;
                wordGraph[j][i]=1;
            }
            else{//else fill with 0
                wordGraph[i][j]=0;
                wordGraph[j][i]=0;
            }
        }

    }

}
int isEdge(char *s1, char *s2){
int i,j;
j = 0;
for(i=0;i<6;i++){
    if(s1[i]==s2[i]){
    //printf("karakter %d ayni\n", i);
    }
    else{j++;}
}
return j;
}
insert(int id){
    if(rear == 2413){
        printf("Overflow\n");
    }
    else{
        if(front == -1)
            front = 0;
            rear ++;
            queue[rear]= id;

    }
}
int del(){
if(front == -1 ){
    printf("Underflow \n");
    return;
}
    else{
        //printf("\n deleted item id is: %d \n", queue[front]);
        front++;
    }
return queue[front - 1];
}
display(){
int p;
for(p=front; p<= rear;p++){
    printf("queue : %d ", queue[p]);
    printf("\n");

}
}
