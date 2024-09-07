#include <iostream> 
using namespace std;


//Prototipos para evitar error de scope
class NodoDeTareasActivas;
class ListaDeTareasActivas;

class NodoDePersonas;
class ListaDePersonas;


class NodoSubListaDeTarea;
class subListaDeTareas;

class NodoTipoDeTarea;
class ListaDeTiposDeTareas;



//--------Lista de tareas completadas--------
/*
Esta clase convierte los nodos de las tareas activas a tareas completadas y los enlaza
en una lista simple con insercion al final

*/
class NodoDeTareasCompletadas {
public:
    NodoSubListaDeTarea* tareaActiva;  // Puntero al nodo de tareas activas
    NodoDeTareasCompletadas* next;

    NodoDeTareasCompletadas(NodoSubListaDeTarea* tareaActiva) {
        this->tareaActiva = tareaActiva;
        this->next = nullptr;
    }
};


class ListaDeTareasCompletadas {
public:
    NodoDeTareasCompletadas* head;
    NodoDeTareasCompletadas* tail;

    ListaDeTareasCompletadas() {
        head = nullptr;
        tail = nullptr;
    }

    void agregarTareaCompletada(NodoSubListaDeTarea* tareaActiva) {
        NodoDeTareasCompletadas* nuevoNodo = new NodoDeTareasCompletadas(tareaActiva);
        if (tail == nullptr) {
            head = tail = nuevoNodo;
        } else {
            tail->next = nuevoNodo;
            tail = nuevoNodo;
        }
    }


};




//-------------------Sub Lista de Tareas-------------------
class NodoSubListaDeTarea{
public:
    NodoSubListaDeTarea* next;
    string nombre;
    string comentarios;
    int PorcentajeDeAvanze;
    bool Estado;

    NodoSubListaDeTarea(string nombre, string comentarios, int PorcentajeDeAvanze){
        this->nombre = nombre;
        this->comentarios = comentarios;
        this->PorcentajeDeAvanze = PorcentajeDeAvanze;
        if(PorcentajeDeAvanze ==100){
            this->Estado = true;
        } else{
            this->Estado = false;
        }
        this->next = nullptr;

    }
};
class subListaDeTareas{
public:
    NodoSubListaDeTarea* head;
    NodoSubListaDeTarea* tail;
    
    subListaDeTareas(){
        this->head = nullptr;
        this->tail = nullptr;
    }

    void InsertarSubTarea(string nombre, string comentarios, int avanze){
        NodoSubListaDeTarea* nuevaSubtarea = new NodoSubListaDeTarea(nombre, comentarios, avanze);
        if(avanze == 100){
            nuevaSubtarea->Estado = true;
            ListaDeTareasCompletadas TareasListas;
            TareasListas.agregarTareaCompletada(nuevaSubtarea);
        } else{
            nuevaSubtarea->Estado = false;
        }
        if(head == nullptr){
            head = nuevaSubtarea;
            tail = nuevaSubtarea;
            return;

        } else{
            tail->next = nuevaSubtarea;
            tail = nuevaSubtarea;
        }
    }

    void BorrarSubTarea(string nombre){
        NodoSubListaDeTarea* temp = head;

        // Caso 1: la lista está vacía
        if (head == nullptr) {
            cout << "La lista está vacía";
            return;
        }

        // Caso 2: La persona a borrar es la primera de la lista
        if (head->nombre == nombre) {
            NodoSubListaDeTarea* BorrarEsteNodo = head;

            // Si solo hay un nodo en la lista
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            } else {
                // Redireccionamos la cabeza al siguiente nodo
                head = head->next;
            }
            delete BorrarEsteNodo;
            return;
        }

        // Caso 3: El nodo a borrar está en el medio o al final
        while (temp != nullptr) {
            if (temp->nombre == nombre) {
                NodoSubListaDeTarea* BorrarEsteNodo = temp;

                if (temp->next != nullptr) {
                    temp->next = temp->next->next;
                }

                // Si el nodo a borrar es el último, actualizar la cola
                if (temp == tail) {
                    tail = temp->next;
                }

                delete BorrarEsteNodo;
                return;
            }
            temp = temp->next;
        }
    }
};

//-------------------Lista de Tipos de Tareas-------------------
class NodoTipoDeTarea{
public:
    int IdDeTarea;
    string nombreDeTipoDeTarea;
    string descripcion;
    NodoTipoDeTarea* next;

