#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 100

struct Element;
typedef struct Element* Pozicija;
typedef struct Element {
	int x;
	Pozicija next;
}element;

int Push(Pozicija, int);
int Povezi(Pozicija, Pozicija);
Pozicija New(int);
int Pop(Pozicija);
int Procitaj(Pozicija, char*);
int Rezultat(Pozicija);

int main() {
	element Stog;
	char dat[MAX] = "postfix.txt";
	Stog.next = NULL;
	Procitaj(&Stog, dat);
	Rezultat(&Stog);
	system("pause");
	return 0;
}

int Push(Pozicija p, int br) {
	Pozicija q;
	q = New(br);
	Povezi(p, q);

	return 0;
}


Pozicija New(int br)
{
	Pozicija p = NULL;
	p = (Pozicija)malloc(sizeof(element));
	if (p == NULL)
	{
		printf("Greska pri alociranju memorije.\n");
		return p;
	}
	else
	{
		p->x = br;
		p->next = NULL;
		return p;
	}
}

int Povezi(Pozicija before, Pozicija after)
{
	if (after == NULL)
	{
		printf("Greska!\n");
		return -1;
	}
	else
	{
		after->next = before->next;
		before->next = after;
		return 0;
	}
}

int Pop(Pozicija p) {
	int br;
	Pozicija temp;
	if (p->next == NULL) {
		return -1;
	}
	else {
		temp = p->next;
		br = temp->x;
		p->next = temp->next;
		free(temp);
		return br;
	}
}

int Procitaj(Pozicija p, char* dat) {
	int br;
	int c;
	int a;
	int b;
	int numB;
	char* niz;
	FILE* ul;
	niz = (char*)malloc(MAX * sizeof(char));
	if (niz == NULL) {
		printf("Greska u alokaciji memorije\n");
		return -1;
	}
	ul = fopen(dat, "r");
	if (ul == NULL) {
		printf("Greska pri otvaranju datoteke\n");
		return -1;
	}
	while (!feof(ul)) {
		fgets(niz, MAX, ul);
	}
	while (*niz != '\n') {//!feof(*niz)
		c = sscanf(niz, "%d %n", &br, &numB);
		if (c == 1) {
			Push(p, br);
			niz = niz + numB;
		}
		else if(c==0){
			switch (*niz) {
			case '+':
				a = Pop(p);
				b = Pop(p);
				if (a != -1 && b != -1)
					Push(p, a + b);
				else {
					printf("Greska\n");
					return -1;
				}
				niz = niz + numB;
				break;
			case '-':
				a = Pop(p);
				b = Pop(p);
				if (a != -1 && b != -1)
					Push(p, b - a);
				else {
					printf("Greska\n");
					return -1;
				}
				niz = niz + numB;
				break;
			case '*':
				a = Pop(p);
				b = Pop(p);
				if (a != -1 && b != -1)
					Push(p, b*a);
				else {
					printf("Greska\n");
					return -1;
				}
				niz = niz + numB;
				break;
			case '/':
				a = Pop(p);
				b = Pop(p);
				if (a != -1 && b != -1 && a != 0)
					Push(p, b / a);
				else {
					printf("Greska\n");
					return -1;
				}
				niz = niz + numB;
				break;
			default:
				printf("Greska\n");
				break;
			}
		}


	}
	fclose(ul);
	return 0;
}

int Rezultat(Pozicija p)
{
	p = p->next;
	if (p == NULL) {
		printf("Greska, stog je prazan.\n");
		return -1;
	}
	printf("Rezultat postfix izraza je %d\n", p->x);
	return 0;
}