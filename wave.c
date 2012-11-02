#include "wave.h"

//Decimacao para audio com dois canais
//decima: fator de decimacao
//origem: nome do arquivo de origem
//destino: nome do audio de destino
void decimacao2(int decima, char* origem, char* destino){
	headerType h, hA;		//cabeca original e cabeca amostrada			
	char *dados, *dadosDec;	//1 byte
	FILE *orig;
	
	orig = fopen(origem, "rb");				//abre para leitura apenas
	fread(&h, sizeof(headerType), 1, orig);	//le o cabecalho

	dados 		= (char *) malloc(h.Subchunk2Size);
	dadosDec	= (char *) malloc(h.Subchunk2Size/decima);

	fread(dados, h.Subchunk2Size, 1, orig); //le todos os dados

	dadosDec = decimacao2_aux(dados, decima, h.Subchunk2Size, h.BitsPerSample/8);

	//atualiza cabecalho e grava audio amostrado
	hA = h;
	hA.Subchunk2Size = h.Subchunk2Size/decima; 
	hA.SampleRate = h.SampleRate/decima;
	grava_arquivo(destino, hA, dadosDec);
	
	fclose(orig);	
}

//vetor: dados do audio original
//dec: fator de decimacao
//nBytes: numero de bytes para os dados
//bAmostra: numero de bytes por amostra
char * decimacao2_aux(char *vetor, int dec, int nBytes, int bAmostra){
	char *novoVetor;
	int i, j, k;
	
	novoVetor = (char *)malloc(nBytes/dec);
	j = k = 0;
	for(i = 0; i < nBytes; ){
		//canal 1
		for(k = 0; k < bAmostra; k++){
			novoVetor[j] = vetor[i];
			j++;
			i++;
		}
		//canal 2
		for(k = 0; k < bAmostra; k++){
			if(i < nBytes){
				novoVetor[j] = vetor[i];
				i++;
				j++;
			}
		}	
		i = i+(bAmostra*2)*(dec-1);
	}
	return novoVetor;
}

//grava um novo arquivo de audio
void grava_arquivo(char *arq, headerType h, char *dados){
	FILE *destino;
	destino = fopen(arq, "wp");
	fwrite(&h, sizeof(headerType), 1, destino);//grava o cabecalho
	fwrite(dados, h.Subchunk2Size, 1, destino);//grava os dados
	fclose(destino);
}

//imprime o cabecalho do arquivo de audio
void print_cabeca(headerType h){
	printf("h.chunkID %d \n", h.ChunkID);
	printf("h.chunkSize %d \n", h.ChunkSize);
	printf("h.fomat %d \n", h.Format);
	printf("h.subChunk1ID %d \n", h.Subchunk1ID);
	printf("h.subChunk1Size %d \n", h.Subchunk1Size);

	printf("h.audioFormat %d \n", h.AudioFormat);
	printf("h.numChannels %d \n", h.NumChannels);
	
	printf("h.sampleRate %d \n", h.SampleRate);
	printf("h.byteRate %d \n", h.ByteRate);
	printf("h.BlockAling %d \n", h.BlockAlign);
	printf("h.BitsPearSample %d \n", h.BitsPerSample);
	printf("h.subChunk2ID %d \n", h.Subchunk2ID);
	printf("h.subChunk2Size %d \n\n\n", h.Subchunk2Size);
	
}
