#include <stdio.h>
#include <stdlib.h>

int ndg_dichte(short *feld_ptr, unsigned int anzahl_atw, float *dichte_ori, float *dichte_diff) {

    unsigned int i=0;
    unsigned int schwelle;

    *dichte_ori = 0;
    *dichte_diff = 0;

    while (i<anzahl_atw) { 

        // 1.   Nulldurchgänge des originalen Signals
        // 1.1  Negativer NDG - Wert kleiner-gleich als negative Schwellwert
        if (*(feld_ptr + i) <= -schwelle) {
            
            //1.1.1 werte bleiben negativ -> abbruch, da kein ndg
            
            //1.1.2 Werte werden positiv -> abbruch  
        }

        // Positiver NDG - Wert größer-gleich als positiver Schwellenwert
        elseif (*(feld_ptr + i) >= schwelle) {

        }

        // Keine Vorzeichenänderung
        else i++;

    } 

    // Nulldurchgangsdichte - 1/N*sum(Werte)
    *dichte_ori = *dichte_ori / anzahl_atw ; 

}