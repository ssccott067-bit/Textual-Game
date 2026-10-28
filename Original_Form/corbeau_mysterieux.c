#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// primordial constant
#define MAX_LINES 256
#define MAX_LENGTH 256

// constant of the questions & riddles 
// Humain
    // Question
        // Question 1
            #define Q1_H_C 31 // read as : question 1, humain, correct
            #define Q1_H_F 26 // read as : question 1, humain, false
        // Question 2
            #define Q2_H_C 60
            #define Q2_H_F 56
        // Question 3
            #define Q3_H_C 77
            #define Q3_H_F 73
        // Question 4
            #define Q4_H_C 92
            #define Q4_H_F 89
    // Riddle 
        // Riddle 1
            #define R1_H_C 107 // read as : riddle 1, human, correct
            #define R1_H_F 101
        // Riddle 2
            #define R2_H_C 122
            #define R2_H_F 119
        // Riddle 3
            #define R3_H_C 138
            #define R3_H_F 135
// Crow
    // Question
        // Question 1
            #define Q1_C_C 47 // read as : question 1, crow, correct
            #define Q1_C_F 42
    // Riddle
        // Riddle 1
            #define R1_C_C 77
            #define R1_C_F 72
        // Riddle 2
            #define R2_C_C 115
            #define R2_C_F 110
        // Riddle 3
            #define R3_C_C 142
            #define R3_C_F 137

// function to show remaining lives
void affichervie(int v, char *lg, int max_vie)
{
    if (strcmp(lg, "fr") == 0) // french
    {
        printf("\n> [VIE(S) RESTANTE(S) : ");
    } 
    else // english
    {
        printf("\n> [LIVE(S) LEFT : ");
    } 

    for(int i=0; i<v; i++) printf(" ❤️ ");
    for(int i=v; i<max_vie; i++) printf(" 🖤 ");
    printf("]\n");
}

// function to propose a hint 
int proposeIndice(int *vie, char *lg, char *indice_fr, char *indice_gb, int max_vie)
{
    char choix_indice[10];
    
    if (*vie <= 1)
    {
        if (strcmp(lg, "fr") == 0)
        {
            printf("\n> [ATTENTION] Vous n'avez plus assez de vies pour acheter un indice!\n");
        }
        else
        {
            printf("\n> [WARNING] You don't have enough lives to buy a hint!\n");
        }
        return 0;
    }
    
    if (strcmp(lg, "fr") == 0)
    {
        printf("\n> [💡 INDICE DISPONIBLE] Voulez-vous dépenser 1 vie pour obtenir un indice ? (oui/non) : ");
    }
    else
    {
        printf("\n> [💡 HINT AVAILABLE] Do you want to spend 1 life to get a hint? (yes/no) : ");
    }
    
    scanf("%s", choix_indice);
    
    if ((strcmp(choix_indice, "oui") == 0 && strcmp(lg, "fr") == 0) || 
        (strcmp(choix_indice, "yes") == 0 && strcmp(lg, "gb") == 0))
    {
        (*vie)--;
        if (strcmp(lg, "fr") == 0)
        {
            printf("\n> [💡 INDICE] %s\n", indice_fr);
        }
        else
        {
            printf("\n> [💡 HINT] %s\n", indice_gb);
        }
        affichervie(*vie, lg, max_vie);
        return 1;
    }
    
    return 0;
}

