#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IPv4_ID_lib.h"

int verif(char *Adress, int *IP_b1, int *IP_b2, int *IP_b3, int *IP_b4)
{
    int verif = -1,
        valid;
    if(Adress == NULL)
    {
        printf("<h1>Vous devez entrer une adresse IP</h1></body></html>");
    }
    else
    {
        printf("<center><table><tr><td class=\"saisi\"><center>Address IP : ");
        recupIP(Adress, IP_b1, IP_b2, IP_b3, IP_b4, &valid);
        verif = validation_1(*IP_b1, *IP_b2, *IP_b3, *IP_b4, valid);
    }
    return (verif);
}

void entete()
{
    printf("Content-Type: text/html\n\n");
    printf("<html>\n\t<head>\n\t\t<title>IPv4 Identification</title>");
    printf("<LINK rel=\"stylesheet\" href=\"style.css\">\n\t</head>\n\t<body>");
}

void recupAdress(char *donnees)
{
    char *recup = getenv("QUERY_STRING");
    if (recup != NULL)
    {
        strcpy(donnees, recup);
    }
}

void recupIP(char *Adress, int *b1, int *b2, int *b3, int *b4, int *valid)
{
    int i = 0;
    char* class = strtok(Adress, "=");
    class = strtok(NULL, "=");
    char other[20];
    i = 0;
    while(class[i] != '\0')
    {
        if(class[i] >= 'a' && class[i] <= 'z' || class[i] >= 'A' && class[i] <= 'Z' || sscanf(class, "%d.%d.%d.%d%s", b1, b2, b3, b4, other) == 5)
        {
            *valid = 1;
            break;
        }
        else if(sscanf(class, "%d.%d.%d.%d", b1, b2, b3, b4) == 4)
        {
            *valid = 0;
        }
        i++;
    }
    printf("%s</center></td></tr></table></center>", class);
}

int IDClass(int b1)
{
    int verif;
    if(b1 >= 0 && b1 <= 127)
    {
        printf("<center><p>Cette adress est de class A</p></center></body></html>");
        verif = 1;
    }
    else if(b1 > 127 && b1 <= 191)
    {
        printf("<center><p>Cette adress est de class B</p></center></body></html>");
        verif = 2;
    }
    else if(b1 > 191 && b1 <= 223)
    {
        printf("<center><p>Cette adress est de class C</p></center></body></html>");
        verif = 3;
    }
    else if(b1 > 223 && b1 <= 239)
    {
        printf("<center><p>Cette adress est de class D</p></center></body></html>");
        verif = 4;
    }
    else if(b1 > 239 && b1 < 256)
    {
        printf("<center><p>Cette adress est de class E</p></center></body></html>");
        verif = 4;
    }
    return (verif);
}

int validation_2(int b1, int b2, int b3, int b4)
{
    int verif;
    if(b1 >= 0 && b1 < 256 && b2 >= 0 && b2 < 256 && b3 >= 0 && b3 < 256 && b4 >= 0 && b4 < 256)
    {
        verif = IDClass(b1);
    }
    else
    {
        printf("<center><p>Cette adress est invalide</p></center></body></html>");
    }
    return (verif);
}

int validation_1(int b1, int b2, int b3, int b4, int valid)
{
    int verif;
    if(valid == 1)
    {
        printf("<center><p>Cette adress est invalide</p></center></body></html>");
    }
    else
    {
        verif = validation_2(b1, b2, b3, b4);
    }
    return (verif);
}

void recupID(char *donnees, char *Adress, char *MSR)
{
    if(sscanf(donnees, "%255[^&]&%255[^\n]", Adress, MSR) != 2)
    {
        printf("<p>Erreur</p>");
    }
}

int msrVerif(int verif, char *MSR, int *MSR_b1, int *MSR_b2, int *MSR_b3, int *MSR_b4)
{
    int valid;
    if(MSR == NULL)
    {
        printf("<h1>Vous devez entrer un masque de sous-reseau</h1></body></html>");
    }
    else
    {
        printf("<center><table><tr><td class=\"saisi\"><center>Masque de sous-reseau : ");
        recupIP(MSR, MSR_b1, MSR_b2, MSR_b3, MSR_b4, &valid);
        valid = validMSR(*MSR_b1, *MSR_b2, *MSR_b3, *MSR_b4);
    }
    return (valid);
}

int validMSR(int b1, int b2, int b3, int b4)
{
    int valid;
    if(b1 >= 0 && b1 < 256 && b2 >= 0 && b2 < 256 && b3 >= 0 && b3 < 256 && b4 >= 0 && b4 < 256)
    {
        printf("<center><p>Ce masque de sous-reseau est valide</p></center>");
        valid = 0;
    }
    else
    {
        printf("<center><p>Ce masque de sous-reseau est invalide</p></center>");
        valid = 1;
    }
    return (valid);
}

void msrverifClass(int valid, int verif, int IP_b1, int IP_b2, int IP_b3, int MSR_b2, int MSR_b3, int MSR_b4)
{
    if(verif == 4 && valid == 0)
    {
        printf("<p>Le masque de sous-reseau des classes D et E n'ont pas encore ete etudiees</p>");
    }
    else if(verif == 3 && valid == 0 && MSR_b4 == 0)
    {
        printf("<center><p>Adress reseau : %d.%d.%d.0</p>", IP_b1, IP_b2, IP_b3);
        printf("<p>Adress de diffusion : %d.%d.%d.255</p>", IP_b1, IP_b2, IP_b3);
        printf("<p>Il y a 16777214 machines qui sont connectees entre-elles</p></center>");
    }
    else if(verif == 2 && valid == 0 && MSR_b3 == 0 && MSR_b4 == 0)
    {
        printf("<center><p>Adress reseau : %d.%d.0.0</p>", IP_b1, IP_b2);
        printf("<p>Adress de diffusion : %d.%d.255.255</p>", IP_b1, IP_b2);
        printf("<p>Il y a 65534 machines qui sont connectees entre-elles</p></center>");
    }
    else if(verif == 1 && valid == 0 && MSR_b2 == 0 && MSR_b3 == 0 && MSR_b4 == 0)
    {
        printf("<center><p>Adress reseau : %d.0.0.0</p>", IP_b1);
        printf("<p>Adress de diffusion : %d.255.255.255</p>", IP_b1);
        printf("<p>Il y a 255 machines qui sont connectees entre-elles</p></center>");
    }
    else
    {
        printf("<p>L'adresse IP et le masque de sous-reseau ne sont pas compatible</p>");
    }
}