#include <stdio.h>
#include <stdlib.h>


int main(){
	FILE *fp = fopen("../source/source_44.1k_2_16.pcm", "rb+");
	FILE *fp_out = fopen("../source/output_44.1k_2_8.pcm", "wb+");
	
	unsigned char * sample = (unsigned char *) malloc(4);

	while(!feof(fp)){
		fread(sample, 1, 4, fp);

		short *samplenum16 = 0;
		char samplenum8 = 0;
		unsigned char samplenum8_u = 0;

		samplenum16 = (short*)sample;
		samplenum8 = (*samplenum16) >> 8;
		samplenum8_u = samplenum8 + 128;
		fwrite(&samplenum8_u, 1, 1, fp_out);

		samplenum16 = (short*)(sample + 2);
		samplenum8 = (*samplenum16) >> 8;  
        samplenum8_u = samplenum8 + 128;
		fwrite(&samplenum8_u, 1, 1, fp_out);
	}

	free(sample);
	fclose(fp);
	fclose(fp_out);
	return 0;
}