    NodoTipoDeTarea(int IdDeTarea, string nombreDeTipoDeTarea, string descripcion){
        this->IdDeTarea = IdDeTarea;
        this->nombreDeTipoDeTarea = nombreDeTipoDeTarea;
        this->descripcion = descripcion;
        this->next = nullptr;
    }
};

class ListaDeTiposDeTareas{
public:
    NodoTipoDeTarea* head;
    NodoTipoDeTarea* tail;

    ListaDeTiposDeTareas(){
        this->head = nullptr;
        this->tail = nullptr;
    }

    
    void InsertarTipoDeTarea(int IdDeTarea, string nombreDeTipoDeTarea, string descripcion) {
        NodoTipoDeTarea* nuevoNodo = new NodoTipoDeTarea(IdDeTarea, nombreDeTipoDeTarea, descripcion);

        // Caso 1: La lista está vacía
        if (head == nullptr) {
            head = nuevoNodo;
            tail = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 2: Insertar antes del head
        if (IdDeTarea < head->IdDeTarea) {
            nuevoNodo->next = head;
            head = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 3: Insertar después del tail
        if (IdDeTarea > tail->IdDeTarea) {
            tail->next = nuevoNodo;
            tail = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 4: Insertar en el medio
        NodoTipoDeTarea* temp = head;
        while (temp->next != head && temp->next->IdDeTarea < IdDeTarea) {
            temp = temp->next;
        }

        nuevoNodo->next = temp->next;
        temp->next = nuevoNodo;
        return;
    }
    
};


//-------------------Lista De Tareas----------------------

class NodoDeTareasActivas {
public:
    int idTipoTarea;
    string Descripcion;
    string NivelDeImportancia;
    int mes;
    int dia;
    int anio;
    int hora;
    NodoDeTareasActivas* next;
    subListaDeTareas* subLista; 
    ListaDeTiposDeTareas* tiposDeTareas;

    NodoDeTareasActivas(int idTipoTarea, string Descripcion, string NivelDeImportancia, int mes, int dia, int anio, int hora) {
        this->idTipoTarea = idTipoTarea;
        this->Descripcion = Descripcion;
        this->NivelDeImportancia = NivelDeImportancia;
        this->mes = mes;
        this->dia = dia;
        this->anio = anio;
        this->hora = hora;
        this->next = nullptr;
        this->subLista = new subListaDeTareas(); 
        this->tiposDeTareas = new ListaDeTiposDeTareas();
    }
};

class ListaDeTareasActivas{
public:
    NodoDeTareasActivas* head;
    NodoDeTareasActivas* tail;
    ListaDeTareasActivas(){
        this->head = nullptr;
        this->tail = nullptr;
    }

    // Función auxiliar para comparar fechas y horas
    bool esFechaYHoraMayor(int anio1, int mes1, int dia1, int hora1, int anio2, int mes2, int dia2, int hora2) {
        if (anio1 > anio2) return true;
        if (anio1 == anio2 && mes1 > mes2) return true;
        if (anio1 == anio2 && mes1 == mes2 && dia1 > dia2) return true;
        if (anio1 == anio2 && mes1 == mes2 && dia1 == dia2 && hora1 > hora2) return true;
        return false;
    }

    void InsertarTareaActivaAPersona(int id, std::string Descripcion, std::string NivelDeImportancia, int mes, int dia, int anio, int hora) {
        NodoDeTareasActivas* nuevoNodo = new NodoDeTareasActivas(id, Descripcion, NivelDeImportancia, mes, dia, anio, hora);

        // Caso 1: La lista está vacía
        if (head == nullptr) {
            head = nuevoNodo;
            tail = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 2: Insertar antes del head 
        if (esFechaYHoraMayor(anio, mes, dia, hora, head->anio, head->mes, head->dia, head->hora)) {
            nuevoNodo->next = head;
            head = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 3: Insertar despues del tail 
        if (!esFechaYHoraMayor(anio, mes, dia, hora, tail->anio, tail->mes, tail->dia, tail->hora)) {
            tail->next = nuevoNodo;
            tail = nuevoNodo;
            tail->next = head; // Mantener la circularidad
            return;
        }

        // Caso 4: Insertar en el medio
        NodoDeTareasActivas* temp = head;
        while (temp->next != head && esFechaYHoraMayor(anio, mes, dia, hora, temp->next->anio, temp->next->mes, temp->next->dia, temp->next->hora)) {
            temp = temp->next;
        }

        nuevoNodo->next = temp->next;
        temp->next = nuevoNodo;
        return;
    }
   

};








//-----------------------Lista de personas---------------------
class NodoDePersonas {
public:
    string nombre;
    string apellido;
    int cedula;
    int edad;
    NodoDePersonas* next;
    NodoDePersonas* previous;
    ListaDeTareasActivas* TareasDeLaPersona;
    ListaDeTareasCompletadas* TareasCompletadas;

    NodoDePersonas(string nombre, string apellido, int edad, int cedula) {
        this->nombre = nombre;
        this->apellido = apellido;
        this->edad = edad;
        this->cedula = cedula;
        this->next = nullptr;
        this->previous = nullptr;
        this->TareasDeLaPersona = new ListaDeTareasActivas(); 
        this->TareasCompletadas = new ListaDeTareasCompletadas();
    }
};

class ListaDePersonas {
public:
    NodoDePersonas* head;
    NodoDePersonas* tail;

    ListaDePersonas() {
        head = nullptr;
        tail = nullptr;
    }

    void InsertarPersona(string nombre, string apellido, int edad, int cedula) {
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

    void MostrarPersona() {
        NodoDePersonas* temp = head;
        while (temp != nullptr) {
            cout << temp->nombre << " " << temp->apellido << " " << temp->edad << " " << temp->cedula << endl;
            temp = temp->next;
        }
    }

    NodoDePersonas* BuscarPersonaPorCedula(int cedulaaa) {
        NodoDePersonas* temp = head;
        while (temp != nullptr) {
            if (temp->cedula == cedulaaa) {
                return temp;
            }
            temp = temp->next; // Avanzar el puntero
        }

        cout << "La persona no existe";
        return nullptr;
    }


    void InsertarTareaActiva(int cedula, int idTipoTarea, string Descripcion, string NivelDeImportancia, int mes, int dia, int anio, int hora) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if (persona != nullptr) {
            persona->TareasDeLaPersona->InsertarTareaActivaAPersona(idTipoTarea, Descripcion, NivelDeImportancia, mes, dia, anio, hora);
        } else {
            cout << "Persona no encontrada." << endl;
        }
    }


    void MostrarTareasActivasDePersona(int cedula) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if (persona != nullptr) {
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            if (tarea != nullptr) {
                do {
                    cout << tarea->idTipoTarea << " " << tarea->Descripcion << " " << tarea->NivelDeImportancia << " " << tarea->mes << " " << tarea->dia << " " << tarea->anio << " " << tarea->hora << endl;
                    tarea = tarea->next;
                } while (tarea != persona->TareasDeLaPersona->head);
            }
        } else {
            cout << "Persona no encontrada." << endl;
        }
    }


    void MostrarTareasCompletadasDeLaPersona(int cedula) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if (persona != nullptr) {
            NodoDeTareasCompletadas* tarea = persona->TareasCompletadas->head;
            if (tarea != nullptr) {
                do {
                    if (tarea->tareaActiva != nullptr) { // Verificar que tareaActiva no sea nulo
                        cout << tarea->tareaActiva->nombre << " " << tarea->tareaActiva->comentarios << " " << tarea->tareaActiva->PorcentajeDeAvanze << endl;
                    } else {
                        cout << "Tarea activa no encontrada." << endl;
                    }
                    tarea = tarea->next;
                } while (tarea != nullptr);
            } else {
                cout << "No hay tareas completadas." << endl;
            }
        } else {
            cout << "Persona no encontrada." << endl;
        }
    }


    void BorrarTareas(int cedula, int IdDeTarea){
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if(persona != nullptr){
            NodoDeTareasActivas* tareas = persona->TareasDeLaPersona->head;
            
            if(tareas != nullptr){
                NodoDeTareasActivas* previo = nullptr;
                NodoDeTareasActivas* actual = tareas;

                // Si la lista tiene solo una tarea y es la que se quiere eliminar
                if (actual->next == tareas && actual->idTipoTarea == IdDeTarea) {
                    delete actual;
                    persona->TareasDeLaPersona->head = nullptr;
                    return;
                }

                do {
                    if (actual->idTipoTarea == IdDeTarea) {
                        if (previo == nullptr) {
                            // Si la tarea a eliminar es la primera
                            NodoDeTareasActivas* ultima = tareas;
                            while (ultima->next != tareas) {
                                ultima = ultima->next;
                            }
                            persona->TareasDeLaPersona->head = actual->next;
                            ultima->next = persona->TareasDeLaPersona->head;
                            delete actual;
                        } else {
                            // Si la tarea a borrar está en medio o al final
                            previo->next = actual->next;
                            delete actual;
                        }
                        return;
                    }
                    previo = actual;
                    actual = actual->next;
                } while (actual != tareas);

                // Si se recorre toda la lista y no se encuentra la tarea
                cout << "Tarea no encontrada" << endl;

            } else{
                cout << "La persona no tiene tareas activas" << endl;
            }

        } else{
            cout << "Persona no encontrada" << endl;
        } 
    }


    void ModificarTareas(int cedula, int IdDeTarea, int nuevoDia, int nuevoMes, int nuevoAnio, int nuevaHora) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);

        if (persona != nullptr) {
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;

            if (tarea != nullptr) {
                NodoDeTareasActivas* inicio = tarea; // Guardar el inicio para detectar el ciclo

                do {
                    if (tarea->idTipoTarea == IdDeTarea) {
                        tarea->dia = nuevoDia;
                        tarea->mes = nuevoMes;
                        tarea->anio = nuevoAnio;
                        tarea->hora = nuevaHora;
                        return;
                    }
                    tarea = tarea->next;
                } while (tarea != inicio);

                cout << "Tarea no encontrada" << endl;
            } else {
                cout << "La persona no tiene tareas activas" << endl;
            }
        } else {
            cout << "La persona no existe" << endl;
        }
    }


    
    // Función para insertar una subtarea
    void InsertarSubTareaEnTareaActiva(int cedula, int idTipoTarea, string nombre, string comentarios, int avanze) {

        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if(persona != nullptr){

            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            while (tarea != nullptr) {
                if (tarea->idTipoTarea == idTipoTarea) {
                    tarea->subLista->InsertarSubTarea(nombre, comentarios, avanze);
                    return;
                }
                tarea = tarea->next;
            }
            cout << "Tarea no encontrada." << endl;
            return;

        } else{
            cout <<"Persona no encontrada";
            return;
        }
    }

    void BorrarSubTareaDeTareaActiva(int cedula, int idTipoTarea, string nombre) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if(persona != nullptr){
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            while (tarea != nullptr) {
                if (tarea->idTipoTarea == idTipoTarea) {
                    tarea->subLista->BorrarSubTarea(nombre);
                    return;
                }
                tarea = tarea->next;
            }
            cout << "Tarea no encontrada." << endl;
            return;

        } else{
            cout <<"Persona no encontrada";
            return;
        }
    }



