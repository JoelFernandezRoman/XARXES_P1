/**************************************************************************/
/*                                                                        */
/* P1 - UEB amb sockets TCP/IP - Part I                                   */
/* Fitxer ser.c que implementa la interfície aplicació-administrador      */
/* d'un servidor de l'aplicació de UEB, sobre la capa d'aplicació de      */
/* (la part servidora de) UEB (fent crides a la interfície de la part     */
/* servidora de la capa UEB).                                             */

/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <stdio.h> o #include "meu.h"     */

#include "UEBp1v3-aUEBs.h"
#include <stdio.h>
#include <stdlib.h>

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int main(int argc,char *argv[])
{
 /* Declaració de variables, p.e., int n;                                 */
    int sesc;
    int portloc;
    char iprem[16];
    int bytes_llegits, bytes_escrits;
    char buffer[200];
    char arrel[100];
    char nomFitxer[20];
	struct dades client, servidor;
 /* Expressions, estructures de control, crides a funcions, etc.          */
    FILE * f = fopen("ser.cfg","r");
	if(fopen == NULL){
		perror("Fitxer de configuracio no trobat");
		exit(-1);
	}
    fscanf(f,"%s %d %s %s",buffer,&portloc,buffer,arrel);	
	if((UEBs_IniciaServ(&sesc,portloc)) == -1){
	   perror("Error en inicia servidor");
	   close(sesc);
	   exit(-1);
    }
    fclose(f);
    FILE *flog = fopen("ser.log","a");
    printf("S'ha iniciat servidor amb #Port: %d\n",portloc);
    fprintf(flog,"S'ha iniciat servidor amb #Port: %d\n",portloc);
    //*while(1){*/
	  int res = UEBs_ServeixPeticio(sesc,arrel,&client,&servidor,nomFitxer);
	  printf("-----------------------------------------------------------\n");
      fprintf(flog,"-----------------------------------------------------------\n");
	  printf("OBTENIR %s\n",nomFitxer);
	  fprintf(flog,"OBTENIR %s\n",nomFitxer);
	  printf("Socket remot : @IP: %s, #Port: %d \n",client.ip,client.port);
      printf("Socket local : @IP: %s, #Port: %d \n",servidor.ip,servidor.port);
      fprintf(flog,"Socket remot : @IP: %s, #Port: %d \n",client.ip,client.port);
      fprintf(flog,"Socket local : @IP: %s, #Port: %d \n",servidor.ip,servidor.port);
	  if(res == 1){
		printf("Fitxer inexistent\n");
		fprintf(flog,"Fitxer inexistent\n");
	  }	
	  else if(res == -1){
	     printf("Error en interfície de sockets\n");
	     fprintf(flog,"Error en interfície de sockets\n");
	  }
	  else if(res == -2){
	     printf("Error en protocol\n");
	     fprintf(flog,"Error en protocol\n");
	  }
	  else if(res == -3){
	    printf("Client ha tancat la connexio\n");
	    fprintf(flog,"Client ha tancat la connexio\n");
	  } 
	  else {
        printf("Fitxer servit correctament\n");		
        fprintf(flog,"Fitxer servit correctament\n");	
      } 	  
    /*}*/
    fclose(flog);
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{
	
} */

