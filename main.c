#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int codigoProducto;
	char marca[50]; // Nintendo Switch, Xbox, Playstation
	float precioEnMiles;
    int stock;
	char modelo[50];// Común, Pro, Slim
}stConsola ;

typedef struct _nodo{
	stConsola dato ;
	struct _nodo* siguiente;
}nodo;

typedef struct {

   char Nombre[50];
  int mediodepago; //1 efectivo, 2 patacones, 3 dolar ahorro
    float totalCompra;
}stCliente ;

typedef struct _nodoCliente{
	stCliente dato;
	struct nodoCliente* siguiente;
	struct nodoCliente* anterior;
}nodoCliente;

nodo * iniclista();
nodo * crearNodo(stConsola consola);
stConsola cargarConsola();
nodo * agregarAlPrincipio(nodo * lista, nodo * nuevoNodo);
nodo * agregarEnOrdenStock(nodo * lista, nodo * nuevoNodo);
void imprimirConsola(nodo * lista);
void mostrarConsolasDePrecioX(nodo * lista, float precio);
int controlarStockConsolas(nodo * lista, int marca, int modelo, int compra);
nodoCliente * agregarAlFinalCliente(nodoCliente * lista, nodoCliente * nuevoNodo);
nodoCliente * buscarUltimo(nodoCliente * lista);
nodoCliente * cargarCliente();
float valorConsola(nodo * lista, int marca, int modelo);
nodoCliente * compraCliente(nodoCliente * listaCliente, nodo * listaConsolas, int* comprasTotales);
void totalCompras(int* compras, int nuevaCompra);
nodoCliente * borrarPrimero(nodoCliente * lista);
nodoCliente * atenderClientes(nodoCliente * lista);
void imprimirCliente(nodoCliente * lista);
void mostrarClientesRecu(nodoCliente * lista);
nodo * agregarMuchasConsolas(nodo * lista);
nodoCliente * compraMuchosClientes(nodoCliente * lista, nodo *listaConsolas, int* compras);

int main()
{
    float precioConsola;

    int* comprasTotales = 0;

    nodo * listaConsolas = iniclista();

    nodoCliente * listaClientes = iniclista();

    listaConsolas = agregarMuchasConsolas(listaConsolas);

    imprimirConsola(listaConsolas);

    printf("Ingrese el precio de las consolas que desea ver:\n\n");
    scanf("%f", &precioConsola);

    mostrarConsolasDePrecioX(listaConsolas, precioConsola);

    listaClientes = compraMuchosClientes(listaClientes, listaConsolas, &comprasTotales);

    listaClientes = atenderClientes(listaClientes);

    printf("\nEl total de ventas realizadas fue de: %d\n\n", comprasTotales);

    return 0;
}

nodo * iniclista()
{
    return NULL;
}

nodo * crearNodo(stConsola consola) /// Inciso 1
{
    nodo * NN = malloc(sizeof(nodo));

    NN->dato = consola;

    NN->siguiente = NULL;

    return NN;
}

stConsola cargarConsola()
{
    stConsola consola;

    printf("\nCargue la consola:\n\n");

    printf("Codigo del producto:\n");
    scanf("%d", &consola.codigoProducto);

    printf("\nMarca:\n");
    fflush(stdin);
    gets(&consola.marca);

    printf("\nPrecio:\n");
    scanf("%f", &consola.precioEnMiles);

    printf("\nStock:\n");
    scanf("%d", &consola.stock);

    printf("\nModelo:\n");
    fflush(stdin);
    gets(&consola.modelo);

    return consola;
}

nodo * agregarAlPrincipio(nodo * lista, nodo * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }else
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }

    return lista;
}



nodo * agregarEnOrdenStock(nodo * lista, nodo * nuevoNodo)  /// Inciso 2
{
    if(lista == NULL)     // si es nulo, lista es el nuevo nodo
    {
        lista = nuevoNodo;
    }else
    {
        if(nuevoNodo->dato.stock < lista->dato.stock)        // si es menor al primero nodo de la lista lo agrega al principio
        {
            lista = agregarAlPrincipio(lista, nuevoNodo);
        }else
        {
            nodo * anterior;             //se crean dos nodos para recorrer
            nodo * aux = lista;

            while(aux != NULL && nuevoNodo->dato.stock > aux->dato.stock)   // se recorre la lista si hay nodo y si es mayor al dato de los nodos

                anterior = aux;
                aux = aux->siguiente;        //aca los va desplzando
            }

            anterior->siguiente = nuevoNodo;       //se pone al nuevo nodo entre anterior y aux
            nuevoNodo->siguiente = aux;
        }
    }

    return lista;
}

