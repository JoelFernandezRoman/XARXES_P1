/**************************************************************************/
/*                                                                        */
/* P1 - UEB amb sockets TCP/IP - Part I                                   */
/* Fitxer ser.c que implementa el servidor de UEB sobre la capa de        */
/* transport TCP (fent crides a la "nova" interfície de la capa de        */
/* transport o "nova" interfície de sockets).                             */
/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <stdio.h> o #include "meu.h"     */

#include "UEBp1v2-tTCP.h"
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
    int sesc, scon, i;
    int portloc, portrem;
    char iprem[16];
    char iploc[16];
    int bytes_llegits, bytes_escrits;
    char buffer[200];
 /* Expressions, estructures de control, crides a funcions, etc.          */
    printf("#Port (servidor):");
    scanf("%d", &portloc);
    sesc=TCP_CreaSockServidor("0.0.0.0",portloc);  
    if((scon=TCP_AcceptaConnexio(sesc,iprem,&portrem))==-1)
	 {
	   perror("Error en accept");
	   close(sesc);
	   exit(-1);
    }
    printf("Socket remot : @IP: %s, #Port: %d \n",iprem,portrem);
    printf("Socket local : @IP: %s, #Port: %d \n",iploc,portloc);
    
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
    printf("Socket remot : @IP: %s, #Port: %d \n",iprem,portrem);
    printf("Socket local : @IP: %s, #Port: %d \n",iploc,portloc);
    do{
		if((bytes_llegits=TCP_Rep(scon,buffer,sizeof(buffer)))==-1)
		{
		 perror("Error en read");
		 close(scon);
		 exit(-1);
		}
		printf("Bytes rebuts %d\n", bytes_llegits);
		if((bytes_escrits=write(1,buffer,bytes_llegits))==-1)
		{
		 perror("Error en write");
		 close(scon);
		 exit(-1);
		}
    } while(buffer[0] != '\n');
    if(TCP_TancaSock(scon)==-1){
      exit(-1);
    }if(TCP_TancaSock(sesc)==-1){
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
