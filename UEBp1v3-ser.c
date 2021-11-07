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
    struct dades {
		char *ip;
		int port;
		char *nomFitxer;
	};
	struct dades client, servidor;
 /* Expressions, estructures de control, crides a funcions, etc.          */
    FILE * f = fopen("ser.cfg","r");
	if(fopen == NULL){
		perror("Fitxer de configuracio no trobat");
		exit(-1);
	}
    fscanf(f,"%s %d",buffer,&portloc);	
	if((UEBs_IniciaServ(&sesc,portloc)) == -1){
	   perror("Error en inicia servidor");
	   close(sesc);
	   exit(-1);
    }
    printf("S'ha iniciat servidor amb #Port: %d\n",portloc);
    while(){
	  int res = UEBs_ServeixPeticio(sesc);
	  if(res == -1){
	    perror("Resposta erronia");
	    exit(-1);
	  }
	  else if(res == -2){
	    perror("Error en la interfície de sockets");
	    exit(-1);
	  }
	  else if(res == -3){
	    perror("Client ha tancat la connexio");
	    exit(-1);
	  } 
    }
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{
	
} */

