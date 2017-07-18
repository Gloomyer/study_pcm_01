#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{    
	char				fccID[4];          
	unsigned   long		dwSize;              
	char				fccType[4];      
} WAVE_HEADER;

typedef struct{    
	char				fccID[4];          
	unsigned   long     dwSize;              
	unsigned   short    wFormatTag;      
	unsigned   short    wChannels;    
	unsigned   long     dwSamplesPerSec;    
	unsigned   long     dwAvgBytesPerSec;    
	unsigned   short    wBlockAlign;    
	unsigned   short    uiBitsPerSample;    
} WAVE_FMT;

typedef struct{    
	char				fccID[4];            
	unsigned long		dwSize;                
} WAVE_DATA;

int main(){
	int channels = 2, sample_rate = 44100, bits = 16;
	
	WAVE_HEADER	pcmHEADER;
    WAVE_FMT	pcmFMT;
    WAVE_DATA   pcmDATA;

	unsigned short m_pcmData;

	FILE *fp = fopen("../source/source_44.1k_2_16.pcm", "rb+");
	FILE *fp_out = fopen("../source/output.wav", "wb+");

	//WAVE_HEADER
	memcpy(pcmHEADER.fccID, "RIFF", strlen("RIFF"));
	memcpy(pcmHEADER.fccType, "WAVE", strlen("WAVE"));
	fseek(fp_out, sizeof(WAVE_HEADER), 1);
	
	//WAVE_FMT
	pcmFMT.dwSamplesPerSec = sample_rate; 
	pcmFMT.dwAvgBytesPerSec = pcmFMT.dwSamplesPerSec * sizeof(m_pcmData);
	pcmFMT.uiBitsPerSample = bits;
	memcpy(pcmFMT.fccID, "fmt ", strlen("fmt "));
	pcmFMT.dwSize = 16;
	pcmFMT.wBlockAlign = 2;
	pcmFMT.wChannels = channels;
	pcmFMT.wFormatTag = 1;

	fwrite(&pcmFMT, sizeof(WAVE_FMT), 1, fp_out);

	//WAVE_DATA;  
    memcpy(pcmDATA.fccID, "data", strlen("data"));    
    pcmDATA.dwSize = 0;  
    fseek(fp_out, sizeof(WAVE_DATA), SEEK_CUR);

	fread(&m_pcmData,sizeof(unsigned short),1,fp);
	while(!feof(fp)){    
        pcmDATA.dwSize += 2;  
        fwrite(&m_pcmData, sizeof(unsigned short), 1, fp_out);  
        fread(&m_pcmData, sizeof(unsigned short), 1, fp);  
    }

	pcmHEADER.dwSize = 44 + pcmDATA.dwSize;

	rewind(fp_out);
	fwrite(&pcmHEADER, sizeof(WAVE_HEADER), 1, fp_out);
	fseek(fp_out, sizeof(WAVE_FMT), SEEK_CUR);
	fwrite(&pcmDATA, sizeof(WAVE_DATA), 1, fp_out);

	fclose(fp);
	fclose(fp_out);
	return 0;
}