nodo * agregarMuchasConsolas(nodo * lista)
{
    char control = 's';

    while(control == 's' || control == 'S')
    {
        stConsola consola = cargarConsola();

        nodo * nuevo = crearNodo(consola);

        lista = agregarEnOrdenStock(lista, nuevo);

        printf("\nDesea seguir ingresando datos? (s / n)\n\n");
        fflush(stdin);
        scanf("%c", &control);

        system("cls");
    }
}

void imprimirConsola(nodo * lista)
{
    printf("\n----------------------\n");
    printf("Codigo del producto: %d", lista->dato.codigoProducto);
    printf("Marca: %s", lista->dato.marca);
    printf("Precio: %f", lista->dato.precioEnMiles);
    printf("Stock: %d", lista->dato.stock);
    printf("Modelo: %s", lista->dato.modelo);
    printf("----------------------\n");
}

void mostrarConsolasDePrecioX(nodo * lista, float precio) /// Inciso 3
{
    if(lista != NULL)
    {
        if(lista->dato.precioEnMiles == precio)
        {
            imprimirConsola(lista);
        }

        mostrarConsolasDePrecioX(lista->siguiente, precio);
    }
}

int seleccionarMarca()
{
    int marca;

    printf("Seleccione la marca que desee:\n\n");
    printf("\t1 - Nintendo Switch\n");
    printf("\t2 - PlayStation\n");
    printf("\t3 - Xbox\n");

    do
    {
        scanf("%d", &marca);

        if(marca != 1 && marca != 2 && marca != 3)
        {
            printf("Ingreso una opcion no valida, intente nuevamente!");
        }

    }while(marca != 1 && marca != 2 && marca != 3);

    return marca;
}

int seleccionarModelo()
{
    int modelo;

    printf("Seleccione el modelo que desee:\n\n");
    printf("\t1 - Comun\n");
    printf("\t2 - Pro\n");
    printf("\t3 - Slim\n");

    do
    {
        scanf("%d", &modelo);

        if(modelo != 1 && modelo != 2 && modelo != 3)
        {
            printf("Ingreso una opcion no valida, intente nuevamente!");
        }

    }while(modelo != 1 && modelo != 2 && modelo != 3);

    return modelo;
}

int cantidadAComprar()
{
    int compra;

    printf("\nCuantas desea comprar:\n\n");
    scanf("%d", &compra);

    return compra;
}

int controlarStockConsolas(nodo * lista, int marca, int modelo, int compra) /// Inciso 4
{
    char auxMarca[20];
    char auxModelo[20];

    if(marca == 1)
    {
        strcpy(auxMarca,"nintendo switch");

    }else if(marca == 2)
    {
        strcpy(auxMarca,"playStation");
    }else
    {
        strcpy(auxMarca, "xbox");
    }


    if(modelo == 1)
    {
        strcpy(auxModelo,"comun");

    }else if(modelo == 2)
    {
        strcpy(auxModelo,"pro");
    }else
    {
        strcpy(auxModelo,"slim");
    }

    int rta = 0;

    nodo * aux = lista;

    while(aux != NULL && strcmpi(aux->dato.marca, auxMarca) > 0 && strcmpi(aux->dato.modelo, auxModelo) > 0)
    {
        aux = aux->siguiente;
    }

    if(aux != NULL)
    {
        if(aux->dato.stock >= compra);
        {
            rta = 1;
        }
    }

    return rta;
}

void restarStock(nodo * lista, int marca, int modelo, int compra)
{
    char auxMarca[20];
    char auxModelo[20];

    nodo * aux = lista;

    if(marca == 1)
    {
        strcpy(auxMarca,"nintendo switch");

    }else if(marca == 2)
    {
        strcpy(auxMarca,"playStation");
    }else
    {
        strcpy(auxMarca, "xbox");
    }


    if(modelo == 1)
    {
        strcpy(auxModelo,"comun");

    }else if(modelo == 2)
    {
        strcpy(auxModelo,"pro");
    }else
    {
        strcpy(auxModelo,"slim");
    }

    while(aux != NULL && strcmpi(aux->dato.marca, auxMarca) > 0 && strcmpi(aux->dato.modelo, auxModelo) > 0)
    {
        aux = aux->siguiente;
    }

    if(aux != NULL)
    {
        aux->dato.stock -= compra;
    }
}

nodoCliente * agregarAlFinalCliente(nodoCliente * lista, nodoCliente * nuevoNodo)
{
    nodoCliente * ultimo = NULL;

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }else
    {
        ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
    }
}

nodoCliente * buscarUltimo(nodoCliente * lista)
{
    nodoCliente * respuesta =lista;

    if(lista != NULL)
    {
        while(respuesta->siguiente != NULL)
        {
            respuesta = respuesta->siguiente;
        }
    }

    return respuesta;
}

