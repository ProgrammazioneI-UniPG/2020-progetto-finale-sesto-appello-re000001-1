#include <stdlib.h>
#include <stdio.h>
#include "gamelib.h"


int main (void)
{


system("clear");

unsigned short int opzione=0;
// opzione è la scelta del giocatore
// mappa esistenza cunicolo 1 esiste 0 non esiste
// modificamappa se esiste un percorso questa mappa ci permette di modificarlo o di crearne uno nuovo

printf("\033[1;31m");

sleep(2);
system("clear");
printf("\t\t\t\t CREATED BY...\n");
sleep(2);
system("clear");
printf("\t\t\t\tEL FADILI RIDA   MATRICOLA N. 321252\n");
sleep(2);
system("clear");


printf("\033[32m");
printf("\033[3m");
printf("La Arvais e la Hartornen sono due famiglie che si contendono da anni sul pianeta Sabbie l’estrazione della Melassa\n");
printf("L’estrazione è ostacolata da numerosi pericoli, come improvvise frane,\n");
printf("scontri con la compagnia rivale, e i pericolosissimi Bachi delle Sabbie.\n\n\n");
printf("\n\t\t\tPER GIOCARE OGNI GIOCATORE DEVE AVERE IL PROPRIO CUNICOLO\n" );
sleep(3);
printf("\033[0m");
// introduzione
do    {
  printf("\033[31m");
  printf("IMMETTERE 1 PER CREARE IL CUNICOLO\n");
  printf("IMMETTERE 2 PER GIOCARE\n");
  printf("IMMETTERE 3 PER USCIRE\n" );
  printf("\033[0m");

  //scanf("%hd\n", &opzione);

  while (scanf("%hu",&opzione) != 1 || opzione >3|| opzione <1){

           printf("\033[1;31m");
           printf("\n\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
           printf("\033[0m");
           while (getchar() != '\n');
  }



switch (opzione) {
  case 1 :// crea cunicolo
        system("clear");
        crea_cunicoli();
        system("clear");
        break;

  case 2 :// si gioca

        gioca();

        break;



  case 3 :

       system("clear");
       termina_gioco();
       break;
       default:
              break;

                }//chiude lo switch

//}
// while (opzione!=3);



}
while(opzione!=3);
}
