//Registro ventas Pasteleria
#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

//Limpiar pantalla
#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

using namespace std;

class Compra{
	private:
		char CodigoDeCompra[20];
		char Cliente[20];
		char Producto[20];
		char Costo[20];	
		char Fecha[20];
	public:	
		void MenuPrincipal();
	    void NuevaCompra();
	    void ListaDeCompras(); 
	    void DetalleDeCompra();	    		
};
/*****************************************************************************************************************************************/
void pausa();																								//Hace una pausa despues de realizar alguna acción
void error();																								//En caso de que ocurra un error
		void pausa()
		{
		    cout<<"Presione Una Tecla Para Continuar...";
		    getch();
		    system(CLEAR);
		}
		void error()
		{
			cout<<endl<<endl;
		    cout<<"\t\t\t\t\tHa Ocurrido Un Error En El Sistema\n\n";
		    cout<<"\t\t\t\t\t\tVuelva A Intentar\n\n";
		    cout<<"\t\t\tSi Persiste El Error Contacte Al Equipo De Desarrolladores\n\n";
		    
		}
/****************************************************************************************************************************************/
void Compra::MenuPrincipal()
{
    int accion;
    do
    {
    	cout<<endl<<endl;
        cout<<"\t\t\t\t***Control de Compras Pasteleria - SAN SEBASTIAN - ""***\t\t\t\t\n\n";
        cout<<"1. Nueva Compra\n\n";
        cout<<"2. Lista de Compras\n\n";
        cout<<"3. Detalle de Compra\n\n";
        cout<<"0. Cerrar Sistema\n\n";
        cout<<"Seleccione Operaci\242n: ";																	 // \242 = ó
        cin>>accion;
				    system(CLEAR);
				        switch(accion)
				        {
				        default:
				            cout<<"Ha ingresado una opci\242n no valida!\n\n";
				            break;
				
				        case 1:
				            NuevaCompra();
				            break;
				
				        case 2:
				            ListaDeCompras();
				            break;
				
				        case 3:
				            DetalleDeCompra();
				            break;
				
				        case 0:
							break;
				        }
    }
    while(accion!=0);																						//Mientras no se seleccione la opción Cerrar Sistema
}
/***************************************************************************************************************************************/
void Compra::NuevaCompra()
{
    ofstream escribir;
    ifstream verificar;
    char auxCodigo[20];
    bool coincidencia=false;
    verificar.open("Compras.txt",ios::in);
    escribir.open("Compras.txt",ios::app);																	// app para modificar, si se colocara out se sobreescribe todo
    
    if(escribir.is_open()&&verificar.is_open())																//Si se abrio correctamente el archivo
    {
        cout<<"\t\t\t\t***Ingresando Una Nueva Compra***\t\t\t\t\n\n";
        fflush(stdin);																						//Limpiar Buffer
        cout<<"Ingrese El C\242digo De Compra: ";
        cin.getline(auxCodigo,20);																			//Escanea el código
        if(strcmp(auxCodigo,"")==0)																			//Si en vez de ingresar un código se presionó enter
            do
            {
                cout<<"C\242digo De Compra NO v\240lido!, Intentalo Nuevamente: ";							// \240 = á
                cin.getline(auxCodigo,20);
            }
            while(strcmp(auxCodigo,"")==0);																	//Seguir haasta que ingrese un codigo válido								
        do
        {
            verificar.seekg(0);																				//Regresa a leer desde la primera linea del archivo .txt
            verificar>>CodigoDeCompra;																		// Captura la primera linea guardada en el archivo .txt que es un Codigo de Compra
            while(!verificar.eof())																			//Mientras no se llegue al final del archivo
            {
                verificar>>Cliente>>Producto>>Costo>>Fecha;

                if(strcmp(CodigoDeCompra,auxCodigo)==0)														//Compara el código ingresado con los leidos de el archivo .txt
                {
                    coincidencia=true;																		//Si el codigo de compra ya exixtia se pide que ingrese uno nuevo
                    cout<<"\n\nYa Existe Una Compra Con Ese C\242digo!\n\n";
                    cout<<"Ingrese Un C\242digo Nuevo: ";
                    cin.getline(auxCodigo,20);
                    if(strcmp(auxCodigo,"")==0)
                        do
                        {
                            cout<<"\nC\242digo De Cliente No V\240lido!, Intentalo Nuevamente: ";			//Nuevamente se verificaa que el usuario no ingrese un enter
                            cin.getline(auxCodigo,20);
                        }
                        while(strcmp(auxCodigo,"")==0);

                    break;
                }

                verificar>>CodigoDeCompra;
            }

            if(verificar.eof()&&strcmp(auxCodigo,CodigoDeCompra)!=0)										//Si se llego al final del archivo y no hubo coincidencias
                coincidencia=false;

        } while(coincidencia==true);
        
        system(CLEAR);       
        strcpy(CodigoDeCompra,auxCodigo);
        cout<<"\t\t\t\t***Ingresando Una Nueva Compra***\t\t\t\t\n\n";
        cout<<"C\242digo De Compra Ingresado: ";
        cout<<CodigoDeCompra;
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Nombre Del Cliente: ";
        cin.getline(Cliente,20);
        cout<<"\n";
        fflush(stdin);
        cout<<"Producto Comprado: ";
        cin.getline(Producto,20);
        cout<<"\n";
        fflush(stdin);
        cout<<"Costo Del Producto: ";
        cin.getline(Costo,20);
        cout<<"\n";
        fflush(stdin);
        cout<<"Fecha De Compra: ";
        cin.getline(Fecha,20);
        cout<<"\n\n";
																												/*Asi se guarda en el archivo .txt*/
        escribir<<CodigoDeCompra<<"\n\n"<<Cliente<<"\n\n"<<Producto<<"\n\n"<<Costo<<"\n\n"<<Fecha<<"\n\n";		/* 	Codigo de compra
        																											Cliente
																													Producto
																													Costo
																													Fecha
																												*/
        cout<<"La Compra Se Ha Registrado Correctamente.\n\n";
    }
    else																										/*Si ocurrio un error al abrir el archivo .txt*/
    {
        error();
    }

    escribir.close();																							//Cerrar el Archivo
    verificar.close();
    pausa();																									//Pausa antes de la siguiente accción
}

