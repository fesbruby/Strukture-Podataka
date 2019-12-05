#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Element;
typedef struct Element *Pozicija;
typedef struct Element {
	int x;
	Pozicija next;
}element;
int Push(Pozicija, int);
int RandomBrojevi();
int Povezi(Pozicija, Pozicija);
Pozicija New(int);
int Ispis(Pozicija);
int Pop(Pozicija);
int StaviURed(Pozicija, int);
char Odabir();

int main() {
	int a;
	char i = 'A';
	element S;
	element R;
	S.next = NULL;
	R.next = NULL;
	srand(time(NULL));
	while (i != '0') {
		i = Odabir();
		switch (i) {
		case '1':
			Push(&S, RandomBrojevi());
			printf("Stog:\n");
			Ispis(&S);
			break;
		case '2':
			a = Pop(&S);
			if (a != -1)
				printf("Element stoga:%d\n", a);
			else
				printf("Strog je prazan.\n");
				break;
		case '3':
			StaviURed(&R, RandomBrojevi());
				printf("Red:\n");
				Ispis(&R);
				break;
		case '4':
			a = Pop(&R);
			if (a != -1)
				printf("Element reda:%d\n", a);
			else
				printf("Red je prazan.\n");
				break;
		case '0':
			break;
		default:
			printf("Greska pri unosu. Pokusaj ponovno.\n");
			break;
		}
	}
	system("pause");
	return 0;
}


int RandomBrojevi() {
	int n;
	n = rand() % (100 - 10 + 1) + 10;

	return n;
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

int Ispis(Pozicija p)
{
	p = p->next;
	if (p == NULL)
		printf("Lista je prazna.\n");
	else {
		while (p != NULL)
		{
			printf("%d ", p->x);
			p = p->next;
		}
		printf("\n");
	}
	return 0;
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

int StaviURed(Pozicija p, int br) {
	while (p->next != NULL)
		p = p->next;

	Push(p, br);

}

char Odabir() {
	char i;
	printf("Odaberi:\n\t1-Unesi u stog\n\t2-Procitaj sa stoga\n\t3-Stavi u red\n\t4-Procitaj iz reda\n\t0-Izadi iz programa\n");
	scanf(" %c", &i);
	return i;
}