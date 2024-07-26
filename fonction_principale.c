#include "header.h"

void fonction()
{
	int num = 0;
	int *number = NULL;
    int choixOption = 0;
    int nbreleve = 0;
    char *tab = NULL;
    person *l1 = NULL;
    FILE* fichier = NULL;

    tab = (char*)malloc(255*sizeof(char));
    fichier = fopen("listeL1.csv", "r");
    if(fichier == NULL)
    {
        printf("Erreur");
        exit(1);
    }
    nbreleve = nombreEleve(fichier, tab);
    l1 = (person*)malloc(nbreleve*sizeof(person));
    number = malloc(nbreleve*sizeof(int));

    obtenirInfo(fichier, tab, l1);
	///////////////////////////////////////
	int w_stdscr, h_stdscr, control, ypos=3;
	int heigth=12, width=61, x0, y0;
	
	x0=(COLS-width)/2;
	y0=(LINES-heigth)/2;
	
	bool run=TRUE;
	WINDOW *fenetre=NULL;
	initscr();
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(2, COLOR_RED, COLOR_WHITE);
	wbkgd(stdscr, COLOR_PAIR(1));
	while(run)
	{
		choose:
		refresh();
		fenetre=createwin(heigth, width, 35-(width)/2, (136/2)-(heigth)/2);
		wbkgd(stdscr, COLOR_PAIR(1));
				

		mvwprintw(fenetre,1,27," Option:"); 
		mvwprintw(fenetre,3,10,"1-  Checker les pc"); 
		mvwprintw(fenetre,4,10,"2-  Recherche des informations"); 
		mvwprintw(fenetre,5,10,"3-  Affichage de tous les élèves"); 
		mvwprintw(fenetre,6,10,"4-  Enregistrer le check d'aujourd'hui"); 
		mvwprintw(fenetre,7,10,"5-  Quitter"); 
		mvwprintw(fenetre,ypos, 1,"--->>>");
		mvwchgat(fenetre,ypos, 1, 59, A_REVERSE, 2, NULL);                                          
		wrefresh(fenetre);
		control=getch();
		if (control==KEY_DOWN && ypos<7)
			ypos+=1;
		if (control==KEY_UP && ypos>3)
			ypos-=1;
		if (control=='\n')
		{
		switch (ypos)
			{
				case 3:
					destroywin(fenetre);
					refresh();
					checker(fenetre, l1, nbreleve, tab, number, num);
					printInfo(l1, nbreleve);
					break;
				case 4:
					search(fenetre, l1);
					break;
				case 5:
					/*destroywin(fenetre);
					clear();
					refresh();*/
					affiche(tab);
					break;
				case 6:
					sortie(tab);
					break;
				case 7:
					goto quit;
					break;
				default:
					goto choose;
			}
		}
		
	}
	quit :
    free(number);
    fclose(fichier);
    free(l1);
    free(tab);
	destroywin(fenetre);
	endwin();
	

}
