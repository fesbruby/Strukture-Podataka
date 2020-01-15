#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 50
struct Cvor;
struct Hash;
typedef struct Hash*HashTab;
typedef struct Cvor*Lista;
typedef struct Cvor {
	char ime[MAX];
	char prezime[MAX];
	int mb;
	Lista next;
}cvor;
typedef struct Hash {
	int vel;
	Lista* tablica;
}hash;

HashTab inicijalizacija(int);
int iduciProst(int);
int stvoriKljuc(char*,char*);
int dodaj(HashTab, char*, char*, int);
Lista stvoriNovi(char*, char*, int);
int dodajUListu(HashTab,Lista,int);
int ispis(HashTab);
Lista trazi(HashTab,char*, char*);
int procitajIzDat(HashTab,char*);
int traziBr(HashTab);
Lista traziLista(Lista, char*, char*);
int brisi(HashTab);
int brisiList(Lista);
int main()
{
	HashTab h = NULL;
	h = inicijalizacija(11);
	procitajIzDat(h, "osobe.txt");
	printf("Hash tablica:\n");
	ispis(h);
	traziBr(h);
	brisi(h);
	system("pause");
	return 0;
}

HashTab inicijalizacija(int velT)
{
	HashTab h = NULL;
	int i = 0;
	h = (HashTab)malloc(sizeof(hash));
	if (h == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return NULL;
	}
	h->vel = iduciProst(velT);
	h->tablica = (Lista*)malloc(h->vel * sizeof(Lista));
	if(h->tablica==NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return NULL;
	}
	for (i = 0; i < h->vel; i++)
	{
		h->tablica[i] = (Lista)malloc(sizeof(cvor));
		h->tablica[i]->next = NULL;
	}
	return h;
}

int procitajIzDat(HashTab h,char*dat)
{
	FILE*ul = NULL;
	char im[MAX];
	char prez[MAX];
	int br = 0;
	ul = fopen(dat, "r");
	while (!feof(ul))
	{
		fscanf(ul, " %s %s %d", prez, im, &br);
		dodaj(h, prez, im, br);
	}
	fclose(ul);
	return 0;
}

int iduciProst(int x)
{
	int y = x;
	int n = 1;
	int i = 0;
	while (n == 1)
	{
		i = 2;
			while (i < sqrt((double)y))
			{
				if (y%i == 0)
					n = 1;
				else
				{
					i++;
					n = 0;
				}
			}
			if (n == 1)
				y++;
		}
	return y;
}



int stvoriKljuc(char*prez,char*im)
{
	int i = 0;
	int k = 0;
	int l = strlen(prez);
	if (l >= 5)
		for (i = 0; i < 5; i++)
			k = k + prez[i];
	else {
		for (i = 0; i < l; i++)
			k = k + prez[i];
		for (i = 0; i < 5 - l; i++)
			k = k + im[i];
	}
	return k % 11;

}


int dodaj(HashTab h, char*prez, char*im, int mBroj)
{
	Lista l = NULL;
	int x = stvoriKljuc(prez, im);
	l=stvoriNovi(im, prez, mBroj);
	if(h->tablica[x]->next==NULL)
		h->tablica[x]->next = l;
	else
		dodajUListu(h, l, x);
	return 0;
}



Lista stvoriNovi(char*im, char*prez, int mBroj)
{
	Lista l=NULL;
	l = (Lista)malloc(sizeof(cvor));
	if (l == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return NULL;
	}
	strcpy(l->ime, im);
	strcpy(l->prezime, prez);
	l->mb = mBroj;
	l->next = NULL;
	return l;
}

int dodajUListu(HashTab h, Lista l, int x)
{
	int i = 0;
	Lista p = h->tablica[x];
	while (p->next != NULL&&strcmp(l->prezime,p->next->prezime)>=0&&i!=1)
	{
		if (strcmp(p->next->prezime, l->prezime) == 0) {
			while (p->next != NULL && strcmp(p->next->prezime, l->prezime) == 0 && strcmp(l->ime, p->next->ime) > 0)
				p = p->next;
			l->next = p->next;
			p->next = l;
			i = 1;
			
		}
		else 
			p = p->next;
	}
	if (i == 0)
	{
		l->next = p->next;
		p->next = l;
	}

	return 0;
}

int ispis(HashTab h)
{
	int i = 0;
	Lista p = NULL;
	for (i = 0; i < 11; i++)
	{
		if (h->tablica[i]->next != NULL)
		{
			p = h->tablica[i]->next;
			while (p != NULL)
			{
				printf("%d %s %s %d\n",i, p->prezime, p->ime, p->mb);
				p = p->next;
			}
		}
	}
	return 0;
}

Lista trazi(HashTab h,char*prez, char*im)
{
	int x = stvoriKljuc(prez, im);
	Lista p = NULL;
	if (h->tablica[x]->next == NULL)
	{
		printf("Trazena osoba ne postoji.\n");
		return NULL;
	}
	p = traziLista(h->tablica[x],prez, im);
	return p;

}

Lista traziLista(Lista p,char*prez, char*im)
{
	p = p->next;
	while (p != NULL && (strcmp(p->prezime, prez) != 0 || strcmp(p->ime, im) != 0))
		p = p->next;
	return p;
}

int traziBr(HashTab h)
{
	Lista p = 0;
	int i = 0;
	char prez[MAX];
	char im[MAX];
	char a[MAX];
	while (i == 0)
	{
		printf("Zelite li naci maticni broj osobe?(DA ili NE)\n");
		scanf(" %s", a);
		if (strcmp(a, "DA") == 0) {
			printf("Unesite prezime: ");
			scanf(" %s", prez);
			printf("Unesite ime: ");
			scanf(" %s", im);
			p = trazi(h, prez, im);
			if (p == NULL)
				printf("Trazena osoba ne postoji.\n");
			else
				printf("Ime:%s Prezime:%s MB:%d\n", p->ime, p->prezime, p->mb);


		}
		else if (strcmp(a, "NE") == 0)
			i = 1;
		else
			printf("Greska pri unosu.\n");
	}
	return 0;
}


int brisiListu(Lista p)
{
	Lista temp = NULL;
	while (p->next != NULL)
	{
		temp = p;
		while (temp->next->next != NULL)
			temp = temp->next;
		free(temp->next);
		temp->next = NULL;
	}
	return 0;

}

int brisi(HashTab h)
{
	int i = 0;
	for (i = 0; i < h->vel; i++)
	{
		brisiListu(h->tablica[i]);
		free(h->tablica[i]);
	}
	return 0;
}

