/**************************************************************************/
/*                                                                        */
/* P1 - UEB amb sockets TCP/IP - Part I                                   */
/* Fitxer capçalera de aUEBc.c                                            */
/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Declaració de funcions EXTERNES de aUEBc.c, és a dir, d'aquelles       */
/* funcions que es faran servir en un altre fitxer extern a aUEBc.c,      */
/* p.e., int UEBc_FuncioExterna(arg1, arg2...) { }                        */
/* El fitxer extern farà un #include del fitxer aUEBc.h a l'inici, i      */
/* així les funcions seran conegudes en ell.                              */
/* En termes de capes de l'aplicació, aquest conjunt de funcions          */
/* EXTERNES formen la interfície de la capa UEB, en la part client.       */
 
int UEBc_ObteFitxer(const char *IPser, int portTCPser, const char *NomFitx, char *Resp, int *LongResp);
int UEBc_HaArribatAlgunaCosa(const int *LlistaSck, int LongLlistaSck);
char* UEBc_ObteMissError(void);
/* int UEBc_FuncioExterna(arg1, arg2...);                                 */


