//Registro ventas Pasteleria
#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
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
		int Mes,Dia;
        int Fecha;
		char Clave[30];
		char CodigoProducto[30];			//Para Lista de Precios
	public:	
        int TiempoDia();
        int TiempoMes();
		void MenuPrincipal();
	    void NuevaCompra();
	    void ListaDeCompras(); 
	    void DetalleDeCompra();	 
		void CambiarContrasena();
		float CalculaGanancia(); 
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
     	printf("4. Cambiar Contrase" "%c" "a \n\n",-92 );
        cout<<"0. Cerrar Sistema\n\n";
        cout<<"Seleccione Operaci\242n: ";																	 // \242 = ó
        cin>>accion;
				    system(CLEAR);
				        switch(accion)
				        {
				        default:
				            cout<<"Ha ingresado una opci\242n no valida!\n\n";
				            Sleep(1000);
				            system(CLEAR);
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
						case 4:
							CambiarContrasena();
							break;		
				        case 0:
				        	system (CLEAR);
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
								       /* fflush(stdin);
								        cout<<"Producto Comprado: ";
								        cin.getline(Producto,20);
								        cout<<"\n";
								        fflush(stdin);
								        cout<<"Costo Del Producto: ";
								        cin.getline(Costo,20);
								        cout<<"\n";
								        fflush(stdin);  */
		escribir<<CodigoDeCompra<<"\n\n"<<Cliente<<"\n\n";
        fflush(stdin);
        cout<<"\n";
        
        escribir<<Producto<<"\n\n"; 		
        fflush(stdin);
        
        char auxProd [30];
        ifstream listar;							//Lista de Precios
    	bool hay=false;								//Para ver que prosucto es
    	listar.open("ListaPrecios.txt",ios::in); 
        
      if(listar.is_open())
    {
        fflush(stdin);
        cout<<"\t\t\t*** Seleccionar Producto ***\n\n";
       
	
        cout<<"Ingrese El C\242digo Del Producto: ";
        cin.getline(auxProd,30);
        listar.seekg(0);
        listar>>CodigoProducto;							//Lee el primer Codigo de Lista de Precios																			
        while(!listar.eof())																					//Mientras no se llegue al finl del archivo
        {	
			//listar.seekg(0);		
            listar>>Producto>>Costo;															//lee los demas datos de la compra
            if(strcmp(auxProd,CodigoProducto)==0)										//Si ha encontrado el codigo de producto ingresado en la Lista de Precios
            {
                hay=true;
              	//cout<<"\n\nProducto Encontrado\n\n";															//Muestra los detalles del producto
                //cout<<"C\242digo De Producto: "<<CodigoProducto<<endl;
                cout<<"\n\t\t\t\tProducto: "<<Producto<<endl;
                cout<<"\t\t\t\t\tCosto: "<<Costo<<endl;
                cout<<"\n\n";
                
                escribir<<Producto<<"\n\n"<<Costo<<"\n\n";
            
            } 
            listar>>CodigoProducto;	
			
			}
			
			
        if(hay==false)							///CUANDO NO HAY COINCIDENCIA SE MUERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        {
        	
            cout<<"\n\nNo Hay Registro Del Producto con el codigo: "<<auxProd<<"\n\n";
			Sleep(500);							//No encontro un registro de esa comp
			
         }
         }
    else
    {
        error();																								//Ocurrio un error al abrir el archivo
    }
    listar.close(); 
       				
        cout<<"\n";
        fflush(stdin);
         
        cout<<"Fecha De Compra: ";
         																										/*Asi se guarda en el archivo .txt*/
        	/* 	Codigo de compra
        																											Cliente
																													Producto
																													Costo
																													Fecha
																												*/
					 Fecha=TiempoDia();
					 
        cout<<"La Compra Se Ha Registrado Correctamente.\n\n";
        escribir<<CodigoDeCompra<<"\n\n"<<Cliente<<"\n\n"<<Producto<<"\n\n"<<Costo<<"\n\n"<<Fecha<<"\n\n";	
    }
    else																										/*Si ocurrio un error al abrir el archivo .txt*/
    {
        error();
    }

    escribir.close();																							//Cerrar el Archivo
    verificar.close();
    system("attrib +h Compras.txt");
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
    system("attrib +h Compras.txt");
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
    mostrar.close();
	system("attrib +h Compras.txt");																							//Cerrar el Archivo
    pausa();	
																									//Pausa antes de la siguiente acción
}
/*------------------------------------------------------------------------------------------------------------------------------------*/
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
		    frase[i-1] = 0;
		    cout << endl;
		}
