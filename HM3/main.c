/* @source Yıldız Technical University, İstanbul
** avaible @ www.github.com/turkerozan/dataStructuresH3
** This was created for assigment solution, no requests will be accepted
** All viewer and/or forkers will be reported to instructor if it is requested
** If there is a copy situation, there is a lots of proof in github so you can see author, so be careful
**
** @author: Ozan Turker Demir, (ozanturkerdemir@gmail.com)
** @@
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOT 2415 //number of words

int isEdge(char *s1, char *s2);
void filladj(unsigned char **wordGraph, int total,char words[TOT][10]);
int findWord(char *needle,char words[TOT][10],int total);
void insert(int id);
int del();
int queue[TOT];//Global variable queue,
int rear = -1;//queue's rear position
int front = -1;//queue's front position
int main()
{
    char words[TOT][10];//for saving all words,
    int backqueue[TOT][2];//for saving state of queue, if it is visited, we will change 0.column, other column is used to save parent id
    FILE *input; //file pointer
    int i = 0;//i and j are used for getting position of words
    int j = 0;
    char needle[10];//for string search
    int k;//iterator
    int choice;//menu choice variable
    int total = 0;//total number of words, we can use TOT but if something goes wrong, or if we want to debug process, we may want to see that
    unsigned char **wordGraph; // adj. matrix variable
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
    while(fgets(words[i], 10 , input)){//10 is buffer size
        words[i][strlen(words[i]) - 1] = '\0';//we need to get rid of \0 character, basic reading function
        i++;
    }
    total = i;//we get readed number of words
    fclose(input);//close the pointer

    //now we got total number of words before closing input
    //for debug purpose
   // for(i = 0; i < total; i++){
    //printf("%d : %s\n",i, words[i]);}
    //We can allocate memory; NxN adjacent matrix
    wordGraph = malloc((total+1) * sizeof(unsigned char *));//total+1 becuase iterator start with 0 but we need +1 more for memory
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
    //For edges it should be 0 first, we will fill later
    for(i=0; i< total;i++){
        wordGraph[i][i]=0;
    }
    //Fill adj. Matrix with function
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
    case 2://findword function gets position of given word
        printf("\n Enter string 1 : ");
        scanf("%s",needle);
        i = findWord(needle,words,total);
        printf("\n Enter string 2 : ");
        scanf("%s", needle);
        j = findWord(needle,words,total);;
        //if findword gives us latest number, we can say it cannot find string if it overflowed total number of words
        if((i == total+1)||(j == total+1)){
            printf("\n String Not found ");
        }
        else{//else we found them and print positions and condition
            printf("\n positions %d :%d", i,j);
            if(wordGraph[i][j]== 1){//if there is a connection, our adj. matrix will tell us
        printf("\n WORD %s and WORD %s has %d connection",words[i],words[j],wordGraph[i][j]);}
        else{
            printf("\n NO CONNECTION");
        }
        }
        break;
    case 3:
        printf("\n Start string :");//same as case 2, find positions first
        scanf("%s",needle);
        i = findWord(needle,words,total);
        printf("\n Stop string :");
        scanf("%s",needle);
        j = findWord(needle,words,total);
        if((i == total+1)||(j == total+1)){
            printf("\n String not found");
        }else{//if we found strings, than initilaze backqueue array with 0 and -1, 0 means no visited, -1 is parent id which is not avaible for first time
        for(k=0;k<TOT;k++){
            backqueue[k][0] = 0;
            backqueue[k][1] = -1;
        }
        // i and j are positions of words.
        printf("First word pos : %d second word pos : %d \n",i,j);
        insert(i);//insert first node
        backqueue[i][0] = 1;//make it visited
        backqueue[i][1] = -2;//for controll, we made root node parent id -2, we will use that information if we will find path
        int stop = -1;//for controlling deleted member
        while((front - rear !=1) && (queue[front] != j)){//while will broke when queue is empty or front member is 2nd word
            stop = del();//take word from queue, return id
            if(stop == j){//if it is 2nd word(desired word) then print status,
                printf("islem tamam \n");
            }
            else{
                printf("%s ->",words[stop]);//print that word
                for(k=0;k<total;k++){
                    if(wordGraph[stop][k]==1){//get connected nodes
                           // printf("%s(%d) komsudur %s(%d)  ",words[stop],stop,words[k],k);
                           // printf("\n backqueue %d \n", backqueue[k][0]);
                        if(backqueue[k][0]!=1){//if it is in queue before, skip, else;
                            backqueue[k][0] = 1;//make it visited
                            backqueue[k][1] = stop;//save parent id
                            insert(k);//insert to queue
                        }
                    }
                }
                //printf("\n QUEUE \n");
                //display();
            }
        }
        if(queue[front] == j){//when while is broked, we have to check ,we found path or not?
        printf("\n %s",words[j]);//if top member of queue is 2nd word, then we can say we found a path
        printf(" \n There is a path like : ");//print path
        k=0;//step size iterator
        do{
                k++;
                printf("%s->",words[j]);//get word id and print it
                //printf("parent : %d %s ",backqueue[j][1], words[backqueue[j][1]]);
                j=backqueue[j][1];//change id to parent
        }while(backqueue[j][1]!=-2);//when we hit root node
        printf("%s",words[j]);//print root node
        printf("\n Total step size is : %d ",k);
        }
        else{
            printf("\n No path found ");
        }
        front = -1;//when all calculations done, reset the queue
        rear = -1;
        for(k=0;k<TOT;k++){//also reset the backqueue
            backqueue[k][0]=0;
            backqueue[k][1]=-1;
        }
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
    //in this function, we need a word, and word array and total number of words
    int i = 0;//iterator
    int tmp = 1;//status
while(i <= total ){//start 0 to total, if strcmp returns 0, then it means we found word, return it number
            tmp = strcmp(words[i], needle);
            if(tmp==0){
                    //printf("%d",i);
                return i;
            }
            i++;
        }
        return i+1;//if we cannot found, return total+1
}

void filladj(unsigned char **wordGraph, int total,char words[TOT][10]){
    int i,j,k;
for(i = 0; i <= total ; i++){
        for(j = i+1; j<total ; j++){
                k = isEdge(words[i],words[j]);//edge returns number of different chars
            if( k == 1){//if k = 1; then it means only 1 difference occured
                wordGraph[i][j]=1;//it is symetrical
                wordGraph[j][i]=1;//thats why i,j = j,i
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
j = 0;//this function gets two strings
for(i=0;i<6;i++){//max number of char is 5, so we compare to 5
    if(s1[i]==s2[i]){//if char is same, then do nothing
    //printf("karakter %d ayni\n", i);
    }
    else{j++;}//if chars are not same, increase iterator
}
return j;//return amount of chars that are different
}
void insert(int id){
    if(rear == 2414){//if we hit the size of stack
        printf("overflow error \n");
    }
    else{//if not
        if(front == -1){//if it is first one
            front = 0;}//make front 0
            rear ++;//increase rear, make area for node
            queue[rear]= id;//insert node to last position of queue

    }
}
int del(){
if(front == -1 ){//if we delete from empty queue
    printf("underrflow error \n");
    return; //return with no int, so program will exit
}
    else{
        front++;//increase front, so queue front is poped
    }
return queue[front - 1];//return poped value
}

