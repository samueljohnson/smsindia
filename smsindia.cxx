/*
 * qtsmsindia.cxx
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

//TODO: Implement a simple text based phonebook.

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
//#include <pwd.h>
#include "curl/curl.h"

int main(int argc, char* argv[]){
	char uid[14],pwd[20],phone[11],msg[141],url[500],temp[150];
	char configpath[15]="./config",phonebookpath[15]="./phonebook",line[30];
	int i=0,j=4,k=0;
	if(argc!=2){
		printf("Usage : smsindia <Destination ten digt phone number>\n");
		exit(-1);
	}
	strcpy(phone,argv[1]);
	if(isalpha(argv[1][0])){
		printf("Phone book not yet implemented!\n");
		printf("For the time being, just enter the phone number\n\n");
		return -1;
	}
	if(strlen(argv[1])!=10){
		printf("Enter 10 digit destination phone number\n\n");
		return -1;
	}
	FILE *cp=fopen(configpath,"r");
	//FILE *pp=fopen(phonebookpath,"r");
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
	//cout<<"Enter your username : ";
	//cin.getline(uid,11);
	//cout<<"Enter Password : ";
	//cin.getline(pwd,20);
	//cout<<"Enter Recipient Phone Number : ";
	//cin.getline(phone,11);
	//cout<<"To : "<<phone<<endl;
	printf("To : %s \n",phone);
	//cout<<"Enter your Message : ";
	printf("Enter your Message : ");
	//Following is the code to replace spaces with '%20'
	//cin.getline(msg,141);
	gets(msg);
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
	//http://ubaid.tk/sms/sms.aspx?uid=9787932732&pwd=wayyer&phone=9486684171&msg=%27Samuel%20Johnson%27&provider=way2sms
	strcpy(url,"http://ubaid.tk/sms/sms.aspx?uid=");
	strcat(url,uid);
	strcat(url,"&pwd=");
	strcat(url,pwd);
	strcat(url,"&phone=");
	strcat(url,phone);
	strcat(url,"&msg=");
	strcat(url,msg);
	strcat(url,"&provider=way2sms");
	//strcpy(url,"http://ubaid.tk/sms/sms.aspx?uid=9787932732&pwd=wayyer&phone=9486684171&msg='Samuel'&provider=way2sms");
	printf("%s\n\n",url);
	//if(curl){
		//curl_easy_setopt(curl, CURLOPT_URL, url);
		//res = curl_easy_perform(curl);
		////printf("Res is %d",res);
		///* always cleanup */ 
		//curl_easy_cleanup(curl);
	//}
	return 0;
}
