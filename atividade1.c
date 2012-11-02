//gcc wave.c  atividade1.c -o wave
#include "wave.h"

main(){
	char arq_Origem[40], arq_Destino[40];	//nome do arquivo de origem e arquivo de destino  			
	int decima = 4;							//valor pelo que eu quero decimar
	
	
	strcpy(arq_Origem, "yamaha.wav");
	strcpy(arq_Destino,"destino.wav");
	
	decimacao2(decima, arq_Origem, arq_Destino);
	
//	print_header(h);
//	print_header(hAmostrado);
}
