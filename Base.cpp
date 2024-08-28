#include <iostream> 
using namespace std;


//-----------------------Lista de personas---------------------
class NodoDePersonas {
public:
    string nombre;
    string apellido;
    int cedula;
    int edad;    
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

    void InsertarPersonaPorCedulaOrdenada(string nombre, string apellido, int edad, int cedula) {
        NodoDePersonas* nuevoNodo = new NodoDePersonas(nombre, apellido, edad, cedula);

        // Verificamos si la lista está vacía
        if (head == nullptr) {
            head = nuevoNodo;
            tail = nuevoNodo;
            return;
        }

        // Verificar duplicados
        NodoDePersonas* temp = head;
        while (temp != nullptr) {
            if (temp->cedula == cedula) {
                cout << "Error: Cedula duplicada no permitida." << endl;
                delete nuevoNodo; // Liberamos la memoria del nodo que no se insertará
                return;
            }
            temp = temp->next;
        }

        // Si la cedula del nuevo nodo es menor que la del head, insertar al inicio
        if (cedula < head->cedula) {
            nuevoNodo->next = head;
            head->previous = nuevoNodo;
            head = nuevoNodo;
            return;
        }

        // Si la cedula del nuevo nodo es mayor que la del tail, insertar al final
        if (cedula > tail->cedula) {
            nuevoNodo->previous = tail;
            tail->next = nuevoNodo;
            tail = nuevoNodo;
            return;
        }

        // Insertar en la posición ordenada
        temp = head;
        while (temp != nullptr && temp->cedula < cedula) {
            temp = temp->next;
        }

        // Insertar el nuevo nodo antes del nodo temp
        nuevoNodo->next = temp;
        nuevoNodo->previous = temp->previous;
        if (temp->previous != nullptr) {
            temp->previous->next = nuevoNodo;
        }
        temp->previous = nuevoNodo;
        return;
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





//-------------------Lista De Tareas----------------------

class NodoTipoDeTarea{
public:
    int idTipoTarea;
    string NombreDelTipoDeTarea;
    string TipoDeObligacion;
    NodoTipoDeTarea* next;

    NodoTipoDeTarea(int idTipoTarea, string NombreDelTipoDeTarea, string TipoDeObligacion){
        this->idTipoTarea = idTipoTarea;
        this->NombreDelTipoDeTarea = NombreDelTipoDeTarea;
        this->TipoDeObligacion = TipoDeObligacion;
        this->next = next;
    }

};

class ListaDeTareas{
private:
     NodoTipoDeTarea* head;
     NodoTipoDeTarea* tail;


public:
    ListaDeTareas(){
        this->head = nullptr;
        this->tail = nullptr;
    }

    void InsertarPorIdOrdenado(int id, string NombreDelTipoDeTarea, string TipoDeObligacion) {
        NodoTipoDeTarea* nuevoNodo = new NodoTipoDeTarea(id, NombreDelTipoDeTarea, TipoDeObligacion);

        // Caso 1: La lista está vacía
        if (head == nullptr) {
            head = nuevoNodo;
            tail = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 2: Insertar antes del head
        if (id < head->idTipoTarea) {
            nuevoNodo->next = head;
            head = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 3: Insertar después del tail
        if (id > tail->idTipoTarea) {
            tail->next = nuevoNodo;
            tail = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 4: Insertar en el medio
        NodoTipoDeTarea* temp = head;
        while (temp->next != head && temp->next->idTipoTarea < id) {
            temp = temp->next;
        }

        nuevoNodo->next = temp->next;
        temp->next = nuevoNodo;
    }


};







//-------------------Sub Lista de Tareas-------------------
class subListaDeTareas{
public:

    int id;
    string Descripcion;
    string NivelDeImportancia;
    int mes;
    int dia;
    int anio;
    int hora;

    subListaDeTareas* next;
    NodoSubListaDeTarea* Tipo;


    subListaDeTareas(int id, string Descripcion, string NivelDeImportancia, int mes, int dia, int anio, int hora, NodoSubListaDeTarea* Tipo){
        this->id = id;
        this->Descripcion = Descripcion;
        this->NivelDeImportancia = NivelDeImportancia;
        this->mes = mes;
        this->dia = dia;
        this->anio = anio;
        this->hora = hora;
        this->Tipo = Tipo;
    }
};



class NodoSubListaDeTarea{
public:

    string nombre;
    string comentarios;
    int PorcentajeDeAvanze;
    bool Estado;

    NodoSubListaDeTarea(string nombre, string comentarios, int PorcentajeDeAvanze, bool Estado){
        this->nombre = nombre;
        this->comentarios = comentarios;
        this->PorcentajeDeAvanze = PorcentajeDeAvanze;
        this->Estado = Estado;
    }
};




int main(){
    ListaDePersonas Hola;
    Hola.InsertarPersonaPorCedulaOrdenada("Juan","Perez",20,1);
    Hola.InsertarPersonaPorCedulaOrdenada("Pedro","Perez",20,12);
    Hola.InsertarPersonaPorCedulaOrdenada("Maria","Perez",20,123);
    Hola.InsertarPersonaPorCedulaOrdenada("Jony","Perez",20,0);
    Hola.MostrarPersona();

    Hola.BorrarPersona("Maria","Perez");
    Hola.MostrarPersona();
    return 0;
}