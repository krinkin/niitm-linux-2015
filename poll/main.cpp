#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <poll.h>

int main(int c, char **v)
{

	struct pollfd fds[2];

	if(c!=3){
		return printf("usage %s pipe1 pipe2\n",v[0]);
	}


	fds[0].fd = open(v[1], O_RDWR);
	fds[1].fd = open(v[2], O_RDWR);

	fds[0].events = fds[1].events = POLLIN;

	printf("desc: %d %d\n",fds[0].fd,fds[1].fd);

  
	while(true) {
	
		
		int ready = poll(fds,2,5000);
		char buf[BUFSIZ];
		
		printf("poll ready: %d\n",ready);

		if(!ready) {
			printf("Nothing happened\n");
			continue;
		}

		for(int i=0;i<2;i++)
		{
			if( fds[i].revents & POLLIN ) {
			read(fds[i].fd, buf, BUFSIZ);
			printf("p%d: have got %s\n",i,buf);
			}
		}
	}
}