    void MostrarSubTareaDePersona(int cedula, int idTipoTarea) {

        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if(persona != nullptr){

            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            while (tarea != nullptr) {
                if (tarea->idTipoTarea == idTipoTarea) {
                    NodoSubListaDeTarea* subTarea = tarea->subLista->head;
                    while (subTarea != nullptr) {
                        cout << subTarea->nombre << " " << subTarea->comentarios << " " << subTarea->PorcentajeDeAvanze <<" "<< endl;
                        if(subTarea->Estado){
                            cout << "Subtarea completada" << endl;
                        } else{
                            cout << "Subtarea no completada" << endl;
                        }
                        subTarea = subTarea->next;
                    }
                    
                    return;
                }
                tarea = tarea->next;
            }
            cout << "Tarea no encontrada." << endl;
            return;

        } else{
            cout <<"Persona no encontrada";
            return;
        }
    }

    void ModificarSubTareaDePersona(int cedula, int idTipoTarea,string nombreDeSubtarea, int nuevoAvanze) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if(persona != nullptr){
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            while (tarea != nullptr) {
                if (tarea->idTipoTarea == idTipoTarea) {
                    NodoSubListaDeTarea* subTarea = tarea->subLista->head;
                    while (subTarea != nullptr){

                        if(subTarea->nombre == nombreDeSubtarea){
                            subTarea->PorcentajeDeAvanze = nuevoAvanze;

                            if(nuevoAvanze == 100){
                                subTarea->Estado = true;
                                persona->TareasCompletadas->agregarTareaCompletada(subTarea);
                                // BorrarSubTareaDeTareaActiva(cedula, idTipoTarea, nombreDeSubtarea);
                                
                            } else{
                                subTarea->Estado = false;
                            }
                            return;
                        }
                        subTarea = subTarea->next;
                    }
                    return;
                }
                tarea = tarea->next;
            }
            cout << "Tarea no encontrada." << endl;
            return;

        } else{
            cout <<"Persona no encontrada";
            return;
        }
    }

    void InsertarTipoDeTareaATareActivas(int cedula, int id, string nombreDeTipoDeTarea, string descripcion){
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if(persona != nullptr){
            
            NodoDeTareasActivas* tareas = persona->TareasDeLaPersona->head;

            while (tareas != nullptr){
                if(tareas->idTipoTarea == id){
                    tareas->tiposDeTareas->InsertarTipoDeTarea(id,nombreDeTipoDeTarea,descripcion);
                    return;
                }
                tareas = tareas->next;
            }
            cout << "Tarea no encontrada." << endl;
            return;

        } else{
            cout << "Persona no encontrada." << endl;
            return;
        }
    }
    

    void MostrarTipoDeTareasDeTareasActivas(int cedula) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);

        if (persona != nullptr) {
            NodoDeTareasActivas* tareas = persona->TareasDeLaPersona->head;
            if (tareas != nullptr) {
                NodoDeTareasActivas* inicioTareas = tareas; 
                do {
                    cout << "Tarea: " << tareas->idTipoTarea << endl;
                    NodoTipoDeTarea* Tipos = tareas->tiposDeTareas->head;
                    if (Tipos != nullptr) {
                        NodoTipoDeTarea* inicioTipos = Tipos; 
                        do {
                            cout << Tipos->IdDeTarea << " " << Tipos->nombreDeTipoDeTarea << " " << Tipos->descripcion << endl;
                            Tipos = Tipos->next;
                        } while (Tipos != inicioTipos);
                    }
                    tareas = tareas->next;
                } while (tareas != inicioTareas);
            }
        } else {
            cout << "Persona no encontrada." << endl;
            return;
        }
    }
};
















