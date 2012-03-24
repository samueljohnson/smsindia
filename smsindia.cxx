/*
 * smsindia.cxx
 * 
 * Copyright 2012 Samuel Johnson <esamueljohnson@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * compile with -lcurl
 * 
 */

//TODO 1 : Implement a simple text based phonebook. : DONE
//TODO 2 : Prompt to save new number in phonebook.

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include "curl/curl.h"

int phonebook(char*, char*);

int main(int argc, char* argv[]){
	char uid[14],pwd[20],phone[11],msg[600],url[500],temp[150];
	char configpath[15]="./config",line[30];
	int i=0,j=4,k=0;
	if(argc!=2){
		printf("Usage : smsindia <Destination ten digt phone number>\n");
		return -1;
	}
	strcpy(phone,argv[1]);
	if(strlen(argv[1])!=10&&isdigit(argv[1][0])){
		printf("Enter 10 digit destination phone number\n\n");
		return -1;
	}
	if(isalpha(argv[1][0])){
		if(!phonebook(argv[1],phone)){
			printf("Phone number not found\n");
			return -1;
		}
	}
	FILE *cp=fopen(configpath,"r");
	//
	fgets(line,200,cp);
	fgets(line,200,cp);
	while(line[j+1]!='\0'){
		uid[i++]=line[j++];
	}
	uid[i]='\0';
	i=0,j=4;
	fgets(line,200,cp);
	while(line[j+1]!='\0'){
		pwd[i++]=line[j++];
	}
	pwd[i]='\0';

	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	printf("To : %s \n",phone);
	printf("Enter your Message : ");
	//Following is the code to replace spaces with '%20'
	gets(msg);
	//fgets (msg, 140, stdin);
	for(i=0;msg[i]!='\0';i++){
		if(msg[i]==' '){
			msg[i++]='%';
			for(k=i,j=0;msg[k]!='\0';k++,j++){
				temp[j]=msg[k];
			}
			temp[j]='\0';
			msg[i++]='2';
			msg[i++]='0';
			msg[i]='\0';
			strcat(msg,temp);
			i--;
		}
	}
	//for(i=0;msg[i]!='\0';i++){
		//if(msg[i]=='\n'){
			//msg[i++]='%';
			//for(k=i,j=0;msg[k]!='\0';k++,j++){
				//temp[j]=msg[k];
			//}
			//temp[j]='\0';
			//msg[i++]='0';
			//msg[i++]='D';
			//msg[i]='\0';
			//strcat(msg,temp);
			//i--;
		//}
	//}
	strcpy(url,"http://ubaid.tk/sms/sms.aspx?uid=");
	strcat(url,uid);
	strcat(url,"&pwd=");
	strcat(url,pwd);
	strcat(url,"&phone=");
	strcat(url,phone);
	strcat(url,"&msg=");
	strcat(url,msg);
	strcat(url,"&provider=way2sms");
	puts(url);
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url);
		res = curl_easy_perform(curl);
		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	return 0;
}

int phonebook(char* name, char* phone){
	char line[200],found=0;
	int i,j;
	FILE *pp=fopen("./phonebook","r");
	while(fgets(line,200,pp)){
		if(strstr(line,name)){
			printf("%s\n",line);
			for(i=0;line[i]!=':';i++);
			i++;
			for(j=0;line[i]!='\n';i++,j++)
				phone[j]=line[i];
			phone[j]='\0';
			found=1;
			break;
		}
	}
	return found;
}
