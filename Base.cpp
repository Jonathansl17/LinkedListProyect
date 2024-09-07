#include <iostream> 
#include <thread>
#include <chrono>
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








ListaDePersonas Hola;
void cargarDatos(){
    //Insertar personas
    Hola.InsertarPersona("Juan","Perez",20,1);
    Hola.InsertarPersona("Pedro","Gomez",21,2);
    Hola.InsertarPersona("Maria","Rodriguez",18,3);
    Hola.InsertarPersona("Jonny","Gonzales",19,4);
    Hola.InsertarPersona("Federico","Murillo",23,5);
    //Insertar tipo de tareas activas
    Hola.InsertarTipoDeTareaATareActivas(1,1,"Estudio","Trabajos del cole");

    
}
void MenuConsulta(){
    system("cls");
    cout<<"------------Menu de Consultas------------\n";
    cout<<"\nQue deseas consultar:\n";
    cout<<"1. Cual es la persona que tiene mas tareas activas\n";
    cout<<"2. Cual es la persona que tiene mas tareas activas de un tipo X\n";
    cout<<"3. Que tipo de tarea es el mas comun\n";
    cout<<"4. Cual es la persona que tiene mas tareas vencidas de un tipo X dado una fecha Y\n";
    cout<<"5. Cual es el tipo de tareas mas comun que se vence sin completarse, dado una fecha Y\n";
    cout<<"6. Cual es el tipo de importancia mas usado por las personas\n";
    cout<<"7. Que es el tipo de tarea mas comun en tareas activas de importancia media\n";
    cout<<"8. Que es el tipo de tarea mas comun en tareas realizadas de importancia alta\n";
    cout<<"9. Volver al Menu Principal\n";
    int opcion;
    cout<<"Ingrese la opcion que desea realizar: ";
    cin>>opcion;
    switch(opcion){
        case 1:{

            break;
        }
        case 2:{

            break;
        }
        case 3:{

            break;
        }
        case 4:{

            break;
        }
        case 5:{

            break;
        }
        case 6:{

            break;
        }
        case 7:{
            
            break;
        }
        case 8:{

            break;
        }
        case 9:{
            return;
            break;
        }
        default:{
            cout<<"Opcion no valida\n";
            MenuConsulta();
        }
    }           
}

