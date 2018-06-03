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
		int Costo;	
		int Fecha;
		//int Mes,Dia;
        //int Fecha;
		char CodigoProducto[30];			//Para Lista de Precios
		//string Costos;
		//char Productos[20];
		
		char Clave[30];
	public:	
		void MenuPrincipal();
	    void NuevaCompra();
	    void ListaDeCompras(); 
	    void DetalleDeCompra();	 
		int TiempoMes();
		int TiempoDia();
		//string SeleccionProducto();
		void CalcularGanancia();
		void CambiarContrasena(); 

		  		
};
/*****************************************************************************************************************************************/
void pausa();																								//Hace una pausa despues de realizar alguna acci�n
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
	srand(time(NULL));
    int accion;
    do
    {
    	cout<<endl<<endl;
        cout<<"\n\n*** Control de Compras Pasteleria - SAN SEBASTIAN - ***\n\n";
        cout<<"1. Nueva Compra\n\n";
        cout<<"2. Lista de Compras\n\n";
        cout<<"3. Detalle de Compra\n\n";
    	cout<<"4. Calcular Ganancia Mensual\n\n";
    	printf("5. Cambiar Contrase" "%c" "a \n\n",-92 );
    	
        cout<<"0. Cerrar Sistema\n\n";
        cout<<"Seleccione Operaci\242n: ";																	 // \242 = �
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
							CalcularGanancia();
							break;		
														
						case 5:
							CambiarContrasena();
							break;
							
				        case 0:
				        	system (CLEAR);
							break;
				        }
    }
    while(accion!=0);																						//Mientras no se seleccione la opci�n Cerrar Sistema
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
        fflush(stdin);
		cout<<"Ingrese Codigo de Compra: ";																						//Limpiar Buffer
		cin.getline(auxCodigo,20);																			//Escanea el c�digo
        if(strcmp(auxCodigo,"")==0)																			//Si en vez de ingresar un c�digo se presion� enter
            do
            {
                cout<<"C\242digo De Compra NO v\240lido!, Intentalo Nuevamente: ";							// \240 = �
                cin.getline(auxCodigo,20);
            }
            while(strcmp(auxCodigo,"")==0);																	//Seguir haasta que ingrese un codigo v�lido								
        do
        {
            verificar.seekg(0);																				//Regresa a leer desde la primera linea del archivo .txt
            verificar>>CodigoDeCompra;																		// Captura la primera linea guardada en el archivo .txt que es un Codigo de Compra
            while(!verificar.eof())																			//Mientras no se llegue al final del archivo
            {
                verificar>>Cliente>>Fecha>>Producto>>Costo;
                

                if(strcmp(CodigoDeCompra,auxCodigo)==0)														//Compara el c�digo ingresado con los leidos de el archivo .txt
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
        
        cout<<"Fecha De Compra: ";
        Fecha=TiempoMes();
        
        escribir<<CodigoDeCompra<<"\n\n"<<Cliente<<"\n\n"<<Fecha<<"\n\n";
        fflush(stdin);
     /*************************************************************/   
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
				
            listar>>Producto>>Costo;															//lee los demas datos de la compra
            if(strcmp(auxProd,CodigoProducto)==0)										//Si ha encontrado el codigo de producto ingresado en la Lista de Precios
            {
                hay=true;
              	
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
																												/*Asi se guarda en el archivo .txt*/
        /*escribir<<Fecha<<"\n\n";*/																				/* 	Codigo de compra
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
    system("attrib +h Compras.txt");
    pausa();																									//Pausa antes de la siguiente accci�n
}

/***************************************************************************************************************************************/
void Compra::ListaDeCompras()
{
    int i=0;
    ifstream leer;
    leer.open("Compras.txt",ios::in);
    if(leer.is_open())
    {
        cout<<"\t\t\t***Lista De Compras***\n\n";
        leer>>CodigoDeCompra;																					//Lo primero que lee es el c�digo de compra
        while(!leer.eof())																						//Mientras no se llegue al final del archivo
        {
            i++;																								//Iterador para contar el numero de Compras registradas
            leer>>Cliente>>Fecha>>Producto>>Costo;  
            cout<<"C\242digo De Compra: "<<CodigoDeCompra<<endl;
            cout<<"Nombre Del Cliente: "<<Cliente<<endl;           
            cout<<"Producto: "<<Producto<<endl;
            cout<<"Costo: "<<Costo<<endl;
            cout<<"Mes De Compra: "<<Fecha<<endl;
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
    pausa();																									//Pausa antes de la siguiente acci�n
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
        cout<<"\t\t\t***Consultar Detalles De Compras***\n\n";
        cout<<"Ingrese El C\242digo De Compra A Consultar: ";
        cin.getline(auxCodigo,30);
        mostrar>>CodigoDeCompra;																				//Lee el primer codigo de compra del archivo .txt
        while(!mostrar.eof())																					//Mientras no se llegue al finl del archivo
        {
            mostrar>>Cliente>>Fecha>>Producto>>Costo;															//lee los demas datos de la compra
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
																									//Pausa antes de la siguiente acci�n
}

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
    	Ocultar(auxContra);																	//Escanea el c�digo
        if(strcmp(auxContra,Contrasena)==0)		
    	{
    			
    		printf("\nIngrese Nueva Contrase" "%c" "a\n",-92 );
    		Ocultar(auxContra);	
    		auxiliar<<auxContra;
    		Sleep(500);
    		system(CLEAR);
    		auxiliar.close();
    		checar.close();
			remove("Password.txt");									//EliminaArchivo
    		rename("auxiliar.txt","Password.txt");					//Renombra archivo
    		system("attrib +h Password.txt");						//Oculta el Archivo
    		
    
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
int Compra::TiempoDia() {
	time_t tiempo;	
	time(&tiempo);
			struct tm *eltiempo= localtime (&tiempo);
			printf("	     La fecha de hoy es: %s\n",ctime(&tiempo));
			return eltiempo->tm_mday;
}
int Compra::TiempoMes() {
	time_t tiempo;	
	time(&tiempo);
			struct tm *eltiempo= localtime (&tiempo);
			printf("%s\n",ctime(&tiempo));
			return eltiempo->tm_mon+1;
}
/*************************************************************************************************************************************/
/*AQUI VIENE EL MAIN */
/*************************************************************************************************************************************/
int main()
{
	char Contrasena[30];
	bool acceso=false;
    system ("color a0");
	char contrasena[]=" ";
	char entrada[]=" ";
				cout<<"\n\n\n\t***Control de Compras Pasteleria - SAN SEBASTIAN - ***\n";	
				Compra uno;
				 int a=uno.TiempoDia();
																								
					if(a==1){																	//Recordatorios al inicio del mes
						printf("	Usted tiene que hacer el deposito de las ganancias del mes que acaba de terminar");
					}
					else if (a==15){															//Recordatorios a mitad del mes
						printf("	Hoy es quincena hay que hacer las compras de los insumos"); 
					}																			
					else if(a==30){																//Recordatorio final de mes
						printf("	Usted tiene que generar las ganancias del mes");
					} 
						printf("	No hay recordatorios para hoy");
inicio:	
				printf("\n Ingrese su Contrase" "%c" "a \n",-92 );
				Ocultar(entrada);
	 															
				ifstream password;
				password.open("Password.txt",ios::in);				//AQUI ESTABA EL PROBLEMA!!!!! lo tenia como app y no loreconocia as�
				
				if(password.is_open()){
					
					password.seekg(0);																				//Regresa a leer desde la primera linea del archivo .txt
            		password>>Contrasena;
            		if(password.eof()&&strcmp(entrada,Contrasena)==0)										//Si slas contrase�as coinciden
                	acceso=true;	
				}
				password.close();
          									// cout<<contrasena<<endl;										//Imprime el dato importado de la primera celda de excel
            																								//Comparar datos entrada - contrase�a
		            if (acceso==true) {
		            cout<<"\n Acceso permitido!! \n";
		            Sleep(500);
					system(CLEAR);
		            	 Compra inicio;
		             		 inicio.MenuPrincipal();  				
				}
		            else {
						printf("\nAcceso Denegado\nContrase" "%c" "a Incorrecta\n",-92 );
						Sleep(1000);  		//Pausa 1s
						system(CLEAR);
						cout<<"\n\n\n\t*** Control de Compras Pasteleria - SAN SEBASTIAN - ***\n\n";	
						goto inicio;
		        }
    return 0;
}
/**************************************************************************************************************************/
void Compra::CalcularGanancia(){
	int Mes;
	float Ganancia=0;
    ifstream sumar;
    bool mencontrado=false;
    sumar.open("Compras.txt",ios::in);
    if(sumar.is_open())
    {
        fflush(stdin);
        cout<<"\t\t\t***Calcular Ganancia Mensual***\n\n";
        cout<<"Ingrese El Mes A Consultar: ";
        cin>>Mes;
        sumar>>CodigoDeCompra>>Cliente>>Fecha>>Producto;																				//Lee el primer codigo de compra del archivo .txt
        while(!sumar.eof())																					//Mientras no se llegue al finl del archivo
        {
            sumar>>Costo;															//lee los demas datos de la compra
            if((Mes-Fecha)==0)																//Si ha encontrado el codigo de compra ingresado en el archivo .txt		
            {
                mencontrado=true;
				Ganancia+=Costo;
            }
            sumar>>CodigoDeCompra>>Cliente>>Fecha>>Producto;																			//lee el siguiente codigo de compra  
        }
        if(mencontrado==false)
        {
            cout<<"\n\nNo Hay Registro Del Mes: "<<Mes<<"\n\n";						//No encontro un registro de esa compra
        }
    }
    else
    {
        error();																								//Ocurrio un error al abrir el archivo
    }
    sumar.close();
    cout<<"\n\t\t\t***Ganancia Mensual: "<<Ganancia<<"***\n\n";
	system("attrib +h Compras.txt");																							//Cerrar el Archivo
    pausa();	
}
