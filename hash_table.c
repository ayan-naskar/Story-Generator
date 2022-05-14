#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

#include "common structure.h"

#define si(n) scanf("%d",&n)
#define sf(n) scanf("%f",&n)
#define sd(n) scanf("%lf",&n)
#define sc(n) scanf("%c",&n)
#define su(n) scanf("%u",&n)

#define pi(n) printf("%d\n",n)
#define pf(n) printf("%f\n",n)
#define pd(n) printf("%lf\n",n)
#define pc(n) printf("%c\n",n)
#define pu(n) printf("%u\n",n)

#define PI 3.1415926535897932384626
#define fo(i,n) for(i=0;i<n;i++)

#define prr(p,n) p=(int*)malloc(sizeof(int)*n)
#define srr(p,n) p=(char*)malloc(sizeof(char)*n)
#define ll long long
#define ui unsigned int

#define prime_num 7919
#define max 500

unsigned long some_cons = 1571;
int size = max;
int COUNTKEYS=0;

void create_hash(){
	int i;
	ar=(struct hash_table*)malloc(max * sizeof(struct hash_table));
	fo(i,max) ar[i].hash=0;
}

void increaseSize(){
	int i;
	size+=500;
	ar=(struct hash_table*)realloc(ar,size * sizeof(struct hash_table));
	fo(i,500) ar[i+size-500].hash=0;
}

int hashcode1(int key){
	return key%some_cons;
}

int hashcode2(int key){
	return prime_num-(key%prime_num);
}

int getHash(char *a){
	int i=0,h1,h2,qqqqq;
	char c;
	//unsigned long key=0;
	unsigned long key = 5381;
	while(a[i]!='\0'){
		//key=key*(pow(1.15,i))+(a[i]-' ');

		c=a[i];
		//key = ((key << 5) + key) + c;

		key = c + (key << 6) + (key << 16) - key;

		i++;
	}
 	h1=hashcode1(key);h2=hashcode2(key);
 	qqqqq=(h1+(i*h2))%size;
 	//pi(qqqqq);
	return qqqqq;
}

void insert(char *key,struct node *value){
	int h=getHash(key);
	here: if(ar[h].hash==h && strcmp(ar[h].key,key)!=0){
		//printf("Already present!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		/*printf("\nword already present = ");
		puts(ar[h].key);
		printf("Incomming word: ");
		puts(key);
		puts("----------------------");*/
		//some_cons++;
		h++;
		goto here;
	}

	strcpy(ar[h].key,key);
	ar[h].value=value;
	ar[h].hash=h;
	COUNTKEYS++;
}

struct node* create_list(){
	int n,i;
	char w[30];
	float prob;
	struct node *p,*q;
	p=NULL;
	printf("Enter the number of Words: ");
	si(n);
	fo(i,n){
		//puts("output");
		fflush(stdin);
		gets(w);
		//fflush(stdin);
		//sf(prob);
		q=(struct node*)malloc(sizeof(struct node));
		strcpy(q->word,w);
		q->probability=prob;
		q->next=NULL;
		if(p!=NULL){
			q->next=p;
		}
		p=q;
		//puts(q->word);
	}
	return p;
}

void show_hashtable(){
	int i;
	int countqqqq=0;
	struct node *p;
	fo(i,size){
		if(ar[i].hash!=0){
			countqqqq++;
			//printf("\n----------------\nkey = ");
			puts(ar[i].key);
			//printf("Hash = %d\n",ar[i].hash);
			//printf("[");
			if(ar[i].value!=NULL){
				p=ar[i].value;
				while(p!=NULL){
					//printf("word = ");
					//puts(p->word);
					//printf("probability = %f\n\n",p->probability);
					//printf("%s(%f)\t",p->word,p->probability);
					p=p->next;
				}
			}
			/*else{
				printf("\n-------NULL-------\n");
			}
			printf("]\n-------------------\n");*/
			
		}
	}
	printf("\ncountqqqq=%d",countqqqq);
}

struct node* reference(char *a){
	int i,h;
	h=getHash(a);
	return ar[h].value;
}

void add_WORD(char *key, char *word, float prob){
	int h=getHash(key);
	struct node* p=(struct node*)malloc(sizeof(struct node));
	p->probability=prob;
	strcpy(p->word,word);
	p->next=ar[h].value;
	ar[h].value=p;
}

int countKeys(){
	return COUNTKEYS;
}



/*int main()// not the MAIN main to run the program!!
{
	int i,j,n,t,a,b;
	int *p;
	char w[30];
	struct node *q;
	create_hash();
	while(true){
		printf("\nEnter 1 to insert, Enter 2 to show the hashtable, else to terminate: ");
		si(a);
		switch(a){
			case 1:
			fflush(stdin);
			printf("Enter the phrase: ");
			gets(w);
			q=create_list();
			insert(w,q);
			break;
			case 2:
			printf("\nThe hash_table is->\n");
			show_hashtable();
			break;
			default:
			return 0;
		}
	}
}*/

/*
1
at the
2
cat
0.5
rat
0.5

1
cat spat
2
at
0.5
on
0.5

1
fat rat
2
jump
0.5
put
0.5

1
it is
1
now
1

1
on the
4
cat
0.1428571
flat
0.1428571
hat
0.42857142
rat
0.2857142
*/