void MenuImprimir(){
    system("cls");
    cout<<"------------Menu de Impresion------------\n";
    cout<<"\nQue deseas imprimir:\n";
    cout<<"1. Imprimir las personas\n";
    cout<<"2. Imprimir la lista de tipos de tarea\n";
    cout<<"3. Imprimir las personas sin tareas activas\n";
    cout<<"4. Imprimir las tareas activas de una persona X, por orden de fecha y hora\n";
    cout<<"5. Imprimir las tareas próximo a vencer (menos de una semana) de una fecha X.\n";
    cout<<"6. Imprimir todas las subtareas de una tarea X de una persona Y.\n";
    cout<<"7. Imprimir las tareas realizadas por una persona X.\n";
    cout<<"8. Imprimir las tareas realizadas al 100%\n";
    cout<<"9. Volver al Menu Principal\n";
    int opcion;
    cout<<"Ingrese la opcion que desea realizar: ";
    cin>>opcion;cout<<"\n";
    switch(opcion){
        case 1:{
            Hola.MostrarPersona();
            this_thread::sleep_for(chrono::seconds(3));
            break;
        }
        case 2:{
            

            break;
        }
        case 3:{

            break;
        }
        case 4:{

            break;
        }
        case 5:{

            break;
        }
        case 6:{

            break;
        }
        case 7:{
            
            break;
        }
        case 8:{

            break;
        }
        case 9:{
            return;
            break;
        }
        default:{
            cout<<"Opcion no valida\n";
            MenuImprimir();}
    }
}
void Menu(){
    system("cls");
    cout<<"------------Bienvenido al Gestor de Tareas------------\n";
    cout<<"\nQue deseas hacer:\n";
    cout<<"1. Insertar persona\n";
    cout<<"2. Borrar persona\n";
    cout<<"3. Insertar tipo de tarea\n";
    cout<<"4. Insertar tarea activa a una persona X\n";
    cout<<"5. Modificar tarea activa de una persona X\n";
    cout<<"6. Borrar tarea activa de una persona X\n";
    cout<<"7. Insertar subtarea a una tarea activa de una persona X\n";
    cout<<"8. Borrar subtarea de una tarea activa de una persona X\n";
    cout<<"9. Modificar el porcentaje de avance y estado de completado a una subtarea X\n";
    cout<<"10. Realizar alguna consulta de datos\n";
    cout<<"11. Imprimir datos\n";
    cout<<"12. Salir\n";
    int opcion;
    cout<<"Ingrese la opcion que desea realizar: ";
    cin>>opcion;
    switch(opcion){
        case 1:{
            string nombre, apellido;
            int edad, cedula;
            cout<<"Ingrese el nombre de la persona: ";
            cin>>nombre;
            cout<<"Ingrese el apellido de la persona: ";
            cin>>apellido;
            cout<<"Ingrese la edad de la persona: ";
            cin>>edad;
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            Hola.InsertarPersona(nombre,apellido,edad,cedula);
            Menu();
            break;
        }
        case 2:{
            string nombre, apellido;
            cout<<"Ingrese el nombre de la persona que desea borrar: ";
            cin>>nombre;
            cout<<"Ingrese el apellido de la persona que desea borrar: ";
            cin>>apellido;
            Hola.BorrarPersona(nombre,apellido);
            Menu();
            break;
        }
        case 3:{
            int id;
            string nombreDeTipoDeTarea, descripcion;
            cout<<"Ingrese el id de la tarea: ";
            cin>>id;
            cout<<"Ingrese el nombre de la tarea: ";
            cin>>nombreDeTipoDeTarea;
            cout<<"Ingrese la descripcion de la tarea: ";
            cin>>descripcion;
            Hola.InsertarTipoDeTareaATareActivas(1,id,nombreDeTipoDeTarea,descripcion);
            Menu();
            break;
        }
        case 4:{
            int cedula, idTipoTarea, mes, dia, anio, hora;
            string Descripcion, NivelDeImportancia;
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cout<<"Ingrese la descripcion de la tarea: ";
            cin>>Descripcion;
            cout<<"Ingrese el nivel de importancia de la tarea: ";
            cin>>NivelDeImportancia;
            cout<<"Ingrese el mes de la tarea: ";
            cin>>mes;
            cout<<"Ingrese el dia de la tarea: ";
            cin>>dia;
            cout<<"Ingrese el anio de la tarea: ";
            cin>>anio;
            cout<<"Ingrese la hora de la tarea: ";
            cin>>hora;
            Hola.InsertarTareaActiva(cedula,idTipoTarea,Descripcion,NivelDeImportancia,mes,dia,anio,hora);
            Menu();
            break;
}
        case 5:{
            int cedula, idTipoTarea, nuevoDia, nuevoMes, nuevoAnio, nuevaHora;
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cout<<"Ingrese el nuevo dia de la tarea: ";
            cin>>nuevoDia;
            cout<<"Ingrese el nuevo mes de la tarea: ";
            cin>>nuevoMes;
            cout<<"Ingrese el nuevo anio de la tarea: ";
            cin>>nuevoAnio;
            cout<<"Ingrese la nueva hora de la tarea: ";
            cin>>nuevaHora;
            Hola.ModificarTareas(cedula,idTipoTarea,nuevoDia,nuevoMes,nuevoAnio,nuevaHora);
            Menu();
            break;
        }
        case 6:{
            int cedula, idTipoTarea;
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            Hola.BorrarTareas(cedula,idTipoTarea);
            Menu();
            break;
        }
        case 7:{
            int cedula, idTipoTarea, avanze;
            string nombre, comentarios;
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cout<<"Ingrese el nombre de la subtarea: ";
            cin>>nombre;
            cout<<"Ingrese los comentarios de la subtarea: ";
            cin>>comentarios;
            cout<<"Ingrese el porcentaje de avance de la subtarea: ";
            cin>>avanze;
            Hola.InsertarSubTareaEnTareaActiva(cedula,idTipoTarea,nombre,comentarios,avanze);
            Menu();
            break;
        }
        case 8:{
            int cedula, idTipoTarea;
            string nombre;
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cout<<"Ingrese el nombre de la subtarea: ";
            cin>>nombre;
            Hola.BorrarSubTareaDeTareaActiva(cedula,idTipoTarea,nombre);
            Menu();
            break;
        }
        case 9:{
            int cedula, idTipoTarea, nuevoAvanze;
            string nombreDeSubtarea;
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cout<<"Ingrese el nombre de la subtarea: ";
            cin>>nombreDeSubtarea;
            cout<<"Ingrese el nuevo porcentaje de avance de la subtarea: ";
            cin>>nuevoAvanze;
            Hola.ModificarSubTareaDePersona(cedula,idTipoTarea,nombreDeSubtarea,nuevoAvanze);
            Menu();
            break;
        }
        case 10:{
            MenuConsulta();
            Menu();
            break;
        }
        case 11:{
            MenuImprimir();
            Menu();
            break;
        }
        case 12:{
            cout<<"Gracias por usar el Gestor de Tareas";
            break;
        }
        default:{
            cout<<"Opcion no valida";
            Menu();
            break;
        }
    }
}


int main(){
    cargarDatos();
    Menu();


    return 0;
}