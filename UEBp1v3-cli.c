/**************************************************************************/
/*                                                                        */
/* P1 - UEB amb sockets TCP/IP - Part I                                   */
/* Fitxer cli.c que implementa el client de UEB sobre la capa de          */
/* transport TCP (fent crides a la "nova" interfície de la capa de        */
/* transport o "nova" interfície de sockets).                             */
/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <stdio.h> o #include "meu.h"     */

#include "UEBp1v2-tTCP.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int main(int argc,char *argv[])
{
	 /* Declaració de variables, p.e., int n;                                 */
	 int scon;
	 char buffer[200];
	 char iprem[16];
	 char iploc[16];
	 int portrem, portloc;
	 int bytes_llegits, bytes_escrits;
	 /* Expressions, estructures de control, crides a funcions, etc.          */
	 if((scon=TCP_CreaSockClient("0.0.0.0",0))==-1)
	 {
	   perror("Error en socket");
	   exit(-1);
	 }
	 //Llegeix @IP del servidor
	 printf("@IP (servidor): ");
	 scanf("%s",iprem);
	 //Llegeix #Port del servidor
	 printf("#Port (servidor): ");
	 scanf("%d", &portrem);
	 if(TCP_DemanaConnexio(scon,iprem,portrem) == -1){
		  perror("Error en connect");
		  close(scon);
		  exit(-1);
     }
	 if((TCP_TrobaAdrSockLoc(scon,iploc,&portloc)) == -1){
        perror("Error en getsockname");
		  close(scon);
		  exit(-1);
	 }
    if((TCP_TrobaAdrSockRem(scon,iprem,&portrem)) == -1){
        perror("Error en getpeername");
		  close(scon);
		  exit(-1);
    }
    printf("Socket local : @IP: %s, #Port: %d \n",iploc,portloc);
    printf("Socket remot : @IP: %s, #Port: %d \n",iprem,portrem);
	 do{
		 if((bytes_llegits=read(0,buffer,sizeof(buffer)))==-1)
		{
			 perror("Error en read");
			 close(scon);
			 exit(-1);
		}
		if((bytes_escrits=TCP_Envia(scon,buffer,bytes_llegits))==-1)
		{
			 perror("Error en write");
			 close(scon);
			 exit(-1);
		}
		printf("Bytes enviats %d\n", bytes_escrits);
	 } while(buffer[0] != '\n');
	 if(TCP_TancaSock(scon)==-1){
	   perror("Error en close");
	   exit(-1);
	 }
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{
	
} */
