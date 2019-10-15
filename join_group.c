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

void join_group(char *uid,char *gid){
	FILE *fp;
        string path("/home/aklesh/public/group");
        string grp(gid);
        path+=grp+".txt";
        if((fp=fopen(&(path[0]),"a+"))==NULL){
                perror("Unable to open\n");
                exit(EXIT_FAILURE);
        }
        fprintf(fp,"%s",uid);
        fprintf(fp,"%s","\n");
	fclose(fp);
}

/*int main(int argc,char **argv){
	FILE *fp;
	string path("/home/aklesh/public/group");
	string grp(argv[2]);
	path+=grp+".txt";
	char *p=&(path[0]);
	if((fp=fopen(p,"a+"))==NULL){
		perror("Unable to open\n");
		exit(EXIT_FAILURE);
	}
	fprintf(fp,"%s",argv[1]);
	fprintf(fp,"%s","\n");
	return 0;
}*/
