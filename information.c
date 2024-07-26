#include "header.h"

int nombreEleve(FILE* fichier, char* tab)
{

    int nombre = 0;
    rewind(fichier);
    while(fgets(tab, 255, fichier) != NULL)
    {
        nombre++;
    }
    return nombre;

}


void obtenirInfo(FILE* fichier, char *tab, person *l1)
{

	int i = 0;
	int a = 0;
	int b = 0;
	rewind(fichier);
	while (fgets(tab, 255, fichier) != NULL)
	{
		for (i = 0; i < strlen(tab); i++)
		{
			b = 0;
			while (tab[i] != ';')
			{
				l1[a].numero[b] = tab[i];
				b++;
				i++;
			}
			b = 0;
			i++;
			while (tab[i] != ' ')
			{
				l1[a].nom[b] = tab[i];
				b++;
				i++;
			}
			i++;
			b = 0;
			while (tab[i] != ';')
			{
				l1[a].prenom[b] = tab[i];
				b++;
				i++;
			}
			break;
		}
		a++;
	}

}

void printInfo(person *l1, int nbreleve)
{

	int i = 0;
	FILE *fichier1 = NULL;
	fichier1 = fopen("index.html", "w");
	if (fichier1 == NULL)
	{
		exit(1);
	}

	fprintf(fichier1, 	
    "<HTML>\n"
	"   <HEAD>\n"
	"       <TITLE>\n"
	"           PRESENCE L1\n"
	"       </TITLE>\n"
    "       <style>\n"
    "           body {\n"
    "               background-image: url('fond.png');\n"
    "               background-size: cover;\n"
    "               background-position: center;\n"
    "               background-attachment: fixed;\n"
    "               background-repeat: no-repeat;\n"
    "           }\n"
    "           .tete\n"
    "           {\n"
    "               background-color: #F1450D;\n"
    "           }\n"
	"	        h3\n"
	"	        {\n"
	"			    font-size : 20;\n"
	"			    font-family: Arial, Helvetica, sans-serif;\n"
	"			    text-align: center;\n"
	"	        }\n"
	"	        p\n"
	"	        {\n"
	"	            font-size: 18;\n"
	"	            font-family: Arial;\n"
	"	            color: maroon;\n"
	"	        }\n"
    "           div{\n"
	"		    	background-color:lightskyblue;\n"
	"			    display: flex;\n"
    "        	    justify-content: center;\n"
    "        	    align-items: center;\n"
    "        	    height: 100px;\n"
	"			    width : 600px;\n"
    "        	    border: 6px solid yellowgreen;\n" 
    "        	    border-radius: 20px;\n"
	"			    box-shadow: 0 6px 12px rgba(0, 0, 0, 0.3);\n"
	"		    }\n"
    "       </style>\n"  
    "   </HEAD>\n"
	"   <BODY>\n"   
    "       <CENTER><IMG src=\"logo_mit.png\"/></CENTER><BR>\n"
    "       <center>\n"
    "           <div>\n"
    "               <FONT color=\"red\" size=\"20\">LISTE DE PRESENCE MIT</FONT>\n"
    "           </div>\n"
    "       </center>\n"
    "       <br><br><br>"
	"       <CENTER>\n"
    "       <TABLE border=\"5\" bgcolor=\"#FF0000\">\n"
	"           <TR>\n"
    "           <B><I>\n"
	"               <TD class=\"tete\"><h3>NUMERO</h3></TD>\n"
	"               <TD class=\"tete\"><h3>NOM</h3></TD>\n"
	"               <TD class=\"tete\"><h3>PRENOM(S)</h3></TD>\n"
	"               <TD class=\"tete\"><h3>PRESENCE</h3></TD>\n"
	"               <TD class=\"tete\"><h3>TEMPS</h3></TD>\n"
    "           </I></B>\n"
	"           </TR>\n");

	for(i = 0; i < nbreleve; i++)
	{
		fprintf(fichier1, 	"           <TR>\n");
		fprintf(fichier1, 	"               <TD bgcolor=\"white\"> <p> %s </p> </TD>\n", l1[i].numero);
		fprintf(fichier1,	"               <TD bgcolor=\"white\"> <p> %s </p> </TD>\n", l1[i].nom);
		fprintf(fichier1,	"               <TD bgcolor=\"white\"> <p> %s </p> </TD>\n", l1[i].prenom);
		if(strcmp(l1[i].check, "OUI") == 0)
		{
			fprintf(fichier1,	"               <TD bgcolor=\"#46FB82\"> <p>%s</p> </TD>\n", l1[i].check);
		}
		else if(strcmp(l1[i].check, "NON") == 0)
		{
			fprintf(fichier1,	"               <TD bgcolor=\"#FB5446\"> <p>%s</p> </TD>\n", l1[i].check);
		}
		else if(strcmp(l1[i].check, "PERSO") == 0)
		{
			fprintf(fichier1,	"               <TD bgcolor=\"#46B9FB\"> <p>%s</p> </TD>\n", l1[i].check);
		}
		else if(strcmp(l1[i].check, "ABSENT") == 0)
		{
			fprintf(fichier1,	"               <TD bgcolor=\"#F8FB46\"> <p>%s</p> </TD>\n", l1[i].check);
		}
		else
		{
			fprintf(fichier1,	"               <TD bgcolor=\"#FFFFFF\"> <p>%s</p> </TD>\n", l1[i].check);
		}
	    fprintf(fichier1,       "               <TD bgcolor=\"white\"> <p>%s</p> </TD>\n", l1[i].temp);
		fprintf(fichier1, 	    "           </TR>\n");
	}

	fprintf(fichier1,   
    "       </TABLE>\n"
    "       </CENTER>\n"
	"   </BODY>\n"
	"</HTML>\n");

	fclose(fichier1);
}