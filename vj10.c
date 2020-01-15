#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 50
struct Cvor;
typedef struct Cvor *Pozicija;
typedef struct Cvor {
	char el;
	Pozicija lijevo;
	Pozicija desno;
}cvor;
struct Element;
typedef struct Element *Stog;
typedef struct Element {
	Pozicija x;
	Stog next;
}element;
int push(Stog, Pozicija);
Pozicija pop(Stog);
int procitaj(Stog, char*);
Pozicija StvoriNovu(char);
void ispis(Pozicija, char*, int*);
int upisi(char, char*, int*);
int upisiUDat(char*,char*, int);
int main() {
	int i = 0;
	Stog stog=NULL;
	char niz[MAX]={'0'};
	stog = (Stog)malloc(sizeof(element));
	if (stog == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}
	stog->next = NULL;
	procitaj(stog,  "postfiks.txt");
	ispis(stog->next->x, niz, &i);
	upisiUDat(niz, "infiks.txt", i);
	return 0;
}


int push(Stog s, Pozicija p)
{
	Stog q = NULL;
	q = (Stog)malloc(sizeof(element));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}
	q->x = p;
	q->next = s->next;
	s->next = q;
	return 0;
}

Pozicija pop(Stog s)
{
	Pozicija a = NULL;
	Stog temp = NULL;
	if (s->next == NULL)
		return NULL;
	a = s->next->x;
	temp = s->next;
	s->next = temp->next;
	free(temp);
	return a;

}
int procitaj(Stog s, char* ime) {
	FILE* ul=NULL;
	char* niz=NULL;
	int znak=0;
	int numB=0;
	int n=0;
	Pozicija temp = NULL;
	Pozicija a = NULL;
	Pozicija b = NULL;
	niz = (char*)malloc(sizeof(char)*MAX);
	if (niz == NULL) {
		printf("Greska pri alokaciji memorije");
		return -1;
	}
	ul = fopen(ime, "r");
	if (ul == NULL) {
		printf("Greska pri otvaranju datoteke");
		return -1;
	}
	fgets(niz, MAX, ul);
	while (*niz != '\n') {
		n = sscanf(niz, " %d %n", &znak, &numB);
		if (n == 1) {
			temp = StvoriNovu(znak + '0');
			push(s, temp);
			niz = niz + numB;
		}
		else if (n == 0) {
			if (*niz == '+' || *niz == '-' || *niz == '*' || *niz == '/') {
				temp = StvoriNovu(*niz);
				a = pop(s);
				if (s != NULL)
					temp->desno = a;
				b = pop(s);
				if (s != NULL)
					temp->lijevo = b;
				push(s, temp);
				niz = niz + numB;
			}
		}
	}
	fclose(ul);
	return 0;
}
Pozicija StvoriNovu(char c) {
	Pozicija p = NULL;
	p = (Pozicija)malloc(sizeof(cvor));
	if (p == NULL) {
		printf("Greska pri alokaciji memorije");
		return NULL;
	}
	p->desno = NULL;
	p->lijevo = NULL;
	p->el = c;
	return p;
}

void ispis(Pozicija p,  char* niz, int* i) 
{
	if (p != NULL) {
		if (p->lijevo != NULL)
		{
			upisi('(', niz, i);
			ispis(p->lijevo, niz, i);
			upisi(')', niz, i);
		}

		upisi(p->el, niz, i);
		if(p->desno!=NULL)
		{
			upisi('(', niz, i);
			ispis(p->desno, niz, i);
			upisi(')', niz, i);
		}
	}
}

int upisi(char c, char* niz, int* i) {
	niz[*i] = c;
	(*i)++;
	return 0;
}

int upisiUDat(char*niz, char*dat, int n)
{
	int i = 0;
	FILE*izl = NULL;
	izl = fopen(dat, "w");
	if (izl == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	for (i = 0; i < n; i++)
		fprintf(izl,"%c ", niz[i]);
	fclose(izl);
	return 0;

}