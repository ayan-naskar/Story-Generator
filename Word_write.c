//gcc -o output Word_write.c hash_table.c
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
#include<time.h>
#include<conio.h>

#include "hash_table.h"

#define si(n) scanf("%d",&n)
#define sf(n) scanf("%f",&n)
#define sd(n) scanf("%lf",&n)
#define sc(n) scanf("%c",&n)
#define su(n) scanf("%u",&n)

#define pi(n) printf("%d\n",n)
#define pf(n) printf("%f\n",n)
#define pd(n) printf("%lf\n",n)
#define pc(n) printf("%c",n)
#define pu(n) printf("%u\n",n)

#define PI 3.1415926535897932384626
#define fo(i,n) for(i=0;i<n;i++)

#define prr(p,n) p=(int*)malloc(sizeof(int)*n)
#define srr(p,n) p=(char*)malloc(sizeof(char)*n)
#define ll long long
#define ui unsigned int

struct node *PREVIOUSword,*head=NULL;

bool okay(char a){
	if((a>='a' && a<='z')||(a=='\''))
		return true;
	return false;
}

void setWord(char *w){
	struct node* newWORD=(struct node*)malloc(sizeof(struct node));
	strcpy(newWORD->word,w);
	newWORD->probability=0;
	newWORD->next=NULL;
	if(head==NULL){
		head=newWORD;
	}
	else{
		PREVIOUSword->next=newWORD;
	}
	PREVIOUSword=newWORD;
}

void makeList(const char *FILEname){
	int i,j=0;
	char c,word[30],a;
	FILE *op=fopen(FILEname,"r");
	if(op==NULL){
		printf("\n\nError opening the file.\nExecution terminated.");
		exit(0);
	}
	printf("\nFile found, Copying required files...");
	for(a=fgetc(op);a!=EOF;a=fgetc(op)){
		a=tolower(a);
		if(okay(a)){
			word[j]=a;
			j++;
		}
		else if(a==' ' || a=='\n'){
			word[j]='\0';
			//puts(word);
			setWord(word);
			j=0;
		}
	}
	puts("Done Making the List");
}

void showList(){
	struct node *n=head;
	char ch;
	int i, number=0;
	while(n!=NULL){
		i=0;
		ch=n->word[0];
		while(ch!='\0'){
			pc(ch);
			i++;
			ch=n->word[i];
		}
		printf("[%f], ",n->probability);
		n=n->next;
		number++;
	}
	printf("\nNumber of Words is : %d",number);
}

int countLength(){
	struct node *p=head;
	int c=0;
	while(p!=NULL){
		c++;
		p=p->next;
	}
	return c;
}

int countOccurence(char *wr){
	struct node *prw=head;
	int cou=0;
	while(prw!=NULL){
		if(strcmp(prw->word,wr)==0)
			cou++;
		prw=prw->next;
	}
	return cou;
}

void setprobability(){
	struct node *p=head;
	int occu,len=countLength();
	while(p!=NULL){
		occu=countOccurence(p->word);
		p->probability=(float)occu/(float)len;
		p=p->next;
	}
}

struct node* keyList(char *key){//returns the list of words for particular key
	struct node *p=head,*headp=NULL,*q;
	char x[100];
	int len=countLength()-2,i,j,k;
	fo(i,len){
		j=0;
		while(p->word[j]!='\0'){
			x[j]=p->word[j];
			j++;
		}
		x[j]=' ';
		j++;
		k=0;
		while(p->next->word[k]!='\0'){
			x[j]=p->next->word[k];
			j++;
			k++;
		}
		x[j]='\0';
		//printf("\nx is: ");
		//puts(x);
		if(strcmp(x,key)==0){
			q=(struct node*)malloc(sizeof(struct node));
			strcpy(q->word,p->next->next->word);
			q->probability=p->next->next->probability;
			q->next=NULL;
			if(headp==NULL)
				headp=q;
			else{
				q->next=headp;
				headp=q;
			}
		}
		p=p->next;
	}
	return headp;
}

void setPhrase(char *w1, char *w2){
	int i=0,j=0;
	struct node *poi;
	char neww[100];
	while(w1[i]!='\0'){
		neww[i]=w1[i];
		i++;
	}
	neww[i]=' ';
	i++;
	while(w2[j]!='\0'){
		neww[i]=w2[j];
		i++;
		j++;
	}
	neww[i]='\0';
	poi=keyList(neww);
	//printf("\npoi = %d, neww is: ",poi);
	//puts(neww);
	insert(neww,poi);
}

void createPhrase(){
	int len=countLength()-1,i;
	struct node *wr=head;
	fo(i,len){
		//puts("setting");
		setPhrase(wr->word,wr->next->word);
		wr=wr->next;
	}
}

char* getSTARTING_PHRASE(){
	char *phrase=(char*)malloc(sizeof(char)*100);
	//srand(time(0));
	int len=countLength()-1;
	int randNUM=rand()%len;
	struct node *ph=head;
	while(randNUM>0){
		randNUM--;
		ph=ph->next;
	}
	strcpy(phrase,ph->word);
	strcat(phrase," ");
	strcat(phrase,ph->next->word);
	//printf("\nphrase = ");
	//puts(phrase);
	return phrase;
}

