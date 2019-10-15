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

using namespace std;

void seperator(char *str,vector<string> &parsedstr){
        int i=0;
        char *token=strtok(str," ");
        while(token){
                parsedstr.push_back(token);
                token=strtok(NULL,"\n");
        }
}
void login(char *user,char *passwd){
	FILE *fp;
        char *line=NULL;
        size_t len=0;
        ssize_t r;
	bool flag=false;
        string uid(user),pass(passwd);
        if((fp=fopen("/home/aklesh/public/usrinfo.log","r"))==NULL){
                printf("Cannot open file\n");
                exit(EXIT_FAILURE);
        }
        while((r=getline(&line,&len,fp))!=-1){
                vector<string> parsedstr;
                seperator(line,parsedstr);
                if(parsedstr[0]==uid and parsedstr[1]==pass){
			bool flag=true;
                        cout<<"login successfull!!!!\n"<<"\n";
                        break;
                }
        }
	if(!flag) cout<<"login unsuccessfull!!!\n";
        fclose(fp);
}

/*int main(int argc,char **argv){
	FILE *fp;
        char *line=NULL;
        size_t len=0;
        ssize_t r;
	bool flag
	string uid(argv[1]),pass(argv[2]);
        if((fp=fopen("/home/aklesh/public/usrinfo.log","r"))==NULL){
                printf("Cannot open file\n");
                exit(EXIT_FAILURE);
        }
        while((r=getline(&line,&len,fp))!=-1){
		vector<string> parsedstr;
                seperator(line,parsedstr);
		if(parsedstr[0]==uid and parsedstr[1]==pass){
			flag=true;
			cout<<"login successfull!!!!"<<"\n";
			break;
		}
        }
        fclose(fp);
}*/
