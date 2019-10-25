#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 30

struct osoba;
typedef struct osoba* Pozicija;
struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int god;
	Pozicija next;
};
int UnosP(Pozicija);
int Ispis(Pozicija);
int UnosK(Pozicija);
Pozicija TraziPrezime(Pozicija);
int BrisiEl(Pozicija);
char Odabir();
int main()
{
	struct osoba Head;
	Pozicija t = NULL;
	char i=' ';
	Head.next = NULL;
	while (i!='0')
	{
		i = Odabir();
		switch (i) {
			case '1':
				UnosP(&Head);
				Ispis(&Head);
				break;
			case '2':
				Ispis(&Head);
				break;
			case '3':
				UnosK(&Head);
				Ispis(&Head);
				break;
			case '4':
				t = TraziPrezime(&Head);
				if (t == NULL)
					printf("Trazena osoba ne postoji u listi.\n");
				else
					printf("Trazena osoba je %s %s(%d)\n", t->ime, t->prezime, t->god);
				break;
			case '5':
				BrisiEl(&Head);
				Ispis(&Head);
				break;
			case '0':
				break;
			default:
				printf("Greska pri odabiru pokusaj ponovo.\n");
				break;
		}
	}
	free(t);
	system("pause");
	return 0;
}
int UnosP(Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct osoba));
	if (q == NULL)
	{
		printf("Greska u alokaciji memorije.\n");
		return -1;
	}
	printf("Unesi ime:\n");
	scanf(" %s", q->ime);
	printf("Unesi prezime:\n");
	scanf(" %s", q->prezime);
	printf("Unesi godinu rodenja:\n");
	scanf("%d", &(q->god));
	q->next = P->next;
	P->next = q;
	return 0;
}

int Ispis(Pozicija P)
{
	if (P->next == NULL) {
		printf("Lista je prazna.\n");
		return -1;
	}
	P = P->next;
	printf("Elementi liste:\n");
	while (P != NULL)
	{
		printf("%s %s %d\n", P->ime, P->prezime, P->god);
		P = P->next;
	}
	return 0;
}
int UnosK(Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct osoba));
	if (q == NULL)
	{
		printf("Greska u alokaciji memorije.\n");
		return -1;
	}
	printf("Unesi ime:\n");
	scanf(" %s", q->ime);
	printf("Unesi prezime:\n");
	scanf(" %s", q->prezime);
	printf("Unesi godinu rodenja:\n");
	scanf("%d", &(q->god));
	while (P->next != NULL)
	{
		P = P->next;
	}
	q->next = P->next;
	P->next = q;
	return 0;
}

Pozicija TraziPrezime(Pozicija p)
{
	char prez[MAX];
	printf("Unesi trazeno prezime: ");
	scanf(" %s", prez);
	p = p->next;
	while (p != NULL && strcmp(prez, p->prezime) != 0)
		p = p->next;
	return p;
}



int BrisiEl(Pozicija p)
{
	char prez[MAX];
	printf("Unesi prezime osobe koje zelis izbrisati: ");
	scanf(" %s", prez);
	Pozicija temp;
	temp = p;
	p = p->next;
	while (p != NULL && strcmp(p->prezime, prez) != 0)
	{
		temp = p;
		p = p->next;
	}
	if (p == NULL)
		printf("Trazeni element ne postoji.\n");
	else
	{
		temp->next = p->next;
		free(p);
	}
	return 0;
}
	

char Odabir()
{
	char zn;
	printf("Odaberite zeljenu funkciju:\n\t1 - dodati element na pocetak liste\n\t2 - ispisati listu\n\t3 - dodati elemet na kraj liste\n\t4 - pronaci osobu po prezimenu\n\t5 - izbrisati odabranu osobu\n\t0 - izaci iz programa\n");
	scanf(" %c", &zn);
	return zn;
}
