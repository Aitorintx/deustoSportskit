#include "ClienteVip.h"
#include <iostream>

using namespace std;

int main()
{
	Cliente* c=new Cliente("Aitor",1,633091217,"aintxaustim@opendeusto.es","hola","12345");
    ClienteVip* cv=new ClienteVip("Sara",2,722,"sara.hernandez@opendeusto.es","hola","234","standar");

    c->calculoPrecioFinal(200);
    cv->calculoPrecioFinal(500);
    
    delete cv;
    delete c;
    

    return 0;
}
