#include <stdio.h>
#include <stdlib.h>

//#include "erkenner.h"

int ANZ_HIST_KAN = 4;

int ndg_histogramm(short *feld_ptr, unsigned int anzahl_atw, float *hist_ori, float *hist_diff) {

    unsigned int i=0;
    unsigned int pos_1, pos_2;  // Start- und Entposition eines dedektierten NDG
    short d1=10, d2=40, d3=100; // Grenzen zwischen den Kanälen; ggf. einstellen
    short inc_k1=1, inc_k2=1, inc_k3=1, inc_k4=1;   // Inkremente der Histogrammkanäle; ggf. einstellen
    signed int schwelle=100; // Schwellwert; ggf. EINSTELLEN!
    int returnwert = 0;

    // Originalsignal:
    while(i<anzahl_atw) {
 
        // größer-gleich als +s
        if(*(feld_ptr+i)>=schwelle) {
        
            pos_1 = i;

            //solange Schwellenwert +s erreicht oder überschritten bleibt
            while(*(feld_ptr+i)>=schwelle) {
                i++;
            }

            pos_2 = i;

            int laenge = 0;
            laenge = pos_2 - pos_1;

            if (laenge <= d1) {
                *(hist_ori)+= inc_k1;
            }
            else if (laenge <=d2) {
                *(hist_ori+1)+=inc_k2;
            }
            else if (laenge <=d3) {
                *(hist_ori+2)+=inc_k3;
            }
            else {
                *(hist_ori+3)+=inc_k4;
            }
        }
        // kleiner-gleich als -s
        else if(*(feld_ptr+i)<=(-schwelle)) {
            
            pos_1 = i;

            //solange Schwellenwert -s erreicht oder unterschritten bleibt
            while(*(feld_ptr+i)<=schwelle) {
                i++;
            }
            
            pos_2 = i;
            
            int laenge = 0;
            laenge = pos_2 - pos_1;

            if (laenge <= d1) {
                *(hist_ori)+= inc_k1;
            }
            else if (laenge <=d2) {
                *(hist_ori+1)+=inc_k2;
            }
            else if (laenge <=d3) {
                *(hist_ori+2)+=inc_k3;
            }
            else {
                *(hist_ori+3)+=inc_k4;
            }
        }

        // keines von beiden, also zwischen dne Schwellenwerten
        else i++;   
    }

    // Differenziertes Signal:
    i = 1;   // i=1 da sosnt fehler beim differenzieren mit ersten Eintrag.

     while(i<anzahl_atw) {

        // größer-gleich als +s
        if((*(feld_ptr+i) - *(feld_ptr+(i-1))) >= schwelle) {
        
            pos_1 = i;

            //solange Schwellenwert +s erreicht oder überschritten bleibt
            while((*(feld_ptr+i) - *(feld_ptr+(i-1))) >= schwelle) {
                i++;
            }
            
            pos_2 = i;

            int laenge = 0;
            laenge = pos_2 - pos_1;

            if (laenge <= d1) {
                *(hist_diff)+= inc_k1;
            }
            else if (laenge <=d2) {
                *(hist_diff+1)+=inc_k2;
            }
            else if (laenge <=d3) {
                *(hist_diff+2)+=inc_k3;
            }
            else {
                *(hist_diff+3)+=inc_k4;
            }
        }
        // kleiner-gleich als -s
        else if((*(feld_ptr+i) - *(feld_ptr+(i-1))) <= (-schwelle)) {
            
            pos_1 = i;

            //solange Schwellenwert -s erreicht oder unterschritten bleibt
            while((*(feld_ptr+i) - *(feld_ptr+(i-1))) <= schwelle) {
                i++;
            }
            
            pos_2 = i;
            
            int laenge = 0;
            laenge = pos_2 - pos_1;

            if (laenge <= d1) {
                *(hist_diff)+= inc_k1;
            }
            else if (laenge <=d2) {
                *(hist_diff+1)+=inc_k2;
            }
            else if (laenge <=d3) {
                *(hist_diff+2)+=inc_k3;
            }
            else {
                *(hist_diff+3)+=inc_k4;
            }
        }

        // keines von beiden, also zwischen dne Schwellenwerten
        else i++;   
    }

    // Returnwert ermitteln
    for (i=0; i<ANZ_HIST_KAN; i++) {
 	
        returnwert += *(hist_ori+i) + *(hist_diff+i);  
    };

    if(returnwert > 0 ) {
        return (0);     // kein Fehler aufgetreten
    }

    return(1);    //Keine Daten

}