#include "Cabecera.h"


int cmpMediciones_ALU(const void* e1, const void* e2)
{
    t_Mediciones* med1 = (t_Mediciones*) e1;
    t_Mediciones* med2 = (t_Mediciones*) e2;

    return med1->dispositivo-med2->dispositivo;
}

int cmpCoeficientes_ALU(const void* e1, const void* e2)
{
    t_Coeficientes* coef1 = (t_Coeficientes*) e1;
    t_Coeficientes* coef2 = (t_Coeficientes*) e2;


    return coef1->disp-coef2->disp;
}

int cmpMedicionesAcum(const void* e1, const void* e2)
{
    t_MedicionesAcum* med1 = (t_MedicionesAcum*) e1;
    t_MedicionesAcum* med2 = (t_MedicionesAcum*) e2;

    return med1->dispositivo-med2->dispositivo;
}

void actMedAcum(void* actualizado, const void* actualizador)
{
    t_MedicionesAcum* med = (t_MedicionesAcum*) actualizado;
    t_MedicionesAcum* medActualizador = (t_MedicionesAcum*) actualizador;

    med->cantMediciones++;
    med->tempCruda+=medActualizador->tempCruda;

}

tNodo* crearNodo(const void* elem, size_t tamElem)
{
    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));
    if(!nue)
        return NULL;
    nue->info = malloc(tamElem);
    if(!nue->info)
        return NULL;

    nue->tam=tamElem;
    nue->ant=nue->sig=NULL;
    memcpy(nue->info,elem,tamElem);


    return nue;
}

void leerLinea(char* linea,t_Coeficientes* coef)
{
    char* c;

    c = strrchr(linea,'\n');

    if(!c)
    {
        c = strrchr(linea,'\0');
        if(!c)
            return;
    }

    *c='\0';


    c=strrchr(linea,'=');
    sscanf(c+1,"%f",&coef->desplazamiento);
    *c='\0';


    c=strrchr(linea,'=');
    sscanf(c+1,"%f",&coef->ganancia);
    *c='\0';

    c=strrchr(linea,'=');
    sscanf(c+1,"%d",&coef->disp);



}

bool leerArchivoCoef(const char* nomArch,Lista* pl)
{
    FILE *pf= fopen(nomArch,"r");
    char linea[TAM_LINEA];

    t_Coeficientes coef;

    while(fgets(linea,TAM_LINEA,pf))
    {
        leerLinea(linea,&coef);

        //printf("\nCoeficiente: disp=%d;ganancia=%f;desplazamiento=%f",coef.disp,coef.ganancia,coef.desplazamiento);
        insertarAlFinal_ALU(pl,&coef,sizeof(t_Coeficientes));

    }

    fclose(pf);

    return true;
}

