#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_LINE 50
typedef struct {
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int apsBr;
	double relBr;
}student;
int Izbroji(char*);
int Upisi(student*, char*,int);
int MaxBod(student*, int);
int relativni(student*, int, int);
int Ispis(student*, int);
int main()
{
	int br,max;
	student* s;
	char imeDat[] = "studenti.txt";
	br = Izbroji(imeDat);
	s = (student*)malloc(sizeof(student)*br);
	Upisi(s, imeDat,br);
	max=MaxBod(s, br);
	relativni(s, br, max);
	Ispis(s, br);
	system("pause");
	return 0;

}

int Izbroji(char* ime)
{
	int n = 0;
	char buffer[MAX_LINE] = { 0 };
	FILE* ul;
	ul = fopen(ime, "r");
	if (ul == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	else
	{
		while (!feof(ul))
		{
			fgets(buffer, MAX_LINE, ul);
			n++;
		}
		fclose(ul);
		return n-1;
	}
}
int Upisi(student* s, char* ime,int n)
{
	FILE* ul;
	int i = 0;
	ul = fopen(ime, "r");
	if (ul == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	else
	{
		for(i=0;i<n;i++)
		{
			fscanf(ul, " %s %s %d", s[i].ime, s[i].prezime, &s[i].apsBr);
		}
		fclose(ul);
		return 1;
	}
}

int MaxBod(student* s, int n)
{
	int i;
	int max;
	max = s[0].apsBr;
	for (i = 1; i < n; i++)
	{
		if (max < s[i].apsBr)
			max = s[i].apsBr;
	}
	return max;
}

int relativni(student *s, int n, int max)
{
	int i;
	for (i = 0; i < n; i++)
		s[i].relBr = (double)s[i].apsBr / (double)max * 100;
	return 1;
}

int Ispis(student* s, int n)
{
	int i;
	printf("Ime i prezime:        Apsolutni bod.:        Relativni bod.:\n");
	for (i = 0; i < n; i++)
		printf("%5s %5s       %10d                    %10f\n", s[i].ime, s[i].prezime, s[i].apsBr, s[i].relBr);
	return 1;
}