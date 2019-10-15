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
#include <thread>
//#include <errorno.h>
#include <time.h>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void read_file(int newsockfd,char *filepath){

        FILE *fp;
        if((fp=fopen(filepath,"r"))==NULL){
                perror("Uable to open\n");
                exit(EXIT_FAILURE);
        }
        char buffer[256];
        char ch,c;
	char *cid=new char[256];
        char **keys=new char*[256];
        char **values=new char*[256];
        char *ipaddr=new char[256];
	char *portno=new char[256];
	char *chunk=new char[256];
	char *tsha1=new char[256];
	int i=0,j=0,cnt=0,tot=0;
        int no_chunk;
        bool flag=false;
	while(c!=EOF){
		fscanf(fp,"%s",buffer);
                if(strcmp(buffer,filepath)==0) tot++;
		c=fgetc(fp);
	}
	rewind(fp);
	write(newsockfd,&tot,sizeof(int));

        while(ch!=EOF){
            cnt++;
            fscanf(fp,"%s",buffer);
	    /*values[i]=new char[256];
            strcpy(values[i],buffer);
	    //cout<<values[i]<<"\n";
	    if(i<10){
		    values[i]=new char[256];
		    strcpy(values[i],buffer);
	            cout<<values[i]<<"\n";
	    }
	    if(cnt==4){
		    strcpy(chunk,buffer);
		    no_chunk=stoi(chunk);
		    cout<<"no_chunks"<<" "<<no_chunk<<"\n";
		    no_chunk<<=1;
		    flag=true;
	    }
            else if(flag){
		    no_chunk--;
		    if(!no_chunk) break;
	    }
	    i++;
	    //cout<<buffer<<"\n";*/
            if(!flag and strcmp(buffer,filepath)==0) flag=1;
            if(flag){
		    //cout<<cnt<<" ";
		    if(cnt==2){
                            strcpy(cid,buffer);
                           // cout<<tsha1<<"\n";
                            write(newsockfd,cid,256);
                    }
		    else if(cnt==3){
			    strcpy(ipaddr,buffer);
			    write(newsockfd,ipaddr,256);
			    //cout<<ipaddr<<"\n";
		    }
		    else if(cnt==4){
			    strcpy(portno,buffer);
			    write(newsockfd,portno,256);
		    }
		    else if(cnt==5){
			    //cout<<chunk<<"\n";
                            strcpy(chunk,buffer);
                            no_chunk=atoi(chunk);
			    write(newsockfd,chunk,128);
			    no_chunk<<=1;
                    }
                    else if(cnt==6){
                            strcpy(tsha1,buffer);
			   // cout<<tsha1<<"\n";
			    write(newsockfd,tsha1,128);
		    }
		    else if(cnt>6){
                            int k;
                            if((cnt%2)){
				    keys[i]=new char[256];
                                    strcpy(keys[i],buffer);
				    //cout<<keys[i]<<"\n";
				    i++;
                            }
                            else{
                                    values[j]=new char[256];
                                    strcpy(values[j],buffer);
                                    j++;
                            }
                            no_chunk--;
                            if(!no_chunk){
				    cnt=0;
//				    for(int p=0;p<j;p++)
//					    cout<<keys[p]<<" ";
				    char szi[128],szj[128];
				    sprintf(szi,"%d",i);
				    sprintf(szj,"%d",j);
				    //cout<<szi<<" "<<szj<<"\n";
                                    write(newsockfd,szi,128);
				    for(int p=0;p<i;p++){
                                        write(newsockfd,keys[p],256);
                                    }
				    write(newsockfd,szj,128);
				    for(int p=0;p<j;p++){
					write(newsockfd,values[p],256);
				    }
				    i=0;j=0;
				    flag=false;
				    cout<<"\n";
			    }
                    }
            }
	    else{
		    if(cnt==4){
			    strcpy(chunk,buffer);
                            no_chunk=atoi(chunk);
			    no_chunk<<=1;
		    }
		    else if(cnt>5){
			    no_chunk--;
			    if(!no_chunk){
				    cnt=0;
				    flag=false;
				    i=0;j=0;
			    }
		    }
	    }
            ch=fgetc(fp);
        }
}

int main(int argc,char **argv){
        int sockfd, newsockfd,portno;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
	portno=atoi(argv[1]);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
              error("ERROR on binding");
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
	char *filepath=(char*)"/home/aklesh/public/trackerinfo.txt";

        read_file(newsockfd,filepath);
	
	/*char ip[256];
	strcpy(ip,"127.0.0.1");
	write(newsockfd,ip,256);*/

	close(newsockfd);
	close(sockfd);
     
	/*char *filepath=(char*)"/home/aklesh/public/trackerinfo.txt";
	read_file(filepath);*/
	return 0;
}
