class Linea {
private:
    struct Nodo {
        Nodo *izquierda, *derecha, *padre;
        std::string texto;
        unsigned int peso;
    };
    Nodo* raiz;
    int w;
    unsigned int largo_tot;

    void insertarR(Nodo* n, int pos, char c) { //necesito de alguna forma pasar el árbol base pa hacer funcar todo
        if (!n) return;
        if (!n->izquierda && !n->derecha) { //por esa misma wea implemento el public mediante funciones auxiliares
            n->texto.insert(pos, 1, c); //en private y luego las llamo, para que no pida mas que lo que agregará 
            n->peso = n->texto.size(); //luego el usuario 

            if (n->texto.size() > (unsigned)w) {//de nuevo, uso unsigned como buena practica pq es un tamaño
                int mid = n->texto.size() / 2;//misma forma implementada en el armado del árbol
                std::string s_izq = n->texto.substr(0, mid);//luego creo 2 weas izq y
                std::string s_der = n->texto.substr(mid);//der como string 
                n->izquierda = new Nodo{nullptr, nullptr, n, s_izq, (unsigned int)s_izq.size()};//y finalmente como hoja izq
                n->derecha = new Nodo{nullptr, nullptr, n, s_der, (unsigned int)s_der.size()};//y der
                n->texto = "";//asigno el texto del nodo interior
                n->peso = mid;//se van actualizando los pesos mientras se ejecuta
            }
            return;
        }
        if (pos <= (int)n->peso) {//se usa el mismo sistema de peso de subarbol para recorrer.
            n->peso++; 
            insertarR(n->izquierda, pos, c);
        }//acá simplemente tmb se llama recursivamente y actualiza su peso   
        else {
            insertarR(n->derecha, pos - n->peso, c);//esto se hace para obtener la pos dentro de la hoja
        }//que es diferente de la pos en el arbol completo
    }

    void eliminarR(Nodo* n, int pos) {
        if (!n) return; //esta funcion es LITERALMENTE la misma lógica de insertarR, pero reversa
        if (!n->izquierda && !n->derecha) {//verifica si es hoja
            if (pos < n->texto.size()) {
                n->texto.erase(pos, 1);//borra la wea, para finalmente dejar su peso en 0
                n->peso = n->texto.size();//actualiza el peso, revisandolo directamente
            }
            return;
        }
        if (pos < (int)n->peso) {//esto es para actualizar el peso de los nodos internos
            n->peso--;//mientras se va armando la wea.
            eliminarR(n->izquierda, pos);//llamada recursiva a izq
        } else {//el peso en este caso no cambia, pero si va desplazandose si corresponde
            eliminarR(n->derecha, pos - n->peso);//llamada a derecha para moverse.
        }
    }

    void printR(Nodo* n) {//funcion auxiliar de print (para otorgarle el arbol mediante un puntero)
        if (!n) return;//manejo de errores
        if (!n->izquierda && !n->derecha) {//si es hoja
            std::cout << n->texto;//printea
        } else {//si no
            printR(n->izquierda);//llamada recursiva izq
            printR(n->derecha);//llamada recursiva der
        }
    }

    unsigned int invertirR(Nodo* n) { //otra wea de funcion auxiliar me quiero matar ctm
        if (!n) return 0; //validacion para que no haya error (asi no se aweona el IDE)

        if (!n->izquierda && !n->derecha) {//esto es pa cachar que sea hoja la wea
            int i = 0;//esto es como el metodo de los palíndromos, pero en lugar de comparar texto
            int j = n->texto.size() - 1;//lo damos vuelta con el ciclo y la funcion swap
            while (i < j) {//literalmente recorre desde izq a derecha y de derecha a izquierda, swapeando
                std::swap(n->texto[i++], n->texto[j--]); //y cambiando el valor
                }
            return n->peso;//este es el peso de la hoja, se le retorna a la instancia que lo haya llamado lol
            }

        unsigned int l_izq = invertirR(n->izquierda);//se llama recursivamente en izq
        unsigned int l_der = invertirR(n->derecha); //y der
        Nodo* aux = n->izquierda;//auxiliar pq tenemos que copiar otra wea pa poder invertirlo
        n->izquierda = n->derecha;//asi no perdemos informacion we:V
        n->derecha = aux;//derecha se copia a aux
        n->peso = l_der;//intercambia los pesos tmb, como hice esta wea un int que retorna los pesos, funca
        return l_izq + l_der;
        }
    Nodo* Build(std::string s, Nodo* figurapaterna=nullptr) {//creo esa wea para asignar al instante padres pa cada wea
        Nodo* n = new Nodo();         //en este caso es nullptr pq es la raíz
        n->padre = figurapaterna;//en el caso de la primera ejecucion da nullptr, para el resto, su nodo padre
        if (s.size() <= (unsigned)w){//manejo de errores pq tamaño es siempre positivo o 0
            n->texto = s;
            n->izquierda = nullptr;//todo esto inicializa un nuevo nodo hoja
            n->derecha = nullptr;//al ser un struct inicio wea a wea
            n->peso = s.size();
            return n;
        }
        int mid = s.size() / 2; //esto es para dividir, funciona sea par o impar y es recursivo
        n->izquierda = Build(s.substr(0, mid), n);//con esto creo recursivamente divisiones hasta que para cada hoja
        n->derecha = Build(s.substr(mid), n);    //su peso sea menor o igual a w. 
        n->texto = "";//crea valores vacíos para cada interno en texto
        n->peso = mid;//eso sirve pq se trunca la operación creo
        return n;//jajalol
    }

