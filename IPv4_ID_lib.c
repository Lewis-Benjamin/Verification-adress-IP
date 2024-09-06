#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IPv4_ID_lib.h"

void entete()
{
    printf("Content-Type: text/html\n\n");
    printf("<html>\n\t<head>\n\t\t<title>IPv4 Identification</title><LINK rel=\"stylesheet\" href=\"style.css\">\n\t</head>\n\t<body>");
}

void recupAddress(char *donnees)
{
    char *recup = getenv("QUERY_STRING");
    if (recup != NULL)
    {
        strcpy(donnees, recup);
    }
}

void recupID(char *donnees, char *Address, char *MSR)
{
    if(sscanf(donnees, "%99[^&]&%99[^\n]", Address, MSR) != 2)
    {
        printf("<p>Erreur</p>");
    }
}

int recupMsrCIDRforma(char *MSR, int *valide) //<==
{

    int i = 0,
        msr = -1;
    char other[100];
    char* class = strtok(MSR, "=");
    class = strtok(NULL, "=");
    i = 0;
    while(class[i] != '\0')
    {
        if(class[i] >= 'a' && class[i] <= 'z' || class[i] >= 'A' && class[i] <= 'Z' || sscanf(class, "%d%s", &msr, other) == 2)
        {
            *valide = 1;
            break;
            exit(1);
        }
        else
        {
            *valide = 0;
            sscanf(class, "%d", &msr);
        }
        i++;
    }
    return (msr);
}

int* recupIP(char *Address, int *valid)
{
    int i = 0,
        *IP = NULL;
    char other[100];
    char* class = strtok(Address, "=");
    class = strtok(NULL, "=");
    IP = allocation(4);
    i = 0;
    while(class[i] != '\0')
    {
        if(class[i] >= 'a' && class[i] <= 'z' || class[i] >= 'A' && class[i] <= 'Z' || sscanf(class, "%d.%d.%d.%d%s", &IP[0], &IP[1], &IP[2], &IP[3], other) == 5)
        {
            *valid = 1;
            break;
        }
        i++;
    }
    if(*valid != 1)
    {
        sscanf(class, "%d.%d.%d.%d", &IP[0], &IP[1], &IP[2], &IP[3]);
        for(int i = 0; i < 4; i++)
        {
            if(IP[i] > 255 || IP[i] < 0)
            {
                *valid = 1;
                break;
            }
            else
            {
                *valid = 0;
            }
        }
    }
    return (IP);
}

int recupMsr(int *IP)
{
    int netmask;
    if(IP[0] >= 0 && IP[0] < 128)
    {
        printf("<center><p>Cette addresse  est de classe A</p></center>");
        netmask = 8;
    }
    else if(IP[0] >= 128 && IP[0] < 192)
    {
        printf("<center><p>Cette addresse  est de classe B</p></center>");
        netmask = 16;
    }
    else if(IP[0] >= 192 && IP[0] < 224)
    {
        printf("<center><p>Cette addresse  est de classe C</p></center>");
        netmask = 24;
    }
    else
    {
        printf("<center><p>Cette addresse  est de classe D ou de classe E</p></center>");
    }
    return (netmask);
}

int* allocation(int size) //<==
{
    int *tab = NULL;
    tab = (int*)malloc(size*sizeof(int));
    if(tab == NULL)
    {
        printf("Erreur d'allocation\n");
        exit(1);
    }
}

int* convertion(int chiffre)
{
    int *tab = NULL;
    tab = allocation(8);
    int i = 0, q;
    while(chiffre >= 1)
    {
        tab[i] = chiffre%2;
        q = (chiffre - tab[i])/2;
        chiffre = q;
        i++;
    }
    return (tab);
}

int* puissance(int pow) //<==
{
    int retour = 1,
        *fact = NULL;
    fact = allocation(pow);
    for(int i = 0; i < pow; i++)
    {
        fact[i] = retour;
        retour *= 2;
    }
    return (fact);
}

int reconversion(int *tab, int *fact)
{
    int retour = 0;
    for(int k = 0; k < 8; k++)
    {
        retour += tab[k]*fact[k];
    }
    return (retour);
}

int* netmaskRecup(int msr)
{
    int *tabmsr = NULL,
        *tab = NULL,
        *revers = NULL;
    tabmsr = allocation(4);
    tab = allocation(32);
    revers = allocation(8);
    revers = puissance(8);
    for (int i = 0; i < 32; i++)
    {
        if (i < msr)
        {
            tab[i] = 1;
        }
        else
        {
            tab[i] = 0;
        }
    }
    int j = 7;
    for(int i = 0; i <= 7; i++)
    {
        tabmsr[0] += revers[j]*tab[i];
        tabmsr[1] += revers[j]*tab[i + 8];
        tabmsr[2] += revers[j]*tab[i + 16];
        tabmsr[3] += revers[j]*tab[i + 24];
        j--;
    }
    free(tab);
    free(revers);
    return (tabmsr);
}

