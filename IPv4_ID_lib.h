void recupIP(char *Adress, int *b1, int *b2, int *b3, int *b4, int *valid);
int IDClass(int b1);
int validation_1(int b1, int b2, int b3, int b4, int valid);
int validation_2(int b1, int b2, int b3, int b4);
void recupAdress(char *Adress);
int verif(char *Adress, int *IP_b1, int *IP_b2, int *IP_b3, int *IP_b4);
void recupID(char* donnees, char *Adress, char *MSR);
int msrVerif(int verif, char *MSR, int *MSR_b1, int *MSR_b2, int *MSR_b3, int *MSR_b4);
int validMSR(int b1, int b2, int b3, int b4);
void entete();
void msrverifClass(int valid, int verif, int IP_b1, int IP_b2, int IP_b3, int MSR_b2, int MSR_b3, int MSR_b4);