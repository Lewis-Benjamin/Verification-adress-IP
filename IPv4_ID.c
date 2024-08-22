#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void recupIP(char *Adress, int *b1, int *b2, int *b3, int *b4);
void IDClass(int b1);
void validation(int b1, int b2, int b3, int b4);
void recupAdress(char *Adress);
void entete();

int main()
{
    char Adress[30];
    int b1,
        b2,
        b3,
        b4;
    entete();
    recupAdress(Adress);
    recupIP(Adress, &b1, &b2, &b3, &b4);
    validation(b1, b2, b3, b4);
    return 0;
}

void entete()
{
    printf("Content-Type: text/html\n\n");
    printf("<html>\n\t<head>\n\t\t<title>IPv4 Identification</title>\n\t</head>\n\t<body>");
}

void recupAdress(char *Adress)
{
    char *recup = getenv("QUERY_STRING");
    if (recup != NULL)
    {
        strcpy(Adress, recup);
    }
}

void recupIP(char *Adress, int *b1, int *b2, int *b3, int *b4)
{
    char* class = strtok(Adress, "=");
    class = strtok(NULL, "=");
    printf("<p>%s</p>", class);
    char* suite_1 = strtok(class, ".");
    char* suite_2 = strtok(NULL, ".");
    char* suite_3 = strtok(NULL, ".");
    char* suite_4 = strtok(NULL, ".");
    if(class != NULL && suite_1 != NULL && suite_2 != NULL && suite_3 != NULL)
    {
        *b1 = atoi(class);
        *b2 = atoi(suite_1);
        *b3 = atoi(suite_2);
        *b4 = atoi(suite_3);
    }
}

void IDClass(int b1)
{
    if(b1 >= 0 && b1 <= 127)
    {
        printf("<p>Cette adress est de class A</p></body></html>");
    }
    else if(b1 > 127 && b1 <= 191)
    {
        printf("<p>Cette adress est de class B</p></body></html>");
    }
    else if(b1 > 191 && b1 <= 223)
    {
        printf("<p>Cette adress est de class C</p></body></html>");
    }
    else if(b1 > 223 && b1 <= 239)
    {
        printf("<p>Cette adress est de class D</p></body></html>");
    }
    else if(b1 > 239 && b1 < 256)
    {
        printf("<p>Cette adress est de class E</p></body></html>");
    }
}

void validation(int b1, int b2, int b3, int b4)
{
    if(b1 >= 0 && b1 < 256 && b2 >= 0 && b2 < 256 && b3 >= 0 && b3 < 256 && b4 >= 0 && b4 < 256)
    {
        IDClass(b1);
    }
    else
    {
        printf("<p>Cette adress est invalide</p></body></html>");
    }
}