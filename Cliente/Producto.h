#ifndef PRODUCTO_H_
#define PRODUCTO_H_

class Producto{
    private:
    int id;
    char* nombre;
    char* tipo;
    float precio;
    int stock;
    int talla;
    public:
    Producto(int id, const char* nombre, const char* tipo, float precio,int stock, int talla);
    Producto(const Producto& p);
    ~Producto();

    int getId() const;
    char* getNombre() const;
    char* getTipo() const;
    float getPrecio() const;
    int getStock() const;
    int getTalla() const;
    void setId(int id);
    void setNombre(char* nombre);
    void setTipo(char* tipo);
    void setPrecio(float precio);
    void setStock(int stock);
    void setTalla(int talla);

   void static imprimirProductos(Producto** listaProductos, int num);

};

#endif