nodoCliente * cargarCliente()
{
    nodoCliente * nuevo = malloc(sizeof(nodoCliente));

    int opcion;

    printf("\nIngrese su nombre:\n\n");
    fflush(stdin);
    gets(&nuevo->dato.Nombre);

    printf("Seleccione su medio de pago:\n\n");
    printf("\t1 - Efectivo\n");
    printf("\t2 - Patacones\n");
    printf("\t3 - Dolar ahorro\n\n");

    do
    {
        scanf("%d", &opcion);

        if(opcion != 1 && opcion != 2 && opcion != 3)
        {
            printf("\nIngreso una opcion no valida, intente nuevamente!");
        }
    }while(opcion != 1 && opcion != 2 && opcion != 3);

    nuevo->dato.mediodepago = opcion;

    nuevo->anterior = NULL;

    nuevo->siguiente = NULL;

    return nuevo;
}

float valorConsola(nodo * lista, int marca, int modelo)
{
    char auxMarca[20];
    char auxModelo[20];

    float valor = 0;

    nodo * aux = lista;

    if(marca == 1)
    {
        strcpy(auxMarca,"nintendo switch");

    }else if(marca == 2)
    {
        strcpy(auxMarca,"playStation");
    }else
    {
        strcpy(auxMarca, "xbox");
    }


    if(modelo == 1)
    {
        strcpy(auxModelo,"comun");

    }else if(modelo == 2)
    {
        strcpy(auxModelo,"pro");
    }else
    {
        strcpy(auxModelo,"slim");
    }

    while(aux != NULL && strcmpi(aux->dato.marca, auxMarca) > 0 && strcmpi(aux->dato.modelo, auxModelo) > 0)
    {
        aux = aux->siguiente;
    }

    if(aux != NULL)
    {
        valor = aux->dato.precioEnMiles;
    }

    return valor;
}

nodoCliente * compraMuchosClientes(nodoCliente * lista, nodo *listaConsolas, int* compras)
{
    char control = 's';

    while(control == 's' && control == 'S')
    {
        lista = compraCliente(lista, listaConsolas, compras);

        printf("\nOtro cliente comprando? (s / n)\n\n");
        fflush(stdin);
        scanf("%c", &control);

        system("cls");
    }
}

nodoCliente * compraCliente(nodoCliente * listaCliente, nodo * listaConsolas, int* comprasTotales) /// inciso 5
{
    nodoCliente * cliente = cargarCliente();

    int marca, modelo, rta = 0, compra;

    while(rta == 0)
    {
        compra = cantidadAComprar();

        marca = seleccionarMarca();

        modelo =seleccionarModelo();

        rta = controlarStockConsolas(listaConsolas, marca, modelo, compra);

        if(rta == 1)
        {
            restarStock(listaConsolas, marca, modelo, compra);
            cliente->dato.totalCompra += valorConsola(listaConsolas, marca, modelo) * compra;
            totalCompras(comprasTotales, compra);

        }else
        {
            printf("\nNo queda esa cantidad de stock, intente nuevamente!\n\n");
        }
    }

    listaCliente = agregarAlFinalCliente(listaCliente, cliente);

    return listaCliente;
}

void totalCompras(int* compras, int nuevaCompra) /// Inciso 6
{
    *compras += nuevaCompra;
}

nodoCliente * borrarPrimero(nodoCliente * lista)
{
    nodoCliente * aux = lista;

    if(lista != NULL)
    {
        lista = lista->siguiente;

        if(lista != NULL)
        {
            lista->anterior = NULL;
        }

        free(aux);
    }

    return lista;
}

nodoCliente * atenderClientes(nodoCliente * lista) /// inciso 7
{
    printf("Clientes para atender:\n\n");
    mostrarClientesRecu(lista);

    while(lista != NULL)
    {
        lista = borrarPrimero(lista);
    }

    return lista;
}

void imprimirCliente(nodoCliente * lista)
{
    printf("\n----------------------\n");
    printf("Nombre: %s", lista->dato.Nombre);
    printf("Medio de pago:");
    if(lista->dato.mediodepago == 1)
    {
        printf("  Efectivo");

    }else if(lista->dato.mediodepago == 2)
    {
        printf("  Patacones");

    }else
    {
        printf("  Dolar ahorro");
    }
    printf("Total de compra: %f", lista->dato.totalCompra);
    printf("----------------------\n");
}

void mostrarClientesRecu(nodoCliente * lista) /// inciso 8
{
    if(lista != NULL)
    {
        mostrarClientesRecu(lista->siguiente);
        imprimirCliente(lista);
    }
}
