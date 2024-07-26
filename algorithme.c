#include "header.h"

void check(WINDOW *fenetre, person *l1, int i)
{
		
	delwin(fenetre);
	clear();
	refresh();
	//fenetre=createwin(52, 111, 0, 0);
	int choix;
	label :
		attron(COLOR_PAIR(1));
		printw("1- OUI\n");
		printw("2- NON\n");
		printw("3- PERSO\n");
		printw("4- ABSENT\n");
		printw("%s : %s : %s : ", l1[i].numero, l1[i].nom, l1[i].prenom);
		scanw("%d", &choix);
		attroff(COLOR_PAIR(1));
		strcpy(l1[i].temp, __TIME__);
		switch(choix)
		{
			case OUI:
				strcpy(l1[i].check, "OUI");
				break;
			case NON:
				strcpy(l1[i].check, "NON");
				break;
			case PERSO:
				strcpy(l1[i].check, "PERSO");
				break;
			case ABSENT:
				strcpy(l1[i].check, "ABSENT");
				break;
			default:
				goto label;
		}
		printInfoTemp(l1);

}

void recherche(char *tab, int nbreleve, person *l1, int* num, int *number)
{

	int i = 0;
	int verif = 0;
	int a = 0;
	retour :
		printw("Donner un indice du personne à rechercher : ");
		getstr(tab);
		for(i = 0; i < nbreleve; i++)
		{
			if (strcmp(l1[i].nom, tab) == 0 || strcmp(l1[i].numero, tab) == 0 || strcmp(l1[i].prenom, tab) == 0 || strcmp(l1[i].check, tab) == 0)
			{
				number[a] = i;
				a++;
				verif = 1;
			}
		}
		if(verif == 0)
		{
			printw("Cette indice ne correspond à aucun profil\n");
			goto retour;
		}
	*num = a;

}

void checker(WINDOW *fenetre, person *l1, int nbreleve, char *tab, int *number, int num)
{

	int i;
	int ypos1=3;
    char choix;
	int choixCheck;
	initscr();
//
	bool running=TRUE;
	while(running)
	{
		refresh();
		fenetre=createwin(12, 61, 35-(61)/2, (136/2)-(12)/2);
		mvwprintw(fenetre, 2, 27,"Option:");
		mvwprintw(fenetre, 3, 10,"1-  Checker tous les pc");
		mvwprintw(fenetre, 4, 10,"2-  Checker un à un");
		mvwprintw(fenetre,ypos1, 1,"--->>>");
		mvwchgat(fenetre,ypos1, 1, 59, A_REVERSE, 2, NULL); 
		wrefresh(fenetre);
		choixCheck=getch();
		if (choixCheck==KEY_DOWN && ypos1<4)
			ypos1+=1;
		if (choixCheck==KEY_UP && ypos1>3)
			ypos1-=1;
		if (choixCheck=='\n')
			{
				running=FALSE;
				switch(ypos1)
					{	
						case 3:
							for(i = 0; i < nbreleve; i++)
								{
									check(fenetre, l1, i);
								}
							break;
						case 4:
							do
								{
									delwin(fenetre);
									clear();
									refresh();
									attron(COLOR_PAIR(1));
									recherche(tab, nbreleve, l1, &num, number);
									check(fenetre, l1, number[0]);
									getchar();
									printw("Recommencer (o/n) : ");
									scanw("%c", &choix);
									attroff(COLOR_PAIR(1));
								}
							 while(choix != 'n');
							break;
					}
			}

	}	
}

void affiche(char *tab)
{

	FILE *fichier1 = NULL;
	fichier1 = fopen("fichier_temp.csv", "r");
	int y=0;
	if (fichier1 == NULL)
	{
		exit(1);
	}

	while (fgets(tab, 255, fichier1) != NULL)
	{
		printw("%s\n", tab);
	}

	fclose(fichier1);
}

/*void searcheAffiche(person *l1, char *tab, int num)
{
	
	int i = 0;
	int ligne = 0;
	int compteur;
	FILE* stream = NULL;
	stream = fopen("fichier_temp.csv", "r");

	while (fgets(tab, 255, stream) != NULL)
	{
		for (i = 0; i < strlen(tab); i++) // 1
		{
			if(tab[i] == '=')
			{
				printf("%s", tab);
				ligne = compteur;
				break;
			}
			if (compteur == (ligne + num) + 1)
			{
				printf("\n%s\n", tab);
				break;
			}
		}
		compteur++;
	}

	fclose(stream);
	return;
}*/

char *toLowerCase(char *i_str)
{
    int i;//loop 1
    char *f_str;
    f_str = malloc(sizeof(char)*strlen(i_str));

    for(i = 0; i < strlen(i_str); i++)
	{
        f_str[i] = tolower(i_str[i]);
	}

    return f_str;
}

