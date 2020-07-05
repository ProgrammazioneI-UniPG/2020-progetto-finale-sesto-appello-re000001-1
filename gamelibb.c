
#include "gamelib.h"


//PROTOTIPI DELLE FUNZIONI

static void ins_caverna();

static void canc_caverna();// ho cambiato il nome della funzione e quindi va cambiata

static void stampa_cunicolo();

static void chiudi_cunicolo();

void crea_cunicoli();

void gioca();

void termina_gioco();

static void crea_cunicoli_arvais();

static void crea_cunicoli_hartornen();

static void turnoarvais();

static void turnohartornen();

static struct scavatrice arvais = { .posizione_attuale=NULL,.serbatoio_raccolta[energia_presente]=4, .serbatoio_raccolta[melassa_attiva]=0, .vittoria=0 };// manca il null

static struct scavatrice hartornen = {.posizione_attuale=NULL, .serbatoio_raccolta[energia_presente]=4, .serbatoio_raccolta[melassa_attiva]=0, .vittoria=0 };

static void scontro_scavatrici();

static void avanza(struct scavatrice*);

static void abbatti(struct scavatrice*);

static void aggira(struct scavatrice*);



static void melas_trov();

static void reset();

static void reset_abbatti(  struct scavatrice *player);

static enum Quantita_melassa p_melassa(int probabilita_melassa);

static enum Tipo_imprevisto p_imprevisto(int probabilita_imprevisto);

static enum Tipo_imprevisto avanza_imprevisto( int probabilita_imprev);

static void stato_imprevisto(struct scavatrice* player);

static void melas_trov(struct scavatrice* player);

static enum chiusura {si,no} chiusura = no;
static short int numcaverne=0;
static short int direzione=0;
static int controllo_cav=0, num_abbatti_a=0, num_abbatti_h=0;
static short int num_turni=0;//ogni turno aumenta di 1 (quindi per)
//static short int num_abbatti=0;

static short int ordinalita_arvais=1;
static short int ordinalita_hartornen=1;

unsigned short int cunicolo_a=0, cunicolo_h=0;
// la funzione che mi fa partire il gioco da capo cioè da 0
static void reset(){
        chiusura=no;
        arvais.serbatoio_raccolta[energia_presente]=4;
        arvais.serbatoio_raccolta[melassa_attiva]=0;
        hartornen.serbatoio_raccolta[energia_presente]=4;
        hartornen.serbatoio_raccolta[melassa_attiva]=0;
        arvais.vittoria=0;
        hartornen.vittoria=0;
        ordinalita_arvais=1;
        ordinalita_hartornen=1;
        num_turni=0;
        num_abbatti_a=0;
        num_abbatti_h=0;
        direzione=0;
}



static void crea_cunicoli_arvais(){

    short int scelta_arvais=0;
     system("clear");
    do{
       printf("\033[1;36m");
       printf("ARVAIS INIZIATE\n" );
       printf("CREA IL CUNICOLO\n");
       printf("\033[1;36m");
       printf("\033[5m");
       printf("\n\t\tRICORDA NON PUOI INIZIARE A GIOCARE SE PRIMA NON CHIUDI IL CUNICOLO!\n");
       printf("\033[0m");

       printf("\033[1;36m");


       printf("PREMERE 1 PER INSERIRE LA CAVERNA     2 PER CANCELLARE LA CAVERNA     3 PER STAMPARE LA CAVERNA      4 PER CHIUDERE IL CUNICOLO       5 PER PASSARE ALLA MOSSA SUCCESSIVA\n" );
       printf("\033[0m");


       while (scanf("%hu",&scelta_arvais) != 1 || scelta_arvais >5|| scelta_arvais <1){

       printf("\033[1;36m");
       printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
       printf("\033[0m");
       while (getchar() != '\n');
       }
       switch(scelta_arvais){
           case 1:

                 ins_caverna(&arvais);
                 system("clear");
           break;
           case 2:
                 canc_caverna(&arvais);
                 system("clear");

           break;
           case 3:
                 stampa_cunicolo(&arvais);
                 system("clear");

           break;
           case 4:
                 printf("\n");
                 chiudi_cunicolo();


           break;
           case 5:

           printf("\033[1;36m");
           if(arvais.prima_caverna==NULL){
               printf("\n\t\tPRIMA DI GIOCARE,COSTRUISCI IL CUNICOLO!\n");

               crea_cunicoli_arvais();
           }
           else if(chiusura== no){
               printf("\n\t\tNON PUOI INIZIARE A GIOCARE SE PRIMA NON CHIUDI IL CUNICOLO!\n");

               cunicolo_a=1;
               crea_cunicoli_arvais();
           }

               system("clear");

           break;
           default:



           break;
        }

       }while(scelta_arvais!=5);

}


