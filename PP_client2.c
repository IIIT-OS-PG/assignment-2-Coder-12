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
#include <time.h>
#include <openssl/sha.h>
#include "create_user.c"
#include "login.c"
#include "create_group.c"
#include "join_group.c"
#include "split_file.c"

#define vi vector<int>
#define vs vector<std::string>
#define SERVPORT 8991
#define BUFSIZE 4096
#define SERROR (-1);
#define QLEN 100

using namespace std;

int clientid=2;

string client_id(std::string("1"));
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

void *handle_connection(void* pclient);
int check(int exp,const char *msg);
void create_tracker_socket(char *pno);
void create_client_socket(char *pno);
void download_file(char *gid,char *filename,char *destpath);

char ch;
char *cid=new char[256];
char **keys=new char*[256];
char **values=new char*[256];
char *ip=new char[256];
char *nportno=new char[256];
char *chunk=new char[256];
char *tsha1=new char[256];
char *szi=new char[256];
char *szj=new char[256];
char buffer[100][4096];
int tot;
int no_chunk;

void *upload_sock(int n,int cid,void* pclient);
void check(int exp,const char *msg);

vi cli_id(100),nport(100),chnk(100),sz_i(100),sz_j(100);
vector<vi> chnkno(100);
vector<vs> hash(100);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void seperator(char *str,vector<string> &parsedstr){
        int i=0;
        char *token=strtok(str," ");
        while(token){
		string s_tok(token)
                parsedstr.push_back(s_tok);
                token=strtok(NULL,"\n");
        }
}
void upload_file(char *filepath,char *grid){
	char *tsha1=new char[SHA_DIGEST_LENGTH];
	tsha1=encrypt(filepath);
	vector<std::string> sha1=split_file(filepath);
	int no_chunk=sha1.size();
	int MAX_CLNT=0;
	FILE *fp;
        char *line=NULL;
        size_t len=0;
        ssize_t r;
        bool flag=false;
        string path("/home/aklesh/public/group"),cpath("/home/aklesh/"),gid(grid);
        cpath+=std::string("P2P_C")+std::to_string(clientid);
        path+=gid+".txt";
	vector<int> client;
        if((fp=fopen(&(path[0]),"r"))==NULL){
                perror("Unable to open\n");
                exit(EXIT_FAILURE);
        }
        while((r=getline(&line,&len,fp))!=-1){
                //string cid(line),path(std::string("/home/aklesh/P2P_C"));
                if(line!=client_id){
                      path+=cid;
                      int x=atoi(line);
                      client.push_back(x);
		      MAX_CLNT=max(MAX_CLNT,client[i]);
                }
        }
        int *clnt=new int[client.size()];
	int *no_file=new int[MAX_CLNT+1];
	for(int i=0;i<client.size();i++) clnt[i]=client[i];
	FILE *f;
        f=fopen("/home/aklesh/public/trackerifo.txt","a+");
        int y=no_chunks;
        for(int i=0;i<client.size();i++){
                if(i<client.size()-1){
                   int x=rand()%y;
                   no_file[client[i]]=y;
                   y-=x;
                }
                else no_file.push_back(y);
        }
	int sum=0;
	for(int i=0;i<client.size();i++){
            fprintf(f,"%s ",filepath);
            fprintf(f,"%s ","127.0.0.1");
            fprintf(f,"%s ",std::to_string(portno));
            fprintf(f,"%s ",std::to_string(no_file[i]));
            fprintf(f,"%s ",tsha1);
            portno++;
            string path("/home/aklesh/P2P_C");
            path+=clientid+"/";
            for(int j=sum;j<=(no_file[i]+sum);j++){
                    ostringstream s;
                    s<<i;
                    path+=std::string(s.str());
                    FILE *fp;
                    fp=fopen(path,"r");
                    fprintf(f,"%s ",std::to_string(i));
                    if(i<n) fprintf(f,"%s ",sha1[i]);
                    else{
                            fprintf(f,"%s",sha1[i]);
                            fprintf(f,"%s","\n");
                     }
                     char ch;
                     while(ch!=EOF){
                           fscanf(fp,"%s",buffer);
                           ch=fgetc(fp);
                     }
             }
             sum+=no_file[i];
        }

        fclose(fp);

	int sockfd, portno=7000, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        char buffer[256],*ipaddr=(char*)"127.0.0.1";
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        server = gethostbyname(ipaddr);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");
        printf("\nConnection enstablished\n");

        int server_socket,client_socket,addr_size;
        sockaddr_in  server_addr,client_addr;

	check((server_socket=socket(AF_INET,SOCK_STREAM,0)),
		"Failed to create socket\n");
        
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(SERVPORT);

	check(bind(server_socket,(sockaddr*)&server_addr,sizeof(server_addr)),
			"Bind Failed\n");
	check(listen(server_socket,100),"Listen Failed\n");

	while(1){
		printf("Waiting for connection....\n");
		addr_size=sizeof(SA_IN);
		check(client_socket=
			accept(server_socket,(SA*)&client_addr,
				(socklen_t*)&addr_size),"accept failed\n");
		printf("Connected\n");
                       
		pthread_t t;
		int *pclient=(int*)malloc(sizeof(int));
		*pclient=client_socket;
		pthread_create(&t,NULL,upload_sock,no_file[i],clientid,pclient);

	}

}

int check(int exp,const char *msg){
	if(exp==-1){
		perror(msg);
		exit(1);
	}
	return exp;
}

