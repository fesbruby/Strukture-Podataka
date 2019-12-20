
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
struct Element;
typedef struct Element* pok;
typedef struct Element {
	char ime[MAX];
	pok sibling;
	pok child;
}element;
struct Status;
typedef struct Status* Pozicija;
typedef struct Status {
	pok el;
	Pozicija next;
}status;
int mkdir(Pozicija,Pozicija, char*);
int mkRoot(pok,Pozicija,Pozicija,char*);
int push(Pozicija, pok);
pok pop(Pozicija);
int ispis(Pozicija);
int vracanjeUnatrag(Pozicija,Pozicija);
int cdDir(pok, Pozicija, Pozicija,pok,char *im);
int izbrisi(Pozicija);
int Odabir(pok,pok,Pozicija,Pozicija);
int main() {
	status stog;
	status razina;
	element stablo;
	pok pocetak=NULL;
	stog.next = NULL;
	razina.next = NULL;
	mkRoot(&stablo,&stog,&razina,"C:");
	pocetak = &stablo;
	Odabir(&stablo, pocetak, &stog, &razina);
	izbrisi(&stog);
	izbrisi(&razina);
	system("pause");
	return 0;
}
int mkRoot(pok s,Pozicija stog,Pozicija razina,char* im)
{
	s->sibling = NULL;
	s->child = NULL;
	strcpy(s->ime, im);
	push(stog,s);
	push(razina, s);
	return 0;
}
int mkdir(Pozicija stog,Pozicija razina, char *im) {
	pok n=NULL;
	pok temp=NULL;
	pok trenutni = NULL;
	trenutni = pop(stog);
	if (trenutni == NULL)
	{
		printf("Greska. Stog je prazan.\n");
		return -1;
	}
	n = (pok)malloc(sizeof(element));
	if (n == NULL) {
		printf("Greska pri alokaciji memorije");
		return -1;
	}
	strcpy(n->ime, im);
	if (trenutni->child == NULL)
	{
		trenutni->child = n;
		n->sibling = NULL;
		n->child = NULL;
		trenutni->child = n;
		push(stog, trenutni);
		push(stog, n);
		push(razina, trenutni);
	}
	else {
		temp = trenutni->child;
		trenutni->child = n;
		n->child = NULL;
		n->sibling = temp;
		push(stog, trenutni);
		push(stog, n);
		push(razina, trenutni);
	}
	return 0;
}
int push(Pozicija stog, pok p)
{
	Pozicija q=NULL;
	q = (Pozicija)malloc(sizeof(status));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}
	q->el = p;
	q->next = stog->next;
	stog->next = q;
	return 0;
}

pok pop(Pozicija stog)
{
	pok a=NULL;
	Pozicija temp=NULL;
	if (stog->next == NULL)
		return NULL;
	a = stog->next->el;
	temp = stog->next;
	stog->next = temp->next;
	free(temp);
	return a;

}

int ispis(Pozicija stog)
{
	if (stog->next != NULL)
		ispis(stog->next);
	printf("%s\n", stog->el->ime);
	return 0;
}

int vracanjeUnatrag(Pozicija stog, Pozicija razina)
{
	pok temp1=NULL;
	pok temp2=NULL;
	temp1 = pop(razina);
	if (temp1 == NULL)
	{
		printf("Greska. Stog je prazan.\n");
		return -1;
	}
	printf("Trenutno se nalazite u direktoriju %s.\n", temp1->ime);
	temp2 = pop(stog);
	if (temp2 == NULL)
	{
		printf("Greska. Stog je prazan.\n");
		return -1;
	}
	while (strcmp(temp2->ime, temp1->ime) != 0)
		temp2 = pop(stog);
	push(stog,temp2);
	return 0;
}


int cdDir(pok s, Pozicija stog, Pozicija razina,pok pocetak, char* im)
{
	pok trenutni = NULL;
	char c='a';
	char b = '\0';
	char *temp=NULL;
	int numB;
	int i = 0;
	temp = (char*)malloc(MAX * sizeof(char));
	if (temp == NULL) {
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}
	trenutni = pop(stog);
	if (trenutni == NULL)
	{
		printf("Greska. Prazan stog.\n");
		return -1;
	}
	while (c != '*') {
		i = 0;
		do {
			sscanf(im, "%c %n", &c, &numB);
			im = im + numB;
			if (i == 0) {
				strcpy(temp, &c);
				i = 1;
			}
			else if(c!='/'&&c!='*'){
				strcat(temp, &c);
			}
		} while (c != '/' && c != '*');
		strcat(temp, &b);
		if (trenutni->child != NULL) {
			push(stog, trenutni);
			trenutni = trenutni->child;
			if (strcmp(temp, trenutni->ime) == 0) {
				push(stog, trenutni);
				push(razina, trenutni);
				printf("Usli ste u %s.\n", trenutni->ime);
			}
			else if (strcmp(temp, pocetak->ime) == 0)
			{
				izbrisi(stog);
				izbrisi(razina);
				push(stog, pocetak);
				push(razina, pocetak);
				printf("Usli ste u %s.\n", pocetak->ime);
			}
			else {
				printf("Greska. Krivi path.\n");
				return -1;
			}
		}

	}
	free(temp);
	return 0;
}


int izbrisi(Pozicija p)
{
	Pozicija temp = p;
	while (temp->next != NULL) {
		p = temp;
		while (p->next->next != NULL)
			p = p->next;
		free(p->next);
		p->next = NULL;
	}
	return 0;
}

int Odabir(pok s,pok pocetak,Pozicija stog,Pozicija razina)
{
	int i=0;
	char str1[MAX];
	char str2[MAX];
	while (i == 0) {
		printf("Unesite naredbu:\n\tmd - unos direktorija u trenutni direktoriji\n\tdir - ispis trenutnog direktorija\n\tcd - promjena trenutnog direktorija(na kraju unosa patha unesite *)\n\tcd .. - vracanje u parent direktoriji\n\tizlaz - izlaz\n");
		scanf(" %s", str1);
		if (strcmp(str1, "md") == 0)
		{
			scanf(" %s", str2);
			mkdir(stog, razina, str2);
			ispis(stog->next);
		}
		else if (strcmp(str1, "dir") == 0)
		{
			ispis(stog->next);
		}
		else if (strcmp(str1, "cd") == 0)
		{
			scanf(" %s", str2);
			if (strcmp(str2, "..") == 0) {
				vracanjeUnatrag(stog, razina);
				ispis(stog->next);
			}
			else {
				cdDir(s, stog, razina, pocetak, str2);
				ispis(stog->next);
			}
		}
		else if (strcmp(str1, "izlaz") == 0) {
			i = 1;
			return 0;
		}
		else {
			printf("Greska pri unosu.Pokusaj ponovo.\n");
		}
	}
	return 0;
}



