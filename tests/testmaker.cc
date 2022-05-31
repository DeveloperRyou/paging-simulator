# include <stdio.h>
#include<cstdlib> //rand(), srand()
#include<ctime> //time()

int main()
{
	srand((unsigned int)time(NULL));
	int op = 1000;
	int process = 3;
	int virt = 64;
	int phys = 32;
	printf("%d %d %d %d\n", op, process, virt*32, phys*32);

	int idx = 0;
	int mem = 4;
	int pid = 0;
	for (;pid<process;pid++){
		for (int i=0;i<virt;i+=mem){
			printf("0 %d %d\n", pid, mem);
			idx++;
		}
	}
	while (idx<op){
		int p = rand()%process;
		int a = rand()%(virt / mem);
		printf("1 %d %d\n", p, a);
		idx++;
	}
}