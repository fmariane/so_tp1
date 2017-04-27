
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/stat.h>



int getChildren(char *children, int tab){
	char file_name[50], proc_name[50], comm_name[50], stat_name[50], estado[2], trash[10];
	FILE *fp, *nf, *st;
	int x,i, pid;
	struct passwd *pw ;
 
	
	snprintf(file_name, sizeof(file_name), "/proc/%s/task/%s/children", children, children); //seta o diretorio para filhos
	//snprintf(comm_name, sizeof(comm_name), "/proc/%s/task/%s/comm", children, children); //seta o diretorio para nome do processo
	//snprintf(stat_name, sizeof(stat_name), "/proc/%s/stat", children); //seta o diretorio para o dono do processo
	
	fp = fopen(file_name,"r"); // abre arquivo para leitura dos filhos
	//nf = fopen(comm_name,"r"); // abre arquivo para leitura do nome dos processos
	//st = fopen(stat_name,"r"); // abre arquivo para leitura do dono do processo

	if(  fp == NULL )//|| nf == NULL || st == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	} 
 
	while( ( fscanf(fp, "%s", children) ) != EOF ) //lê os filhos do processo
	{
		snprintf(comm_name, sizeof(comm_name), "/proc/%s/task/%s/comm", children, children); //seta o diretorio
		snprintf(stat_name, sizeof(stat_name), "/proc/%s/stat", children); //seta o diretorio
		
		nf = fopen(comm_name,"r"); // abre arquivo para leitura
		st = fopen(stat_name,"r"); // abre arquivo para leitura

		fscanf(nf, "%s", proc_name);

		for(i=0;i<=4;i++)
		{ 
			if(i==2) 
				fscanf(st, "%s", estado);
			else if(i==3) 
				fscanf(st, "%d", &pid);
			else 
				fscanf(st, "%s", trash);
		} 	

		pw = getpwuid(pid);

		printf("\n%s  |%s  |%s   |%s   |",children,pw->pw_name , proc_name, estado);
      

		snprintf(file_name, sizeof(file_name), "/proc/%s/task/%s/children", children, children);
		snprintf(comm_name, sizeof(comm_name), "/proc/%s/task/%s/comm", children, children); //seta o diretorio
		
		fclose(st);
		fclose(nf);
		
		x = getChildren(children,tab+1);
	}
 
	fclose(fp);
	return 0;
}

int main()
{
	char children[10];
	char file_name[50], proc_name[50], comm_name[50], estado[2], trash[10];
	int x, tab=1,i, pid=0;
	FILE *fp, *nf, *st;	
	struct passwd *pw;

	fp = fopen("/proc/1/task/1/children","r"); // abre arquivo para leitura
	nf = fopen("/proc/1/task/1/comm","r"); // abre arquivo para leitura
	st = fopen("/proc/1/stat","r"); // abre arquivo para leitura

	if(  fp == NULL || nf == NULL || st == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	} 
	
	snprintf(children, sizeof(children), "1"); 
	
	for(i=0;i<=4;i++)
	{ 
		if(i==2)
			fscanf(st, "%s", estado);
		else if(i==3) fscanf(st, "%d", &pid);
		else fscanf(st, "%s", trash);
	}

	pw = getpwuid(pid);
	fscanf(nf, "%s", proc_name);
	
	printf("PID | User   | PROCNAME  | Estado |");
	printf("\n%s  |%s  |%s   |%s   |",children,pw->pw_name , proc_name, estado);

	fclose(nf);
	fclose(fp);

	x = getChildren(children,tab);

	return 0;
}
