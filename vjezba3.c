#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
struct osoba;
typedef struct osoba* Pozicija;
struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int god;
	Pozicija next;
};

int Povezi(Pozicija, Pozicija);
Pozicija New(char*,char*,int);
int UnosiKorisnik(char*, char*, int*);
int Ispis(Pozicija);
char* Odabir();
int UnosP(Pozicija, char*, char*, int);
int UnosK(Pozicija, char*, char*, int);
Pozicija TraziPrezime(Pozicija, char*);
int BriseEl(Pozicija, char*);
int DodajIza(Pozicija, char*);
int DodajIspred(Pozicija, char*);
int Sortiraj(Pozicija);
int UpisDatoteka(Pozicija, char*);
int CitajDatoteka(char*);
int main()
{
	char i[MAX] = { 0 };
	char im[MAX], prez[MAX];
	char dat[] = "osobe.txt";
	int g;
	struct osoba Head;
	Pozicija t = NULL;
	Head.next = NULL;
	while (strcmp(i,"0")!=0)
	{
		strcpy(i, Odabir());
		if (strcmp(i, "1") == 0) {
			UnosiKorisnik(im, prez, &g);
			UnosP(&Head, im, prez, g);
			Ispis(&Head);
		}
		else if (strcmp(i, "2") == 0) {
			Ispis(&Head);
		}
		else if (strcmp(i, "3") == 0) {
			UnosiKorisnik(im, prez, &g);
			UnosK(&Head, im, prez, g);
			Ispis(&Head);
		}
		else if (strcmp(i, "4") == 0) {
			printf("Unesite trazeno prezime: ");
			scanf(" %s", prez);
			t = TraziPrezime(&Head, prez);
			if (t == NULL)
				printf("Trazena osoba ne postoji u listi.\n");
			else
				printf("Trazena osoba je %s %s(%d)\n", t->ime, t->prezime, t->god);
		}
		else if (strcmp(i, "5") == 0) {
			printf("Unesite prezime koje zelite izbrisati: ");
			scanf(" %s", prez);
			BriseEl(&Head, prez);
			Ispis(&Head);
		}
		else if (strcmp(i, "6") == 0) {
			printf("Unesite prezime iza kojeg zelite unjeti novu osobu: ");
			scanf(" %s", prez);
			DodajIza(&Head, prez);
			Ispis(&Head);
		}
		else if (strcmp(i, "7") == 0) {
			printf("Unesite prezime ispred kojeg zelite unjeti novu osobu: ");
			scanf(" %s", prez);
			DodajIspred(&Head, prez);
			Ispis(&Head);
		}
		else if (strcmp(i, "8") == 0) {
			Sortiraj(&Head);
			Ispis(&Head);
		}
		else if (strcmp(i, "9") == 0){
			UpisDatoteka(&Head, dat);
		}
		else if (strcmp(i, "10") == 0) {
			CitajDatoteka(dat);
		}
		else if (strcmp(i, "0") == 0) {
			
		}
		else{
			printf("Greska pri odabiru pokusaj ponovo.\n");
		}
	}
	return 0;
}

