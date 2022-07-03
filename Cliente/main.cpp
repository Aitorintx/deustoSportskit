#include "ClienteVip.h"
#include "Compra.h"
#include "LoggerCliente.h"
#include <iostream>
#include <winsock2.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

WSADATA wsaData;
SOCKET s;
struct sockaddr_in server;
char sendBuff[512], recvBuff[512];
using namespace std;

int numClientes(){
    int numeroClientes;
    
    strcpy(sendBuff, "Numero de Clientes");
	send(s, sendBuff, sizeof(sendBuff), 0);
    recv(s, recvBuff, sizeof(recvBuff), 0);
	numeroClientes = atoi(recvBuff);
    return numeroClientes;
}
int numClientesVIP(){
    int numeroClientesVip;
    strcpy(sendBuff, "Numero de Clientes VIP");
	send(s, sendBuff, sizeof(sendBuff), 0);
    recv(s, recvBuff, sizeof(recvBuff), 0);
	numeroClientesVip = atoi(recvBuff);
	return numeroClientesVip;
}
Cliente** rellenarListaClientes(){
    int numeroClientes=numClientes();
    int numeroClientesVip=numClientesVIP();
	int num=numeroClientes + numeroClientesVip;
    Cliente** listaClientes=new Cliente*[num];
	Cliente* c;
	ClienteVip* cv;
	int idCliente;
	int telefono;
	char* nombre=new char[20];
	char* correo=new char[20];
	char* dir = new char[20];
	char* contra=new char[20];
    if(numeroClientes>0){
        for (int i = 0; i < numeroClientes; i++)
        {
            strcpy(sendBuff, "Quiero el ID de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			int idCliente;
			idCliente = atoi(recvBuff);

            strcpy(sendBuff, "Quiero Los Nombres de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

	
			strcpy(nombre, recvBuff);

            strcpy(sendBuff, "Quiero el telefono de los clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			telefono = atoi(recvBuff);

            strcpy(sendBuff, "Quiero los CORREOS de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			strcpy(correo, recvBuff);


            strcpy(sendBuff, "Quiero las direcciones de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

	
			strcpy(dir, recvBuff);

            strcpy(sendBuff, "Quiero Las Contraseñas de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			strcpy(contra, recvBuff);
            c=new Cliente(nombre,idCliente,telefono,correo,dir,contra);
            listaClientes[i]=c;
			i++;
			cout<<i<<".Cliente IMPORTADO:"<<endl;
			cout<<"----------------------------------------"<<endl;
			cout<<"ID: "<<idCliente<< " NOMBRE: "<<nombre<<"("<<telefono<<") CORREO: "<<correo<<" DIRECCION: "<<dir<<"\n"<<endl;
			i--;
        }
    }

    if(numeroClientesVip>0){
            for (int i = numeroClientes; i < num; i++)
        {
            strcpy(sendBuff, "Quiero el ID de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			idCliente = atoi(recvBuff);

            strcpy(sendBuff, "Quiero Los Nombres de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			strcpy(nombre, recvBuff);

            strcpy(sendBuff, "Quiero el telefono de los clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
		

			
			telefono = atoi(recvBuff);

            strcpy(sendBuff, "Quiero los CORREOS de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			strcpy(correo, recvBuff);


            strcpy(sendBuff, "Quiero las direcciones de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			strcpy(dir, recvBuff);

            strcpy(sendBuff, "Quiero Las Contraseñas de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			strcpy(contra, recvBuff);

            strcpy(sendBuff, "Quiero Los Niveles de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			char* nivel;
			nivel = new char[20];
			strcpy(nivel, recvBuff);
            cv=new ClienteVip(nombre,idCliente,telefono,correo,dir,contra,nivel);
			listaClientes[i]=cv;
			i++;
			cout<<i<<".Cliente IMPORTADO:"<<endl;
			cout<<"----------------------------------------"<<endl;
			cout<<"ID: "<<idCliente<< " NOMBRE: "<<nombre<<"("<<telefono<<") CORREO: "<<correo<<" DIRECCION: "<<dir<<" NIVEL: "<<nivel<<"\n"<<endl;
            i--;
        }
    }
    return listaClientes;
}
int numProductos(){
    int numeroProductos;

    strcpy(sendBuff, "Numero de Productos");
	send(s, sendBuff, sizeof(sendBuff), 0);
    recv(s, recvBuff, sizeof(recvBuff), 0);
	numeroProductos = atol(recvBuff);
    return numeroProductos;
}

Producto** rellenarListaProductos(){
    int numeroProductos=numProductos();
    Producto** listaProductos=new Producto*[numeroProductos];
	Producto* p;
	int idProd;
	char* nombre=new char[20];
	char* tipo=new char[20];
	float precio;
	int stock;
	int talla;

    if(numeroProductos>0){
        for (int i = 0; i < numeroProductos; i++)
        {
            strcpy(sendBuff, "Quiero el ID de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			idProd = atoi(recvBuff);

            strcpy(sendBuff, "Quiero el Nombre de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

            
            strcpy(nombre,recvBuff);

            strcpy(sendBuff, "Quiero el Tipo de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

            
            strcpy(tipo,recvBuff);

            strcpy(sendBuff, "Quiero el precio de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			precio = atof(recvBuff);

            strcpy(sendBuff, "Quiero el Stock de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			stock = atoi(recvBuff);

            strcpy(sendBuff, "Quiero la talla de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			
			talla = atoi(recvBuff);

            p=new Producto(idProd,nombre,tipo,precio,stock,talla);
            listaProductos[i]=p;
			i++;
			cout<<i<<".Producto Importado:"<<endl;
			cout<<"-------------------------------------"<<endl;
			cout<<"ID: "<<idProd<<" NOMBRE: "<<nombre<<"("<<tipo<<") PRECIO:"<<precio<<" STOCK: "<<stock<<" TALLA: "<<talla<<"\n"<<endl;
			i--;
        }
        
    }
    return listaProductos;
}

int numCompras(){
    int numeroCompras;
    strcpy(sendBuff, "Numero de Compras");
	send(s, sendBuff, sizeof(sendBuff), 0);
    recv(s, recvBuff, sizeof(recvBuff), 0);
	
	numeroCompras = atol(recvBuff);
    return numeroCompras;
}

int numComprasReal(){
	strcpy(sendBuff, "Quiero el numero Real de Compras");
	send(s, sendBuff, sizeof(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);
	

	char* nRC;
	nRC = new char[20];
	int nRealC;
	strcpy(nRC, recvBuff);
	nRealC = atoi(nRC);
	return nRealC;
}

void realizarCompra(Cliente** listaClientes, Cliente* cliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC, Producto** prods, int tamanyo){
    int res;
    char* res1=new char[100];
    strcpy(sendBuff, "Quiero el MAX ID de la Compra");
	send(s, sendBuff, sizeof(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);
	

	int idMAXC;
	idMAXC = atoi(recvBuff);
	int id=idMAXC;
	id++;
    Producto** ps;
	Compra* c;
    Producto::imprimirProductos(listaProductos,numP);
    cout<<"Inserta el ID del producto que desees comprar:";
    cin>>res;
    for (int i = 0; i < numP; i++)
    {
        if (listaProductos[i]->getId()==res)
        {
            tamanyo++;
            if(tamanyo==1){
                
                prods[tamanyo-1]->setId(listaProductos[i]->getId());
                prods[tamanyo-1]->setNombre(listaProductos[i]->getNombre());
                prods[tamanyo-1]->setTipo(listaProductos[i]->getTipo());
                prods[tamanyo-1]->setPrecio(listaProductos[i]->getPrecio());
                prods[tamanyo-1]->setStock(listaProductos[i]->getStock());
                prods[tamanyo-1]->setTalla(listaProductos[i]->getTalla());
            }else{
                ps=new Producto*[tamanyo];
                for (int j = 0; j < tamanyo-1; j++)
                {
                    ps[j]=prods[j];
                }
                ps[tamanyo-1]=listaProductos[i]; 
            }
            
        }
    }
    if(tamanyo==0){
        cout<<"Compra fallida"<<endl;
        
    }else{
        do{
            cout<<"Deseas anyadir un nuevo producto a la compra? S/N";
            cin>>res1;
        }while(strcmp(res1,"S")!=0 & strcmp(res1,"N")!=0);
        
        if(strcmp(res1,"S")==0 & tamanyo==1){
            realizarCompra(listaClientes,cliente, num, listaProductos, numP, listaCompras, numC, prods, tamanyo);
        }else if(strcmp(res1,"S")==0 & tamanyo!=1){
            realizarCompra(listaClientes,cliente, num, listaProductos, numP, listaCompras, numC, ps, tamanyo);
        }else if(strcmp(res1,"N")==0 & tamanyo==1){
            numC++;
            Compra** compras=new Compra*[numC];
            for (int i = 0; i < numC-1; i++)
            {
                compras[i]=listaCompras[i];
            }
            
            
            c=new Compra(id,prods,cliente,tamanyo);
            compras[numC-1]=c;
            cout<<"Compra realizada con exito. Muchas gracias!"<<endl;
            loggerTxt("Se ha realizado una compra", cliente->getId());
			char* codigo1=new char[5];
			char* codigo2=new char[5];
			char* codigo3=new char[5];
			char* codigo4=new char[15];
			for (int i = 0; i < tamanyo; i++)
			{
				sprintf(codigo1, "Com%i",id);
				strcpy(sendBuff, codigo1);
				send(s, sendBuff, sizeof(sendBuff), 0);	
				
				sprintf(codigo2, "Pro%i",res);
				strcpy(sendBuff, codigo2);
				send(s, sendBuff, sizeof(sendBuff), 0);	

				sprintf(codigo3, "Cli%i",c->getCliente()->getId());
				strcpy(sendBuff, codigo3);
				send(s, sendBuff, sizeof(sendBuff), 0);	

				sprintf(codigo4, "Pre%f",c->getProducto(i)->getPrecio());
				strcpy(sendBuff, codigo4);
				send(s, sendBuff, sizeof(sendBuff), 0);	
				
			}
            Compra::imprimirCompras(listaClientes,cliente,num,listaProductos, numP, compras, numC);
            
        }else{
            numC++;
            Compra** compras=new Compra*[numC];
            for (int i = 0; i < numC-1; i++)
            {
                compras[i]=listaCompras[i];
            }
            
            
            c=new Compra(id,ps,cliente,tamanyo);
            compras[numC-1]=c;
            cout<<"Compra realizada con exito. Muchas gracias!"<<endl;
            loggerTxt("Se ha realizado una compra", cliente->getId());
			char* codigo1=new char[5];
			char* codigo2=new char[5];
			char* codigo3=new char[5];
			char* codigo4=new char[15];
			for (int i = 0; i < tamanyo; i++)
			{
				sprintf(codigo1, "Com%i",id);
				strcpy(sendBuff, codigo1);
				send(s, sendBuff, sizeof(sendBuff), 0);	
				
				sprintf(codigo2, "Pro%i",c->getProducto(i)->getId());
				strcpy(sendBuff, codigo2);
				send(s, sendBuff, sizeof(sendBuff), 0);	

				sprintf(codigo3, "Cli%i",c->getCliente()->getId());
				strcpy(sendBuff, codigo3);
				send(s, sendBuff, sizeof(sendBuff), 0);	

				sprintf(codigo4, "Pre%f",c->getProducto(i)->getPrecio());
				strcpy(sendBuff, codigo4);
				send(s, sendBuff, sizeof(sendBuff), 0);	
				
			}
			Compra::imprimirCompras(listaClientes,cliente,num,listaProductos, numP, compras, numC);
				
        }
    }
    
	
	
}

void pantallaInicio(Cliente** listaClientes, Cliente* cliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC){
    int opcion;
    char* res=new char[100];
    char* res1=new char[2];
    do{
    cout<<"Sportskit"<<endl;
    cout<<"---------"<<endl;
    cout<<"1.Ver todos los productos de la tienda."<<endl;
    cout<<"2.Hacer una nueva compra."<<endl;
    cout<<"3.Ver las compras hechas."<<endl;
    cout<<"0.Salir."<<endl;
    cout<<"Que desea hacer?";
    cin>> opcion;
    }while (0>opcion | opcion>3); 
    
    if(opcion==0){
        do
        {
            cout<<"Estas seguro que quieres abandonar? S/N"<<endl;
            cin>>res;
        } while (strcmp(res,"S")!=0 & strcmp(res,"N")!=0);
        
        if(strcmp(res,"S")==0){
            cout<<"Hasta la proxima :)"<<endl;
        }else{
            pantallaInicio(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC);
        }
        
    }else if(opcion==1){
        Producto::imprimirProductos(listaProductos,numP);
        do{
            cout<<"Si desea volver a la pantalla de inicio pulse 0: ";
            cin>>res1;
        }while(strcmp(res1,"0")!=0);
        if (strcmp(res1,"0")==0)
        {
            pantallaInicio(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC);
        }
        
    }else if(opcion==2){
        Producto* p=new Producto(0,"","",0,0,0);
        Producto* prods[]={p};
        int tamanyo=0;
        realizarCompra(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC, prods, tamanyo);
    }else{
        Compra::imprimirCompras(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC);
    }
    
}

void registrarCliente(Cliente** listaClientes,int num, Producto** productos, int numP, Compra** compras, int numC){
    int id=listaClientes[num-1]->getId();
    id++;
    char* nombre=new char[100];
    int tel;  
    char* correo=new char[100];
    char* dir=new char[200];
    char* contra=new char[100];
    char* contraRep=new char[100];
    char* aceptar=new char[2];
    char* vip=new char[100];
	char* codigo1 = new char[6];
	char* codigo2 = new char[6];
	char* codigo3=new char[6];
	char* codigo4=new char[6];
	char* codigo5=new char[15];
	char* codigo6=new char[10];
    cout<<"Introduzca Nombre de Usuario:";
    cin>>nombre;
    cout<<"Introduzca Telefono:";
    cin>>tel;
    cout<<"Introduzca Correo:";
    cin>>correo;
    cout<<"Introduzca Direccion:";
    cin>>dir;
    do{
        cout<<"AVISO! Mientras no sean iguales no podrás seguir!"<<endl;
        cout<<"Introduzca Contrasena:";
        cin>>contra;
        cout<<"Repita Contrasena:";
        cin>>contraRep;
    }while(strcmp(contra,contraRep)!=0);

    do{
        cout<<"Deseas hacerte VIP? S/N:";
        cin>>aceptar;
    }while(strcmp(aceptar,"S")!=0 & strcmp(aceptar,"N")!=0);

    if(strcmp(aceptar,"N")==0){
        Cliente* c=new Cliente(nombre, id, tel, correo, dir, contra);
        num++;
        Cliente** listaCliente=new Cliente*[num];
        for (int i = 0; i < num-1; i++)
        {
            listaCliente[i]=listaClientes[i];
        }
        
        listaCliente[num-1]=c;
        cout<<"Registro Completado con Exito"<<endl;
        cout<<"Muchas gracias por contar con nosotros!"<<endl;
        pantallaInicio(listaClientes,c,num,productos,numP,compras,numC);
		
	
		strcpy(codigo1, "Nombre");
		strcat(codigo1, nombre);
		strcpy(sendBuff, codigo1);
		send(s, sendBuff, sizeof(sendBuff), 0);

		
		sprintf(codigo5, "Telefo%i",tel);
		strcpy(sendBuff, codigo5);
		send(s, sendBuff, sizeof(sendBuff), 0);	
	
		strcpy(codigo3, "Correo");
		strcat(codigo3, correo);
		strcpy(sendBuff, codigo3);
		send(s, sendBuff, sizeof(sendBuff), 0);

		strcpy(codigo2, "Direcc");
		strcat(codigo2, dir);
		strcpy(sendBuff, codigo2);
		send(s, sendBuff, sizeof(sendBuff), 0);		


		strcpy(codigo4, "Contra");
		strcat(codigo4, contra);
		strcpy(sendBuff, codigo4);
		send(s, sendBuff, sizeof(sendBuff), 0);	
		
    }else if (strcmp(aceptar,"S")==0){
        do{
            cout<<"AVISO! Debera de escribir los nombres tal y como los pone ahí, en caso contrario no podra seguir con el regisro!"<<endl;
            cout<<"Niveles de cliente vip\n-standar(Descuento del 5%)\n-plus(Descuento del 15%)\n Que nivel VIP desea escoger?"<<endl;
            cin>>vip;
        }while(strcmp(vip,"standar")!=0 & strcmp(vip,"plus")!=0);
        
        ClienteVip* cv= new ClienteVip(nombre, id, tel, correo, dir, contra, vip);
        num++;
        Cliente** listaCliente=new Cliente*[num];
        for (int i = 0; i < num-1; i++)
        {
            listaCliente[i]=listaClientes[i];
        }
        listaCliente[num-1]=cv;
        cout<<"Registro Completado con Exito"<<endl;
        cout<<"Muchas gracias por contar con nosotros!"<<endl;
        pantallaInicio(listaClientes,cv,num,productos,numP,compras,numC);
		
	
		strcpy(codigo1, "NomV");
		strcat(codigo1, nombre);
		strcpy(sendBuff, codigo1);
		send(s, sendBuff, sizeof(sendBuff), 0);
	
		sprintf(codigo5, "TelV%i",tel);
		strcpy(sendBuff, codigo5);
		send(s, sendBuff, sizeof(sendBuff), 0);	

		strcpy(codigo3, "CorV");
		strcat(codigo3, correo);
		strcpy(sendBuff, codigo3);
		send(s, sendBuff, sizeof(sendBuff), 0);	

		strcpy(codigo2, "DirV");
		strcat(codigo2, dir);
		strcpy(sendBuff, codigo2);
		send(s, sendBuff, sizeof(sendBuff), 0);		

		

		strcpy(codigo4, "ConV");
		strcat(codigo4, contra);
		strcpy(sendBuff, codigo4);
		send(s, sendBuff, sizeof(sendBuff), 0);	

		strcpy(codigo6, "NivV");
		strcat(codigo6, vip);
		strcpy(sendBuff, codigo6);
		send(s, sendBuff, sizeof(sendBuff), 0);

			
        
    }

}

void iniciarSesion(Cliente** listaClientes, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC){
    char* contrasena= new char[100];
    char* nombre= new char[100];
    int numero=0;
    
    
    cout<<"Introduce el nombre de usuario:";
    cin>>nombre;
    cout << endl;
    cout<<"Introduce la contrasena:";
    cin>>contrasena;
    cout << endl;
    
    do{
        char* nom=listaClientes[numero]->getNombre();
        char* con= listaClientes[numero]->getContra();
        
        if(strcmp(contrasena,con)==0 & strcmp(nombre,nom)==0){
            cout<<"Encantado de tenerte aqui otra vez "<< nom << "!"<<endl;
            Cliente* c= listaClientes[numero];
            pantallaInicio(listaClientes,c,num,listaProductos,numP,listaCompras,numC);
            numero=0;
            break;
        }
        numero++;

    }
    while(numero<num);
    if(numero==num){
        cout<<"El nombre de usuario o la contrasena son incorrectas. Por favor intentelo de nuevo"<<endl;
        cout<<"----------------------------------------------------------------------------------"<<endl;
        iniciarSesion(listaClientes,num, listaProductos, numP, listaCompras, numC);
    }
    
}

void iniciarCliente(Cliente** listaClientes, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC){
    int opcion;
    cout<<"Bienvenido a DeustoSportskit"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"1. Iniciar Sesión"<<endl;
    cout<<"2. Registrarse"<<endl;
    cout<<"0.Abandonar"<<endl;
    cout<<"¿Qué desea hacer?: ";
    cin>>opcion;
    while(0>opcion | opcion>2){
        cout<<"La opcion introducida no se puede aceptar"<<endl;
        cout<<"-----------------------------------------"<<endl;
        cout<<"1. Iniciar Sesión"<<endl;
        cout<<"2. Registrarse"<<endl;
        cout<<"0.Abandonar"<<endl;
        cout<<"¿Qué desea hacer?: ";
        cin>>opcion;
    };
    if(opcion==0){
        cout<<"Esperemos que vuelvas pronto :)"<<endl;
    }else if(opcion==1){
        iniciarSesion(listaClientes, num, listaProductos, numP, listaCompras, numC);
    }else{
        registrarCliente(listaClientes, num, listaProductos, numP, listaCompras, numC);
    }
}







int main() {

	cout<<"Initialising Winsock..."<<endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout<<"Failed. Error Code :"<< WSAGetLastError()<<endl;
		return -1;
	}

	cout<<"Initialised."<<endl;

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout<<"Could not create socket :"<<WSAGetLastError()<<endl;
		WSACleanup();
		return -1;
	}

	cout<<"Socket created."<<endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		cout<<"Connection error: "<< WSAGetLastError()<<endl;
		closesocket(s);
		WSACleanup();
		return -1;
	}

	cout<<"Connection stablished with: "<< inet_ntoa(server.sin_addr)<<
			ntohs(server.sin_port)<< endl;
            
    //Recibir y mandar info

    Cliente** listaClientes = rellenarListaClientes();
    Producto** listaProductos = rellenarListaProductos();
	
	

    int numCl = numClientes() + numClientesVIP();
    int numP = numProductos();
    int numC = numComprasReal();
	int numeroCompras=numCompras();
	Compra** listaCompras;
	int contador3=0;
    
	int listaFalsa[3][numeroCompras];
    if(numeroCompras>0){
        for (int i = 0; i < numeroCompras; i++)
        {
            strcpy(sendBuff, "Quiero el ID de las Compras");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			int idCompra;
			idCompra = atoi(recvBuff);

			strcpy(sendBuff, "Quiero el ID del Producto");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			


			int idCompraP;
			idCompraP = atoi(recvBuff);

			strcpy(sendBuff, "Quiero el ID del Comprador");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			

			int idCompraC;
			idCompraC = atoi(recvBuff);
			
            
			listaFalsa[0][i]=idCompra;
			listaFalsa[1][i]=idCompraP;
			listaFalsa[2][i]=idCompraC;
        }
		strcpy(sendBuff, "Quiero el MAX ID de la Compra");
		send(s, sendBuff, sizeof(sendBuff), 0);
		recv(s, recvBuff, sizeof(recvBuff), 0);
		
		 

		int idMAXC;
		idMAXC = atoi(recvBuff);


		
		int nRealC=numComprasReal();
		
		int contador1=0;
		int id;
		Cliente* c;
	 	listaCompras=new Compra*[nRealC];
		
		
		for (int i = 1; i <= idMAXC; i++)
		{
			int contador=0;
			for (int j = 0; j < numeroCompras; j++)
			{
				if(listaFalsa[0][j]==i)
				{
					contador++;
				}
			}
			
			Producto** listaProds=new Producto*[contador];
			int j=0;
			
			for (int k = 0; k < numeroCompras; k++)
			{
				if(listaFalsa[0][k]==i){
					for (int l = 0; l < numP; l++)
					{
						if(listaFalsa[1][k]==listaProductos[l]->getId()){

							listaProds[j]=listaProductos[l];
							j++;
						}
					}
				}
			
			}
			contador3+=contador;
			
			for(int l=0; l<numCl;l++){
					if(listaFalsa[2][contador3-1]==listaClientes[l]->getId()){
						c=listaClientes[l];
					}
				}
				
				
			
			
			Compra* compra=new Compra(i,listaProds,c,contador);
			listaCompras[contador1]=compra;
			contador1++;
			cout<<contador1<<".COMPRA IMPORTADA:"<<endl;
			cout<<"--------------------------------------------"<<endl;
			cout<<"ID: "<<i<<" LISTA DE PRODUCTOS[";
			for(int z=0;z<contador;z++){
				if(z==contador-1){
					cout<<listaProds[z]->getNombre();
				}else{
					cout<<listaProds[z]->getNombre()<<", ";
				}
				
			}
			cout<<"] CLIENTE: "<<c->getNombre()<< "\n"<<endl;
		}
	
	}

	



    
	iniciarCliente(listaClientes, numCl, listaProductos, numP, listaCompras, numC);
	
	
	
    strcpy(sendBuff, "Terminar");
	send(s, sendBuff, sizeof(sendBuff), 0);



	// CLOSING the socket and cleaning Winsock...
	closesocket(s);	
	WSACleanup();

	exit(1);

    
    
    

    return 0;
}