int main(){
    ListaDePersonas Hola;
    Hola.InsertarPersona("Juan","Perez",20,123456);
    Hola.InsertarPersona("Pedro","Perez",20,12);
    Hola.InsertarPersona("Maria","Perez",20,123);
    Hola.InsertarPersona("Jony","Perez",20,0);
    Hola.MostrarPersona();

    Hola.BorrarPersona("Maria","Perez");
    Hola.MostrarPersona();
    cout<<endl;
    
    
    Hola.InsertarTareaActiva(123456,1,"Hacer tarea","Alta",12,12,2021,18);
    Hola.InsertarTareaActiva(123456,2,"Hacer tarea 2","Alta",12,12,2021,17);
    Hola.InsertarTareaActiva(123456,3,"Hacer tarea 3","Alta",12,12,2021,33);
    Hola.MostrarTareasActivasDePersona(123456);
    cout<<endl;
    Hola.BorrarTareas(123456,2);
    Hola.MostrarTareasActivasDePersona(123456);
    // Hola.MostrarTareasCompletadasDeLaPersona(123456);

    cout<<endl;
    Hola.ModificarTareas(123456,1,32,312,312,31);
    Hola.MostrarTareasActivasDePersona(123456);
    Hola.InsertarSubTareaEnTareaActiva(123456,1,"Subtarea","Prueba",30);
    Hola.MostrarSubTareaDePersona(123456,1);
    Hola.ModificarSubTareaDePersona(123456,1,"Subtarea",100);
    Hola.MostrarSubTareaDePersona(123456,1);
    Hola.InsertarSubTareaEnTareaActiva(123456,1,"Subtarea2","Prueba",30);
    Hola.MostrarSubTareaDePersona(123456,1);
    cout<<endl;

    cout<<"JAJAJA"<<endl;


     cout<<endl;
    Hola.InsertarTipoDeTareaATareActivas(123456,1,"estudio","cosas de la U");
    Hola.InsertarTipoDeTareaATareActivas(123456,2,"hogar","casa");
    Hola.MostrarTipoDeTareasDeTareasActivas(123456);



    cout<<"Mostrando tareas completadas"<<endl;
    Hola.InsertarSubTareaEnTareaActiva(123456,1,"Subtarea2","Prueba",30);
    Hola.InsertarSubTareaEnTareaActiva(123456,1,"Subtarea3","Prueba",30);
    Hola.InsertarSubTareaEnTareaActiva(123456,1,"Subtarea4","Prueba",100);
    Hola.ModificarSubTareaDePersona(123456,1,"Subtarea2",100);
    Hola.ModificarSubTareaDePersona(123456,1,"Subtarea3",100);
    Hola.MostrarTareasCompletadasDeLaPersona(123456);
    return 0;
}









