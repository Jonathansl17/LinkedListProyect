#include <iostream> 
using namespace std;

class NodoDePersonas {
public:
    string nombre;
    string apellido;
    int edad;
    int cedula;
    NodoDePersonas* next;
    NodoDePersonas* previous;

    NodoDePersonas(string nombre, string apellido, int edad, int cedula) {
        this->nombre = nombre;
        this->apellido = apellido;
        this->edad = edad;
        this->cedula = cedula;
        this->next = nullptr;
        this->previous = nullptr;
    }
};

class ListaDePersonas{
public:
    NodoDePersonas* head;
    NodoDePersonas* tail;

    void InsertarPersonaAlFinal(string nombre, string apellido, int edad, int cedula){
        NodoDePersonas* nuevoNodo = new NodoDePersonas(nombre,apellido,edad,cedula);

        //Verficamos si la lista esta vacia
        if(head == nullptr){
            head = nuevoNodo;
            head->previous = nullptr;
            tail = nuevoNodo;
            tail->previous = nullptr;

        } else{
            tail->next = nuevoNodo;//Apuntamos la cola al siguiente nodo
            nuevoNodo->previous = tail; //Hacemos que el nuevo nodo apunte al ultimo
                                        //Para mantener en enlace
            tail = nuevoNodo; //Definimos la cola como el nuevo nodo
            tail->next = nullptr;//Aseguramos que la nueva cola no apunte a nada
        }
    }

    void BorrarPersona(string NombreDePersona, string ApellidoDePersona) {
        NodoDePersonas* temp = head;

        // Caso 1: la lista está vacía
        if (head == nullptr) {
            cout << "La lista está vacía";
            return;
        }

        // Caso 2: La persona a borrar es la primera de la lista
        if ((head->nombre == NombreDePersona) && (head->apellido == ApellidoDePersona)) {
            NodoDePersonas* BorrarEsteNodo = head;

            // Si solo hay un nodo en la lista
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            } else {
                // Redireccionamos la cabeza al siguiente nodo
                head = head->next;
                if (head != nullptr) {
                    head->previous = nullptr; // El nuevo head no debe tener un nodo previo
                }
            }
            delete BorrarEsteNodo;
            return;
        }

        // Caso 3: El nodo a borrar está en el medio o al final
        while (temp != nullptr) {
            if ((temp->nombre == NombreDePersona) && (temp->apellido == ApellidoDePersona)) {
                NodoDePersonas* BorrarEsteNodo = temp;

                if (temp->previous != nullptr) {
                    temp->previous->next = temp->next;
                }
                if (temp->next != nullptr) {
                    temp->next->previous = temp->previous;
                }

                // Si el nodo a borrar es el último, actualizar la cola
                if (temp == tail) {
                    tail = temp->previous;
                }

                delete BorrarEsteNodo;
                return;
            }
            temp = temp->next;
        }
    }


    void MostrarPersona(){
        NodoDePersonas* temp = head;
        while(temp != nullptr){
            cout<<temp->nombre<<" "<<temp->apellido<<" "<<temp->edad<<" "<<temp->cedula<<endl;
            temp = temp->next;
        }
    }
};


int main(){
    ListaDePersonas Hola;
    Hola.InsertarPersonaAlFinal("Juan","Perez",20,123456);
    Hola.InsertarPersonaAlFinal("Pedro","Perez",20,123456);
    Hola.InsertarPersonaAlFinal("Maria","Perez",20,123456);
    Hola.MostrarPersona();

    Hola.BorrarPersona("Maria","Perez");
    Hola.MostrarPersona();
    return 0;
}


// class TiposDeTarea{
// public:
//     //Se definen la head, la tail y el next, esto para facilitar las operaciones
//     //de insercion, borrar, ya que no se necesita iterar tanto
//     TiposDeTarea* head;
//     TiposDeTarea* tail;
//     TiposDeTarea* next;

//     int id;
//     string TipoTarea;
//     string Descripcion;

//     //Constructor de la clase 
//     /*
//     args
//         int: id
//         string TipoTarea
//         string Descripcion
//     */
//     TiposDeTarea(int id, string TipoTarea, string Descripcion){
//         this->id = id;
//         this->TipoTarea = TipoTarea;
//         this->Descripcion = Descripcion;
//         this->head = nullptr;
//         this->tail = nullptr;
//         this->next = nullptr;
//     }
// };



// class TareasSimples{
// public:
//     TareasSimples* head;
//     TareasSimples* tail;
//     TareasSimples* next;

//     int id;
//     string Descripcion;
//     string NivelDeImportancia;
//     int mes;
//     int dia;
//     int anio;
//     int hora;
//     SubListaDeTareas* Tipo;

//     TareasSimples(int id, string Descripcion, string NivelDeImportancia, int mes, int dia, int anio, int hora, SubListaDeTareas* Tipo){
//         this->id = id;
//         this->Descripcion = Descripcion;
//         this->NivelDeImportancia = NivelDeImportancia;
//         this->mes = mes;
//         this->dia = dia;
//         this->anio = anio;
//         this->hora = hora;
//         this->Tipo = Tipo;
//     }
// };



// class SubListaDeTareas{
// public:
//     SubListaDeTareas* head;
//     SubListaDeTareas* tail;
//     SubListaDeTareas* next;

//     string nombre;
//     string comentarios;
//     int PorcentajeDeAvanze;
//     bool Estado;

//     SubListaDeTareas(string nombre, string comentarios, int PorcentajeDeAvanze, bool Estado){
//         this->nombre = nombre;
//         this->comentarios = comentarios;
//         this->PorcentajeDeAvanze = PorcentajeDeAvanze;
//         this->Estado = Estado;
//     }
// };


// class TipoDeTarea{
// public:
//     TipoDeTarea* head;
//     TipoDeTarea* tail;
//     TipoDeTarea* next;

//     string TipoDeTarea;
//     string TipoDeObligacion;

// };