#include <stdio.h>
#include <stdlib.h>


int main(){
	FILE *fp = fopen("../source/source_44.1k_2_16.pcm", "rb+");
	FILE *fp_out = fopen("../source/output_halfleft.pcm", "wb+");
	
	unsigned char * sample = (unsigned char *) malloc(4);

	while(!feof(fp)){
		fread(sample, 1, 4, fp);
		short *samplenum = (short *)sample;
		*samplenum = *samplenum / 2;

		fwrite(sample, 1, 4, fp_out);
	}

	free(sample);
	fclose(fp);
	fclose(fp_out);
	return 0;
}