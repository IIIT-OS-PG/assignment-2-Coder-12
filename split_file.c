#include <bits/stdc++.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <openssl/sha.h>
#define BUFFS 2048*16

using namespace std;

unsigned char* encrypt(FILE *fp){
        SHA_CTX c;
        unsigned char *md=new unsigned char[SHA_DIGEST_LENGTH];
	unsigned char *buffer=new unsigned char[BUFFS];
        int i,fd=fileno(fp);
        SHA1_Init(&c);
        while(1){
            i=read(fd,buffer,BUFFS);
            if(i<=0) break;
            SHA1_Update(&c,buffer,(unsigned long)i);
        }
        SHA1_Final(&(md[0]),&c);
	return md;
        /*for(int i=0;i<SHA_DIGEST_LENGTH;i++)
                printf("%02x",md[i]);
        printf("\n");*/
}
FILE *openforwrite(int filecounter){
	char fileout[20];

	sprintf(fileout,"file_part%d",filecounter);
	return fopen(fileout,"w");
}

int split_file(char *filename){
	FILE *ptr_readfile,*ptr_writefile;
        char line[128];
	//char *filename=(char*)"/home/aklesh/OS_DIR_P2P/p2p_client.cpp";
        int filecounter=1,linecounter=1,temp;

        if((ptr_readfile = fopen(filename,"r"))==NULL){
                perror("Fileopen error\n");
                exit(1);
        }
        ptr_writefile=openforwrite(filecounter);

        while(fgets(line,sizeof line,ptr_readfile)!=NULL){
                if(linecounter==5){
                        fclose(ptr_writefile);
                        linecounter=1;
                        temp=filecounter;
                        filecounter++;
                        if((ptr_writefile=openforwrite(filecounter))==NULL){
                                perror("No write file\n");
                                exit(1);
                        }
                        //printf("SHA1(file_part%d)= ",temp);
                        //encrypt(ptr_writefile);
                }
                fprintf(ptr_writefile,"%s\n",line);
                linecounter++;
        }
        for(int i=1;i<=filecounter;i++){
            char fname[]="/home/aklesh/OS_DIR_P2P/file_part";
            int x=strlen(fname);
            if(i>=10){
               string str;
               int n=i;
               while(n>0){
                       str.push_back((char)(n%10+'0'));
                       n/=10;
               }
               for(int i=str.size()-1;i>=0;i--)
                       fname[x++]=str[i];
            }
            else fname[x++]=(char)(i+'0');
            fname[x]='\0';
            FILE *fp;
            if((fp=fopen(fname,"r"))==NULL){
                    perror("Unable to open");
                    exit(EXIT_FAILURE);
            }
            unsigned char *md=new unsigned char[SHA_DIGEST_LENGTH];
            md=encrypt(fp);
            //for(int i=0;i<SHA_DIGEST_LENGTH;i++)
              //  printf("%02x",md[i]);
            //cout<<std::endl<<std::endl;
        }
	return filecounter;

}
int main(){
	FILE *ptr_readfile,*ptr_writefile;
	char line[128],*filename=(char*)"/home/aklesh/OS_DIR_P2P/p2p_client.cpp";
	int filecounter=1,linecounter=1,temp;

	if((ptr_readfile = fopen(filename,"r"))==NULL){
		perror("Fileopen error\n");
		exit(1);
	}
	ptr_writefile=openforwrite(filecounter);

	while(fgets(line,sizeof line,ptr_readfile)!=NULL){
		if(linecounter==5){
			fclose(ptr_writefile);
                        linecounter=1;
		        temp=filecounter;
			filecounter++;
			if((ptr_writefile=openforwrite(filecounter))==NULL){
				perror("No write file\n");
				exit(1);
			}
			//printf("SHA1(file_part%d)= ",temp);
			//encrypt(ptr_writefile);
		}
		fprintf(ptr_writefile,"%s\n",line);
                linecounter++;
	}
	for(int i=1;i<=filecounter;i++){
	    char fname[]="/home/aklesh/OS_DIR_P2P/file_part";
	    int x=strlen(fname);
	    if(i>=10){
               string str;
	       int n=i;
	       while(n>0){
		       str.push_back((char)(n%10+'0'));
		       n/=10;
	       }
	       for(int i=str.size()-1;i>=0;i--)
		       fname[x++]=str[i];
	    }
	    else fname[x++]=(char)(i+'0');
	    fname[x]='\0';
	    FILE *fp;
	    if((fp=fopen(fname,"r"))==NULL){
		    perror("Unable to open");
		    exit(EXIT_FAILURE);
	    }
	    unsigned char *md=new unsigned char[SHA_DIGEST_LENGTH];
            md=encrypt(fp);
	    for(int i=0;i<SHA_DIGEST_LENGTH;i++)
                printf("%02x",md[i]);
	    //cout<<std::endl<<std::endl;
	} 
	fclose(ptr_readfile);
	return 0;
}