int* reversNetmaskRecup(int msr)
{
    int *msr_inverse = NULL,
        *tab = NULL,
        *revers = NULL;
    msr_inverse = allocation(4);
    tab = allocation(32);
    revers = allocation(8);
    revers = puissance(8);
    for (int i = 0; i < 32; i++)
    {
        if (i >= msr)
        {
            tab[i] = 1;
        }
        else
        {
            tab[i] = 0;
        }
    }
    int j = 7;
    for(int i = 0; i <= 7; i++)
    {
        msr_inverse[0] += revers[j]*tab[i];
        msr_inverse[1] += revers[j]*tab[i + 8];
        msr_inverse[2] += revers[j]*tab[i + 16];
        msr_inverse[3] += revers[j]*tab[i + 24];
        j--;
    }
    free(tab);
    free(revers);
    return (msr_inverse);
}

int nbHote(int msr)
{
    int nb_hote,
        *tab = NULL;
    tab = allocation(33-msr);
    tab = puissance(33-msr);
    nb_hote = tab[32-msr] - 2;
    free(tab);
    return (nb_hote);
}

int* addressReseau(int *IP, int *netmask)
{
    int *adresreseau = NULL;
    int *tab_1 = NULL;
    int *tab_2 = NULL;
    int *tab_3 = NULL;
    int *tab_4 = NULL;
    adresreseau = allocation(4);
    tab_1 = allocation(8);
    tab_2 = allocation(8);
    tab_3 = allocation(8);
    tab_4 = allocation(8);
    tab_4 = puissance(8);
    for(int i = 0; i < 4; i++)
    {
        tab_1 = convertion(IP[i]);
        tab_2 = convertion(netmask[i]);
        for(int j = 0; j < 8; j++)
        {
            tab_3[j] = tab_1[j]*tab_2[j];
        }
        adresreseau[i] = reconversion(tab_3, tab_4);
    }
    return (adresreseau);
}

int* addressDiffus(int *adresreseau, int *reversnetmask)
{
    int *adresdiffus = NULL;
    int *tab_1 = NULL;
    int *tab_2 = NULL;
    int *tab_3 = NULL;
    int *tab_4 = NULL;
    adresdiffus = allocation(4);
    tab_1 = allocation(8);
    tab_2 = allocation(8);
    tab_3 = allocation(8);
    tab_4 = allocation(8);
    tab_4 = puissance(8);
    for(int i = 0; i < 4; i++)
    {
        tab_1 = convertion(adresreseau[i]);
        tab_2 = convertion(reversnetmask[i]);
        for(int j = 0; j < 8; j++)
        {
            tab_3[j] = tab_1[j]+tab_2[j];
        }
        adresdiffus[i] = reconversion(tab_3, tab_4);
    }
    return (adresdiffus);
}

void verifCIDRforma()
{
    char donnees[250],
         MSR[100],
         Address[100];
    int msr,
        nb_hote,
        *netmask, *msr_inverse,
        *IP,
        *adresreseau, *adresdiffus,
        validIP, validmsr;
    entete();
    recupAddress(donnees);
    recupID(donnees, Address, MSR);
    msr = recupMsrCIDRforma(MSR, &validmsr);
    IP = recupIP(Address, &validIP);
    if(msr > 0 && msr <= 32 && validmsr == 0 && validIP == 0)
    {
        netmask = netmaskRecup(msr);
        msr_inverse = reversNetmaskRecup(msr);
        nb_hote = nbHote(msr);
        adresreseau = addressReseau(IP, netmask);
        adresdiffus = addressDiffus(adresreseau, msr_inverse);
        display(IP, netmask, nb_hote, adresreseau, adresdiffus);
        free (netmask);
        free (msr_inverse);
        free (adresreseau);
        free (adresdiffus);
    }
    else
    {
        printf("<center><p>Le calcul n'a pas pu etre exectute soit parce-que l'addresse");
        printf(" IP ou le masque de sous-reseau est non valide</p></center></body></html>");
    }
    free(IP);
}

void verif()
{
    char donnees[250];
    int msr = 0,
        nb_hote,
        *netmask, *msr_inverse,
        *IP,
        *adresreseau, *adresdiffus,
        validIP;
    entete();
    recupAddress(donnees);
    IP = recupIP(donnees, &validIP);
    if(validIP == 0)
    {
        msr = recupMsr(IP);
        netmask = netmaskRecup(msr);
        msr_inverse = reversNetmaskRecup(msr);
        nb_hote = nbHote(msr);
        adresreseau = addressReseau(IP, netmask);
        adresdiffus = addressDiffus(adresreseau, msr_inverse);
        display(IP, netmask, nb_hote, adresreseau, adresdiffus);
        free (netmask);
        free (msr_inverse);
        free (adresreseau);
        free (adresdiffus);
    }
    free (IP);
}

void display(int *IP, int *netmask, int nb_hote, int *adresreseau, int *adresdiffus)
{
    printf("<center><p><u>Voici les resultats du calcul :</u></p></center>");
    printf("<center><p>l'addresse IP : %d.%d.%d.%d</p>", IP[0], IP[1], IP[2], IP[3]);
    printf("<p>le masque de sous-reseau : %d.%d.%d.%d</p>", netmask[0], netmask[1], netmask[2], netmask[3]);
    printf("<p>le nombre d'hote : %d", nb_hote);
    printf("<p>l'addresse du reseau : %d.%d.%d.%d</p>", adresreseau[0], adresreseau[1], adresreseau[2], adresreseau[3]);
    printf("<p>l'addresse de diffusion(Broadcast) : %d.%d.%d.%d</p></center>", adresdiffus[0], adresdiffus[1], adresdiffus[2], adresdiffus[3]);
}
