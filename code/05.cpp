#include <stdio.h>
#include <stdlib.h>


int main(){
	int start_num = 2360, dur_num = 120;

	FILE *fp = fopen("../source/drum.pcm", "rb+");
	FILE *fp_out = fopen("../source/output_cut.pcm", "wb+");
	FILE *fp_stat = fopen("../source/output_cut.txt","wb+");

	unsigned char * sample = (unsigned char *) malloc(2);

	int cnt = 0;
	while(!feof(fp)){
		fread(sample, 1, 2, fp);

		if(cnt > start_num && cnt <= (start_num + dur_num)){  
            fwrite(sample, 1, 2, fp_out);  
			
            short samplenum = sample[1];  
            samplenum = samplenum * 256;  
            samplenum = samplenum + sample[0];  
			
            fprintf(fp_stat, "%6d,", samplenum);  
            if(cnt % 10 == 0)  
                fprintf(fp_stat, "\n", samplenum);  
        }  

		cnt++;
	}

	free(sample);
	fclose(fp);
	fclose(fp_out);
	fclose(fp_stat);
	return 0;
}