#include<stdio.h>
#include<stdlib.h>

int signal_detekt(short **sample_anfang, int *sample_anzahl) {

   unsigned int anzahl_zeitintervalle=100; // einstellen
   unsigned int laenge_zeitintervalle=*sample_anzahl/anzahl_zeitintervalle;

   unsigned int energieverlauf[100]; // einstellen
   unsigned int energie=0;
   unsigned int energie_index=0;

   unsigned int energie_max=0;

   float einstellung_schwelle=0.3; // einstellen

   unsigned int schwelle;

   unsigned int index_Beginn_Signal;

   // Schritt 1: Energieverlauf bestimmen
   for(int i=0; i<*sample_anzahl; i++) {
    energie = energie + (*(*sample_anfang+i)) * (*(*sample_anfang+i));

    if((i+1)%laenge_zeitintervalle==0) {
        energieverlauf[energie_index] = energie;
        energie_index++;
        energie = 0;
    }
   }

   // Schritt 2: Schwellwert bestimmen
   for (int i=0; i<anzahl_zeitintervalle; i++) {
    if(energieverlauf[i]>energie_max) {
        energie_max=energieverlauf[i];
    }
   }
   schwelle=energie_max*einstellung_schwelle;

   // Schritt 3: Startwert bestimmen
   for(int i=0; i<anzahl_zeitintervalle; i++) {
    if(energieverlauf[i]>schwelle) {
        *sample_anfang=*sample_anfang+(i*laenge_zeitintervalle);
        index_Beginn_Signal=i;
        break;
    }
   }

   // Schritt 4: Ende des Signals bestimmen
   for(int i=index_Beginn_Signal;i<anzahl_zeitintervalle;i++) {
    if(energieverlauf[i]<schwelle||i==anzahl_zeitintervalle) {
        *sample_anzahl=(i-index_Beginn_Signal)*laenge_zeitintervalle;
        return(0);
        break;
    }
   }
   
   

}




void main(void) {

    // Beispielsignal
    short sample[20] = {1,2,3,2,3,9,7,13,17,4,5,-2,-5,3,4,3,2,1,-2,2};
    for (int i=0;i<20;i++) {
        printf("%d ", sample[i]);
    }
    printf("\n");

    // Pointer auf Beginn des relevanten Teiles
    short *beginn;
    beginn=&sample[0]; //der Pointer "beginn" zeigt auf Adresse des ersten Objektes

    // Breite des relevanten Teiles
    int anzahl=20;

    // Funktionsaufruf Signaldetektion
    int fehlermeldung=signal_detekt(&beginn, &anzahl);

    printf("Startwert: %d\n", *beginn);
    printf("Anzahl der relevaten Abtastwerte nach Beginn: %d\n", anzahl);
}
