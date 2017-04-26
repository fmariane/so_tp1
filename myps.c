

#include <stdio.h>
#include <stdlib.h>
 


int getChildren(char *children, int tab){
	char file_name[50];
   FILE *fp;
   int x,i;
 
	
   snprintf(file_name, sizeof(file_name), "/proc/%s/task/%s/children", children, children); //seta o diretorio
   fp = fopen(file_name,"r"); // abre arquivo para leitura
 
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   } 
 
   while( ( fscanf(fp, "%s", children) ) != EOF ) //lê os filhos do processo
   {
   	  for(i=0;i<tab;i++)
   	  	printf("   ");
      printf("%s\n",children);
      snprintf(file_name, sizeof(file_name), "/proc/%s/task/%s/children", children, children);
       x = getChildren(children,tab+1);
   }
 
   fclose(fp);
   return 0;
}


int main()
{
   char children[10];
   int x, tab=1;
   snprintf(children, sizeof(children), "1");   
   printf("1\n");
   x = getChildren(children,tab);
   return 0;
}






/*

int main(void)
{
	char url[]="arquivo.txt",
	     ch1, ch2, ch3;
	FILE *arq;
	
	arq = fopen(url, "r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while( (fscanf(arq,"%c %c %c\n", &ch1, &ch2, &ch3))!=EOF )
			printf("%c %c %c\n", ch1, ch2, ch3);
	
	fclose(arq);
	
	return 0;
}
*/