Pozicija New(char* im,char* prez,int g)
{
	Pozicija p=NULL;
	p = (Pozicija)malloc(sizeof(struct osoba));
	if (p == NULL)
	{
		printf("Greska pri alociranju memorije.\n");
		return p;
	}
	else
	{
		strcpy(p->ime, im);
		strcpy(p->prezime, prez);
		p->god = g;
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
char* Odabir()
{
	char zn[MAX];
	printf("Odaberite zeljenu funkciju:\n\t1 - dodati element na pocetak liste\n\t2 - ispisati listu\n\t3 - dodati elemet na kraj liste\n\t4 - pronaci osobu po prezimenu\n\t5 - izbrisati odabranu osobu\n\t6 - Dodaj osobu iza odredenog elementa\n\t7 - Dodaj osobu ispred odredenog elementa\n\t8 - Sortiraj\n\t9 - Upisi u datoteku\n\t10 - Procitaj iz datoteke\n\t0 - izaci iz programa\n");
	scanf(" %s", zn);
	return zn;
}

int UnosiKorisnik(char* i, char* p, int* g)
{
	printf("Unesite ime: ");
	scanf(" %s", i);
	printf("Unesite prezime: ");
	scanf(" %s", p);
	printf("Unesite godinu rodenja: ");
	scanf("%d", g);
	return 0;
}

int UnosP(Pozicija p, char* im, char* prez, int g)
{
	Pozicija q=NULL;
	q = New(im, prez, g);
	if (q != NULL)
	{

		Povezi(p, q);
	}

	return 0;
}


int Ispis(Pozicija p)
{
	p = p->next;
	if (p == NULL)
		printf("Lista je prazna.\n");
	else {
		printf("Ispis liste:\n");
		while (p != NULL)
		{
			printf("%s %s %d\n", p->ime, p->prezime, p->god);
			p = p->next;
		}
	}
	return 0;
}


int UnosK(Pozicija p, char*im, char* prez, int g)
{
	Pozicija q;
	while (p->next != NULL)
		p = p->next;
	q = New(im, prez, g);
	if (q != NULL)
		Povezi(p, q);
	return 0;
}


Pozicija TraziPrezime(Pozicija p, char*prez)
{
	while (p != NULL && strcmp(p->prezime, prez) != 0)
		p = p->next;
	return p;
}


int BriseEl(Pozicija p, char* prez)
{
	Pozicija temp;
	temp = p->next;
	while (p->next != NULL && strcmp(temp->prezime, prez) != 0)
	{
		p = p->next;
		temp = p->next;
	}
	if (temp == NULL) {
		printf("Trazeni element ne postoji.\n");
	}
	else {
		p->next = temp->next;
		free(temp);
	}
	return 0;
}


int DodajIza(Pozicija p, char* prez)
{
	Pozicija q = NULL;
	Pozicija x = NULL;
	char im[MAX], pr[MAX];
	int g;
	x = TraziPrezime(p, prez);
	if (x == NULL)
		printf("Trazena osoba ne postoji.\n");
	else
	{
		UnosiKorisnik(im, pr, &g);
		q = New(im, pr, g);
		Povezi(x, q);
	}
	return 0;
}

int DodajIspred(Pozicija p, char* prez)
{
	char im[MAX], pr[MAX];
	int g;
	Pozicija temp=NULL;
	Pozicija q = NULL;
	temp = p;
	p = p->next;
	while (p != NULL && strcmp(p->prezime, prez) != 0)
	{
		temp = p;
		p = p->next;
	}
	if (p == NULL)
		printf("Trazeni element ne postoji.\n");
	else {
		UnosiKorisnik(im, pr, &g);
		q = New(im, pr, g);
		Povezi(temp, q);
	}
	return 0;
}


int Sortiraj(Pozicija p)
{
	Pozicija end = NULL;
	Pozicija prevj, j,temp;
	while (p->next != end)
	{
		prevj = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				prevj->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}
			prevj = j;
			j = j->next;
		}
		end = j;
	}
	return 0;
}


int UpisDatoteka(Pozicija p, char*dat)
{
	FILE*izl;
	izl = fopen(dat, "w");
	if (izl == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	else
	{
		p = p->next;
		while (p != NULL)
		{
			fprintf(izl, "%s %s %d\n", p->ime, p->prezime, p->god);
			p = p->next;
		}
		fclose(izl);
		return 0;
	}
}

int CitajDatoteka(char*dat)
{
	FILE*ul;
	char im[MAX], prez[MAX];
	int g;
	ul = fopen(dat, "r");
	if (ul == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	else
	{
		while (!feof(ul))
		{
			fscanf(ul, " %s %s %d\n", im, prez, &g);
			printf("%s %s %d\n", im, prez, g);
		}
		fclose(ul);
		return 0;
	}
}