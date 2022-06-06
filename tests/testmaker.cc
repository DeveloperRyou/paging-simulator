# include <stdio.h>
# include <string.h>
# include <cstdlib> //rand(), srand()
# include <ctime> //time()
# include <deque>
using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2) return 0;
	srand((unsigned int)time(NULL));
	int pages = atoi(argv[1]);
	int process = 2;
	int virt = 32;
	int phys = 32;
	int mem = 4;
	int op = virt/mem*process;
	printf("%d %d %d %d\n", op+pages, process, virt*32, phys*32);

	for (int pid=0;pid<process;pid++)
		for (int i=0;i<virt;i+=mem)
			printf("0 %d %d\n", pid, mem);

	deque<pair<int, int>> que;
	for (int i=0;i<pages;i++){
		int p, a;
		if (rand()%100 < 50 && !que.empty()){
			auto temp = que.front(); que.pop_front();
			p = temp.first;
			a = temp.second;
		}
		else{
			p = rand()%process;
			a = rand()%(virt/mem);
			if (que.size()>=4) que.pop_front();
		}
		que.push_back(make_pair(p, a));
		printf("1 %d %d\n", p, a);
	}
}