void sortie(char *tab)
{
	FILE *fichier1 = NULL;
	FILE *fichier2 = NULL;
	fichier1 = fopen("fichier_temp.csv", "r");
	fichier2 = fopen("fichier_sortie.csv", "a");
	if (fichier1 == NULL || fichier2 == NULL)
	{
		exit(1);
	}

	while (fgets(tab, 255, fichier1) != NULL)
	{
		fprintf(fichier2, "%s", tab);
	}

	fclose(fichier1);
	fclose(fichier2);
}
WINDOW *createwin(int h, int w, int y, int x)
{
	WINDOW *fenetre;
	fenetre=newwin(h, w, y, x);
	wborder(fenetre, frame, frame, frame, frame, frame, frame, frame, frame);
	wbkgd(fenetre, COLOR_PAIR(2));
	wrefresh(fenetre);
	
	return fenetre;
}
void destroywin(WINDOW *fenetre)
{
	wborder(fenetre, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(fenetre);
	delwin(fenetre);
}
void printInfoTemp(person *l1)
{

	int i = 0;
	FILE *fichier1 = NULL;
	fichier1 = fopen("fichier_temp.csv", "w");
	if (fichier1 == NULL)
	{
		exit(1);
	}

	fprintf(fichier1, "\t\t\t\t\t\t\t\t\t\t\t==> Date : %s <==\n", __DATE__);
	fprintf(fichier1, "\t\t\t\t\t\t\t\t\t\t\t==> heure : %s <==\n\n", __TIME__);
	for (i = 0; i < NOMBRE_ELEVE; i++)
	{
		fprintf(fichier1, "%2s : %26s : %7s : %7s\n", l1[i].numero, l1[i].nom, l1[i].prenom, l1[i].check);
	}

	fclose(fichier1);
}

void searchInstant(WINDOW *fenetre)
{
	FILE *stream = NULL;
	//stream = fopen("fichier_sortie.csv", "r");
	stream = fopen("fichier_temp.csv", "r");

    char *buff;
    buff = malloc(sizeof(char)*255);
    
	char *toSearch;
	toSearch = malloc(sizeof(char)*255);
		
	delwin(fenetre);
	clear();
	refresh();
	attron(COLOR_PAIR(1));
	
	do
	{
		printw("recherche -> ");
		getstr(toSearch);
	} while (strcmp(toSearch, " ") == 0 || strcmp(toSearch, "\t") == 0 || toSearch[0] == '\t');
		
    while ((fgets(buff, 255, stream)) != NULL)
    {
        if (strstr(toLowerCase(buff), toLowerCase(toSearch)) != NULL)
        {
            printw("%s", buff);
        }
    }
	attroff(COLOR_PAIR(1));
	free(toSearch);
	free(buff);
	fclose(stream);
    return;
}

void searchArchive(WINDOW *fenetre)
{
	FILE *stream = NULL;
	stream = fopen("fichier_sortie.csv", "r");

    char *buff;
    buff = malloc(sizeof(char)*255);
    
	char *toSearch;
	toSearch = malloc(sizeof(char)*255);
		
	delwin(fenetre);
	clear();
	refresh();
	attron(COLOR_PAIR(1));
	
	do
	{
		printw("recherche -> ");
		getstr(toSearch);
	} while (strcmp(toSearch, " ") == 0 || strcmp(toSearch, "\t") == 0 || toSearch[0] == '\t');
		
    while ((fgets(buff, 255, stream)) != NULL)
    {
        if (strstr(toLowerCase(buff), toLowerCase(toSearch)) != NULL)
        {
            printw("%s", buff);
        }
    }
	attroff(COLOR_PAIR(1));
	free(toSearch);
	free(buff);
	fclose(stream);
    return;
}

void search(WINDOW *fenetre, person *l1)
{

	int i;
	int ypos1=3;
    char choix;
	int choixCheck;
	initscr();
//
	bool running=TRUE;
	while(running)
	{
		refresh();
		fenetre=createwin(12, 61, 35-(61)/2, (136/2)-(12)/2);
		mvwprintw(fenetre, 2, 27,"Option:");
		mvwprintw(fenetre, 3, 10,"1-  Recherche par defaut");
		mvwprintw(fenetre, 4, 10,"2-  Recherche dans les archives");
		mvwprintw(fenetre,ypos1, 1,"--->>>");
		mvwchgat(fenetre,ypos1, 1, 59, A_REVERSE, 2, NULL); 
		wrefresh(fenetre);
		choixCheck=getch();
		if (choixCheck==KEY_DOWN && ypos1<4)
			ypos1+=1;
		if (choixCheck==KEY_UP && ypos1>3)
			ypos1-=1;
		if (choixCheck=='\n')
			{
				running=FALSE;
				switch(ypos1)
					{	
						case 3:
							searchInstant(fenetre);
							break;
						case 4:
							searchArchive(fenetre);
							break;
					}
			}

	}	
}