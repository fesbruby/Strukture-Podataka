#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
struct Cvor;
typedef struct Cvor* Pozicija;
typedef struct Cvor {
	int el;
	Pozicija desno;
	Pozicija lijevo;
}cvor;

Pozicija dodaj(Pozicija, int);
void ispisInorder(Pozicija);
void ispisPostorder(Pozicija);
void ispisPreorder(Pozicija);
Pozicija trazi(Pozicija, int);
Pozicija brisi(Pozicija, int);
Pozicija traziMin(Pozicija);
char izbornik();
int main() {
	Pozicija root = NULL;
	Pozicija temp = NULL;
	char i = ' ';
	int x;
	while (i!='7')
	{
		i = izbornik();
		switch (i) {
		case '1':
			printf("Koji element zelite unjeti: ");
			scanf(" %d", &x);
			root = dodaj(root, x);
			break;
		case '2':
			ispisPreorder(root);
			printf("\n");
			break;
		case '3':
			ispisInorder(root);
			printf("\n");
			break;
		case '4':
			ispisPostorder(root);
			printf("\n");
			break;
		case '5':
			printf("Unesite trazeni element: ");
			scanf(" %d", &x);
			temp = trazi(root, x);
			if (temp == NULL)
				printf("Trazeni element ne postoji.\n");
			else
				printf("Trazeni element je %d.\n", temp->el);
			break;
		case '6':
			printf("Unesite element koji zelite izbrisati: ");
			scanf("%d", &x);
			root = brisi(root, x);
			break;
		case '7':
			break;
		default:
			printf("Greska pri odabiru. Pokusaj ponovo.\n");
			break;
		}

	}
	system("pause");
	return 0;
}

Pozicija dodaj(Pozicija p, int x)
{
	if (p == NULL)
	{
		p = (Pozicija)malloc(sizeof(cvor));
		p->el = x;
		p->lijevo = NULL;
		p->desno = NULL;
		return p;
	}
	else if (p->el > x) {
		p->lijevo = dodaj(p->lijevo, x);
		return p;
	}
	else {
		p->desno = dodaj(p->desno, x);
		return p;
	}

}

void ispisInorder(Pozicija p)
{
	if (p != NULL)
	{
		ispisInorder(p->lijevo);
		printf("%d ", p->el);
		ispisInorder(p->desno);
	}
}

void ispisPostorder(Pozicija p) 
{
	if (p != NULL)
	{
		ispisPostorder(p->lijevo);
		ispisPostorder(p->desno);
		printf("%d ", p->el);
	}
}

void ispisPreorder(Pozicija p)
{
	if (p != NULL)
	{
		printf("%d ", p->el);
		ispisPreorder(p->lijevo);
		ispisPreorder(p->desno);
	}
}

Pozicija trazi(Pozicija p, int x)
{
	if (p == NULL)
		return NULL;
	else {
		if (p->el > x)
			return trazi(p->lijevo, x);
		else if(p->el<x)
			return trazi(p->desno, x);
		return p;
	}
}

Pozicija brisi(Pozicija p, int x)
{
	Pozicija temp = NULL;
	if (p == NULL) {
		printf("Trazeni element ne postoji.\n");
		return p;
	}
	else {
		if (x < p->el)
			p->lijevo = brisi(p->lijevo, x);
		else if (x > p->el)
			p->desno = brisi(p->desno, x);
		else if (p->lijevo != NULL && p->desno != NULL)
		{
			temp = traziMin(p->desno);
			p->el = temp->el;
			p->desno = brisi(p->desno, p->el);
		}
		else {
			temp = p;
			if (p->desno != NULL)
			{
				p = p->desno;

			}
			else
				p = p->lijevo;
			free(temp);
		}
		return p;
	}

}

Pozicija traziMin(Pozicija p)
{
	if (p == NULL)
		return NULL;
	while (p->lijevo != NULL)
		p = p->lijevo;
	return p;
}

char izbornik()
{
	char zn;
	printf("Odaberite:\n\t1 - unos novog elementa\n\t2 - preorder ispis stabla\n\t3 - inorder ispis stabla\n\t4 - postorder ispis stabla\n\t5 - trazenje elementa\n\t6 - brisanje elementa\n\t7 - izlaz iz programa\n");
	scanf(" %c", &zn);
	return zn;
}

