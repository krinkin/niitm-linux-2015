#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int c, char **v)
{
	fd_set rd;
	int ready = 0;
	struct timeval to = { 5, 0 };
	char buf[BUFSIZ];

	if(c!=3){
		return printf("usage %s pipe1 pipe2\n",v[0]);
	}


	int p1 = open(v[1], O_RDWR);
	int p2 = open(v[2], O_RDWR);

	printf("desc: %d %d\n",p1,p2);

  
	while(true) {
	
		FD_ZERO(&rd);
		FD_SET(p1,&rd);
		FD_SET(p2,&rd);

		to.tv_sec = 5;
		
		// Atention: 1st param
		ready = select(10, &rd, NULL, NULL,&to);
		
		printf("select: %d\n",ready);

		if(!ready) {
			printf("Nothing happened\n");
			continue;
		}

		if(FD_ISSET(p1,&rd)) {
			read(p1, buf, BUFSIZ);
			printf("p1: have got %s\n",buf);
		}

		if(FD_ISSET(p2,&rd)) {
			read(p2, buf, BUFSIZ);
			printf("p2: have got %s\n",buf);
		}
	}

}
