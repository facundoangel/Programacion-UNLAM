#include "parcail2.h"

//======================FUNCIONES PARA MANIPULAR CADENAS===========================
int strComparar(char c1, char c2)
{

    return c1-c2;
}

void strCopiar(char* cad1, char*cad2)
{
    while(*cad2)
    {
        *cad1=*cad2;
        cad1++;
        cad2++;
    }
    *cad1='\0';
    *cad2='\0';
}

char* strBuscar(char* cad,char c)
{


    while(*cad)
    {
        if(c==*cad)
            return cad;
        cad++;
    }

    return NULL;
}


void leerLinea(char* linea,Alumno* alu)
{

    char *fin, *ini=linea;
    int cont=0;

    if(!linea)
        return;

    fin = strBuscar(linea,'\n');
    *fin='\0';


    fin = strBuscar(linea,';');
    *fin='\0';
    sscanf(ini,"%10d",&alu->dni);
    ini=++fin;

    fin = strBuscar(ini,';');
    *fin='\0';
    strCopiar(alu->apyn,ini);
    ini=++fin;

    while(fin)
    {
        fin = strBuscar(ini,',');
        sscanf(ini,"%8f",&alu->notas[cont]);
        cont++;
        if(fin!=NULL)
        {
            *fin='\0';
            ini=++fin;
        }
    }


    for(int i=cont;i<5;i++)
    {
        alu->notas[i]=0;
    }



}

void actualizarNodo(void* elem, Nodo* nodo)
{
    memcpy(nodo->info,elem,sizeof(CondFinal));
}

//======================FUNCIONES===========================


void escribirArchivo(Lista* pl)
{
    FILE *pf = fopen("notas.dat","wb");

    CondFinal cond;

    //RETORNO AL INICIO LA LISTA

    while((*pl)->ant)
    {
        *pl=(*pl)->ant;
    }


    //VACIO LA LISTA Y ESCRIBO EN ARCHIVO
    while(!listaVacia(pl))
    {
        desenlistarAlInicio(pl,&cond,sizeof(CondFinal));
        fwrite(&cond,sizeof(CondFinal),1,pf);
        printf("\n%-30s %d %c",cond.apyn,cond.dni,cond.condicion);
    }

    fclose(pf);
}

int compararAlumno(void* elem1, void* elem2)
{

    CondFinal al1, al2;
    Nodo *nodo = (Nodo*)elem2;
    memcpy(&al1,elem1,sizeof(CondFinal));
    memcpy(&al2,nodo->info,sizeof(CondFinal));

    return al1.dni-al2.dni;
}

int compararAlumnoXNota(void* elem1, void* elem2)
{

    CondFinal al1, al2;
    Nodo *nodo = (Nodo*)elem2;
    memcpy(&al1,elem1,sizeof(CondFinal));
    memcpy(&al2,nodo->info,sizeof(CondFinal));

    int result = strComparar(al1.condicion,al2.condicion);

    if(result!=0)
        return result;

    return al1.dni-al2.dni;
}


void pasarNota(Alumno* alu, CondFinal* cond)
{
    int cont=0, sumatoria=0;
    float prom;
    strCopiar(cond->apyn,alu->apyn);
    cond->dni=alu->dni;

    //SI TIENE MENOS DE 2 NOTAS COLOCO CONDICION AUSENTE
    for(int i=0;i<5;i++)
    {
        if(alu->notas[i]!=0)
        {
            sumatoria+=alu->notas[i];
            cont++;
        }
    }
    if(cont<2)
    {
        cond->condicion='A';
        return;
    }

    prom=sumatoria/cont;
    //ASIGNO CONDICION EN BASE A PROMEDIO
    if(prom<4)
        cond->condicion='D';
    else if(prom>=4 && prom<7)
        cond->condicion='C';
    else if(prom>=7)
        cond->condicion='P';




}


bool ordenarNotas(Lista* plAlu,Lista* plNot)
{
    if(!plAlu)
        return false;


    CondFinal cond;

    while(!listaVacia(plAlu))
    {
        desenlistarAlInicio(plAlu,&cond,sizeof(CondFinal));
        enlistarEnOrdCDup(plNot,&cond,sizeof(CondFinal),compararAlumnoXNota);

    }


    return true;
}


bool leerArchivo(char* archAlumnos,Lista* pl)
{
    FILE *pf=fopen(archAlumnos,"r");
    char linea[TAM_LINEA];
    Alumno alu;
    CondFinal cond;

    if(!pf)
        return false;

    while(fgets(linea,TAM_LINEA,pf))
    {
        //LEO CADA LINEA Y CARGO CON LOS DATOS AL ALUMNO
        leerLinea(linea,&alu);
        pasarNota(&alu,&cond);
        //INSERTO ALUMNO EN LA LISTA
        enlistarDesordSDup(pl,&cond,sizeof(CondFinal),compararAlumno,actualizarNodo);
        //mostrarLista(pl,imprimirAlumno);

    }

    //mostrarLista(pl,imprimirAlumno);
    fclose(pf);

    return true;
}

void imprimirAlumno(Nodo* nodo)
{
    CondFinal alu;
    memcpy(&alu,nodo->info,sizeof(CondFinal));
    printf("%s\t%d\t%c",alu.apyn,alu.dni,alu.condicion);

    printf(" | ");


}