/***************************************************************************************************************************************/
void Compra::ListaDeCompras()
{
    int i=0;
    ifstream leer;
    leer.open("Compras.txt",ios::in);
    if(leer.is_open())
    {
        cout<<"\t\t\t\t***Lista De Compras***\t\t\t\t\n\n";
        leer>>CodigoDeCompra;																					//Lo primero que lee es el código de compra
        while(!leer.eof())																						//Mientras no se llegue al final del archivo
        {
            i++;																								//Iterador para contar el numero de Compras registradas
            leer>>Cliente>>Producto>>Costo>>Fecha;  
            cout<<"C\242digo De Compra: "<<CodigoDeCompra<<endl;
            cout<<"Nombre Del Cliente: "<<Cliente<<endl;           
            cout<<"Producto: "<<Producto<<endl;
            cout<<"Costo: "<<Costo<<endl;
            cout<<"Fecha De Compra: "<<Fecha<<endl;
            cout<<"\n\n";
            leer>>CodigoDeCompra;																				//Lee el siguente codigo de compra
        }
            cout<<"El Numero Total de Compras Registradas es: "<<i<<" \n\n";									//Muestra cuantas compras se han registrado
    }
    else																										//Si hubo un error al abrir el archivo .txt
    {
        error();
    }
    leer.close();
    pausa();																									//Pausa antes de la siguiente acción
}
/**************************************************************************************************************************************/
void Compra::DetalleDeCompra()
{
    char auxCodigo [30];
    ifstream mostrar;
    bool encontrado=false;
    mostrar.open("Compras.txt",ios::in);
    if(mostrar.is_open())
    {
        fflush(stdin);
        cout<<"\t\t\t\t***Consultar Detalles De Compras***\t\t\t\t\n\n";
        cout<<"Ingrese El C\242digo De Compra A Consultar: ";
        cin.getline(auxCodigo,30);
        mostrar>>CodigoDeCompra;																				//Lee el primer codigo de compra del archivo .txt
        while(!mostrar.eof())																					//Mientras no se llegue al finl del archivo
        {
            mostrar>>Cliente>>Producto>>Costo>>Fecha;															//lee los demas datos de la compra
            if(strcmp(auxCodigo,CodigoDeCompra)==0)																//Si ha encontrado el codigo de compra ingresado en el archivo .txt		
            {
                encontrado=true;
                cout<<"\n\nRegistro Encontrado\n\n";															//Muestra los detalles de la compra en pantalla
                cout<<"C\242digo De Compra: "<<CodigoDeCompra<<endl;
                cout<<"Nombre Del Cliente: "<<Cliente<<endl;
                cout<<"Producto: "<<Producto<<endl;
                cout<<"Costo: "<<Costo<<endl;
                cout<<"Fecha De Compra: "<<Fecha<<endl;
                cout<<"\n\n";
            }
            mostrar>>CodigoDeCompra;																			//lee el siguiente codigo de compra  
        }
        if(encontrado==false)
        {
            cout<<"\n\nNo Hay Registro De La Compra Con El C\242digo: "<<auxCodigo<<"\n\n";						//No encontro un registro de esa compra
        }
    }
    else
    {
        error();																								//Ocurrio un error al abrir el archivo
    }
    mostrar.close();																							//Cerrar el Archivo
    pausa();																									//Pausa antes de la siguiente acción
}
using namespace std;
void Ocultar(char frase[])																						//FUNCION ocultar dambia caracteres por "*"
		{
		    int i=0;
		    cout.flush();
		    do
		    {
		        frase[i] = (unsigned char)getch();
		        if(frase[i]!=8)  									 											// no es retroceso
		        {
		            cout << '*';  																				// muestra por pantalla
		            i++;
		        }
		        else if(i>0)   										 											// En caso de retroceso y hay caracteres
		        {
		            cout << (char)8 << (char)32 << (char)8;
		            i--;   	 										 											//el caracter a borrar el backspace
		        }
		        cout.flush();
		    }while(frase[i-1]!=13); 																			// por si presiona ENTER el mae
		    frase[i-1] = NULL;
		    cout << endl;
		}
