#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>
using namespace std;
 
int main()
{
	FILE *archivo;
	char caracter;
	char contrasena[]=" ";
	char entrada[]=" ";
	
	cout << "Ingrese su contraseña: " << endl;
	cin >> entrada;
	 
	archivo = fopen("prueba.csv","r");
 
		if (archivo == NULL)
		   printf("Error al abrir el archivo");
		//printf("\nContrasena : ");
	 	
	while (feof(archivo) == 0)
         {
            int i;            
            
	            for(i=0; i<10; i++)			//La contraseña deben ser 10 caracteres
	            {
	            caracter = fgetc(archivo);
	            if(caracter == ',')
	            break;
	                            
	            else{
	            fflush(stdin);
	            contrasena[i]= caracter;
				}
            }
            //cout<<contrasena<<endl;		//Imprime el dato importado de la primera celda de excel
        
            //Comparar datos entrada - contraseña
            if (strcmp(entrada,contrasena) == 0) 
    		printf("\n Acceso permitido!! \n");

            else printf("\n Contrasena Incorrecta!! \n");
    
            getch();
            return 0;
            }
}