    void Free(Nodo* n) { //libera en post orden la memoria del arbol
        if (!n) return; //esto se logra implementando recursividad priorizando el recorrer cada
        Free(n->izquierda); //sub arbol antes de eliminar su correspondiente padre, sucesivamente
        Free(n->derecha); //desde la raíz a la hoja pero eliminando inversamente.
        delete n; //se elimina después de llamarse de forma recursiva para cada nodo existente.
        //freddyturbina me cagaste la vida
    }
public:
    Linea(std::string str, int w) {
        this->w = w;//esta wea es como decir Linea->w
        this->raiz = Build(str);//funca con esta wea de instancia basicamente
        this->largo_tot=str.size();//se el tamaño total al crearse es el size del texto.
    }
    ~Linea() {
        Free(raiz);
        raiz = nullptr; //pa q no me putees por leaks de memoria lol
    }

    void insertar(int posicion, char caracter) {
        if (posicion < 0 || posicion > (int)largo_tot) return;
        if (!raiz){//por si llegas a crear un arbol en el momento de insercion (insertando a uno vacío)
            std::string s(1, caracter);//haces el string y buildeas la wea
            raiz = Build(s);//llamando al auxiliar constructor
        } else {
            insertarR(raiz, posicion, caracter);//si no, llamas al auxiliar insertar y se ejecuta todo
        }
        largo_tot++;//y se actualiza el largo total de todo finalmetne
    }

    void eliminar(int posicion){
        if (posicion < 0 || posicion >= (int)largo_tot || !raiz) {//manejo basico de errores
            return; 
        }
        eliminarR(this->raiz, posicion);//llamo a la funcion auxiliar
        largo_tot--;//y actualizo el largo total
    }

    void concatenar(Linea* linea) {
        if (!linea || !linea->raiz) return;//verificaciones de validez
        if (!this->raiz) {//si el arbol base llega a estar vacío, crea uno nuevo
            this->raiz = linea->raiz;//edita la instancia y su raiz
            this->largo_tot = linea->largo_tot;//y tmb el largo
    }
        else {
            Nodo* n = new Nodo();//si no, pasa a hacer un nuevo nodo
            n->texto = "";
            n->padre = nullptr;//como es la nueva raiz no tiene padre
            n->peso = this->largo_tot;//su peso es el del subarbol izq en este caso
            n->izquierda = this->raiz;//y su hijo izq, es la vieja raíz
            n->derecha = linea->raiz;//su hijo der es la raiz der
            this->raiz->padre = n;//se le da padre al arbol original
            linea->raiz->padre = n;//el padre del nuevo arbol es tmb la nueva raiz
            this->raiz = n;//ahora cambiamos la weaita de raiz de todo
            this->largo_tot += linea->largo_tot;//luego el largo de todo, pasa a ser la suma de las 2 weas
    }/*mujer = tiempo*dinero=dinero*dinero=dinero²
     tiempo=dinero
     dinero=sqrt(todos los problemas) <=> dinero²=problemas
     mujer=sqrt(problemas²)
     \(\therefore \) (por lo tanto) mujer=problemas                  (me proyecté)  */                                                                                         
        linea->raiz = nullptr;//ya no necesitamos esto 
        linea->largo_tot = 0;//ni esta wea
        //si ponia un delete linea la wea podía no funcar si ponias tu una wea en stack
}

    void invertir() {
        if (raiz) {
            invertirR(raiz);//llamo a la weaita si es valido el arbol
        }
    }

    int print(void) {
        if (!raiz) {//manejo de errores, no pongo un cout ni cerr pq no fue solicitado
            return 0;//se sale
        }//aguanten los hondas civic
        printR(raiz);//si es válido, printea llamando a raiz, (printeará todas las hojas)
        std::cout << "\n";//por si usas multiples print, mantenga orden y ya
        return (int)largo_tot; //ya que se especifico que la funcion fuera de tipo int, aprovecho de
    }//retornarte el largo para comodidad de verificaciones en consola
};/*tenme piedad, no compilé esto, hice solo el "TDA.hpp" tal cual pediste ;(
  spike un grande
*/
