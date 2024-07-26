#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <ncurses.h>

#define frame '$'
#define frame_del ' '
#define col 144
#define line 48
#define NOMBRE_ELEVE 75

typedef struct person person;
typedef enum presence presence;

enum presence
{
	OUI = 1,
	NON = 2,
	PERSO = 3,
	ABSENT = 4
};

struct person
{
	char numero[3];
	char nom[30];
	char prenom[40];
	char check[15];
	char temp[15];
};

void fonction();
int nombreEleve(FILE* fichier, char* tab);
void obtenirInfo(FILE* fichier, char *tab, person *l1);
void printInfo(person *l1, int nbreleve);
void check(WINDOW *fenetre, person *l1, int i);
void recherche(char *tab, int nbreleve, person *l1, int* num, int *number);
void checker(WINDOW *fenetre, person *l1, int nbreleve, char *tab, int *number, int num);
void affiche(char *tab);
void searcheAffiche(person *l1, char *tab, int num);
char *toLowerCase(char *i_str);
void search(WINDOW *fenetre, person *l1);
void sortie(char *tab);
void destroywin(WINDOW *fenetre);
WINDOW *createwin(int h, int w, int y, int x);
void printInfoTemp(person *l1);
void searchArchive(WINDOW *fenetre);
void searchInstant(WINDOW *fenetre);
