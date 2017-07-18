#include <stdio.h>
#include <stdlib.h>


int main(){
	FILE *fp = fopen("../source/source_44.1k_2_16.pcm", "rb+");
	FILE *fp_out = fopen("../source/output_doublespeed.pcm", "wb+");
	
	unsigned char * sample = (unsigned char *) malloc(4);
	
	int i = 0;

	while(!feof(fp)){
		fread(sample, 1, 4, fp);
	
		if(i % 2 == 0){
			fwrite(sample, 1, 4, fp_out);
		}
		
		i++;
	}

	free(sample);
	fclose(fp);
	fclose(fp_out);
	return 0;
}