/*------------------------------------------------------------------------------------------------------------------------------------*/
/*class Tiempo{                                                                                                 //Esta banda nos permite generar la fecha en que se registra una venta                                                                                                  
	public:		
		Tiempo ();
}; */
int Compra::TiempoDia() {
	time_t tiempo;	
	time(&tiempo);
	
	struct tm *eltiempo= localtime (&tiempo);
		//printf("  %d/%d/%d\n\n",  eltiempo->tm_mday,eltiempo->tm_mon+1,eltiempo->tm_year+1900);
			printf("%s\n",ctime(&tiempo));
		return eltiempo->tm_mday;
}
int Compra::TiempoMes() {
	time_t tiempo;	
	time(&tiempo);
			struct tm *eltiempo= localtime (&tiempo);
			return eltiempo->tm_mon+1;
}	
/*************************************************************************************************************************************/
float CalculaGanancia()	{
	
	
}
/*************************************************************************************************************************************/
void Compra::CambiarContrasena(){
	char Contrasena[30];
	char auxContra[30];
	char entrada[]=" ";
    ofstream cambiar;
    ifstream checar;
    ofstream auxiliar;
    
    auxiliar.open("auxiliar.txt",ios::out);
	checar.open("Password.txt",ios::in);
    
	if(checar.is_open())																//Si se abrio correctamente el archivo
    {
    	checar.seekg(0);																				//Regresa a leer desde la primera linea del archivo .txt
    	checar>>Contrasena;
    	fflush(stdin);
    	cout<<"Ingrese su contrasena: ";
    	Ocultar(auxContra);																	//Escanea el código
        if(strcmp(auxContra,Contrasena)==0)		
    	{
    			
    		printf("\nIngrese Nueva Contrase" "%c" "a\n",-92 );
    		Ocultar(auxContra);	
    		auxiliar<<auxContra;
    		Sleep(500);
    		system(CLEAR);
    		auxiliar.close();
    		checar.close();
			remove("Password.txt");									                               //EliminaArchivo
    		rename("auxiliar.txt","Password.txt");					                               //Renombra archivo
    		system("attrib +h Password.txt");						                               //Oculta el Archivo
    		
		}
    	 else {
    	 			printf("\nAcceso Denegado\nContrase" "%c" "a Incorrecta\n",-92 );
					Sleep(1000);
					system(CLEAR);

		 }
		}	
	else error();	
}
/*************************************************************************************************************************************/
/*AQUI VIENE EL MAIN */
/*************************************************************************************************************************************/
int main()
{
	char Contrasena[30];
	bool acceso=false;
    system ("color a0");
    FILE *archivo;						
	char caracter;
	char contrasena[]="";
	char entrada[]="";
	
				printf("\n\n\n\t\t\t\t***Control de Compras Pasteleria - SAN SEBASTIAN - ""***\t\t\t\t\n\n");	
inicio:	
				 int Tiempo();
				//cout << "Ingrese su contrasena: " << endl;
				printf("\n Ingrese su Contrase" "%c" "a \n",-92 );
				Ocultar(entrada);
	 															
				
				ifstream password;
				password.open("  Password.txt",ios::app);	
				
				/*if(password.is_open()){
					
					password.seekg(0);																		//Regresa a leer desde la primera linea del archivo .txt
            		password>>Contrasena;
            		if(password.eof()&&strcmp(entrada,Contrasena)==0)										//Si slas contraseñas coinciden
                	acceso=true;
				}*/
					acceso=true;
				password.close();
		            if (acceso==true) {
		            cout<<"\n Acceso permitido!! \n";
		            Sleep(500);
					system(CLEAR);
		            	 Compra inicio;
		             inicio.MenuPrincipal();
		    			
					//cout<<"\t\t\t\t***Control de Compras Pasteleria - SAN SEBASTIAN - ""***\t\t\t\t\n\n";			    				
				}
		            else {
					printf("\nAcceso Denegado\nContrase" "%c" "a Incorrecta\n",-92 );
					Sleep(1000);  		                                                                    //Pausa 1s
					system(CLEAR);
					cout<<"\n\n\n\t\t\t\t***Control de Compras Pasteleria - SAN SEBASTIAN - ""***\t\t\t\t\n\n";	
					goto inicio;
		        }
		        
    //getch();
    return 0;
}
