#include <stdio.h>
#include <stdlib.h>


int main(){
	FILE *fp = fopen("../source/source_44.1k_2_16.pcm", "rb+");
	FILE *fp_l = fopen("../source/output_left.pcm", "wb+");
	FILE *fp_r = fopen("../source/output_right.pcm", "wb+");
	
	unsigned char * sample = (unsigned char *) malloc(4);

	while(!feof(fp)){
		fread(sample, 1, 4, fp);
		fwrite(sample, 1, 2, fp_l);
		fwrite(sample + 2, 1, 2, fp_r);
	}

	free(sample);
	fclose(fp);
	fclose(fp_l);
	fclose(fp_r);
	return 0;
}