void *upload_sock(int n,int cid,void* pclient){
	if(cid!=clientid) return NULL;

	int client_socket=*((int*)pclient);
	free(pclient);
	char buffer[BUFSIZE];
	size_t bytes_read;
	int msgsize=0;

	FILE *fp;
        std::string path("/home/aklesh/P2P_C"),t_path;
        path+=std::string(std::to_string(cid))+"/";
	for(int i=0;i<n;i++){
	     tpath=path+std::to_string(i+1);
	     fp=fopen(tpath,"a+");
             while((bytes_read=fread(buffer,1,BUFSIZE,fp))>0){
		    printf("send %zu bytes\n",bytes_read);
		    write(client_socket,buffer,bytes_read);
	     }
	}
        close(client_socket);
	fclose(fp);
        printf("Closing connection\n");
	return NULL;
}

void download_file(char *gid,char *filename,char *destpath){
	create_tracker_socket(8000);
	int sockfd, portno=7000, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        char buffer[256],*ipaddr=(char*)"127.0.0.1";
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        server = gethostbyname(ipaddr);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");
        printf("\nConnection enstablished\n");
       
        int i=0,j,cnt=0;	
	pthread_t tid[tot];
	while(i<tot){
		if(pthread_create(&tid[i],NULL,create_client_socket,chnkno[cli_id[i]],nport[i],cli_id[i])!=0){
			perror("Failed to create thread\n");
			exit(1);
		}
	        i++;
	}
	sleep(20);
	i=0;
	while(i<tot){
		pthread_join(tid[i++],NULL);
	}

	std::string d_path("/home/aklesh/P2P_C");
	d_path+=std::string(std::to_string(clientid))+std::string("/output_received.c");
        FILE *fp=fopen(d_path,"a+");
	map<int,int> c_no;
	for(int i=0;i<tot;i++){
		for(int j=0;j<chnk.size();j++){
			c_no[chnkno[cli_id[i]][chnk[j]]]++;
		}
	}
	for(auto &v:c_no){
            fprintf(fp,"%s ",buffer[v.first]);
	}
  	close(sockfd);

}
void create_tracker_socket(int portno){
	int sockfd,n;
        struct sockaddr_in serv_addr;
        struct hostent *server;

        char buffer[256],*ipaddr=(char*)"127.0.0.1";
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        server = gethostbyname(argv[1]);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
              (char *)&serv_addr.sin_addr.s_addr,
              server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");
        bzero(buffer,256);

        read(sockfd,&tot,sizeof(int));

        for(int p=0;p<tot;p++){
	      int a,b,c,d,e,f; 
              read(sockfd,cid,256);
              read(sockfd,ip,256);
              read(sockfd,nportno,256);
              read(sockfd,chunk,128);
              read(sockfd,tsha1,128);
              read(sockfd,szi,128);
              a=atoi(cid);b=atoi(nportno);
	      c=atoi(chunk);d=atoi(szi);
	      cli_id.push_back(a);
	      nport.push_back(b);
	      chnk.push_back(c);
	      sz_i.push_back(d);
              for(int p=0;p<d;p++){
                  keys[p]=new char[256];
                  read(sockfd,keys[p],256);
                  e=atoi(key[p]);
		  chnkno[a].push_back(e);
               }
               read(sockfd,szj,128);
               f=atoi(szj);
	       sz_j.push_back(f);
               for(int p=0;p<f;p++){
                  values[p]=new char[256];
                  read(sockfd,values[p],256);
		  string h(value[p]);
                  hash[a].push_back(h);
               }
	}
	close(sockfd);
}

void create_client_socket(vector<int> &pno,int portno,int cid){
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,10);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
     if (newsockfd < 0)
          error("ERROR on accept");

     std::string path("/home/aklesh/P2P_C"),t_path;
     path+=std::string(std::to_string(cid)); 
     for(int i=0;i<chnkno.size();i++){
	     t_path=path;
	     t_path+=std::string(std::to_string(chnkno[i]));
	     FILE *fp;
	     check(fp=fopen(tpath,"r"),"Unable to open\n");
	     int bytes_read;
	     bytes_read=fread(buffer[chnkno[i]],sizeof(char),BUFSIZE,fp);
	     if(bytes_read<0){
		     perror("ERROR in reading file\n");
		     return;
	     }
     }
     cout<<"Closing client\n"<<"\n";
     close(newsockfd);
     close(sockfd);     
}

void process_cmd(char *str){
	vector<string> parsedstr;
	seperator(str,parsedstr);
        if(parsedstr[0]==std::string("create_user"))
	     create_user(&(parsedstr[1]),&(parsedstr[2]));
	else if(parsedstr[0]==std::string("login"))
	     login(&(parsedstr[1]),&(parsedstr[2]));
	else if(parsedstr[0]==std::string("create_group"))
	     create_group(&(parsedstr[1]),&(parsedstr[2]));
	else if(parsedstr[0]==std::string("upload_file"))
	     upload_file(&(parsedstr[1]),&(parsedstr[2]));
	else if(parsedstr[0]==std::string("download_file"))
	     download_file(&(parsedstr[1]),&(parsedstr[2]),&(parsedstr[3]));
}

int main(int argc, char *argv[]){
	memset(buffer,0,sizeof(buffer));
        string str;
	getline(cin,str);
	process_cmd(&(str[0]));
        return 0;
}

