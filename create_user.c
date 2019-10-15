#include <bits/stdc++.h>
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
//#include <errorno.h>

using namespace std;

void seperator(char *str,vector<string> &parsedstr){
        int i=0;
        char *token=strtok(str," ");
        while(token){
                parsedstr.push_back(token);
                token=strtok(NULL,"\n");
        }
}

void create_user(char *user,char *passwd){
	FILE *fp;
	char *line=NULL;
        size_t len=0;
        ssize_t r;
	bool flag=false;
	string uid(user),pass(passwd);
        if((fp=fopen("/home/aklesh/public/usrinfo.log","a+"))==NULL){
                perror("Unable to open\n");
                exit(EXIT_FAILURE);
        }
	while((r=getline(&line,&len,fp))!=-1){
                vector<string> parsedstr;
                seperator(line,parsedstr);
                if(parsedstr[0]==uid){
			flag=true;
                        cout<<"User Exists"<<"\n";
                        break;
                }
        }
	if(!flag){
             fprintf(fp,"%s ",user);
             fprintf(fp,"%s",pass);
             fprintf(fp,"%s","\n");
	     cout<<"User account is created!!!\n";
	}
	fclose(fp);
}
/*int main(int argc,char *argv[]){
	FILE *fp;
	if((fp=fopen("/home/aklesh/public/usrinfo.log","a+"))==NULL){
		perror("Unable to open\n");
		exit(EXIT_FAILURE);
	}
	fprintf(fp,"%s ",argv[1]);
	fprintf(fp,"%s",argv[2]);
	fprintf(fp,"%s","\n");
	return 0;
}*/


