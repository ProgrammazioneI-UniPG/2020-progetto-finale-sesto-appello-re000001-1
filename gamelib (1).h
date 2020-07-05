
#ifndef gamelib_h
#define gamelib_h



#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>



void crea_cunicoli();
/* serve per creare il cunicolo e cancella il vecchio cunicolo */
void gioca();
// serve per iniziare a giocare dinimica del gioco
void termina_gioco();
// serve per uscire dal gioco e di cancellare il percorso


//
 enum Tipo_imprevisto {

      nessun_imprevisto,
      crollo,
      baco
    };


 enum Quantita_melassa {

      nessuna,
      poca,
      molta

 };


  enum raccolta {
       energia_presente,
       melassa_attiva
};


  enum Tipo_caverna {

      normale,
      accidentata,// toglie un'unita dalla melassa
      speciale,// aggiunge un'unita dalla melassa
      uscita

  };

 enum Direzione{

     direzione_sinistra,
     direzione_avanti,
     direzione_destra
 };

struct caverna {


     enum Tipo_caverna tipologia_caverna ;
     enum Quantita_melassa melassa_presente;
     enum Tipo_imprevisto imprevisto;
     enum Direzione direzione_caverna;
     struct caverna  *caverna_successiva,*avanti, *destra, *sinistra;

 };


struct scavatrice{

     struct caverna* posizione_attuale,* prima_caverna,* ultima_caverna;
     int vittoria;

     short int serbatoio_raccolta[16];



};
#endif
