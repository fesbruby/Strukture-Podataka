#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20
struct polinom;
typedef struct polinom*Pozicija;
typedef struct polinom {
	int pot;
	double koef;
	Pozicija next;
}Polinom;
int UnosDat(Pozicija, char*);
int Povezi(Pozicija, Pozicija);
Pozicija New(double, int);
int Ispis(Pozicija);
int Unos(Pozicija,double,int);
int Suma(Pozicija, Pozicija, Pozicija);
int Produkt(Pozicija, Pozicija, Pozicija);
int FreeAllocatedData(Pozicija);
char* Odabir();
int main()
{
	Polinom Head1;
	Polinom Head2;
	Polinom S; 
	Polinom P;
	char i[MAX] = { 0 };
	Head1.next = NULL;
	Head2.next = NULL;
	S.next = NULL;
	P.next = NULL;
	char dat1[] = "polinom1.txt";
	char dat2[] = "polinom2.txt";
	UnosDat(&Head1, dat1);
	UnosDat(&Head2, dat2);
	printf("Polinom iz prve datoteke:\n");
	Ispis(&Head1);
	printf("Polinom iz druge datoteke:\n");
	Ispis(&Head2);
	while (strcmp(i, "0") != 0)
	{
		strcpy(i, Odabir());
		if (strcmp(i, "1") == 0)
		{
			Suma(&Head1, &Head2, &S);
			printf("Suma polinoma:\n");
			Ispis(&S);
		}
		else if (strcmp(i, "2") == 0)
		{
			Produkt(&Head1, &Head2, &P);
			printf("Produkt polinoma:\n");
			Ispis(&P);
		}
		else if (strcmp(i, "0") == 0)
		{
		}
		else {
			printf("Greska pri odabiru.Pokusaj ponovo.\n");
		}
	}
	FreeAllocatedData(&Head1);
	FreeAllocatedData(&Head2);
	FreeAllocatedData(&S);
	FreeAllocatedData(&P);
	system("pause");
	return 0;
}


int Ispis(Pozicija p)
{
	p = p->next;
	if (p == NULL)
		printf("Lista je prazna.\n");
	else {
		while (p != NULL)
		{
			printf("%.3lf x^%d\n", p->koef, p->pot);
			p = p->next;
		}
		printf("\n");
	}
	return 0;
}
int UnosDat(Pozicija p, char* dat)
{
	FILE* ul;
	int potencija;
	double k;

	ul = fopen(dat, "r");
	if (ul == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
			return -1;
	}
	else
	{
		while (!feof(ul)) {
			fscanf(ul, " %lf %d", &k, &potencija);
			Unos(p, k, potencija);
		}
		fclose(ul);
		return 0;
	}


}


int Unos(Pozicija p,double k, int potencija)
{
	Pozicija q = NULL;
	while (p->next != NULL && p->next->pot > potencija)
		p = p->next;
	if (p->next != NULL && p->next->pot == potencija)
		p->next->koef += k;
	else
	{
		q = New(k, potencija);
		Povezi(p, q);
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

Pozicija New(double k,int potencija)
{
	Pozicija p = NULL;
	p = (Pozicija)malloc(sizeof(Polinom));
	if (p == NULL)
	{
		printf("Greska pri alociranju memorije.\n");
		return p;
	}
	else
	{
		p->koef = k;
		p->pot = potencija;
		p->next = NULL;
		return p;
	}
}

char* Odabir()
{
	char iz[MAX];
	printf("Odaberite operaciju:\n\t1 - zbroji polinome\n\t2 - pomnozi poliome\n\t0 - izadi iz programa\n");
	scanf(" %s", iz);
	return iz;
}

int Suma(Pozicija p1, Pozicija p2, Pozicija s)
{
	Pozicija q = NULL;
	Pozicija temp = NULL;
	if (p1 == NULL && p2 == NULL)
	{
		printf("Liste su prazne.\n");
		s = NULL;
	}
	p1 = p1->next;
	p2 = p2->next;
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->pot == p2->pot)
		{
			q = New(p1->koef + p2->koef, p1->pot);
			Povezi(s, q);
			s = s->next;
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->pot > p2->pot)
		{
			q = New(p1->koef, p1->pot);
			Povezi(s, q);
			s = s->next;
			p1 = p1->next;
		}
		else if(p2->pot>p1->pot){
			q = New(p2->koef, p2->pot);
			Povezi(s, q);
			s = s->next;
			p2 = p2->next;
		}
	}
	if (p1 != NULL)
		temp = p1;
	else if (p2 != NULL)
		temp = p2;
	while (temp != NULL)
	{
		q = New(temp->koef, temp->pot);
		Povezi(s, q);
		s = s->next;
		temp = temp->next;
	}
	return 0;
}


int Produkt(Pozicija p1, Pozicija p2, Pozicija p)
{
	Pozicija poc;
	p1 = p1->next; 
	p2 = p2->next;
	poc = p2;
	while (p1 != NULL)
	{
		p2 = poc;
		while (p2 != NULL)
		{
			Unos(p, p1->koef*p2->koef, p1->pot + p2->pot);
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return 0;

}

int FreeAllocatedData(Pozicija p)
{
	Pozicija temp;
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