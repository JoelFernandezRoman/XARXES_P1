/**************************************************************************/
/*                                                                        */
/* P1 - UEB amb sockets TCP/IP - Part I                                   */
/* Fitxer capçalera de aUEBs.c                                            */
/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Declaració de funcions EXTERNES de aUEBs.c, és a dir, d'aquelles       */
/* funcions que es faran servir en un altre fitxer extern a aUEBs.c,      */
/* p.e., int UEBs_FuncioExterna(arg1, arg2...) { }                        */
/* El fitxer extern farà un #include del fitxer aUEBs.h a l'inici, i      */
/* així les funcions seran conegudes en ell.                              */
/* En termes de capes de l'aplicació, aquest conjunt de funcions          */
/* EXTERNES formen la interfície de la capa UEB, en la part servidora.    */

struct dades {
  char ip[100];
  int port;
};

 
int UEBs_IniciaServ(int *SckEsc, int portTCPser);
int UEBs_ServeixPeticio(int SckEsc, const char *arrel, struct dades *client, struct dades *servidor, char *nomFitxer);
int UEBs_HaArribatAlgunaCosa(const int *LlistaSck, int LongLlistaSck);
char* UEBs_ObteMissError(void);
/* int UEBs_FuncioExterna(arg1, arg2...);                                 */




