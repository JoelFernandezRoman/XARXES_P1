/**************************************************************************/
/*                                                                        */
/* P1 - UEB amb sockets TCP/IP - Part I                                   */
/* Fitxer aUEB.c que implementa la capa d'aplicació de UEB, sobre la      */
/* cap de transport TCP (fent crides a la "nova" interfície de la         */
/* capa TCP o "nova" interfície de sockets TCP), en la part servidora.    */
/*                                                                        */
/* Autors: Albert Sastre, Joel Fernandez                                  */
/* Data: 18/11/2021                                                       */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <sys/types.h> o #include "meu.h" */
/*  (si les funcions externes es cridessin entre elles, faria falta fer   */
/*   un #include del propi fitxer capçalera)                              */

#include "UEBp1v3-tTCP.h"
#include "UEBp1v3-aUEBs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

#define LONGTIPUS		3
#define LONGLONG1		4
#define LONGMININFO1	1
#define LONGMAXINFO1	9999
#define LONGMINPUEB		8
#define LONGMAXPUEB		10006

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int ConstiEnvMis(int SckCon, const char *tipus, const char *info1, int long1);
int RepiDesconstMis(int SckCon, char *tipus, char *info1, int *long1);

/* Definició de funcions EXTERNES, és a dir, d'aquelles que es cridaran   */
/* des d'altres fitxers, p.e., int UEBs_FuncioExterna(arg1, arg2...) { }  */
/* En termes de capes de l'aplicació, aquest conjunt de funcions externes */
/* formen la interfície de la capa UEB, en la part servidora.             */

/* Inicia el S UEB que escolta peticions a través d’un nou socket TCP,    */
/* d'identificador "SckEsc", que tindrà una @IP local qualsevol i el      */
/* #port TCP “portTCPser” (és a dir, crea un socket “servidor” o en       */
/* estat d’escolta – listen –).                                           */
/*                                                                        */
/* Retorna 0 si tot va bé,                                                */
/* -1 si hi ha un error en la interfície de sockets.                      */
int UEBs_IniciaServ(int *SckEsc, int portTCPser)
{
	if((*SckEsc = TCP_CreaSockServidor("0.0.0.0",portTCPser))== -1){
		return -1;
	}
    return 0;
}

/* A través del socket d'escolta TCP d'identificador "SckEsc", rep una    */
/* petició UEB i la respon.                                               */
/*                                                                        */
/* Retorna 0 si tot va bé i la resposta és CORrecte,                      */
/*  1 si tot va bé i la resposta és ERRònia (p.e., fitxer no existeix),   */
/* -1 si hi ha un error en la interfície de sockets,                      */
/* -2 si protocol és incorrecte (tipus de petició, mal construït, etc.)   */
/* -3 si l'altra part tanca la connexió.                                  */
int UEBs_ServeixPeticio(int SckEsc,const char * arrel, struct dades * client, struct dades* servidor, char *nomFitxer)
{
	int scon;
	char iprem[16];
	int portrem;
	char tipus[3+1];
	int longitud;
	int fdFitxer;
    if((scon=TCP_AcceptaConnexio(SckEsc,iprem,&portrem))==-1)
	{
	 return -1;
    }
    TCP_TrobaAdrSockLoc(scon,servidor->ip,&(servidor->port));
    TCP_TrobaAdrSockRem(scon,client->ip,&(client->port));
    //Rep OBT per part del client
    int res = RepiDesconstMis(scon,tipus,nomFitxer,&longitud);
    if(res == -1 || res == -2 || res == -3){
	  return res;
	}
	//Obre fitxer
	char dir[50];
	strcpy(dir,arrel);
	strcat(dir,nomFitxer);
    if((fdFitxer = open(dir,O_RDONLY)) == -1){
	   ConstiEnvMis(scon,"ERR","error1",6);
	   TCP_TancaSock(scon);
	   return 1;
	}
	//Llegeix fitxer
	char bufferFitxer[LONGMAXINFO1];
	int bytesLlegitsFitxer = read(fdFitxer,bufferFitxer,LONGMAXINFO1);
	close(fdFitxer);	
	//Enviar fitxer
	ConstiEnvMis(scon,"COR",bufferFitxer,bytesLlegitsFitxer);
	TCP_TancaSock(scon);
	return 0;
}