char* getRandWord(char *phrase){
	//srand(time(0));
	int h=getHash(phrase);
	char* wordddd=(char*)malloc(sizeof(char)*30);
	while(strcmp(phrase,ar[h].key)!=0)
		h++;
	struct node *p=ar[h].value;
	float prob=(float)rand() / (float)((unsigned)RAND_MAX + 1);
	float tot=0.0;
	while(p!=NULL){
		tot+=p->probability;
		p=p->next;
	}
	p=ar[h].value;
	float c=0.0;
	while(p!=NULL){
		c+=(p->probability)/tot;
		if(prob<=c){
			strcpy(wordddd,p->word);
			break;
		}
		p=p->next;
	}
	return wordddd;
}

char* getLastWord(char *ph){
	char *lastword=(char*)malloc(sizeof(char)*100);
	int i=0,j=0,fl=0;
	while(ph[i]!='\0'){
		if(fl==1){
			lastword[j]=ph[i];
			j++;
		}
		else if(ph[i]==' ')
			fl=1;
		i++;
	}
	lastword[j]='\0';
	return lastword;
}

/*char* getSTORY(int maxCharactersInStory){//****************RUN THIS PART IF MAIN main is ran*****************
	char *str=(char*)malloc(sizeof(char)*(maxCharactersInStory+15));//15 is just large random number
	char *ph;
	char *randWordFromList;
	ph=getSTARTING_PHRASE();
	strcpy(str,ph);
	int currentCharacterLength=strlen(ph);
	while(currentCharacterLength<maxCharactersInStory){
		randWordFromList=getRandWord(ph);
		strcat(str," ");
		strcat(str,randWordFromList);
		ph=getLastWord(ph);
		strcat(ph," ");
		strcat(ph,randWordFromList);
		currentCharacterLength=strlen(str);
	}
	return str;
}*/

char* getSTORY(int maxCharactersInStory,char *ph){//ph is the starting phrase
	char *str=(char*)malloc(sizeof(char)*(maxCharactersInStory+15));//15 is just large random number
	//char *ph;
	char *randWordFromList;
	//ph=getSTARTING_PHRASE();
	strcpy(str,ph);
	int currentCharacterLength=strlen(ph);
	while(currentCharacterLength<maxCharactersInStory){
		randWordFromList=getRandWord(ph);
		strcat(str," ");
		strcat(str,randWordFromList);
		ph=getLastWord(ph);
		strcat(ph," ");
		strcat(ph,randWordFromList);
		currentCharacterLength=strlen(str);
	}
	return str;
}

void makeStory(char *genre){
	int i;
	makeList(genre);
	setprobability();
	create_hash();
	fo(i,10)increaseSize();
	createPhrase();
}

int main(){
	int ch;
	srand(time(0));
	int numberOfCharactersinStory;
	puts("Welcome to Story generator!!");
	puts("----------------------------");
	puts("To continue, press any key...");
	char *a,*b,*c;
	char A[20]="The Tempest.txt";
	char B[20]="Alice in WDRLND.txt";
	char C[20]="science fiction.txt";
	getch();
	puts("Select the desired genre of story:\n[1:SHAKESPEAREN ROMANCE]\t[2:KIDS ADVENTURE]\t[3:SCIENCE FICTION]");
	si(ch);//point 1 e probleem hoche******************
	switch(ch){
		case 1:
		makeStory(A);
		break;
		case 2:
		makeStory(B);
		break;
		case 3:
		makeStory(C);
		break;
		default:
		puts("Select 1, 2 or 3 from the list");
		return 0;
	}
	a=getSTARTING_PHRASE();
	b=getSTARTING_PHRASE();
	srand(time(0));
	c=getSTARTING_PHRASE();
	puts("Select the desired starting phrases from the list: ");
	printf("1: ");
	puts(a);
	printf("2: ");
	puts(b);
	printf("3: ");
	puts(c);
	si(ch);
	printf("Enter the size of the story [i.e., number of characters in the story]\nNo of Characters: ");
	si(numberOfCharactersinStory);
	switch(ch){
		case 1:
		puts(getSTORY(numberOfCharactersinStory,a));
		break;
		case 2:
		puts(getSTORY(numberOfCharactersinStory,b));
		break;
		case 3:
		puts(getSTORY(numberOfCharactersinStory,c));
		break;
		default:
		puts("Yaar thik se choose karo na!!");
		return 0;
	}
	puts("\t\t\t\t\t**************  THE END  ***************");
	
}

/*int main()//this the MAIN main to run the program
{
	int i,j,n,t,a,b;
	makeList("Alice in WDRLND.txt");
	setprobability();
	//showList();	

	create_hash();
	fo(i,4)
		increaseSize();
	//puts("DONE!!");
	createPhrase();
	//show_hashtable();
	a=countKeys();
	printf("\nNumber of keys= %d",a);
	puts(getSTARTING_PHRASE());
	puts("Enter the number of characters you want in your story: ");
	si(b);
	puts("The story is: ");
	puts(getSTORY(b));
}*/