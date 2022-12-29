

#define DEBUG_MODE 1
#include "Cabecera.h"

int main()
{

    system("chcp 1252 > nul");

    Lista listCoef, listMed;
    crearLista(&listCoef);
    crearLista(&listMed);


    leerArchivoCoef("coeficientes.txt",&listCoef);


    FILE *pfMed=fopen("mediciones.dat","rb");
    float resultado;
    t_Mediciones med;
    t_MedicionesAcum medAcum={0,0,0};
    t_Coeficientes coef;



    fread(&med,sizeof(t_Mediciones),1,pfMed);

    printf("\n====================================MEDICIONES============================================");
    while(!feof(pfMed))
    {
        printf("\nMedicion: disp:%d cantMedida:%d",med.dispositivo,med.tempCruda);
        medAcum.cantMediciones=1;
        medAcum.dispositivo=med.dispositivo;
        medAcum.tempCruda=med.tempCruda;
        insertarOActualizarEnOrden(&listMed,&medAcum,sizeof(t_MedicionesAcum),cmpMedicionesAcum,actMedAcum);
        fread(&med,sizeof(t_Mediciones),1,pfMed);
    }


    printf("\n====================================RESULTADO============================================");
    while(eliminarPrimero(&listMed,&medAcum, sizeof(t_MedicionesAcum)))
    {

        //printf("\nMedicionAcum: disp:%d medicion:%d cantMediciones:%d",medAcum.dispositivo,medAcum.tempCruda,medAcum.cantMed);
        coef.disp=medAcum.dispositivo;
        buscarEnLista(&listCoef,&coef,sizeof(t_Coeficientes),cmpCoeficientes_ALU);
        resultado = (medAcum.tempCruda*coef.ganancia+coef.desplazamiento*medAcum.cantMediciones)/medAcum.cantMediciones;
        printf("\nDispositivo Nº%d: promedio=%.4f",medAcum.dispositivo,resultado);

    }


    fclose(pfMed);

    return 0;
}

