#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 10 /* can change the buffer size as well */
#define TOT 2500
int main()
{
    char words[TOT][10];
    FILE *input;
    int i = 0;
    int j = 0;
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
    for(i = 0; i < total ; i++){
        for(j = i+1; j<total ; j++){

        }

    }
    for(i = 0; i < total +1; i++)
        free(wordGraph[i]);
	free(wordGraph);

    return 0;
}
