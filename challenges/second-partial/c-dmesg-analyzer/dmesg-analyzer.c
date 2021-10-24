#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <fcntl.h> 
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define HASHSIZE 1024
#define REPORT_FILE "file.txt"

struct Node
{
    char  *data;
    struct Node *next;
}; 

// nlist func
struct nlist{
    struct nlist *next;
    char *name;
    char *defi;
    struct Node *vals;
};

void push(struct Node** head_ref, char *new_data)
{
    struct Node* new_node = (struct Node*)calloc(1,sizeof(struct Node));
  
    new_node->data  =strdup(new_data);
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

static struct nlist *hashtablee[HASHSIZE];

unsigned hash(char *s){
    unsigned hashvalue;
    for (hashvalue = 0; *s != '\0'; s++){
        hashvalue = *s + 31 * hashvalue;
    }
    return hashvalue % HASHSIZE;
}

// estructura de nlist
struct nlist *lookup(char *s){
    struct nlist *np;
    for(np = hashtablee[hash(s)]; np != NULL; np = np->next){
        if(strcmp(s, np->name) == 0){
            return np; 
        }
    }
    return NULL; 
}

struct nlist *install(char *name, char *defi){
    struct nlist *np;
    unsigned hashvalue;
    if((np=lookup(name))==NULL){ 
        np = (struct nlist *) calloc(1,sizeof(*np));
        if(np == NULL || (np->name=strdup(name))==NULL){
            return NULL;
        }
        hashvalue = hash(name);
        np->next = hashtablee[hashvalue];
        hashtablee[hashvalue] = np;
        np->vals=NULL;
    }else
        free((void *)np->defi);
    if((np->defi = strdup(defi))==NULL)
        return NULL;
    push(&np->vals,defi);
    return np;
}



struct data{
    char *category; 
    char *info; //data para Log
};

struct data arrangeData(char *s){
    struct data ready; // data sorteada

    int blan = 0;
    int strLength = 0;
    int colons = 0;
    int catLength = 0;
    
    char *time; 
    char *desc; 
    char *cur = s; //current
    char *cat;

    while(*cur){
        strLength++;
        cur++; // add to current
        if(*(cur-1)==']') break; 
    }

    if(strLength<1){
        ready.category = "General"; // asign category
        ready.info = (char*)malloc(strlen(s)*sizeof(char)+1);
        strcpy(ready.info, s);
        return ready;
    };

    time = (char*)malloc(strLength*sizeof(char));
    strncpy(time, s, strLength); 

    while(*cur){
        if(catLength == 0 && *cur == ' '){
            blan++;
        }else if(colons && *cur == ' '){
            break;
        }else if(!colons && *cur==':'){
            colons++;
            catLength++;
        }else{
            catLength++;
        }
        cur++;
    }

    if(colons){
        desc = (char*)malloc(strlen(s)*sizeof(char)-blan-catLength+1);
        strcpy(desc, time);
        strcat(desc, cur);

        cat = (char*)malloc(catLength*sizeof(char));
        strncpy(cat, s+blan+strLength, catLength);
    }else{
        cat = (char*)malloc(strlen("General")*sizeof(char)+1);
        strcpy(cat,"General");
        desc = (char*)malloc(strlen(s)*sizeof(char)+1);
        strcpy(desc,s);
    }
    ready.category = cat;
    ready.info = desc;
    return ready;
}
// Hashtab finished

void analizeLog(char *logFile, char *report);

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./dmesg-analizer logfile.txt\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);
    // Implement your solution here.
    int file = open(logFile, O_RDONLY);
	if (file == -1){ // error 
        printf("Error reading the log file\n");
        return;
    }

    int bytesRead;
	int fileLen = 0;
    int newLine = 1;
	char buffee;
    
	do {
        
        bytesRead = read(file, &buffee, 1);
        if(newLine && bytesRead>0) {
            fileLen++;
            newLine=0;
        }
        if(buffee=='\n') newLine=1;
    } 
    while (bytesRead>0);

    printf("Analyzing: %d lines\n",fileLen);
    lseek(file,0,SEEK_SET);
    int lineLength = 0;
    do{
        bytesRead = read(file, &buffee, 1);
        if(bytesRead>0){
            if(buffee =='\n'){
                if(lineLength<1){
                    continue;
                }

                lineLength++;
                lseek(file,-lineLength,SEEK_CUR);
                char* lineBuff = (char*) malloc(lineLength*sizeof(char));
                read(file,lineBuff,lineLength);
                lineBuff[strcspn(lineBuff, "\n")] = 0;
                lineLength=0;
                struct data datos = arrangeData(lineBuff);
                install(datos.category,datos.info);
            }else{
                lineLength++;
            }
        }
    } while(bytesRead>0);

    close(file);

    // report generation
    FILE *result = fopen(report, "w+");
    struct nlist *start;  // start the hashtable

    for(int i=0; i<=HASHSIZE; i++){
        start=hashtablee[i];
        if(start==NULL) continue;
        fputs(start->name, result);
        fputs("\n", result);
        struct nlist *cur; // current
        for(cur = start; cur!=NULL; cur = cur->next){
            fputs(" ", result);
            fputs(cur->defi, result);
            fputs("\n", result);
        }
    }
    fclose(result);

    // notify user 
    printf("Report is generated at: [%s]\n", report);
}
// References: https://www.geeksforgeeks.org/generic-linked-list-in-c-2/