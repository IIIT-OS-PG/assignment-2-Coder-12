#include <bits/stdc++.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>
#include <dirent.h>

using namespace std;

void create_group(char *grp){
	FILE *fp;
        string path("/home/aklesh/public/group"),gid(grp);
        path+=gid+".txt";
        if((fp=fopen(&(path[0]),"a+"))==NULL){
                perror("Unable to open\n");
                exit(EXIT_FAILURE);
        }
        fclose(fp);
}
/*int main(int argc,char **argv){
	FILE *fp;
        string path("/home/aklesh/public/group"),gid(argv[1]);
	path+=gid+".txt";
	if((fp=fopen(&(path[0]),"a+"))==NULL){
		perror("Unable to open\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}*/
