#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 10                                                     
struct producto {
    int codigo;
    char nombre[31];
    int existencia;
    int vendidos;
};
//  Prototipos de Funciones

void capturar_inventario(struct producto inventario[], int *n); 
void registrar_ventas(struct producto inventario[], int n);
void mostrar_reporte(struct producto inventario[], int n);

//Modulo Principal
int main() {
    struct producto inventario[MAX_PRODUCTOS];
    int n = 0; 
    int opcion;

    do {
        printf("\n=================================================================\n");
        printf("                      PAPELERIA DEL CAMPUS \n");
        printf("Nombre: Noe Dominguez Villegas\n");
        printf("Matricula: ES261112078\n");
        printf("Grupo: DS-DFPR-2601-B1-007\n");

        printf("---------------------------MENU PRINCIPAL------------------------\n");
        printf("1. Capturar Inventario Inicial\n");
        printf("2. Registrar Venta\n");
        printf("3. Mostrar Reporte del Dia\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        if (opcion < 1 || opcion > 4) {
            printf("\n--- OPCION INVALIDA ---\nFavor de ingresar una opcion valida (1 a 4).\n");
        } else {
            switch(opcion) {
                case 1: capturar_inventario(inventario, &n); break;
                case 2: registrar_ventas(inventario, n); break;
                case 3: mostrar_reporte(inventario, n); break;
            }
        }
    } while (opcion != 4);

    printf("\nGracias por usar el sistema. Saliendo...\n");
    return 0;
}
void capturar_inventario(struct producto inventario[], int *n) {
    printf("\n--- CAPTURA DE INVENTARIO INICIAL ---\n");
    printf("¿Cuantos productos deseas registrar? (1 a 10): ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        printf("\nProducto %d\n", i + 1);
        printf("Codigo (entero de max 3 digitos): ");
        scanf("%d", &inventario[i].codigo);
        printf("Nombre (sin espacios): ");
        scanf("%s", inventario[i].nombre);
        printf("Existencia: ");
        scanf("%d", &inventario[i].existencia);
        inventario[i].vendidos = 0;
    }
    printf("\nInventario capturado correctamente.\n");
}

void registrar_ventas(struct producto inventario[], int n) {
    int cod_buscado, cantidad, encontrado = 0;
    
    printf("\n--- REGISTRAR VENTA ---\n");
    printf("Ingresa codigo del producto: ");
    scanf("%d", &cod_buscado);

    // Busqueda del producto en el inventario
    for (int i = 0; i < n; i++) {
        if (inventario[i].codigo == cod_buscado) {
            encontrado = 1;
            printf("Ingresa cantidad a vender: ");
            scanf("%d", &cantidad);

            if (cantidad <= inventario[i].existencia) {
                inventario[i].existencia -= cantidad;
                inventario[i].vendidos += cantidad;
                printf("Venta exitosa del producto: %s\n", inventario[i].nombre);
            } else {
                printf("ERROR: Existencia insuficiente. Actual de %s: %d\n", 
                        inventario[i].nombre, inventario[i].existencia);
            }
            break;
        }
    }
    if (!encontrado) printf("ERROR: El Codigo %d NO existe en el inventario.\n", cod_buscado);
}

void mostrar_reporte(struct producto inventario[], int n) {
    int total_piezas = 0;
    int indice_mas_vendido = 0;

    printf("\n------------------- REPORTE FINAL DEL DIA -------------------\n");

    for (int i = 0; i < n; i++) {
        total_piezas += inventario[i].vendidos;
        if (inventario[i].vendidos > inventario[indice_mas_vendido].vendidos) {
            indice_mas_vendido = i;
        }
    }

    printf("Total de piezas vendidas en el dia: %d\n", total_piezas);
    printf("Producto mas vendido: %s (Codigo: %d) con %d piezas.\n", 
            inventario[indice_mas_vendido].nombre, 
            inventario[indice_mas_vendido].codigo, 
            inventario[indice_mas_vendido].vendidos);

    printf("\nINVENTARIO FINAL:\n");
    printf("COD\tNOMBRE\t\tEXIST\tVENDIDOS\tALERTA\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%d\t%d", inventario[i].codigo, inventario[i].nombre, 
            inventario[i].existencia, inventario[i].vendidos);
        
        if (inventario[i].existencia <= 2) {
            printf("\t\tEXISTENCIA BAJA");
        }
        printf("\n");
    }
}