/* Examina simultàniament i sense límit de temps (una espera indefinida)  */
/* els sockets (poden ser TCP, UDP i  teclat -stdin-) amb identificadors  */
/* en la llista “LlistaSck” (de longitud “LongLlistaSck” sockets) per     */
/* saber si hi ha arribat alguna cosa per ser llegida.                    */
/*                                                                        */
/* "LlistaSck" és un vector d'enters d'una longitud >= LongLlistaSck      */
/*                                                                        */
/* Retorna -1 si hi ha error; si arriba alguna cosa per algun dels        */
/* sockets, retorna l’identificador d’aquest socket.                      */
/*                                                                        */
/* (aquesta funció és equivalent a la funció TCP_HaArribatAlgunaCosa() de */
/* la “nova” interfície de la capa TCP però ara a la capa d’aplicació)    */
int UEBs_HaArribatAlgunaCosa(const int *LlistaSck, int LongLlistaSck)
{
 return TCP_HaArribatAlgunaCosa(LlistaSck, LongLlistaSck);
 /* o return TCP_HaArribatAlgunaCosaEnTemps(LlistaSck, LongLlistaSck, -1);*/
}

/* Obté un missatge de text que descriu l'error produït en la darrera     */
/* crida de sockets TCP (de UEB).                                         */
/*                                                                        */
/* Retorna aquest missatge de text en un "string" de C (vector de chars   */
/* imprimibles acabat en '\0')                                            */
/*                                                                        */
/* (aquesta funció és equivalent a la funció TCP_ObteMissError() de la    */
/* "nova" interfície de la capa TCP però ara a la capa d’aplicació)       */
char* UEBs_ObteMissError(void)
{
 return TCP_ObteMissError();
} 

/* Si ho creieu convenient, feu altres funcions EXTERNES                  */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/* int UEBs_FuncioExterna(arg1, arg2...)
{
	
} */

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es        */
/* troben a l'inici d'aquest fitxer.                                      */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/* int FuncioInterna(arg1, arg2...)
{
	
} */

/* "Construeix" un missatge de PUEB a partir dels seus camps tipus,       */
/* long1 i info1, escrits, respectivament a "tipus", "long1" i "info1"    */
/* (que té una longitud de "long1" bytes), i l'envia a través del         */
/* socket TCP “connectat” d’identificador “SckCon”.                       */
/*                                                                        */
/* "tipus" és un "string" de C (vector de chars imprimibles acabat en     */
/* '\0') d'una longitud de 4 chars (incloent '\0').                       */
/* "info1" és un vector de chars (bytes) qualsevol (recordeu que en C,    */
/* un char és un enter de 8 bits) d'una longitud <= 9999 bytes.           */
/*                                                                        */
/* Retorna 0 si tot va bé,                                                */
/* -1 si hi ha un error en la interfície de sockets,                      */
/* -2 si protocol és incorrecte (tipus de petició, mal construït, etc.)   */
int ConstiEnvMis(int SckCon, const char *tipus, const char *info1, int long1)
{
  if(long1 < LONGMININFO1) return -2;	
  int bytes_escrits;	
  char missatge[LONGMAXPUEB+1];
  memcpy(missatge,tipus,3);
  
  //conversió int a char de quatre digits
  char n[LONGLONG1];
  sprintf(n, "%.4d", long1);
  
  memcpy(missatge+3,n,4);
  memcpy(missatge+7,info1,long1);
  missatge[7+long1] = '\0'; //per poder utilitzar strlen correctament
  if((bytes_escrits=TCP_Envia(SckCon,missatge,strlen(missatge)))==-1)
  {
     return -1;
  }	
  return 0;
}

/* Rep a través del socket TCP “connectat” d’identificador “SckCon” un    */
/* missatge de PUEB i el "desconstrueix", és a dir, obté els seus camps   */
/* tipus, long1 i info1, que escriu, respectivament a "tipus", "long1"    */
/* i "info1" (que té una longitud de "long1" bytes).                      */
/*                                                                        */
/* "tipus" és un "string" de C (vector de chars imprimibles acabat en     */
/* '\0') d'una longitud de 4 chars (incloent '\0').                       */
/* "info1" és un vector de chars (bytes) qualsevol (recordeu que en C,    */
/* un char és un enter de 8 bits) d'una longitud <= 9999 bytes.           */
/*                                                                        */
/* Retorna 0 si tot va bé,                                                */
/* -1 si hi ha un error en la interfície de sockets,                      */
/* -2 si protocol és incorrecte (tipus de petició, mal construït, etc.)   */
/* -3 si l'altra part tanca la connexió.                                  */
int RepiDesconstMis(int SckCon, char *tipus, char *info1, int *long1)
{
	int bytes_llegits;
	char missatge[LONGMAXPUEB];
	char l[LONGLONG1];
	if((bytes_llegits=TCP_Rep(SckCon,missatge,sizeof(missatge)))==-1)
	{
		 return -1;
	}
	if(bytes_llegits < LONGMINPUEB){
		return -2;
	}	
	memcpy(tipus,missatge,3);
	tipus[3] = '\0';
    memcpy(l,missatge+3,4);
	*(long1) = atoi(l);
	memcpy(info1,missatge+7,*(long1));
	info1[*(long1)] = '\0';
	return 0;
}

