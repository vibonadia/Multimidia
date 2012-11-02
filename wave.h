//Viviane Bonadia

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct headerType{	/* cabeçalho padrão de um arquivo WAVE */
	int32_t ChunkID; 		/* cabeçalho RIFF (Resource Interchange File Format) */
	int32_t ChunkSize; 		/* tamanho do arquivo menos 8 */ 
	int32_t Format; 		/* contem as letras "WAVE" (0x57415645 no formato big-endian) */
	int32_t Subchunk1ID; 	/* contem as letras "fmt" (0x666d7420 no formato big-endian) */
	int32_t Subchunk1Size;	/* 16 for PCM */
	uint16_t AudioFormat; 	/* PCM = 1 (significa uma quantização linear) */
	uint16_t NumChannels; 	/* canais: 1 = mono e 2 = stereo */
	int32_t SampleRate; 	/* frequencia de amostragem */
	int32_t ByteRate; 		/* SampleRate * NumChannels * BitsPerSample/8 */
	uint16_t BlockAlign; 	/* NumChannels * BitsPerSample/8 */
	uint16_t BitsPerSample; /* numero de bits por amostra: 8 ou 16 bits */

	int32_t Subchunk2ID; 	/* contem as letras "data" (0x64617461 no formato big-endian) */
	int32_t Subchunk2Size; 	/* numero de bytes para os dados */
}headerType;

void decimacao2(int decima, char* origem, char* destino);				//Decimacao para audio com dois canais
char * decimacao2_aux(char *vetor, int dec, int nBytes, int bAmostra);	
void grava_arquivo(char *arq, headerType h, char *dados);				//grava um novo arquivo de audio
void print_cabeca(headerType h);										//imprime o cabecalho do arquivo de audio
