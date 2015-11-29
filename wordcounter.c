#include <stdio.h>

#define MAX_WORD_LENGTH 30	

int main(int argc,char *argv[]){
	
	FILE *file = fopen(argv[1], "r");
	char string1[MAX_WORD_LENGTH];
	int wordCount = 0;
	//loops while the fscanf is not EOF
	while(fscanf(file, "%s", string1)!=EOF){
		wordCount++;//increments the wordCount variable
	}

	
	printf("%i total words\n", wordCount);//Prints to console the number of words found in the file
	return 0;
}