static void crea_cunicoli_hartornen(){

  short int scelta_hartornen = 0;
  system("clear");
  do{

    printf("\033[1;36m");
    printf("CREATE IL VOSTRO CUNICOLO HARTORNEN\n");
    printf("\033[1;36m");
    printf("\033[5m");
    printf("\n\t\tRICORDA NON PUOI INIZIARE A GIOCARE SE PRIMA NON CHIUDI IL CUNICOLO!\n");
    printf("\033[0m");
    printf("\033[1;36m");
    printf("PREMERE 1 PER INSERIRE LA CAVERNA     2 PER CANCELLARE LA CAVERNA     3 PER STAMPARE LA CAVERNA      4 PER CHIUDERE IL CUNICOLO       5 PER PASSARE ALLA MOSSA SUCCESSIVA\n" );
    printf("\033[0m");


    while (scanf("%hu", &scelta_hartornen)!=1 || scelta_hartornen<1 || scelta_hartornen>5){
           printf("\n\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
           while (getchar() != '\n');

  };


     switch(scelta_hartornen){
            case 1:

                   ins_caverna(&hartornen);
                   system("clear");
                   break;
            case 2:
                    canc_caverna(&hartornen);
                    system("clear");
                    break;
            case 3:
                    stampa_cunicolo(&hartornen);
                    system("clear");
                     break;
            case 4:
                   printf("\n");
                   chiudi_cunicolo();
                   break;
            case 5:
                    printf("\033[1;36m");
                    if(hartornen.prima_caverna==NULL){
                    printf("\n\t\t\tPRIMA DI GIOCARE,COSTRUISCI IL CUNICOLO!\n");

                    crea_cunicoli_hartornen();
                    }
                    else if(chiusura== no){
                    printf("\n\t\tNON PUOI INIZIARE A GIOCARE SE PRIMA NON CHIUDI IL CUNICOLO!\n");

                    cunicolo_h=1;
                    crea_cunicoli_hartornen();
                     }


                   break;

          }// chiusura swich
          }
          while(scelta_hartornen!=5);



}


void crea_cunicoli(){

    system("clear");




     printf("\033[1;36m");
     printf("INIZIANO GLI ARVAIS POI TOCCHERA' AGLI HARTORNEN \n" );
     printf("\033[0m");

    crea_cunicoli_arvais();
    system("clear");
// INIZIANO  GLI HARTORNEN
   chiusura = no;
   numcaverne=0;
   controllo_cav=0;


   crea_cunicoli_hartornen();
   system("clear");
          }


static void canc_caverna(struct scavatrice* player){

      struct caverna *posizionecoda=NULL;
      posizionecoda = player->prima_caverna;
      if (player->prima_caverna==NULL) {
        printf("NON HAI INSERITO NESSUNA CAVERNA\n");
                              }
      else if (player->prima_caverna->caverna_successiva==NULL) {
        printf("NON PUOI ELIMINARE LA PRIMA CAVERNA");
                                                        }
          else{
               numcaverne--;

              while (posizionecoda->caverna_successiva != NULL) {
                    player-> ultima_caverna = posizionecoda;
                     posizionecoda = posizionecoda->caverna_successiva;
               }
               free(posizionecoda);
               player->ultima_caverna->caverna_successiva=NULL;
               printf("ULTIMA CAVERNA CANCELLATA CORRETTAMENTE\n" );

               }
}


static enum Quantita_melassa p_melassa(int probabilita_melassa){

           if (probabilita_melassa<=50) {
              return nessuna;
           }
           else if (probabilita_melassa>=50 &&probabilita_melassa<=80 ) {
             return poca;
           }
           else {
             return molta;
            }
}


static enum Tipo_imprevisto p_imprevisto( int probabilita_imprevisto){


            if (probabilita_imprevisto>=51 &&probabilita_imprevisto<=85 ) {
             return crollo;
           }
           else if (probabilita_imprevisto>85){
             return baco;
            }
            else  {
               return nessun_imprevisto;
            }
}


static void ins_caverna(struct scavatrice* player){

  /* NELLA CREAZIONE DELLE CAVERNA NEL gamelib.H HO CEATO UN ENUM DIREZIONE E QUANDO L'UTENTE SCEGLIE LA DIREZIONE nuova_cav PUNTA AD QUESTO ENUM
  E ASSUME UNO DEI TRE VALORI (AVANTI;DESTRA;SINISTRA). NON HO VOLUTO FARE IN MODO CHE nuova_cav PUNTASSE DIRETTAMENTE AI TRE PUNTATORI(AVANTI,DESTRA,SINISTRA)
  PERCHE' IN PRATICA LA DIREZIONE DELLA CAVERNA E' SEMPRE VERSO AVANTI ESSENDO UNA LISTA, QUINDI LA DIREZIONE E' SOLO PER DARE L'IDEA CHE IL player STA
  GIRANDO; NEL CODICE HO MESSO PER COMMENTO LA OARTE IN CUI SE SI VOLEVA FARE LA DIREZIONE  CON TRE PUNTATORI

*/


  time_t t;
  srand((unsigned) time(&t));
  int numcaverne=0, direction=0, type=0;
  int probabilita_melassa = 0;
  int probabilita_imprevisto = 0;



       printf("QUANTE CAVERNE VUOI INSERIRE? RICORDA CHE LE CAVDRNE IN TUTTO DEVO ESSERE MINIMO 10\n");
       while (scanf("%d", &numcaverne)!=1 || controllo_cav+numcaverne<10) {
       printf("DEVI INSERIRE ALMENO 10 CAVERNE! RIPROVA\n" );
       while (getchar() != '\n');
       }
       system("clear");

  for (int i = 0; i < numcaverne; i++) {
            system("clear");
            struct caverna* nuova_cav=NULL;
             nuova_cav =(struct caverna*) malloc (sizeof(struct caverna));
            printf("INSERISCI LA DIREZIONE DELLA CAVERNA: 1 PER SINISTRA,  2 PER AVANTI,  3 PER DESTRA\n");

        //  while (scanf("%u", &  nuova_cav->direzione_caverna) !=1 ||   nuova_cav->direzione_caverna<1 ||   nuova_cav->direzione_caverna>3){
      //  while ( scanf("%u", &nuova_cav->direzione )!=1  ||  nuova_cav->direzione<1   ||  nuova_cav->direzione>3) {
            while ( scanf("%d", &direction)!=1 || direction<1 || direction>3) {

              printf("\033[1;36m");
              printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
              printf("\033[0m");
              while (getchar() != '\n');
            }
            switch (direction) {

       case 1:
              printf("HAI SCELTO DI CREARE LA CAVERNA VERSO SINISTRA\n" );
              nuova_cav->direzione_caverna=direzione_sinistra;
            //  nuova_cav->sinistra;
              break;

       case 2:
              printf("HAI SCELTO DI CREARE LA CAVERNA VERSO AVANTI\n" );
          //    nuova_cav->avanti;
              nuova_cav->direzione_caverna=direzione_avanti;
              break;

       case 3:
              printf("HAI SCELTO DI CREARE LA CAVERNA VERSO DESTRA\n");
            //  nuova_cav->destra;
              nuova_cav->direzione_caverna=direzione_destra;
              break;

            }




        printf("SCEGLIERE LA TIPOLOGIA DELLA CAVERNA :1 PER NORMALE      2 PER SPECIALE     3 ACCIDENTATA\n");
        //while ( scanf("%u", &nuova_cav->tipologia_caverna )!=1  ||  nuova_cav->tipologia_caverna<1   ||  nuova_cav->tipologia_caverna>3) {
      while ( scanf("%d", &type )!=1  ||  type<1   ||  type>3) {
          printf("\033[1;36m");
          printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
          printf("\033[0m");
          while (getchar() != '\n');
        }
    switch (type) {
    case 1:
          printf("LA CAVERNA SARA' DI TIPO NORMALE\n" );
          nuova_cav->tipologia_caverna=normale;
          break;

    case 2:
          printf("LA CAVERNA SARA' DI TIPO SPECIALE\n" );
          nuova_cav->tipologia_caverna=speciale;
          break;

    case 3:
          printf("LA CAVERNA SARA' DI TIPO ACCIDENTATA\n");
          nuova_cav->tipologia_caverna=accidentata;
          break;


        }

        probabilita_melassa= 1 + (rand() % 100);
        probabilita_imprevisto= 1 + (rand() % 100);
    //    nuova_cav->tipologia_caverna = p_melassa( probabilita_melassa);
        nuova_cav->melassa_presente = p_melassa( probabilita_melassa);
    //    nuova_cav->tipologia_caverna = p_imprevisto( probabilita_imprevisto);
        nuova_cav->imprevisto = p_imprevisto( probabilita_imprevisto);


        controllo_cav++;

         nuova_cav->caverna_successiva =NULL;


         if (player->prima_caverna==NULL) {
         player->prima_caverna=nuova_cav;
         player->ultima_caverna=player->prima_caverna;
         player->posizione_attuale =player->prima_caverna;
         system("clear");
       }
       else{
           player->ultima_caverna ->caverna_successiva = nuova_cav;
           player->ultima_caverna = player->ultima_caverna->caverna_successiva;
       }
system("clear");
}

       printf("CUNICOLO CREATO CORRETTAMENTE\n" );

}


static void stampa_cunicolo(struct scavatrice* player){

  int cav=0;
  if(player->prima_caverna == NULL){
      printf("\033[1;36m");
      printf("\n\t\t\t\tIL CUNICOLO È VUOTO!\n");
      sleep(1);
      printf("\033[0m");
  }
  else{
      struct caverna *temp = player->prima_caverna;
      printf("\033[1;33m");
      printf("\n\t\t\t+---------------+---------------+---------------+\n");
      printf("\t\t\t|  CAVERNA N°   |   DIREZIONE   |  TIPOLOGIA    |\n");
      printf("\t\t\t+---------------+---------------+---------------+\n");
      printf("\033[0m");
      while(temp!=NULL){
           cav++;
           if (cav>9) {
             printf("\t\t\t| CAVERNA N° %d |", cav );
           }
           else{
             printf("\t\t\t| CAVERNA N° %d  |", cav );
           }

           switch(temp-> direzione_caverna){
               case direzione_sinistra:
               printf(  "   SINISTRA    |");
               break;
               case direzione_avanti:
               printf(  "    AVANTI     |");
               break;
               case direzione_destra:
               printf(  "    DESTRA     |");
               break;

               default:
               break;
               }

          switch(temp-> tipologia_caverna){
              case normale:
              printf(  "  NORMALE      |");
              break;
              case speciale:
              printf(  "  SPECIALE     |");
              break;
              case accidentata:
              printf(  "  ACCIDENTATA  |");
              break;

              default:
              break;
              }
              printf("\n" );
              temp= temp->caverna_successiva;


            //  player->posizione_attuale->caverna_successiva;

      }

      printf("\033[1;33m");
      printf("\t\t\t+---------------+---------------+---------------+");
      printf("\033[0m");
      puts("");
      puts("");
      sleep(3);

}

}//chiudo stamapa cunicolo

static void chiudi_cunicolo() {
    chiusura=no;
    if (numcaverne+controllo_cav<10) {
      printf("\t\t\tNON PUOI CHIUDERE IL CUNICOLO NON CI SONO 10 CAVERNE\n" );
    }
    else if (chiusura==si){
      printf("\033[1;36m");
      printf("\t\t\tIL CUNICOLO E' STATA CREATO CORRETTAMENTE \n" );
      printf("\033[0m");
    }
    else if (chiusura==no){
        //se tutte le condizioni sono rispettate,il percorso viene chiuso correttamente ed il lucchetto diventa closed
                printf("\t\t\tIL CUNICOLO E' STATO CHIUS0 CORRETTAMENTE!\n");
                sleep(1);
                chiusura = si;
                printf("\t\t\tADESSO PUOI INIZIARE A GIOCARE! ...\n");
                sleep(1);
            }

}


static void scontro_scavatrici(){

//  printf("\033[1;32m");
//  printf("NON SI MOLLA CONTINUA A COMBATTERE\n" );
  int vincitore;
  int pos_scontro=num_turni * 3;// num turni va definito in turno arvais e turno hartornen
  time_t t;
  srand((unsigned) time(&t));
  int possibilita= (rand()%100);

     printf("\033[1;36m");


  if(possibilita<=pos_scontro) {
     printf("CI SARA UNO SCONTRO TRA LE SCVATRICI VEDREMO LA FORTUNA DOVE GIRERA'!!!!!\n" );
     sleep(3);
     if (arvais.serbatoio_raccolta[melassa_attiva]>hartornen.serbatoio_raccolta[melassa_attiva]) {
       printf("DOPO UNA LUNGA BATTAGLIA IN CUI LE DUE  FAMIGLIE HANNO USATO LA MELASSA PER EFFETTUARE MOSSE SPECIALI\n" );
       printf(" E CERVARE DI ANNIENTARE L'AVVERSARIO HANNO VINTO GLI ARVAIS PERCHE HANNO PIU MELASSA RISPETTO AGLI HARTORNEN\n" );
       sleep(3);
       arvais.vittoria=1;
     }

     else if (arvais.serbatoio_raccolta[melassa_attiva]<hartornen.serbatoio_raccolta[melassa_attiva]) {
       printf("DOPO UNA LUNGA BATTAGLIA IN CUI LE DUE  FAMIGLIE HANNO USATO LA MELASSA PER EFFETTUARE MOSSE SPECIALI\n" );
       printf(" E CERVARE DI ANNIENTARE L'AVVERSARIO HANNO VINTO GLI ARVAIS PERCHE HANNO PIU MELASSA RISPETTO AGLI HARTORNEN\n" );
       sleep(3);
       hartornen.vittoria=1;
     }

     else{
     vincitore=possibilita % 2;
     if (vincitore==0) {
       printf("DOPO UNA LUNGA BATTAGLIA IN CUI LE DUE  FAMIGLIE HANNO USATO LA MELASSA PER EFFETTUARE MOSSE SPECIALI\n" );
       printf(" E CERVARE DI ANNIENTARE L'AVVERSARIO, NONOSTANTE LE DUE FAMIGLIE ABBIANO STESSA MELASSA HANNO VINTO GLI ARVAIS GRAZIE ALLA LORO AUDACIA\n" );
       sleep(3);
       arvais.vittoria=1;
     }
    else {
      printf("DOPO UNA LUNGA BATTAGLIA IN CUI LE DUE  FAMIGLIE HANNO USATO LA MELASSA PER EFFETTUARE MOSSE SPECIALI\n" );
      printf(" E CERVARE DI ANNIENTARE L'AVVERSARIO, NONOSTANTE LE DUE FAMIGLIE ABBIANO STESSA MELASSA HANNO VINTO GLI HARTORNEN GRAZIE ALLA LORO AUDACIA\n" );
      sleep(3);
      hartornen.vittoria=1;
         }
     }
  }

}


static void melas_trov(struct scavatrice* player){

    int scelta_raccol;
  //  short int melassa_raccolta;// deve essere di tipo char controllare
    short int resto;

    switch (player->posizione_attuale->melassa_presente) {

          case nessuna:
                      printf("\t\t\tNON HAI TROVATO NESSUNA MELASSA\n" );

                break;

          case poca:

                  printf("\n\t\t\tHAI TROVATO POCA MELASSA PUOI INCREMENTARE DI 1 L'ENERGIA O LA RACCOLTA DELLA MELASSA\n" );
                  printf("\n\t\t\tPREMMERE 1 PER AUMENTARE LA RACCOLTA DELLA MELASSA       PREMERE 2 PER L'ENERGIA\n" );
                  while (scanf("%d", &scelta_raccol) !=1 || scelta_raccol<1 || scelta_raccol>2){
                  printf("\033[1;36m");
                  printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
                  printf("\033[0m");
                  while (getchar() != '\n');
                }


                if (scelta_raccol==2  && player->serbatoio_raccolta[energia_presente]<4) {
                   player->serbatoio_raccolta[energia_presente]++;
                   printf("\n\t\t\tHAI AUMENTATO L'ENERGIA DI UNO\n");
                }

                if (scelta_raccol==2  && player->serbatoio_raccolta[energia_presente]==4) {
                   player->serbatoio_raccolta[melassa_attiva]++;
                   printf("\n\t\t\tHAI RAGGIUNTO IL LIMITE DI ENERGIA QUINDI VERRA AUMENTATA LA MELASSA\n");
                }
                else if (scelta_raccol==1 ) {
                   player->serbatoio_raccolta[melassa_attiva]++;
                   printf("\n\t\t\tHAI AUMENTATO LA MELASSA DI 1\n");
                }
                break;
           case molta :
        //printf("l'energia o la melassa verranno incrementata di 3\n" );
        //printf("premere 1 per la raccolta 2 per l'energia \n" );
                printf("\n\t\t\tHAI TROVATO POCA MELASSA PUOI INCREMENTARE DI 3 L'ENERGIA O LA RACCOLTA DELLA MELASSA\n" );
                printf("\n\t\t\tPREMMERE 1 PER AUMENTARE LA RACCOLTA DELLA MELASSA       PREMERE 2 PER L'ENERGIA\n" );
                while (scanf("%d", &scelta_raccol) !=1 || scelta_raccol<1 ||  scelta_raccol>2){
                printf("\033[1;36m");
                printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
                printf("\033[0m");
                while (getchar() != '\n');
                }


               if (scelta_raccol==2){
               if (player->serbatoio_raccolta[energia_presente]>1) {

                 resto = (player->serbatoio_raccolta[energia_presente] + 3) % 4;
                 player->serbatoio_raccolta[melassa_attiva]= player->serbatoio_raccolta[melassa_attiva] + resto;
                 player->serbatoio_raccolta[energia_presente]=4;
                 }
              else {
                player->serbatoio_raccolta[energia_presente]+=3;
                  }
                                 }
               if  (scelta_raccol==1) {
                   player->serbatoio_raccolta[melassa_attiva]+=3;
                }
               break;
               default:

               break;


    }// chiudo switch

}


static void stato_imprevisto(struct scavatrice* player){


  switch (player->posizione_attuale->imprevisto ) {
    case nessun_imprevisto:
                          printf("\t\t\tIN QUESTA CAVERNA NON C'E NESSUN IMPREVISTO\n" );
                          break;
    case crollo:
                          printf("\t\t\tIN QUESTA CAVERNA C'E' STATO UN CROLLO\n" );
                          player->serbatoio_raccolta[energia_presente]--;
                          break;
    case baco:
                          printf("\t\t\tWTF!!!!!!!!!! E' ARRIVATO UN BACO MOSTROSO E TI HA PROSCIUGATO LA MELASSA E L'ENERGIA\n" );
                          player->serbatoio_raccolta[energia_presente]=0;
                          player->serbatoio_raccolta[melassa_attiva]=0 ;
                          break;
  }
}


static void stato_caverna(struct scavatrice* player){

  switch (player->posizione_attuale->tipologia_caverna ) {
    case normale:
                          printf("\t\t\tLA CAVERNA E' DI TIPO NORMALE QUINDI NON CI SARANNO INCREMENTI E NENACHE DECREMENTI \n" );
                          break;
    case speciale:
                          printf("\t\t\tLA CAVERNA E' DI TIPO SPECIALE E QUINDI CI SARA' UN AUMENTO DI ENERGIA\n" );
                          if (player->serbatoio_raccolta[energia_presente]<4) {
                              player->serbatoio_raccolta[energia_presente]++;
                          }
                          else if (player->serbatoio_raccolta[melassa_attiva]<10) {
                              printf("\t\t\tATTENZIONE IL SERBATOIO DELL'ENERGIA E' PIENO QUINDI VERRA' INCREMENTATA LA MELASSA\n" );
                              player->serbatoio_raccolta[melassa_attiva]++;
                          }
                          else{
                              printf("\t\t\tATTENZIONE IL SERBATOIO DELL'ENERGIA E DELLA MELASSA SONO PIENI QUINDI NON VERRANNO INCREMENTATI\n" );
                          }

                          break;
    case accidentata:
                          printf("\t\t\tOPS! LA CAVERNA E' DI TIPO ACCIDENTATA E QUINDI CI SARA' UNA DIMINUZIONE DI ENERGIA\n" );
                          player->serbatoio_raccolta[energia_presente]--;
                          break;
    case uscita:
                          printf("\t\t\tSI VEDE UNA LUCE! EVVIVA SEI RIUSCITO A TROVARE L'USCITA!\n" );
                        //  player->serbatoio_raccolta[energia_presente]--;

                          break;
  }


}


static enum Tipo_imprevisto avanza_imprevisto(int probabilita_imprev){//probilita avanza

        if (probabilita_imprev<=25) {
          return crollo;
        }

        else if (probabilita_imprev>85) {
          return baco;
        }
        else {
          return nessun_imprevisto;
        }

}


static void avanza(struct scavatrice *player){

       int probabilita_imprev=0;
       time_t t;
       srand((unsigned) time(&t));
       player->serbatoio_raccolta[energia_presente]--;
       probabilita_imprev= 1 + (rand() % 100);
       player->posizione_attuale->imprevisto= avanza_imprevisto(probabilita_imprev);




}


static void aggira(struct scavatrice *player){
      int probabilita_melassa = 0;
      int probabilita_imprev=0;

      printf("\t\t\tVERRA AGGIRATA LA CAVERNA CROLLATA\n");
      struct caverna* caverna_aggira = malloc (sizeof(struct caverna));
      caverna_aggira = player->posizione_attuale;//->caverna_successiva;
      probabilita_melassa= 1 + (rand() % 100);
      probabilita_imprev= 1 + (rand() % 100);
      caverna_aggira->tipologia_caverna = normale;
      caverna_aggira->melassa_presente = p_melassa( probabilita_melassa);
      player->posizione_attuale->imprevisto= avanza_imprevisto(probabilita_imprev);
      player->serbatoio_raccolta[energia_presente]--;
      printf("\t\t\tCAVERNA AGGIRATA CORRETTAMENTE\n");

}


static void reset_abbatti(  struct scavatrice *player){

  printf("\n\t\t\tSTIAMO PER ABBATTERE MANCA POCO PREPARATI!\n" );
  struct caverna *posizionecoda=NULL;
  posizionecoda = player->posizione_attuale;
  int sceltatt,sceltaa;


  if (player->posizione_attuale->caverna_successiva==NULL) {
   printf("\n\t\t\tNON PUOI ANNATTERE LA CAVERNA DOVE SEI\n");
                                                   }
  else{
//    do {

            while (posizionecoda->caverna_successiva != NULL){
            player-> ultima_caverna = posizionecoda;
            posizionecoda = posizionecoda->caverna_successiva;

            free(posizionecoda);
            player->ultima_caverna->caverna_successiva=NULL;
}
//  }while (player->posizione_attuale->caverna_successiva!=NULL);

    printf("\n\t\t\tMISSION IMPOSSIBILE COMPLETATA\n" );
  }
         printf("\n\t\t\tVUOI VEDERE IL CUNICOLO SE SI PREMERE 1 PER STAMPARLO ALTRIMENTI PREMI 2 PER CONTINUARE\n" );
         while (scanf("%d", &sceltatt)!= 1 || sceltatt<1 || sceltatt >2 ) {
         printf("\033[1;31m");
         printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
         printf("\033[0m");
         while (getchar() != '\n');
         }
    if (sceltatt==1) {
         printf("\n\t\t\tPER STAMPARE IL CUNICOLO C'È BISOGNO DI SAPERE CHI STA GIOCANDO \n" );
         printf("\t\t\tPREMERE 1 SE STANNO GIOCANDO GLI ARVAIS       PREMERE 2 SE STANNO GIOVANDO GLI HARTORNEN \n" );
         while (scanf("%d", &sceltaa)!= 1 || sceltaa<1 || sceltaa>2 ) {
         printf("\033[1;31m");
         printf("\n\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
         printf("\033[0m");
         while (getchar() != '\n');
    }
    if (sceltaa==1) {
         printf("\t\t\tECCO IL CUNICOLO DEGLI ARVAIS \n" );
         stampa_cunicolo(&arvais);
    }
    else{
         printf("\t\t\tECCO IL CUNICOLO DEGLI HARTORNEN \n" );
         stampa_cunicolo(&hartornen);
    }
}

}


static enum Quantita_melassa p_melassa_abbatti(int probabilita_melassa_abbatti){

           if (probabilita_melassa_abbatti<=40) {
              return nessuna;
           }
           else if (probabilita_melassa_abbatti>40 &&probabilita_melassa_abbatti<=80 ) {
             return poca;
           }
           else {
             return molta;
            }
}


static enum Tipo_imprevisto p_imprevisto_abbatti( int probabilita_imprevisto_abbatti){

           if (probabilita_imprevisto_abbatti<=40) {
              return nessun_imprevisto;
           }
           else if (probabilita_imprevisto_abbatti>40 &&probabilita_imprevisto_abbatti<=80 ) {
             return crollo;
           }
           else {
             return baco;
            }
}


static enum Tipo_caverna p_tipologia( int probabilita_tipologia_abbatti){

      int a=100;
      int esco=0;
      int b=0;
      int uscita_cav= 0;



        esco = 10*num_abbatti_a;//30
        b = ((a-esco)-20)/2;//25
        uscita_cav = 100-esco;//70


         if (probabilita_tipologia_abbatti<b) {
        return   arvais.posizione_attuale->tipologia_caverna=  normale;
         }
         else if (probabilita_tipologia_abbatti>=b && probabilita_tipologia_abbatti<(2*b)) {//50
        return   arvais.posizione_attuale->tipologia_caverna=  speciale;
         }
         else if (probabilita_tipologia_abbatti>uscita_cav) {
        return   arvais.posizione_attuale->tipologia_caverna= uscita;
         }
         else{
          return arvais.posizione_attuale->tipologia_caverna= accidentata;
         }

          esco=0;
          b=0;
          uscita_cav= 0;


         esco = 10*num_abbatti_h;//30
         b = ((a-esco)-20)/2;//25
         uscita_cav = 100-esco;//70


          if (probabilita_tipologia_abbatti<b) {
          return   hartornen.posizione_attuale->tipologia_caverna= normale;
          }
          else if (probabilita_tipologia_abbatti>=b && probabilita_tipologia_abbatti<(2*b)) {//50
          return   hartornen.posizione_attuale->tipologia_caverna= speciale;
          }
          else if (probabilita_tipologia_abbatti>uscita_cav) {
          return   hartornen.posizione_attuale->tipologia_caverna= uscita;
          }
          else{
          return   hartornen.posizione_attuale->tipologia_caverna= accidentata;
          }







}


static void abbatti(struct scavatrice* player){


  time_t t;
  srand((unsigned) time(&t));
  int probabilita_tipologia_abbatti = 0;
  int probabilita_melassa_abbatti = 0;
  int probabilita_imprevisto_abbatti = 0;
  //struct caverna *caverna_abbatti=NULL;
//  caverna_abbatti = (struct caverna*) malloc (sizeof(struct caverna));
  struct caverna *caverna_abbatti =  malloc (sizeof(struct caverna));
//  caverna_abbatti->caverna_successiva = NULL;// qui non serve
  player->serbatoio_raccolta[energia_presente]-- ;



  printf("\033[1;33m");
  printf("\n\n\t\t\tINSERISCI LA DIREZIONE DELLA CAVERNA CHE STA PER ABBATTERE\n");
  printf("\t\t\t 1 PER SINISTRA          2 PER AVANTI             3 PER DESTRA\n");
  while (scanf("%hu", &direzione)!= 1 || direzione<1 || direzione >3 ) {
  printf("\033[1;31m");
  printf("\n\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
  printf("\033[0m");
  while (getchar() != '\n');
  }
  switch (direzione) {
    case 1:
           printf("\t\t\tLA DIREZIONE DELLA CAVERNA E' A SINISTRA\n" );
           //caverna_abbatti->sinistra;
           caverna_abbatti->direzione_caverna=direzione_sinistra;
           break;

    case 2:
           printf("\t\t\tLA DIREZIONE DELLA CAVERNA E' AD AVANTI\n" );
           caverna_abbatti->direzione_caverna=direzione_avanti;
           break;

    case 3:
           printf("\t\t\tLA DIREZIONE DELLA CAVERNA E' A DESTRA\n");
           caverna_abbatti->direzione_caverna=direzione_destra;
           break;

   default:
           printf("\t\t\tHAI SBAGLIATO A PREMERE RIPROVA\n");

         break;
             }

             probabilita_melassa_abbatti= 1 + (rand() % 100);
             probabilita_imprevisto_abbatti= 1 + (rand() % 100);
             probabilita_tipologia_abbatti= 1 + (rand() % 100);
             caverna_abbatti->tipologia_caverna = p_tipologia( probabilita_tipologia_abbatti);
             //caverna_abbatti->tipologia_caverna = p_melassa_abbatti( probabilita_melassa_abbatti);
             caverna_abbatti->melassa_presente = p_melassa_abbatti( probabilita_melassa_abbatti);
             caverna_abbatti->imprevisto = p_imprevisto_abbatti( probabilita_imprevisto_abbatti);
             //caverna_abbatti=player->posizione_attuale->caverna_successiva;

             caverna_abbatti->caverna_successiva= NULL;

   printf("\033[0m");
      }


static void turnoarvais(){

       num_turni++;
       int scelta=0;
  //system("clear");


  printf("\033[1;33m");
  printf("\t\t\t+-------------+------------+----------------+---------------+---------------+\n");
  printf("\t\t\t| FAMIGLIA    |  POSIZIONE |  TIPO CAVERNA  |     ENERGIA   |   MELASSA     |\n");
  printf("\t\t\t+-------------+------------+----------------+---------------+---------------+\n");
  printf("\t\t\t| ARVAIS      |");

    printf("CAVERNA N° %hu|", ordinalita_arvais);

switch (arvais.posizione_attuale->tipologia_caverna) {
   case normale:
                printf("    NORMALE     |");
                break;
  case speciale:
                printf("    SPECIALE    |");
                break;
  case accidentata:
                printf("  ACCIDENTATA   |");
                break;
  case uscita:
                printf("    USCITA      |");
                 break;

}

    printf("   %d UNITA     |",arvais.serbatoio_raccolta[energia_presente]);

  if(arvais.serbatoio_raccolta[melassa_attiva]>9){
    printf("   %d UNITA    |\n",arvais.serbatoio_raccolta[melassa_attiva]);
}
  else{
    printf(" %d UNITA       |\n",arvais.serbatoio_raccolta[melassa_attiva]);
}

  printf("\t\t\t+-------------+------------+----------------+---------------+---------------+\n");



printf("\t\t\tLE CARATTERISTICHE DELLA CAVERNA SONO LE SEGUENTI\n\n\n" );
stato_imprevisto(&arvais);
printf("\n" );
melas_trov(&arvais);
printf("\n" );
stato_caverna(&arvais);
printf("\n" );





if (arvais.serbatoio_raccolta[energia_presente]<=0   ) {
   printf("\t\t\tNON HAI PIU ENERGIA E QUINDI HAI PERSO\n" );
   sleep(3);
   hartornen.vittoria=1;
   //termina_gioco();
  // reset();
 }

else{

   if (arvais.posizione_attuale->tipologia_caverna == uscita) {
    printf("\t\t\tCE L'HAI FATTA PREMERE 1 PER AVVIARTI VERSO L'USCITA, MA PER USCIRE DOVRAI ATTRAVERSATE UNA CAVERNA. BUONA FORTUNA!! \n" );
    while (scanf("%d", &scelta)!= 1 || scelta <1 || scelta>1) {
    printf("\033[1;31m");
    printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
    printf("\033[0m");
    while (getchar() != '\n');
          }
    arvais.vittoria=1;
    printf("\033[1;31m");
    if (arvais.vittoria==1) {
       printf("\n\t\t\tHANNO VINTO GLI ARVAIS PERCHE HANNO TROVATO L'USCITA E QUINDI GLI HARTORNEN HANNO PERSO!\n" );
       sleep(3);
      // termina_gioco();
      // reset();
     }
    else if (hartornen.vittoria==1) {
       printf("\n\t\t\tHANNO VINTO GLI HARTORNEN PERCHE HANNO TROVATO L'USCITA E QUINDI GLI ARVAIS HANNO PERSO\n");
       sleep(3);
    //   termina_gioco();
      // reset();
     }

  }
    else if (arvais.posizione_attuale->caverna_successiva != NULL && arvais.posizione_attuale->imprevisto != crollo && arvais.posizione_attuale->tipologia_caverna != uscita) {
       printf("\n\t\t\tPUOI FARE DUE COSE: PREMERE 1 PER AVANZARE    2 PER ABBATTERE UNA CAVERNA\n" );
       while (scanf("%d", &scelta)!= 1 || scelta<1 || scelta >2 ) {
         printf("\033[1;31m");
         printf("\n\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
         printf("\033[0m");
         while (getchar() != '\n');
         }

      switch (scelta) {
        case 1:
              avanza(&arvais);
              ordinalita_arvais++;
              break;
       case 2:

              reset_abbatti(&arvais);
              printf("\t\t\tSTIAMO PER ABBATTERE \n" );
              sleep(1);
              abbatti(&arvais);

              num_abbatti_a++;
              break;
      }


    }
    else  if (arvais.posizione_attuale->imprevisto == crollo ) {
          printf("\t\t\tC'E' STATO UN CROLLO QUINDI DEVI AGGIRARE PREMERE 1 PER FARLO\n" );
          while (scanf("%d", &scelta)!= 1 || scelta <1 || scelta>1) {
          printf("\033[1;31m");
          printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
          printf("\033[0m");
          while (getchar() != '\n');
           }
          aggira(&arvais);
          ordinalita_arvais++;
      }
      else if (arvais.posizione_attuale->caverna_successiva == NULL) {
         printf("\t\t\tNON CI SONO CAVERNE DISPONIBILI QUINDI DEVI ABBATERE\n" );
         printf("\t\t\tPREMERE 1 PER FARLO\n" );
         while (scanf("%d", &scelta)!= 1 || scelta <1 || scelta>1 ) {
         printf("\033[1;31m");
         printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
         printf("\033[0m");
         while (getchar() != '\n');
          }

         //reset_abbatti(&arvais);
         abbatti(&arvais);

         num_abbatti_a++;
       }





}// fine mega eelse
}// fine turno arvais

static void turnohartornen(){


         num_turni++;
         int scelta=0;
  //  system("clear") ;


    printf("\033[1;33m");
    printf("\t\t\t+-------------+------------+----------------+---------------+---------------+\n");
    printf("\t\t\t| FAMIGLIA    |  POSIZIONE |  TIPO CAVERNA  |     ENERGIA   |   MELASSA     |\n");
    printf("\t\t\t+-------------+------------+----------------+---------------+---------------+\n");
    printf("\t\t\t| HARTORNEN   |");

      printf(" CAVERNA N°%hu|", ordinalita_hartornen);

  switch (hartornen.posizione_attuale->tipologia_caverna) {
    case normale:
                  printf("    NORMALE     |");
                  break;
    case speciale:
                  printf("    SPECIALE    |");
                  break;
   case accidentata:
                  printf("  ACCIDENTATA   |");
                  break;
   case uscita:
                  printf("    USCITA      |");
                   break;

  }
    printf(" %d   UNITA'    |",hartornen.serbatoio_raccolta[energia_presente]);

    if(hartornen.serbatoio_raccolta[melassa_attiva]>9){
      printf(" %d  UNITA'    |\n",hartornen.serbatoio_raccolta[melassa_attiva]);
  }
  else{
      printf(" %d  UNITA'     |\n",hartornen.serbatoio_raccolta[melassa_attiva]);
  }

  printf("\t\t\t+-------------+------------+----------------+---------------+---------------+\n");




  printf("\n\n\t\t\tLE CARATTERISTICHE DELLA CAVERNA SONO LE SEGUENTI\n\n\n" );
  stato_imprevisto(&hartornen);
  printf("\n" );
  melas_trov(&hartornen);
  printf("\n" );
  stato_caverna(&hartornen);
  printf("\n" );





  if (hartornen.serbatoio_raccolta[energia_presente]<=0   ) {
     printf("\t\t\tNON HAI PIU ENERGIA E QUINDI HAI PERSO\n" );
     sleep(3);
     arvais.vittoria=1;
    // termina_gioco();
     //reset();
   }

  else{
     if (hartornen.posizione_attuale->tipologia_caverna == uscita) {
      printf("\t\t\tCE L'HAI FATTA PREMERE 1 PER AVVIARTI VERSO L'USCITA, MA PER USCIRE DOVRAI ATTRAVERSATE UNA CAVERNA. BUONA FORTUNA!! \n" );
      while (scanf("%d", &scelta)!= 1 || scelta<1 || scelta >1 ) {
      printf("\033[1;31m");
      printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
      printf("\033[0m");
      while (getchar() != '\n');
            }
      hartornen.vittoria=1;
      printf("\033[1;31m");
      if (arvais.vittoria==1) {
         printf("\n\t\t\tHANNO VINTO GLI ARVAIS PERCHE HANNO TROVATO L'USCITA E QUINDI GLI HARTORNEN HANNO PERSO!\n" );
         sleep(3);
        // termina_gioco();
         //reset();
       }
      else if (hartornen.vittoria==1) {
         printf("\n\t\t\tHANNO VINTO GLI HARTORNEN PERCHE HANNO TROVATO L'USCITA E QUINDI GLI ARVAIS HANNO PERSO\n");
         sleep(3);
         //termina_gioco();
         //reset();
       }
    }
      else if (hartornen.posizione_attuale->caverna_successiva != NULL && hartornen.posizione_attuale->imprevisto != crollo && hartornen.posizione_attuale->tipologia_caverna != uscita) {
         printf("\n\t\t\tPUOI FARE DUE COSE: PREMERE 1 PER AVANZARE    2 PER ABBATTERE UNA CAVERNA\n" );
         while (scanf("%d", &scelta)!= 1 || scelta<1 || scelta >2 ) {
           printf("\033[1;31m");
           printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
           printf("\033[0m");
           while (getchar() != '\n');
           }

        switch (scelta) {
          case 1:
                avanza(&hartornen);
                ordinalita_hartornen++;
                break;
         case 2:

                reset_abbatti(&hartornen);
                abbatti(&hartornen);

                num_abbatti_h++;
                break;
        }


      }
      else  if (hartornen.posizione_attuale->imprevisto == crollo ) {
            printf("\t\t\tC'E' STATO UN CROLLO QUINDI DEVI AGGIRARE PREMERE 1 PER FARLO\n" );
            while (scanf("%d", &scelta)!= 1 ) {
            printf("\033[1;31m");
            printf("\n\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
            printf("\033[0m");
            while (getchar() != '\n');
             }
            aggira(&hartornen);
            ordinalita_hartornen++;
        }
        else if (hartornen.posizione_attuale->caverna_successiva == NULL) {
           printf("\t\t\tNON CI SONO CAVERNE DISPONIBILI QUINDI DEVI ABBATERE\n" );
           printf("\t\t\tPREMERE 1 PER FARLO\n" );
           while (scanf("%d", &scelta)!= 1 || scelta<1 || scelta>1) {
           printf("\033[1;31m");
           printf("\n\t\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
           printf("\033[0m");
           while (getchar() != '\n');
            }
          // reset_abbatti(&hartornen);
           abbatti(&hartornen);
           num_abbatti_h++;
         }





  }// fine mega eelse


}

//inizio ad liberare la memoria
void termina_gioco(){


       //struct scavatrice *sinistra;


       while (arvais.prima_caverna!=NULL) {

       struct caverna  *posizione = arvais.prima_caverna;

       if(posizione->caverna_successiva== NULL){
         free(arvais.prima_caverna);
           arvais.prima_caverna=NULL;
         }
      else{
           while (posizione->caverna_successiva != NULL){
           free(posizione->caverna_successiva);
           posizione->caverna_successiva=NULL;
        }
      }



    /*   if(arvais.prima_caverna->avanti == NULL && arvais.prima_caverna->destra == NULL && arvais.prima_caverna->sinistra == NULL){
       free(arvais.prima_caverna);
         arvais.prima_caverna=NULL;
                                                                                                                                                       }
      // verifico con tre if se i puntatori avanti destra e sinistra sono vuoti quindi se la memoria è stata liberata
       else{
             struct caverna  *posizione = arvais.prima_caverna;
             while (posizione->caverna_successiva->caverna_successiva != NULL) {
             if (destra!=NULL) {
                 free(destra);
                                 }
                 else{
                 if (sinistra!=NULL) {
                 free(sinistra);
                                     }

                 else{  free(avanti) ;
                   }
                   }

                   }

                   }

*/
                 }

                 while (hartornen.prima_caverna!=NULL) {

                /* if(hartornen.prima_caverna->avanti == NULL && hartornen.prima_caverna->destra == NULL && hartornen.prima_caverna->sinistra == NULL){
                 free(hartornen.prima_caverna);
                   hartornen.prima_caverna=NULL;
                                                                                                                                                                 }
                // verifico con tre if se i puntatori avanti destra e sinistra sono vuoti quindi se la memoria è stata liberata
                 else{
                       struct caverna  *posizione = hartornen.prima_caverna;
                       while (posizione->caverna_successiva->caverna_successiva != NULL) {
                       if (destra!=NULL) {
                           free(destra);
                                           }
                           else{
                           if (sinistra!=NULL) {
                           free(sinistra);
                                               }

                           else{  free(avanti) ;
                             }
                             }

                             }

                             }

*/





       struct caverna  *posizionee = hartornen.prima_caverna;

       if(posizionee->caverna_successiva== NULL){
         free(arvais.prima_caverna);
           hartornen.prima_caverna=NULL;
         }
      else{
           while (posizionee->caverna_successiva != NULL){
           free(posizionee->caverna_successiva);
           posizionee->caverna_successiva=NULL;
        }
      }

                             }

  }//qui finisce la funzione termina gioco

void gioca(){

        int inizio=0;
        time_t t;
        srand((unsigned) time(&t));
        if(arvais.prima_caverna==NULL  ||  hartornen.prima_caverna==NULL){
        printf("\033[1;31m");
        printf("\n\t\t\t  C'E' MANCANZA DI CUNICOLO !\n");
        sleep(1);
        printf("\033[0m");

        }
        else{
        inizio=1 + (rand() % 100);
        do{


        if (inizio<=50){




            if (arvais.vittoria==0 && hartornen.vittoria==0) {
              printf("\033[1;31m");
              printf("\t\t\t\t\t\t\t\tINIZIANO IL TURNO GLI ARVAIS \n" );
              printf("\033[0m");
              sleep(2);

              puts("");
              printf("\n" );
              printf("\t3.....\n" );
              sleep(2);
              printf("\t\t2.....\n" );
              sleep(2);
              printf("\t\t\t1....." );
              sleep(2);
              printf("\033[1;32m");
              printf("\t\t\t\tINIZIA IL GIRO \n" );
              printf("\033[0m");
              sleep(1);
              turnoarvais();

              printf("\033[1;32m");
              printf("\nTURNO ARVAIS COMPLETATO!\n");
              printf("\033[0m");
              puts("");
              system("clear");


              if (arvais.vittoria==0 && hartornen.vittoria==0){
              scontro_scavatrici();
              }

              if (arvais.vittoria==0 && hartornen.vittoria==0){
              turnohartornen();

              printf("\033[1;32m");
              printf("\nTURNO HARTORNEN COMPLETATO!\n");
              printf("\033[0m");
              system("clear");
              }
              if (arvais.vittoria==0 && hartornen.vittoria==0){
              scontro_scavatrici();
              }
              if (arvais.vittoria==1 && hartornen.vittoria==0) {
                printf("\033[1;31m");
                printf("\n\nCOMPLIMENTI,ARVAIS AVETE VINTO!\n");
                printf("\033[0m");
                printf("\n\n");
                termina_gioco();
                reset();
                break;
              }
              else if (arvais.vittoria==0 && hartornen.vittoria==1) {
                printf("\033[1;31m");
                printf("\n\nCOMPLIMENTI, HARTORNEN AVETE VINTO!\n");
                printf("\033[0m");
                printf("\n\n");
                termina_gioco();
                reset();
                break;
              }



            }
          }
          else{

            printf("\033[1;31m");

            printf("\033[0m");
            sleep(2);



              if (arvais.vittoria==0 && hartornen.vittoria==0) {

               puts("");
               printf("\n" );
               printf("\t3.....\n" );
               sleep(1);
               printf("\t\t2.....\n" );
               sleep(1);
               printf("\t\t\t1....." );
               sleep(1);
               printf("\033[1;32m");
               printf("\t\t\t\t\t\tINIZIA IL GIRO \n" );
               printf("\033[0m");
               sleep(1);
               printf("\t\t\t\t\t\t\t\tINIZIANO IL TURNO GLI HARTORNEN \n" );
                turnohartornen();

                printf("\033[1;32m");
                printf("\nTURNO HARTORNEN COMPLETATO!\n");
                printf("\033[0m");
                puts("");
                system("clear");

                if (arvais.vittoria==0 && hartornen.vittoria==0){
                scontro_scavatrici();
                }
                if (arvais.vittoria==0 && hartornen.vittoria==0){
                turnoarvais();

                printf("\033[1;32m");
                printf("\n\t\t\tTURNO HARVAIS COMPLETATO!\n\n");
                printf("\033[0m");
                system("clear");
                }
                if (arvais.vittoria==0 && hartornen.vittoria==0){
                scontro_scavatrici();
                }
              //  scontro_scavatrici();

              if (arvais.vittoria==1 && hartornen.vittoria==0) {
               printf("\033[1;31m");
               printf("\n\n\t\t\tCOMPLIMENTI,ARVAIS AVETE VINTO!\n");
               printf("\033[0m");
               termina_gioco();
               reset();
               break;
             }
             else if (arvais.vittoria==0 && hartornen.vittoria==1) {
               printf("\033[1;31m");
               printf("\n\n\t\t\tCOMPLIMENTI, HARTORNEN AVETE VINTO!\n");
               printf("\033[0m");
               termina_gioco();
               reset();
               break;
             }
           }
          }

}while (1);// CHIUDO DO
}//else
}