// programme principale
int main(int argc, char *argv[])
{   
    // principle variables
    char language[10];
    char name[100];
    char ch[50]; // character type 
    char filename[50];
    char choix[10];
    char restart[6];
    int difficulty;
    int reponse;
    float percentage;
    
    // initialisation of live mechanisme variable
    int max_vie;
    int vie;

    // variables to manipulate the table
    char lines[MAX_LINES][MAX_LENGTH];
    int line_count = 0;
    int i;
    int k;

    // select the language
    do 
    {

        printf("> Choisir la langue (fr) / Select language (gb) : ");
        scanf("%s", language);

        if (strcmp(language, "fr") == 0) 
        {
            strcpy(filename, "intro_FR.txt");
        }
        else if (strcmp(language, "gb") == 0)
        {
            strcpy(filename, "intro_GB.txt");
        }
        
    } while (strcmp(language, "fr") != 0 && strcmp(language, "gb") != 0);
    
    // open a file 
    FILE *in_file = fopen(filename, "r");
    if (in_file == NULL) 
    {
        printf("Error opening file\n");
        return 1;
    }
    
    // copy the content of the file inside a table 
    while (fgets(lines[line_count], MAX_LENGTH, in_file) != NULL && line_count < MAX_LINES) 
    {
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0';
        line_count++;
    }

    // print the table line by line 
    for (i = 0; i < line_count; i++) 
    {

        // skip any line marked as comment
        if (lines[i][0] == '#') 
        {
            continue;
        }
        
        // calculate the length of a line
        int len = strlen(lines[i]);

        // stop to ask for an input 
        if (len > 0 && lines[i][len - 2] == ':') 
        {

            // asking name
            if (strstr(lines[i], "name") != NULL || strstr(lines[i], "nom") != NULL) 
            {
                printf("> %s", lines[i]);
                scanf("%s", name);
            } 

            // asking the character type 
            if (strstr(lines[i], "humain") != NULL || strstr(lines[i], "human") != NULL) 
            {
                do 
                {
                    printf ("> %s", lines[i]);
                    scanf("%s", ch);
                } while (strcmp(ch, "h") != 0 && strcmp(ch, "c") != 0);
            }

            // asking for difficulty 
            if ((strstr(lines[i], "Which difficulty") != NULL && strcmp(language, "gb") == 0) || (strstr(lines[i], "quelle difficulté") != NULL && strcmp(language, "fr") == 0))
            {
                
                // avoid any kind of other answer 
                do 
                {

                    printf("> %s", lines[i]);
                    scanf("%d", &difficulty);

                    if (difficulty == 1)
                    {

                        max_vie = 5;
                        vie = max_vie;

                        if (strcmp(language, "fr") == 0)
                        {
                            printf("> Vous n'avez que %d vie(s) \n", max_vie);
                        }
                        else if (strcmp(language, "gb") == 0)
                        {
                            printf("> You only have %d live(s) \n", max_vie);
                        }

                    }
                    else if (difficulty == 2)
                    {

                        max_vie = 3;
                        vie = max_vie;

                        if (strcmp(language, "fr") == 0)
                        {
                            printf("> Vous n'avez que %d vie(s) \n", max_vie);
                        }
                        else if (strcmp(language, "gb") == 0)
                        {
                            printf("> You only have %d live(s) \n", max_vie);
                        }

                    }
                    else if (difficulty == 3) 
                    {

                        max_vie = 1;
                        vie = max_vie;

                        if (strcmp(language, "fr") == 0)
                        {
                            printf("> Vous n'avez que %d vie(s) \n", max_vie);
                        }
                        else if (strcmp(language, "gb") == 0)
                        {
                            printf("> You only have %d live(s) \n", max_vie);
                        }

                    }

                } while (difficulty != 1 && difficulty != 2 && difficulty != 3);
            }

            printf(">\n");

        } 
        else if (strstr(lines[i], ", ,") != NULL) // adding name between text in a line
        {

            printf("> ");

            for (int j = 0; j < len; j++) 
            {

                if (lines[i][j] == ',' && lines[i][j+1] == ' ' && lines[i][j+2] == ',') 
                {
                    printf(", %s,", name);
                    j +=2;
                } 
                else 
                {
                    printf("%c", lines[i][j]);
                }

            }

            printf("\n");

        } 
        else 
        {
            printf("> %s\n", lines[i]);
        }

    }

    // close the file 
    fclose(in_file);

    // reset line to 0 
    line_count = 0;
    
    // choose which file based on the language & character type 
    if (strcmp(ch, "h") == 0 && strcmp(language, "fr") == 0) 
    {
        strcpy(filename, "humain_FR.txt");
    } 
    else if (strcmp(ch, "h") == 0 && strcmp(language, "gb") == 0) 
    {
        strcpy(filename, "human_GB.txt");
    } 
    else if (strcmp(ch, "c") == 0 && strcmp(language, "fr") == 0) 
    {
        strcpy(filename, "corbeau_FR.txt");
    } 
    else if (strcmp(ch, "c") == 0 && strcmp(language, "gb") == 0)
    {
        strcpy(filename, "crow_GB.txt");
    }

    // open the selected file 
    in_file = fopen(filename, "r");

    if (in_file == NULL) 
    {
        printf("Error opening file \n");
        return 1;
    }

    // fill the array
    while (fgets(lines[line_count], MAX_LENGTH, in_file) != NULL && line_count < MAX_LINES) 
    {
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0';
        line_count ++;
    }

    // print the line
    for (i = 0; i < line_count; i++) 
    {

        // skip comment
        if (lines[i][0] == '#')
        {
            continue;
        }

        int len = strlen(lines[i]);

        // to stop in certain line (slowing down the line printing)
        if (len > 0 && lines[i][len-2] == '_')
        {

            strcpy(choix, " ");
            printf("> %s\n", lines[i]);

            if (strcmp(language, "fr") == 0)
            {
                printf("[ENTER pour continuer] ");
            }
            else if (strcmp(language, "gb") == 0)
            {
                printf("[ENTER to continue] ");
            }

            getc(stdin);
            printf("\n");
            continue;

        }

        // stop for asking any input
        if (len > 0 && lines[i][len -2] == ':')
        {

            strcpy(choix, " ");
            reponse = 0;

            // riddle 1 checkpoint (human)
            if (strstr(lines[i], "[Précision") != NULL || strstr(lines[i], "[Precision") != NULL)
            {

                // avoid any unexpected input
                do {
                    printf("> %s\n", lines[i-2]);
                    printf("> %s\n", lines[i-1]);
                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 126)
                    {
                        i = R1_H_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse != 126)
                    {

                        while (reponse != 126)
                        {

                            for (k=R1_H_F; k<R1_H_F+4; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            vie --;
                            affichervie(vie, language, max_vie);

                            // propose a hint
                            proposeIndice(&vie, language, 
                                "Le département du Pas-de-Calais est le 62. Formule : 62 × 2 + 2", 
                                "The Pas-de-Calais department is 62. Formula: 62 × 2 + 2", max_vie);

                            if (vie <= 0 && strcmp(language, "fr") == 0) // french
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] Vos blessures sont trop graves. Vous vous effondrez... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESSION]\n", percentage);
                                
                                do 
                                {

                                    printf("> Voulez-vous recommencer ? (oui / non) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "oui") == 0 )
                                    {
                                        i = 0; // restart to beginning
                                        vie = max_vie; 
                                        reponse = 126;
                                    } 
                                    else if (strcmp(restart, "non") == 0)
                                    {
                                        i = line_count; // end
                                        vie = max_vie;
                                        reponse = 126;
                                    }

                                } while (strcmp(restart, "oui") != 0 && strcmp(restart, "non") != 0);

                            } 
                            else if (vie <= 0 && strcmp(language, "gb") == 0) // english
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] You are badly injured. You are collapsing... \n");

                                // progress bar
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESS]\n", percentage);

                                do 
                                {

                                    printf("> Do you wish to continue ? (yes / no) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "yes") == 0)
                                    {
                                        i = 0;
                                        vie = max_vie;
                                        reponse = 126;
                                    } 
                                    else if (strcmp(restart, "no") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 126;
                                    }

                                } while (strcmp(restart, "yes") != 0 && strcmp(restart, "no") != 0);

                            }

                            if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                            {
                                continue;
                            }

                            printf("> %s\n", lines[i-2]);
                            printf("> %s\n", lines[i-1]);
                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        // to distinguish between continue the story or end/restart
                        if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                        {
                            continue;
                        }
                        else if (reponse == 126)
                        {
                            i = R1_H_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 126);

            }

            // riddle 2 checkpoint (human)
            if (strstr(lines[i], "[Indice :") != NULL || strstr(lines[i], "[Hint :") != NULL)
            {

                do 
                {

                    printf("> %s\n", lines[i-1]);
                    printf("> %s", lines[i]);
                    scanf("%s", choix);

                    if ((strcmp(choix, "COFFRE") == 0 && strcmp(language, "fr") == 0) || (strcmp(choix, "CHEST") == 0 && strcmp(language, "gb") == 0))
                    {
                        i = R2_H_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (!((strcmp(choix, "COFFRE") == 0 && strcmp(language, "fr") == 0) || (strcmp(choix, "CHEST") == 0 && strcmp(language, "gb") == 0)))
                    {

                        while (!((strcmp(choix, "COFFRE") == 0 && strcmp(language, "fr") == 0) || (strcmp(choix, "CHEST") == 0 && strcmp(language, "gb") == 0)))
                        {

                            for (k=R2_H_F; k<R2_H_F+2; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            vie --;
                            affichervie(vie, language, max_vie);
                            
                            // Proposer un indice
                            proposeIndice(&vie, language, 
                                "C'est un code César avec un décalage de -3. Z→C, E→B, B→?, P→?, Q→?", 
                                "It's a Caesar cipher with a shift of -3. Z→C, E→B, B→?, P→?, Q→?", max_vie);

                            if (vie <= 0 && strcmp(language, "fr") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] Vos blessures sont trop graves. Vous vous effondrez... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESSION]\n", percentage);
                                
                                do 
                                {
                                    printf("> Voulez-vous recommencer ? (oui / non) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "oui") == 0 )
                                    {
                                        i = 0; 
                                        vie = max_vie; 
                                        strcpy(choix, "COFFRE");
                                    } 
                                    else if (strcmp(restart, "non") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        strcpy(choix, "COFFRE");
                                    }

                                } while (strcmp(restart, "oui") != 0 && strcmp(restart, "non") != 0);

                            } 
                            else if (vie <= 0 && strcmp(language, "gb") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] You are badly injured. You are collapsing... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESS]\n", percentage);

                                do 
                                {

                                    printf("> Do you wish to continue ? (yes / no) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "yes") == 0)
                                    {
                                        i = 0;
                                        vie = max_vie;
                                        strcpy(choix, "CHEST");
                                    } 
                                    else if (strcmp(restart, "no") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        strcpy(choix, "CHEST");
                                    }

                                } while (strcmp(restart, "yes") != 0 && strcmp(restart, "no") != 0);

                            }

                            if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                            {
                                continue;
                            }

                            printf("> %s\n", lines[i-1]);
                            printf("> %s", lines[i]);
                            scanf("%s", choix);

                        }

                        if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                        {
                            continue;
                        }
                        else if ((strcmp(choix, "COFFRE") == 0 && strcmp(language, "fr") == 0) || (strcmp(choix, "CHEST") == 0 && strcmp(language, "gb") == 0))
                        {
                            i = R2_H_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (!((strcmp(choix, "COFFRE") == 0 && strcmp(language, "fr") == 0) || (strcmp(choix, "CHEST") == 0 && strcmp(language, "gb") == 0)));

            }

            // riddle 3 checkpoint (human)
            if (strstr(lines[i], "[Quel est") != NULL || strstr(lines[i], "[What is") != NULL)
            {
                do 
                {

                    printf("> %s\n", lines[i-2]);
                    printf("> %s\n", lines[i-1]);
                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 10)
                    {
                        i = R3_H_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse != 10)
                    {

                        while (reponse != 10)
                        {

                            for (k=R3_H_F; k<R3_H_F+2; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            vie --;
                            affichervie(vie, language, max_vie);
                            
                            proposeIndice(&vie, language, 
                                "16€ - 25% = 12€, puis 12€ - 2€ = ?", 
                                "16€ - 25% = 12€, then 12€ - 2€ = ?", max_vie);

                            if (vie <= 0 && strcmp(language, "fr") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] Vos blessures sont trop graves. Vous vous effondrez... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESSION]\n", percentage);
                                
                                do 
                                {
                                    printf("> Voulez-vous recommencer ? (oui / non) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "oui") == 0 )
                                    {
                                        i = 0; 
                                        vie = max_vie; 
                                        reponse = 10;
                                    } 
                                    else if (strcmp(restart, "non") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 10;
                                    }

                                } while (strcmp(restart, "oui") != 0 && strcmp(restart, "non") != 0);

                            } 
                            else if (vie <= 0 && strcmp(language, "gb") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] You are badly injured. You are collapsing... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESS]\n", percentage);

                                do 
                                {
                                    printf("> Do you wish to continue ? (yes / no) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "yes") == 0)
                                    {
                                        i = 0;
                                        vie = max_vie;
                                        reponse = 10;
                                    } 
                                    else if (strcmp(restart, "no") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 10;
                                    }

                                } while (strcmp(restart, "yes") != 0 && strcmp(restart, "no") != 0);

                            }

                            if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                            {
                                continue;
                            }

                            printf("> %s\n", lines[i-2]);
                            printf("> %s\n", lines[i-1]);
                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                        {
                            continue;
                        }
                        else if (reponse == 10)
                        {
                            i = R3_H_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 10);

            }

            // riddle 1 checkpoint (crow)
            if (strstr(lines[i], "Your answer") != NULL || strstr(lines[i], "Votre réponse") != NULL)
            {

                do 
                {

                    printf("> %s\n", lines[i-6]);
                    printf("> %s\n", lines[i-5]);
                    printf("> %s\n", lines[i-4]);
                    printf("> %s\n", lines[i-3]);
                    printf("> %s\n", lines[i-2]);
                    printf("> %s\n", lines[i-1]);
                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 1)
                    {
                        i = R1_C_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse != 1)
                    {

                        while (reponse != 1)
                        {

                            for (k=R1_C_F; k<R1_C_F+4; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            vie --;
                            affichervie(vie, language, max_vie);
                            
                            // Proposer un indice
                            proposeIndice(&vie, language, 
                                "Chaque nombre est multiplié par 2, puis on ajoute alternativement -10 et -10. Dernier: 1500×2-10=2990, puis 2990-2989=?", 
                                "Each number is multiplied by 2, then alternately add -10 and -10. Last: 1500×2-10=2990, then 2990-2989=?", max_vie);

                            if (vie <= 0 && strcmp(language, "fr") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] Vos blessures sont trop graves. Vous vous effondrez... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESSION]\n", percentage);
                                
                                do 
                                {

                                    printf("> Voulez-vous recommencer ? (oui / non) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "oui") == 0 )
                                    {
                                        i = 0; 
                                        vie = max_vie; 
                                        reponse = 1;
                                    } 
                                    else if (strcmp(restart, "non") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 1;
                                    }

                                } while (strcmp(restart, "oui") != 0 && strcmp(restart, "non") != 0);

                            } 
                            else if (vie <= 0 && strcmp(language, "gb") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] You are badly injured. You are collapsing... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESS]\n", percentage);

                                do 
                                {
                                    printf("> Do you wish to continue ? (yes / no) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "yes") == 0)
                                    {
                                        i = 0;
                                        vie = max_vie;
                                        reponse = 1;
                                    } 
                                    else if (strcmp(restart, "no") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 1;
                                    }

                                } while (strcmp(restart, "yes") != 0 && strcmp(restart, "no") != 0);

                            }

                            if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                            {
                                continue;
                            }

                            printf("> %s\n", lines[i-6]);
                            printf("> %s\n", lines[i-5]);
                            printf("> %s\n", lines[i-4]);
                            printf("> %s\n", lines[i-3]);
                            printf("> %s\n", lines[i-2]);
                            printf("> %s\n", lines[i-1]);
                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                        {
                            continue;
                        }
                        else if (reponse == 1)
                        {
                            i = R1_C_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 1);

            }

            // riddle 2 checkpoint (crow)
            if (strstr(lines[i], "Quel levier") != NULL || strstr(lines[i], "Which lever") != NULL)
            {

                do 
                {

                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 1)
                    {
                        i = R2_C_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse != 1)
                    {

                        while (reponse != 1)
                        {

                            for (k=R2_C_F; k<R2_C_F+4; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            vie --;
                            affichervie(vie, language, max_vie);
                            
                            proposeIndice(&vie, language, 
                                "L'ampoule est éteinte mais chaude = elle était allumée avant. Quel levier avez-vous éteint après 50 min?", 
                                "The bulb is off but hot = it was on before. Which lever did you turn off after 50 min?", max_vie);

                            if (vie <= 0 && strcmp(language, "fr") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] Vos blessures sont trop graves. Vous vous effondrez... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESSION]\n", percentage);
                                
                                do 
                                {
                                    printf("> Voulez-vous recommencer ? (oui / non) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "oui") == 0 )
                                    {
                                        i = 0; 
                                        vie = max_vie; 
                                        reponse = 1;
                                    } 
                                    else if (strcmp(restart, "non") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 1;
                                    }

                                } while (strcmp(restart, "oui") != 0 && strcmp(restart, "non") != 0);

                            } 
                            else if (vie <= 0 && strcmp(language, "gb") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] You are badly injured. You are collapsing... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESS]\n", percentage);

                                do 
                                {
                                    printf("> Do you wish to continue ? (yes / no) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "yes") == 0)
                                    {
                                        i = 0;
                                        vie = max_vie;
                                        reponse = 1;
                                    } 
                                    else if (strcmp(restart, "no") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 1;
                                    }

                                } while (strcmp(restart, "yes") != 0 && strcmp(restart, "no") != 0);

                            }

                            if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                            {
                                continue;
                            }

                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                        {
                            continue;
                        }
                        else if (reponse == 1)
                        {
                            i = R2_C_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 1);

            }

            // riddle 3 checkpoint (crow)
            if (strstr(lines[i], "Answer 2 or 4") != NULL || strstr(lines[i], "Réponse 2 ou 4") != NULL)
            {

                do
                {

                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 2)
                    {
                        i = R3_C_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse != 2)
                    {

                        while (reponse != 2)
                        {

                            for (k=R3_C_F; k<R3_C_F+4; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            vie --;
                            affichervie(vie, language, max_vie);
                            
                            // Proposer un indice
                            proposeIndice(&vie, language, 
                                "La moitié de 8 = 4, puis la moitié de 4 = ?", 
                                "Half of 8 = 4, then half of 4 = ?", max_vie);

                            if (vie <= 0 && strcmp(language, "fr") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] Vos blessures sont trop graves. Vous vous effondrez... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESSION]\n", percentage);
                                
                                do 
                                {

                                    printf("> Voulez-vous recommencer ? (oui / non) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "oui") == 0 )
                                    {
                                        i = 0; 
                                        vie = max_vie; 
                                        reponse = 2;
                                    } 
                                    else if (strcmp(restart, "non") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 2;
                                    }

                                } while (strcmp(restart, "oui") != 0 && strcmp(restart, "non") != 0);

                            } 
                            else if (vie <= 0 && strcmp(language, "gb") == 0)
                            {

                                strcpy(restart, " ");
                                printf("\n> [GAME OVER] You are badly injured. You are collapsing... \n");
                                percentage = (i* 100.0) / line_count;
                                printf("> [%.2f%% PROGRESS]\n", percentage);

                                do 
                                {

                                    printf("> Do you wish to continue ? (yes / no) : ");
                                    scanf("%s", restart);

                                    if (strcmp(restart, "yes") == 0)
                                    {
                                        i = 0;
                                        vie = max_vie;
                                        reponse = 2;
                                    } 
                                    else if (strcmp(restart, "no") == 0)
                                    {
                                        i = line_count;
                                        vie = max_vie;
                                        reponse = 2;
                                    }

                                } while (strcmp(restart, "yes") != 0 && strcmp(restart, "no") != 0);

                            }

                            if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                            {
                                continue;
                            }

                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        if ((((strcmp(restart, "oui") == 0 || strcmp(restart, "non") == 0) && strcmp(language, "fr") == 0) || ((strcmp(restart, "yes") == 0 || strcmp(restart, "no") == 0) && strcmp(language, "gb") == 0)) && vie == max_vie)
                        {
                            continue;
                        }
                        else if (reponse == 2)
                        {
                            i = R3_C_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 2);

            }

            // Questions checkpoints (human)
            // Q1
            if (strstr(lines[i], "appeler (1)") != NULL || strstr(lines[i], "call (1)") != NULL)
            {

                do 
                {

                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 1)
                    {
                        i = Q1_H_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse == 2)
                    {

                        while (reponse == 2)
                        {

                            for (k=Q1_H_F; k<Q1_H_F+4; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);
                            
                        }

                        if (reponse == 1)
                        {
                            i = Q1_H_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 1 && reponse != 2);

            }

            // Q2
            if (strstr(lines[i], "laisser (2)") != NULL || strstr(lines[i], "dismantle (1)") != NULL)
            {

                do 
                {

                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 1)
                    {
                        i = Q2_H_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse == 2)
                    {

                        while (reponse == 2)
                        {

                            for (k=Q2_H_F; k<Q2_H_F+3; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        if (reponse == 1)
                        {
                            i = Q2_H_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 1 && reponse != 2);

            }

            // Q3
            if (strstr(lines[i], "ouvrir (2)") != NULL || strstr(lines[i], "secure (1)") != NULL)
            {

                do 
                {

                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 2)
                    {
                        i = Q3_H_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse == 1)
                    {

                        while (reponse == 1)
                        {

                            for (k=Q3_H_F; k<Q3_H_F+3; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        if (reponse == 2)
                        {
                            i = Q3_H_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 1 && reponse != 2);

            }

            // Q4
            if (strstr(lines[i], "passer (2)") != NULL || strstr(lines[i], "solve (1)") != NULL)
            {

                do 
                {

                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 1)
                    {
                        i = Q4_H_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse == 2)
                    {

                        while (reponse == 2)
                        {

                            for (k=Q4_H_F; k<Q4_H_F+2; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        if (reponse == 1)
                        {
                            i = Q4_H_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 1 && reponse != 2);

            }

            // Questions checkpoints (crow)
            // Q1
            if (strstr(lines[i], "random (1)") != NULL || strstr(lines[i], "hasard (1)") != NULL)
            {

                do 
                {

                    printf("> %s", lines[i]);
                    scanf("%d", &reponse);

                    if (reponse == 2)
                    {
                        i = Q1_C_C;
                        printf("> %s\n", lines[i]);
                        continue;
                    }
                    else if (reponse == 1)
                    {

                        while (reponse == 1)
                        {

                            for (k=Q1_C_F; k<Q1_C_F+4; k++)
                            {
                                printf("> %s\n", lines[k]);
                            }

                            printf("> %s\n", lines[i-3]);
                            printf("> %s\n", lines[i-2]);
                            printf("> %s\n", lines[i-1]);
                            printf("> %s", lines[i]);
                            scanf("%d", &reponse);

                        }

                        if (reponse == 2)
                        {
                            i = Q1_C_C; 
                            printf("> %s\n", lines[i]);
                            continue;
                        }

                    }

                } while (reponse != 1 && reponse != 2);

            }

        }
        else 
        {
            printf("> %s\n", lines[i]);
        }

    }

    fclose(in_file);
    
    exit(EXIT_SUCCESS);
}  