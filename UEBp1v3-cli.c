/**************************************************************************/
/*                                                                        */
/* P1 - UEB amb sockets TCP/IP - Part I                                   */
/* Fitxer cli.c que implementa la interfície aplicació-usuari             */
/* d'un client de l'aplicació de UEB, sobre la capa d'aplicació de        */
/* (la part client de) UEB (fent crides a la interfície de la part        */
/* client de la capa UEB).                                                */
/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <stdio.h> o #include "meu.h"     */

#include "UEBp1v3-aUEBc.h"
#include <stdio.h>
#include <stdlib.h>

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */
void llegirDades(char *ipRem, int *portRem, char *nomFitxer);

int main(int argc,char *argv[])
{
 /* Declaració de variables, p.e., int n;                                 */
	char iprem[16];
	char nomFitxer[200];
	int portrem;
	char fitxer[9999];
	int longFitxer;
	char peticio[20];
	struct dades client, servidor;	
 /* Expressions, estructures de control, crides a funcions, etc.          */
    printf("Que vols fer? [obtenir][finalitzar]\n");
	scanf("%s",peticio);
    while(strcmp(peticio,"finalitzar") != 0){
      llegirDades(iprem,&portrem,nomFitxer);
      printf("\nOBTENIR %s\n",nomFitxer);	
	  int res = UEBc_ObteFitxer(iprem,portrem,nomFitxer,fitxer,&longFitxer,&client,&servidor);
	  printf("Socket local : @IP: %s, #Port: %d \n",client.ip,client.port);
      printf("Socket remot : @IP: %s, #Port: %d \n",servidor.ip,servidor.port);
	  if(res == 1){
		printf("Fitxer inexistent\n");
	  }	  
	  else if(res == -1){
        printf("Error en interfície de sockets\n");
      }
      else if(res == -2){
        printf("Error en protocol\n");
	    		 
	  }
	  else if(res == -3){
	    printf("Servidor ha tancat la connexio\n");
	  }
	  else {
	    printf("Fitxer resultant:\n%s\n",fitxer);
	  }  
	  printf("-----------------------------------------------------------\n");
	  printf("Que vols fer? [obtenir][finalitzar]\n");
	  scanf("%s",peticio); 
    }
    
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{
	
} */
void llegirDades(char *ipRem, int *portRem, char *nomFitxer){
	//Llegeix @IP del servidor
	 printf("@IP (servidor): ");
	 scanf("%s",ipRem);
	 //Llegeix #Port del servidor
	 printf("#Port (servidor): ");
	 scanf("%d", portRem);
	 //Llegeix nom del fitxer
	 printf("Nom fitxer: ");
	 scanf("%s", nomFitxer);
}