/*************************************************************************************************************************************/
/*AQUI VIENE EL MAIN */
/*************************************************************************************************************************************/
int main()
{
    system ("color a0");
    FILE *archivo;						
	char caracter;
	char contrasena[]=" ";
	char entrada[]=" ";
	
				cout << "Ingrese su contrasena: " << endl;
				Ocultar(entrada);
	 																	//	cout <<" Mostrando password "<< entrada << endl; // Nos permite ver que escribimos XD
	archivo = fopen("prueba.csv","r");
			if (archivo == NULL)
		   		printf("Error al abrir el archivo"); 
		   																									//printf("\nContrasena : ");

	while (feof(archivo) == 0)
         {
            int i;            
	            for(i=0; i<10; i++)																			//La contraseña deben ser 10 caracteres
	            {
	            caracter = fgetc(archivo);
	            if(caracter == ',')
	            break;            
	            else{
	            fflush(stdin);
	            contrasena[i]= caracter;
				}
            }
          									// cout<<contrasena<<endl;										//Imprime el dato importado de la primera celda de excel
            																								//Comparar datos entrada - contraseña
		            if (strcmp(entrada,contrasena) == 0) {
		            	 Compra inicio;
		             inicio.MenuPrincipal();
		    		printf("\n Acceso permitido!! \n");				    				
				}
		            else if(strcmp(entrada,contrasena) == 1){ 
					printf("\n Contrasena Incorrecta!! \n");
		        }
    getch();
    return 0;
}
}
