
#include <stdio.h>
#include <stdlib.h>
 


int getChildren(char *children, int tab){
	char file_name[50], proc_name[50], comm_name[50];
   FILE *fp, *nf;
   int x,i;
 
	
   snprintf(file_name, sizeof(file_name), "/proc/%s/task/%s/children", children, children); //seta o diretorio
   snprintf(comm_name, sizeof(comm_name), "/proc/%s/task/%s/comm", children, children); //seta o diretorio
   fp = fopen(file_name,"r"); // abre arquivo para leitura
   nf = fopen(comm_name,"r"); // abre arquivo para leitura
 
   if(  fp == NULL || nf == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   } 
 
   while( ( fscanf(fp, "%s", children) ) != EOF ) //lê os filhos do processo
   {
   	  snprintf(comm_name, sizeof(comm_name), "/proc/%s/task/%s/comm", children, children); //seta o diretorio
   	  nf = fopen(comm_name,"r"); // abre arquivo para leitura
   	  fscanf(nf, "%s", proc_name);

   	  for(i=0;i<tab;i++)
   	  	printf("	");

      printf("%s\n",proc_name);

      //snprintf(file_name, sizeof(file_name), "/proc/%s/task/%s/children", children, children);
      //snprintf(comm_name, sizeof(comm_name), "/proc/%s/task/%s/comm", children, children); //seta o diretorio
      fclose(nf);

       x = getChildren(children,tab+1);
   }
 
   fclose(fp);
   return 0;
}


int main()
{
   char children[10];
   char file_name[50], proc_name[50], comm_name[50];
   int x, tab=1;
   FILE *fp, *nf;	
   
   fp = fopen("/proc/1/task/1/children","r"); // abre arquivo para leitura
   nf = fopen("/proc/1/task/1/comm","r"); // abre arquivo para leitura

   if(  fp == NULL || nf == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   } 

   snprintf(children, sizeof(children), "1");  

   fscanf(nf, "%s", proc_name);
   printf("%s\n",proc_name);

   fclose(nf);
   fclose(fp);

   x = getChildren(children,tab);

   return 0;
}
