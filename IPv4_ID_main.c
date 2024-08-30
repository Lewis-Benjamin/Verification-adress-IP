#include "IPv4_ID_lib.h"

int main()
{
    int IP_b1, MSR_b1,
        IP_b2, MSR_b2,
        IP_b3, MSR_b3,
        IP_b4, MSR_b4,
        verification,
        verifmsr;
    char Adress[100],
         MSR[100],
         donnees[500];
    entete();
    recupAdress(donnees);
    recupID(donnees, Adress, MSR);
    verification = verif(Adress, &IP_b1, &IP_b2, &IP_b3, &IP_b4);
    verifmsr = msrVerif(verification, MSR, &MSR_b1, &MSR_b2, &MSR_b3, &MSR_b4);
    msrverifClass(verifmsr, verification, IP_b1, IP_b2, IP_b3, MSR_b2, MSR_b3, MSR_b4);
    return 0;
}
