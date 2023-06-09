#include<stdio.h>
#include<stdlib.h>

int ndg_dichte(short *feld_ptr, unsigned int anzahl_atw, float *dichte_ori, float *dichte_diff) {

    unsigned int i=0;
    signed int schwelle=100; // EINSTELLEN!

    // Original-Dichte:

    *dichte_ori=0;

    while(i<anzahl_atw) {

        // größer als +s --> nächsten ermitteln der kleiner ist als -s
        if(*(feld_ptr+i)>schwelle) {
            for(i; i<anzahl_atw; i++) {
                if(*(feld_ptr+i)<(-schwelle)) {
                    (*dichte_ori)++;
                    break;
                }
            }
        }
        // kleiner als -s --> Nächsten ermitteln der überhalb von +s ist
        else if(*(feld_ptr+i)<(-schwelle)) {
            for(i; i<anzahl_atw; i++) {
                if(*(feld_ptr+i)>schwelle) {
                    (*dichte_ori)++;
                    break;
                }
            }
        }
        // keines von beiden: zähle weiter:
        else i++;   
    }
    *dichte_ori=*dichte_ori/anzahl_atw;


    // Differenzierte Dichte:

    i=1;
    *dichte_diff=0;
    while(i<anzahl_atw) {

        // größer als +s --> nächsten ermitteln der kleiner ist als -s
        if((*(feld_ptr+i)-*(feld_ptr+(i-1)))>schwelle) {
            for(i; i<anzahl_atw; i++) {
                if((*(feld_ptr+i)-*(feld_ptr+(i-1)))<(-schwelle)) {
                    (*dichte_diff)++;
                    break;
                }
            }
        }

        // kleiner als -s --> Nächsten ermitteln der überhalb von +s ist
        else if((*(feld_ptr+i)-*(feld_ptr+(i-1)))<(-schwelle)) {
            for(i; i<anzahl_atw; i++) {
                if((*(feld_ptr+i)-*(feld_ptr+(i-1)))>schwelle) {
                    (*dichte_diff)++;
                    break;
                }
            }
        }
        // keines von beiden: zähle weiter:
        else i++;   
    }

    *dichte_diff=*dichte_diff/anzahl_atw;

    if(*dichte_diff==0 || *dichte_ori == 0) return 1; // Signal zu schwach
    return 0; // kein Fehler aufgetreten
}




void main(void) {

    // Beispielsignal
    short sample[20] = {10,20,130,200,-5,99,-110,13,-170,-400, 113,-2,150,5,-2,-130,200,170,-2,20};
    // short sample[20] = {10,20,99,20,-5,99,-10,13,-70,-40, 13,-2,10,5,-2,-30,20,70,-2,20}; // schwaches Signal
    for (int i=0;i<20;i++) {
        printf("%d ", sample[i]);
    }
    printf("\n");

    // Pointer auf Beginn des relevanten Teiles
    short *beginn;
    beginn=&sample[0]; //der Pointer "beginn" zeigt auf Adresse des ersten Objektes

    // Breite des relevanten Teiles
    int anzahl=20;

    // Originaldichte:
    float dichte_original=0;

    // Differenzierte Dichte:
    float dichte_differenziert=0;


    // Funktionsaufruf Signaldetektion
    int fehlermeldung=ndg_dichte(beginn, anzahl, &dichte_original, &dichte_differenziert);


    printf("Original-Dichte: %f\n", dichte_original);
    printf("Differenzierte-Dichte: %f\n", dichte_differenziert);
    printf("Fehlerstatus: %d\n", fehlermeldung);
}
