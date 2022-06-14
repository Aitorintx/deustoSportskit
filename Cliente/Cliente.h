#ifndef CLIENTE_H_
#define CLIENTE_H_

class Cliente
{
private:
    char* nombre;
    int id;
    int tel;
    char* correo;
    char* dir;
    char* contra;
public:
    Cliente(const char* nombre, int id, int tel, const char* correo, const char* dir, const char* contra);
    Cliente(const Cliente& c);
    virtual ~Cliente();


char* getNombre() const;
int getId() const;
int getTel() const;
char* getCorreo() const;
char* getDir() const;
char* getContra() const;

virtual void calculoPrecioFinal(int precio);


};


#endif