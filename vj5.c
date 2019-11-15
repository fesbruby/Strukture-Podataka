#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 50
struct Element;
typedef struct Element* pozicija;
typedef struct Element {
	int el;
	pozicija next;
}element;

int UnosDat(pozicija, char*);
int Unos(pozicija, int);
int Ispis(pozicija);
pozicija New(int);
int FreeAllocatedData(pozicija);
int Unija(pozicija, pozicija, pozicija);
int Postoji(pozicija, int);
int Presjek(pozicija, pozicija, pozicija);
int Povezi(pozicija, pozicija);
int main()
{
	element U;
	element P;
	element L1;
	element L2;
	char dat1[MAX] = "lista1.txt";
	char dat2[MAX] = "lista2.txt";
	U.next = NULL;
	P.next = NULL;
	L1.next = NULL;
	L2.next = NULL;
	UnosDat(&L1, dat1);
	UnosDat(&L2, dat2);
	printf("Prva lista:\n");
	Ispis(&L1);
	printf("Druga lista:\n");
	Ispis(&L2);
	Unija(&L1, &L2, &U);
	printf("Unija:\n");
	Ispis(&U);
	Presjek(&L1, &L2, &P);
	printf("Presjek:\n");
	Ispis(&P);
	FreeAllocatedData(&L1);
	FreeAllocatedData(&L2);
	FreeAllocatedData(&U);
	FreeAllocatedData(&P);
	system("pause");
	return 0;

}

int UnosDat(pozicija p, char* dat)
{
	FILE* ul;
	int br;

	ul = fopen(dat, "r");
	if (ul == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	else
	{
		while (!feof(ul)) {
			fscanf(ul, " %d", &br);
			Unos(p, br);
		}
		fclose(ul);
		return 0;
	}


}

int Unos(pozicija p, int br)
{
	pozicija q = NULL;
	while (p->next != NULL && p->next->el < br)
		p = p->next;
	q = New(br);
	Povezi(p, q);
	return 0;
}

pozicija New(int br)
{
	pozicija p = NULL;
	p = (pozicija)malloc(sizeof(element));
	if (p == NULL)
	{
		printf("Greska pri alociranju memorije.\n");
		return p;
	}
	else
	{
		p->el = br;
		p->next = NULL;
		return p;
	}
}

int Povezi(pozicija before, pozicija after)
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

int Ispis(pozicija p)
{
	p = p->next;
	if (p == NULL)
		printf("Lista je prazna.\n");
	else {
		while (p != NULL)
		{
			printf("%d ", p->el);
			p = p->next;
		}
		printf("\n");
	}
	return 0;
}

int FreeAllocatedData(pozicija p)
{
	pozicija temp;
	if (p->next == NULL)
		return -1;
	while (p->next != NULL)
	{
		temp = p;
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}
		free(temp->next);
		temp->next = NULL;
	}
	return 0;
}

int Unija(pozicija p1, pozicija p2, pozicija p3)
{
	p1 = p1->next;
	p2 = p2->next;
	while (p1 != NULL)
	{
		if (Postoji(p3, p1->el) == 0)
			Unos(p3, p1->el);
		p1 = p1->next;
	}
	while (p2 != NULL)
	{
		if (Postoji(p3, p2->el) == 0)
			Unos(p3, p2->el);
		p2 = p2->next;
	}
	return 0;
}

int Postoji(pozicija p, int br)
{
	p = p->next;
	while (p != NULL && p->el != br)
		p = p->next;
	if (p == NULL)
		return 0;
	else
		return 1;
}

int Presjek(pozicija p1, pozicija p2, pozicija p3)
{
	p1 = p1->next;
	while (p1 != NULL)
	{
		if (Postoji(p2, p1->el) == 1) {
			if (Postoji(p3, p1->el) == 0)
				Unos(p3, p1->el);
		}
		p1 = p1->next;
	}
	return 0;
}