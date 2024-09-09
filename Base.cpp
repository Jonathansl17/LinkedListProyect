
#include <iostream> 
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <unordered_map>
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
    NodoDeTareasCompletadas* next;
    NodoTipoDeTarea* TipoDeTarea;
    int id;
    string descripcion;
    int PorcentajeDeCumplimiento;

    NodoDeTareasCompletadas(int id, string descripcion, int PorcentajeDeCumplimiento) {
        this->TipoDeTarea = TipoDeTarea;
        this->id = id;
        this->descripcion = descripcion;
        this->PorcentajeDeCumplimiento = PorcentajeDeCumplimiento;
        this->next = nullptr;
    }

};

/* Esta clase se encarga mantener una lista de tareas completadas,
 agregando de una en una en el orden en que se completan.*/
class ListaDeTareasCompletadas {
public:
    NodoDeTareasCompletadas* head;
    NodoDeTareasCompletadas* tail;

    ListaDeTareasCompletadas() {
        head = nullptr;
        tail = nullptr;
    }

    void agregarTareaCompletada(int id, string descripcion, int PorcentajeDeCumplimiento) {
        NodoDeTareasCompletadas* nuevoNodo = new NodoDeTareasCompletadas(id, descripcion, PorcentajeDeCumplimiento);

        // Caso 1: La lista está vacía
        if (head == nullptr) {
            head = nuevoNodo;
            tail = nuevoNodo;
            return;
        } else{
            tail->next = nuevoNodo;
            tail = nuevoNodo;
        }

    } 


};




//-------------------Sub Lista de Tareas-------------------
/* La clase crea nodos en una lista enlazada de subtareas. Cada nodo almacena 
información sobre una subtarea específica y un puntero al siguiente nodo en la lista.*/
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

/*La clase de gestion de lista enlazada de subtareas. Controla la inserción de nuevas 
subtareas en la lista y actualiza los punteros para mantener la estructura enlazada.*/
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
            TareasListas.agregarTareaCompletada(1, nombre, avanze);
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
     /* Borra una subtarea existente dentro de una tarea, segun lo indique el usuario */
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
/* Esta clase representa un nodo en la lista enlazada de 
tipos de tareas. Cada nodo almacena información sobre un tipo específico de tarea.*/
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

/* Esta clase maneja una lista enlazada de tipos de tarea. Controla la inserción de nuevos 
tipos de tareas en la lista y mantiene un seguimiento del primer y último nodo de la lista.*/
class ListaDeTiposDeTareas{
public:
    NodoTipoDeTarea* head;
    NodoTipoDeTarea* tail;

    ListaDeTiposDeTareas(){
        this->head = nullptr;
        this->tail = nullptr;
    }

    /* Inserta un tipo de tarea especifico*/
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
/* Esta clase representa un nodo en la lista enlazada circular de tareas activas. 
Cada nodo contiene información detallada sobre una tarea activa.*/
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

/* Esta clase maneja una lista enlazada circular de tareas activas.*/
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
    
    /* Inserta neuvas tareas en la lista de manera ordenada según la fecha y la hora*/
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
/* La clase representa un nodo en la lista doblemente enlazada, donde cada nodo 
almacena información sobre una persona.*/
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

/* Esta clase maneja una lista doblemente enlazada de personas. */
class ListaDePersonas {
public:
    NodoDePersonas* head;
    NodoDePersonas* tail;

    ListaDePersonas() {
        head = nullptr;
        tail = nullptr;
    }
    
    /* Método para insertar personas en la lista de manera ordenada según su cédula, evitando duplicados.*/
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
    
    /* Elimina a la persona indicada por el usuario de la lista de personas*/
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

    /* Indica cual de las personas en la lista de personas posee la mayour cantiddad 
    de tareas activas*/
    void PersonaConMasTareasActivas() {
    if (head == nullptr) {
        cout << "No hay personas en la lista." << endl;
        return;
    }

    NodoDePersonas* temp = head;
    NodoDePersonas* personaConMasTareas = nullptr;
    int maxTareas = 0;

    while (temp != nullptr) {
        NodoDeTareasActivas* tareaTemp = temp->TareasDeLaPersona->head;
        int conteoTareas = 0;

        if (tareaTemp != nullptr) {
            do {
                conteoTareas++;
                tareaTemp = tareaTemp->next;
            } while (tareaTemp != temp->TareasDeLaPersona->head); 
        }

        if (conteoTareas > maxTareas) {
            maxTareas = conteoTareas;
            personaConMasTareas = temp;
        }

        temp = temp->next;
    }

    if (personaConMasTareas != nullptr) {
        cout << "La persona con mas tareas activas es: " 
             << personaConMasTareas->nombre << " " 
             << personaConMasTareas->apellido 
             << " con " << maxTareas << " tareas activas." << endl;
    } 
    else {
        cout << "No hay personas con tareas activas." << endl;
    }
    }

    /* Indica cúal es las personas en la lista cuenta con más tareas de un tipo*/
    void PersonaConMasTareasDeUnTipo(int idTipoTarea) {
    if (head == nullptr) {
        cout << "No hay personas en la lista." << endl;
        return;
    }

    NodoDePersonas* temp = head;
    NodoDePersonas* personaConMasTareas = nullptr;
    int maxTareas = 0;

    while (temp != nullptr) {
        NodoDeTareasActivas* tareaTemp = temp->TareasDeLaPersona->head;
        int conteoTareas = 0;

        if (tareaTemp != nullptr) {
            do {
                if (tareaTemp->idTipoTarea == idTipoTarea) {
                    conteoTareas++;
                }
                tareaTemp = tareaTemp->next;
            } while (tareaTemp != temp->TareasDeLaPersona->head); 
        }

        if (conteoTareas > maxTareas) {
            maxTareas = conteoTareas;
            personaConMasTareas = temp;
        }

        temp = temp->next;
    }

    if (personaConMasTareas != nullptr) {
        cout << "La persona con mas tareas activas del tipo " << idTipoTarea << " es: " 
             << personaConMasTareas->nombre << " " 
             << personaConMasTareas->apellido 
             << " con " << maxTareas << " tareas de ese tipo." << endl;
    } else {
        cout << "No hay personas con tareas activas del tipo " << idTipoTarea << "." << endl;
    }
}
    /* Indica cúal es la tarea más común dentro de las tareas activas de las 
    personas en la lista*/
    void TipoDeTareaMasComun() {
    if (head == nullptr) {
        cout << "No hay personas en la lista." << endl;
        return;
    }

    unordered_map<int, int> conteoTareasPorTipo;
    NodoDePersonas* temp = head;

    while (temp != nullptr) {
        NodoDeTareasActivas* tareaTemp = temp->TareasDeLaPersona->head;

        if (tareaTemp != nullptr) {
            do {
                conteoTareasPorTipo[tareaTemp->idTipoTarea]++;
                tareaTemp = tareaTemp->next;
            } while (tareaTemp != temp->TareasDeLaPersona->head);
        }

        temp = temp->next;
    }

    // Encontrar el tipo de tarea más común
    int tipoMasComun = -1;
    int maxConteo = 0;

    for (const auto& par : conteoTareasPorTipo) {
        if (par.second > maxConteo) {
            maxConteo = par.second;
            tipoMasComun = par.first;
        }
    }

    if (tipoMasComun != -1) {
        cout << "El tipo de tarea mas comun es: " << tipoMasComun
             << " con " << maxConteo << " ocurrencias." << endl;
    } else {
        cout << "No hay tareas activas." << endl;
    }
}
    /* Indica cúal es la persona con más tareas vencidas de un mismo tipo*/
    void PersonaConMasTareasVencidasDeUnTipo(int idTipoTarea, int dia, int mes, int anio) {
        if (head == nullptr) {
             cout << "No hay personas en la lista." << endl;
            return;
        }

        NodoDePersonas* temp = head;
        NodoDePersonas* personaConMasTareasVencidas = nullptr;
        int maxTareasVencidas = 0;

        while (temp != nullptr) {
            NodoDeTareasActivas* tareaTemp = temp->TareasDeLaPersona->head;
            int conteoTareasVencidas = 0;

            if (tareaTemp != nullptr) {
                do {
                    if (tareaTemp->idTipoTarea == idTipoTarea) {
                        if ((tareaTemp->anio < anio) || 
                            (tareaTemp->anio == anio && tareaTemp->mes < mes) ||
                            (tareaTemp->anio == anio && tareaTemp->mes == mes && tareaTemp->dia < dia)) {
                            conteoTareasVencidas++;
                        }
                    }
                    tareaTemp = tareaTemp->next;
                } while (tareaTemp != temp->TareasDeLaPersona->head);
            }

            if (conteoTareasVencidas > maxTareasVencidas) {
                maxTareasVencidas = conteoTareasVencidas;
                personaConMasTareasVencidas = temp;
            }

            temp = temp->next;
        }

    if (personaConMasTareasVencidas != nullptr) {
        cout << "La persona con mas tareas vencidas del tipo " << idTipoTarea << " es: " 
             << personaConMasTareasVencidas->nombre << " " 
             << personaConMasTareasVencidas->apellido 
             << " con " << maxTareasVencidas << " tareas vencidas." << endl;
    } else {
        cout << "No hay personas con tareas vencidas del tipo " << idTipoTarea << "." << endl;
    }
}
    /* Indica cúal es la tarea más común dentro de las tareas activas sin completar 
    según una fecha indicada*/
    void TareaMasComunSinCompletar(int dia, int mes, int anio) {
        if (head == nullptr) {
            cout << "No hay personas en la lista." << endl;
             return;
        }

        unordered_map<string, int> conteoTareasVencidas;  
        NodoDePersonas* temp = head;

        while (temp != nullptr) {
            NodoDeTareasActivas* tareatemp = temp->TareasDeLaPersona->head;

            if (tareatemp != nullptr) {
                do {
                    bool flag = false;

                    if (tareatemp->anio < anio) {
                        flag = true;  
                    } else if (tareatemp->anio == anio) {
                        if (tareatemp->mes < mes) {
                            flag = true;  
                        } else if (tareatemp->mes == mes) {
                            if (tareatemp->dia < dia) {  
                                flag = true;  
                            }
                        }
                    }

                if (flag) {
                    conteoTareasVencidas[tareatemp->Descripcion]++;  
                }

                tareatemp = tareatemp->next;  
            } while (tareatemp != temp->TareasDeLaPersona->head);  
        }

        temp = temp->next;  
    }

    string tareaMasComun = "";
    int cantidad = 0;

    for (const auto& par : conteoTareasVencidas) {
        if (par.second > cantidad) {
            cantidad = par.second;
            tareaMasComun = par.first;
        }
    }

    if (!tareaMasComun.empty()) {
        cout << "La tarea más común sin completar y ya vencida es: " << tareaMasComun << " con " 
             << cantidad << " ocurrencias." << endl;
    } else {
        cout << "No hay tareas vencidas." << endl;
    }
}
    /* Indica cúal es la tarea más común en la clasificación de importancia Media */
    void TareaMasComunDeImportanciaMedia() {
        if (head == nullptr) {
            cout << "No hay personas en la lista." << endl;
            return; 
        }
    
        unordered_map<string, int> tareasImportanciaMedia;  
        NodoDePersonas* temp = head;

        while (temp != nullptr) {
            NodoDeTareasActivas* tareatemp = temp->TareasDeLaPersona->head;

            if (tareatemp != nullptr) {
                do {
                    if (tareatemp->NivelDeImportancia == "Media") {
                        tareasImportanciaMedia[tareatemp->Descripcion]++; 
                    }

                tareatemp = tareatemp->next;  
            } while (tareatemp != temp->TareasDeLaPersona->head);  
        }

        temp = temp->next; 
    }

    string tareaMasComun = "";
    int cantidad = 0;

    for (const auto& par : tareasImportanciaMedia) {
        if (par.second > cantidad) {
            cantidad = par.second;
            tareaMasComun = par.first;
        }
    }

    if (!tareaMasComun.empty()) {
        cout << "El tipo de tarea más común catalogada como de importancia media es: " << tareaMasComun << " con " 
             << cantidad << " tareas." << endl;
    } else {
        cout << "No hay tareas que se repitan en la categoria de importancia media." << endl;
    }
}
    /* Indica cúal es el tipo de importancia más usado por las personas*/
    void TipoDeImportanciaMasUsado() {
        if (head == nullptr) {
            cout << "La lista de personas se encuentra vacía." << endl;
            return;
        }

        NodoDePersonas* temp = head;
        int importanciaAlta = 0;
        int importanciaMedia = 0;
        int importanciaBaja = 0;

   
        while (temp != nullptr) {
            NodoDeTareasActivas* tareastemp = temp->TareasDeLaPersona->head;

            if (tareastemp != nullptr) {
                do {
                    if (tareastemp->NivelDeImportancia == "Alta") {
                        importanciaAlta++;
                    } else if (tareastemp->NivelDeImportancia == "Media") {
                        importanciaMedia++;
                    } else if (tareastemp->NivelDeImportancia == "Baja") {
                        importanciaBaja++;
                    }
                    tareastemp = tareastemp->next;
                } while (tareastemp != temp->TareasDeLaPersona->head);  
            }

            temp = temp->next;  
        }

    if (importanciaAlta > importanciaMedia && importanciaAlta > importanciaBaja) {
        cout << "El tipo de importancia más utilizado en las tareas registradas es Alta" << endl;
    } else if (importanciaMedia > importanciaAlta && importanciaMedia > importanciaBaja) {
        cout << "El tipo de importancia más utilizado en las tareas registradas es Media" << endl;
    } else if (importanciaBaja > importanciaMedia && importanciaBaja > importanciaAlta) {
        cout << "El tipo de importancia más utilizado en las tareas registradas es Baja" << endl;
    } else {
        cout << "Hay importancias que se repiten la misma cantidad de veces" << endl;
    }
}
    /* Indica cúal es al taera más común dentro de las tareas que ya fueron completadas 
    y además que se encontrara en la categoria de importancia Alta*/ 
    void TareaCompletadaMasComunDeImportanciaAlta() {
        if (head == nullptr) {
            cout << "No hay personas en la lista." << endl;
            return; 
        }
    
        unordered_map<string, int> tareasImportanciaAlta;  
        NodoDePersonas* temp = head;

        while (temp != nullptr) {
            NodoDeTareasCompletadas* tareastemp = temp->TareasCompletadas->head;

            if (tareastemp != nullptr) {
                while (tareastemp != nullptr) {
                    if (tareastemp->TipoDeTarea != nullptr) {
                        if (tareastemp->TipoDeTarea->nombreDeTipoDeTarea == "Alta") {
                            tareasImportanciaAlta[tareastemp->descripcion]++;
                        }
                    }
                    tareastemp = tareastemp->next;
                }
            }
            temp = temp->next; 
        }

        string tareaMasComun = "";
        int cantidad = 0;

        for (const auto& par : tareasImportanciaAlta) {
            if (par.second > cantidad) {
                cantidad = par.second;
                tareaMasComun = par.first;
            }
        }

        if (!tareaMasComun.empty()) {
            cout << "El tipo de tarea más común completada, catalogada como de importancia alta es: " << tareaMasComun << " con " 
                << cantidad << " tareas completadas." << endl;
        } else {
            cout << "No hay tareas completadas que se repitan en la categoría de importancia alta." << endl;
        }
    }

    /* Indica cúales son las tareas proximas a vencer dentro del lapso de una semana antes 
    de la fecha indica por el usuario*/
    void TareasProximasAVencer(int anio, int mes, int dia) {
        if(head == nullptr) {
            cout << "La lista no contiene nombres de personas"; 
            return; 
        }
        bool flag = false; 
        NodoDePersonas *temp = head; 
        cout << "La lista de tareas proximas a vencer antes de la fecha, "<< dia <<"/"<<mes<<"/"<<anio<< " es: "<<endl; 

        while(temp != nullptr) {
            if (temp->TareasDeLaPersona != nullptr && temp->TareasDeLaPersona->head != nullptr) {
                NodoDeTareasActivas* tareastemp = temp->TareasDeLaPersona->head;
                do {
                    if (tareastemp != nullptr) {
                        if (tareastemp->anio == anio && tareastemp->mes == mes) {
                            if (tareastemp->dia >= (dia - 7) && tareastemp->dia <= dia) {
                                cout << "La tarea " << tareastemp->Descripcion << " está próxima a vencer. En la fecha "   
                                << tareastemp->dia << "/" << tareastemp->mes << "/" << tareastemp->anio << endl;
                                flag = true; 
                            }
                        }
                    }
                    tareastemp = tareastemp->next;
                } while (tareastemp != temp->TareasDeLaPersona->head);  
            }           
            temp = temp->next; 
        }
        if(flag == false) {
            cout << "\nNo hay tareas a vencer en un rango de una semana antes de al fecha dada."<<endl; 
        }
    }

    /* Indica las subtareas de una tarea en especifico de una persona*/
    void ImprimirSubtareas(int idTipoTarea, int idPersona) {
        if (head == nullptr) {
            cout << "La lista no contiene nombres de personas." << endl;
            return;
        }

        NodoDePersonas* temp = head;

        while (temp != nullptr) {
            if (temp->cedula == idPersona) {
                NodoDeTareasActivas* tareastemp = temp->TareasDeLaPersona->head;
            
                if (tareastemp != nullptr) {
                    do {
                        if (tareastemp->idTipoTarea == idTipoTarea) {
                            if (tareastemp->subLista != nullptr && tareastemp->subLista->head != nullptr) {
                                NodoSubListaDeTarea* subtareas = tareastemp->subLista->head;
                                cout << "Subtareas de la tarea con ID " << tareastemp->idTipoTarea << ":\n";
                                while (subtareas != nullptr) {
                                    cout << "Nombre de la subtarea: " << subtareas->nombre << "\n"
                                        << "Estado: " << (subtareas->Estado ? "Completada" : "No Completada") << "\n"
                                        << "Porcentaje de avance: " << subtareas->PorcentajeDeAvanze << "%\n\n";
                                    subtareas = subtareas->next;
                                }
                            } else {
                                cout << "No hay subtareas para esta tarea.\n";
                            }
                            return;
                        }
                        tareastemp = tareastemp->next;  
                    } while (tareastemp != temp->TareasDeLaPersona->head); 
                }
            }
            temp = temp->next;  
        }
    }

    /* Inidica las tareas completadas de una persona*/
    void TareasRealizadas(string nombre, string apellido) {
        if(head == nullptr) {
            cout << "La lista de personas esta vacia. "; 
            return; 
        }

        NodoDePersonas *temp = head; 
        bool flag = false; 
        while(temp != nullptr) {
            NodoDeTareasCompletadas *tareatemp = temp->TareasCompletadas->head;
            if(temp->nombre == nombre && temp->apellido == apellido) {
                cout << "La lista de tareas completadas de " << nombre << " " << apellido << " es: "<<endl; 
                do {
                    if(tareatemp != nullptr) {
                        cout << tareatemp->descripcion << endl;
                        flag = true; 
                    } 
                } while (tareatemp != temp->TareasCompletadas->head); 
            }
            temp = temp->next; 
        }
        if(flag == false) {
            cout << nombre <<" "<< apellido <<" no posee tareas completadas." << endl; 
        }
    }
    
    /* Indica cúales tareas fueron completadas al 100% */
    void TareasCompletadasAl100 () {
        if(head == nullptr) {
            cout << "No hay personas en la lista. "; 
            return; 
        }

        NodoDePersonas *temp = head;
        bool flag = false;  

        while(temp != nullptr) {
            NodoDeTareasCompletadas *tareastemp = temp->TareasCompletadas->head; 
            if (tareastemp != nullptr) {
                do {
                    cout << "\nLas tareas compeltadas al 100 por ciento son: " << endl; 
                    if(tareastemp->PorcentajeDeCumplimiento == 100) {
                        cout << "-" <<tareastemp->descripcion << "\nPorcentaje: "<< tareastemp->PorcentajeDeCumplimiento<<endl; 
                        flag = true; 
                    }
                    tareastemp = tareastemp->next; 
                } while (tareastemp != temp->TareasCompletadas->head); 
            }
            temp = temp->next; 
        }
        if(flag == false) {
            cout << "No hay tareas completadas al 100 por ciento. " <<endl; 
        }
    }

    /* Muesta los datos de las personas que se encuentras en la lista de personas*/
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
            temp = temp->next; 
        }

        cout << "La persona no existe";
        return nullptr;
    }

    /* Inserta una nueva tarea activa*/
    void InsertarTareaActiva(int cedula, int idTipoTarea, string Descripcion, string NivelDeImportancia, int mes, int dia, int anio, int hora) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if (persona != nullptr) {
            persona->TareasDeLaPersona->InsertarTareaActivaAPersona(idTipoTarea, Descripcion, NivelDeImportancia, mes, dia, anio, hora);
        } else {
            cout << "Persona no encontrada." << endl;
        }
    }

    /* Muestra las tareas activas de una persona dado su núemro de cédula o identificación*/
    void MostrarTareasActivasDePersona(int cedula) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if (persona != nullptr) {
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            if (tarea != nullptr) {
                vector<NodoDeTareasActivas*> tareasVector;
    
                do {
                    tareasVector.push_back(tarea);
                    tarea = tarea->next;
                } while (tarea != persona->TareasDeLaPersona->head);
    
                sort(tareasVector.begin(), tareasVector.end(), [](const NodoDeTareasActivas* a, const NodoDeTareasActivas* b) {
                    if (a->anio != b->anio) {
                        return a->anio < b->anio;
                    }
                    if (a->mes != b->mes) {
                        return a->mes < b->mes;
                    }
                    if (a->dia != b->dia) {
                        return a->dia < b->dia;
                    }
                    return a->hora < b->hora;
                });
    
                for (const auto& tarea : tareasVector) {
                    cout << tarea->idTipoTarea << " " << tarea->Descripcion << " " << tarea->NivelDeImportancia << " " << tarea->mes << " " << tarea->dia << " " << tarea->anio << " " << tarea->hora << endl;
                }
            } else {
                cout << "No hay tareas activas para esta persona." << endl;
            }
        } else {
            cout << "Persona no encontrada." << endl;
        }
    }

    /* Muesta las tareas completadas de una persona dado su número de cédula*/
    void MostrarTareasCompletadasDeLaPersona(int cedula) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if (persona != nullptr) {
            NodoDeTareasCompletadas* tarea = persona->TareasCompletadas->head;
            while (tarea != nullptr){
                cout << tarea->id << " " << tarea->descripcion << " " << tarea->PorcentajeDeCumplimiento << endl;
                tarea = tarea->next;
            }
        
        }
    }

    /* Elimina tareas de la lista de tareas activas de una persona dado su número de cédula 
    y el id de la tarea que se desea eliminar*/
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

    /* Modifica aspectos la las tareas activas en la lista de una persona, como al fecha y hora*/
    void ModificarTareas(int cedula, int IdDeTarea, int nuevoDia, int nuevoMes, int nuevoAnio, int nuevaHora) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);

        if (persona != nullptr) {
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;

            if (tarea != nullptr) {
                NodoDeTareasActivas* inicio = tarea; 

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

    /* Inserta una subtarea a una tarea activa de una persona indicada */
    void InsertarSubTareaEnTareaActiva(int cedula, int idTipoTarea, string nombre, string comentarios, int avanze) {

        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);

        if(persona != nullptr){

            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            while (tarea != nullptr) {
                if (tarea->idTipoTarea == idTipoTarea ) {

                    if(avanze == 100){
                        persona->TareasCompletadas->agregarTareaCompletada(1, nombre, avanze);
                        return;
                    }

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

    /* Elimina subtareas de una tareas activa */
    void BorrarSubTareaDeTareaActiva(int cedula, int idTipoTarea, string nombre) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if (persona != nullptr) {
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            while (tarea != nullptr) {
                if (tarea->idTipoTarea == idTipoTarea) {
                    if (tarea->subLista == nullptr) {
                        cout << "No hay sublistas asociadas a esta tarea." << endl;
                        return;
                    }
                    
                    NodoSubListaDeTarea* subTarea = tarea->subLista->head;
                    NodoSubListaDeTarea* prevSubTarea = nullptr; 
                    
                    while (subTarea != nullptr) {
                        if (subTarea->nombre == nombre) {
                           
                            if (prevSubTarea == nullptr) {
                                tarea->subLista->head = subTarea->next; 
                            } else {
                                prevSubTarea->next = subTarea->next; 
                            }

                            if (subTarea->next == nullptr) {
                                tarea->subLista->tail = prevSubTarea;
                            }

                            delete subTarea;
                            cout << "Subtarea '" << nombre << "' eliminada correctamente." << endl;
                            return;
                        }
                        
                        prevSubTarea = subTarea;
                        subTarea = subTarea->next;
                    }
                    
                    cout << "Subtarea no encontrada." << endl;
                    return;
                }
                tarea = tarea->next;
            }
            cout << "Tarea no encontrada." << endl;
        } else {
            cout << "Persona no encontrada." << endl;
        }
    }

    /* Modifica los datos de una subtares de alguna tarea que corresponde a su vez, a la lista de 
    tareas activas de una persona */
    void ModificarSubTareaDePersona(int cedula, int idTipoTarea, string nombreDeSubtarea, int nuevoAvanze) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if(persona != nullptr){
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            while (tarea != nullptr) {
                if (tarea->idTipoTarea == idTipoTarea) {
                    if(tarea->subLista == nullptr) {
                        cout << "No hay sublistas asociadas a esta tarea." << endl;
                        return;
                    }
                    NodoSubListaDeTarea* subTarea = tarea->subLista->head;
                    while (subTarea != nullptr) {
                        if(subTarea->nombre == nombreDeSubtarea){
                            subTarea->PorcentajeDeAvanze = nuevoAvanze;

                            if(nuevoAvanze == 100){
                                subTarea->Estado = true;
                                persona->TareasCompletadas->agregarTareaCompletada(1, nombreDeSubtarea, nuevoAvanze);
                                BorrarSubTareaDeTareaActiva(cedula, idTipoTarea, nombreDeSubtarea);
                                return;
                            } else{
                                subTarea->Estado = false;
                            }
                            return;
                        }
                        subTarea = subTarea->next;
                    }
                    cout << "Subtarea no encontrada." << endl;
                    return;
                }
                tarea = tarea->next;
            }
            cout << "Tarea no encontrada." << endl;
            return;
        } else {
            cout << "Persona no encontrada." << endl;
            return;
        }
    }

    /* Muesta las subtareas de una tarea perteneciente a una persona */
    void MostrarSubTareaDePersona(int cedula, int idTipoTarea) {
        NodoDePersonas* persona = BuscarPersonaPorCedula(cedula);
        if(persona != nullptr){
            NodoDeTareasActivas* tarea = persona->TareasDeLaPersona->head;
            while (tarea != nullptr) {
                if (tarea->idTipoTarea == idTipoTarea) {
                    if(tarea->subLista == nullptr) {
                        cout << "No hay sublistas asociadas a esta tarea." << endl;
                        return;
                    }
                    NodoSubListaDeTarea* subTarea = tarea->subLista->head;
                    while (subTarea != nullptr) {
                        cout << subTarea->nombre << " " << subTarea->comentarios << " " << subTarea->PorcentajeDeAvanze << endl;
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
        } else {
            cout << "Persona no encontrada." << endl;
            return;
        }
    }

    /*Inserta un tipo de tarea especifico dentro de las tareas activas*/
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
    
    /* Muestra los tipos de tareas que se encuentran en la lista de tareas activas*/
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

/* Carga los datos*/
void cargarDatos(){
    //Insertar personas
    Hola.InsertarPersona("Juan","Perez",20,1);
    Hola.InsertarPersona("Pedro","Gomez",21,2);
    Hola.InsertarPersona("Maria","Rodriguez",18,3);
    Hola.InsertarPersona("Jonny","Gonzales",19,4);
    Hola.InsertarPersona("Federico","Murillo",23,5);
    //Insertar tipo de tareas activas
    Hola.InsertarTareaActiva(1,1,"Estudair","Alta",3,3,2024,3);
    Hola.InsertarTareaActiva(1,1,"Estudiar", "Alta",3,3,2024,3);
    Hola.InsertarTareaActiva(1,1,"Compras","Media",3,3,2024,3);
    Hola.InsertarTareaActiva(1,1,"Compras","Baja",3,3,2024,3);
    Hola.InsertarTareaActiva(1,2,"Limpiar","Media",2,2,2000,3);
    Hola.InsertarTareaActiva(3,2,"Limpiar","Alta",2,2,2000,3);
    Hola.InsertarTareaActiva(2,2,"Limpiar","Alta",3,3,2020,3);
    Hola.InsertarTareaActiva(2,2,"Limpiar","Media",3,3,2020,3);
    Hola.InsertarTareaActiva(2,2,"Limpiar","Media",3,3,2020,3);
    Hola.InsertarTareaActiva(2,2,"Limpiar","Media",3,3,2020,3);
    Hola.InsertarTipoDeTareaATareActivas(1,1,"Estudio","Trabajos del cole");
    Hola.InsertarTipoDeTareaATareActivas(1,2,"Casa", "Hace compras");

    Hola.InsertarSubTareaEnTareaActiva(10, 11, "Casa", "Invitaciones enviadas", 80);
    Hola.InsertarSubTareaEnTareaActiva(10, 11, "Estudio", "Examen matematica", 50);   
    Hola.InsertarSubTareaEnTareaActiva(11, 13, "Estudio", "Proyecto de POO", 60);
    Hola.InsertarSubTareaEnTareaActiva(11, 13, "Casa", "Estiramientos completados", 40);   
    Hola.InsertarSubTareaEnTareaActiva(12, 15, "Estudio", "Estanterías organizadas", 70);
    Hola.InsertarSubTareaEnTareaActiva(12, 16, "Trabajo", "Correos respondidos", 90);

  
}

/* Menú para realizar consultas*/
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
            Hola.PersonaConMasTareasActivas();
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break;
        }
        case 2:{
            int idTipoTarea;
            cout<<"Ingrese el id del tipo de tarea: ";
            cin>>idTipoTarea;
            Hola.PersonaConMasTareasDeUnTipo(idTipoTarea);
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));

            break;
        }
        case 3:{
            Hola.TipoDeTareaMasComun();
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break;
        }
        case 4:{
            int idTipoTarea, dia, mes, anio;
            cout << "Ingrese el ID del tipo de tarea: ";
            cin >> idTipoTarea;
            cout << "Ingrese el dia: ";
            cin >> dia;
            cout << "Ingrese el mes: ";
            cin >> mes;
            cout << "Ingrese el año: ";
            cin >> anio;
            Hola.PersonaConMasTareasVencidasDeUnTipo(idTipoTarea, dia, mes, anio);
            cout << "\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break;
        }
        case 5:{
            int mes, dia, anio; 
            cout << "Ingrese la fecha que desea revisar" <<endl; 
            cout  <<"Ingrese el dia: "; 
            cin >> dia; 
            cout << "Ingrese el mes: "; 
            cin >> mes; 
            cout << "Ingrese el año: "; 
            cin >> anio; 
            Hola.TareaMasComunSinCompletar(dia, mes, anio);
            cout << "\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break;
        }
        case 6:{
            Hola.TipoDeImportanciaMasUsado();
            cout << "\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break;
        }
        case 7:{
            Hola.TareaMasComunDeImportanciaMedia();
            cout << "\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break;
        }
        case 8:{
            Hola.TareaCompletadaMasComunDeImportanciaAlta(); 
            cout << "\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
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

/* Menú para imprimir*/
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
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(3));
            break;
        }
        case 2:{
            int cedula;
            cout<<"Lista de personas:\n";
            Hola.MostrarPersona();
            cout<<"De cual persona deseas ver la lista de tipos de tareas (ingrese la cedula): ";
            cin>> cedula;
            cout<<"\n";
            Hola.MostrarTipoDeTareasDeTareasActivas(cedula);
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break;
        }
        case 3:{
            NodoDePersonas* persona = Hola.head;
            bool sinTareasActivas = true;
            while (persona != nullptr) {
                if (persona->TareasDeLaPersona->head == nullptr) {
                    cout << persona->nombre << " " << persona->apellido << " no tiene tareas activas." << endl;
                    sinTareasActivas = false;
                }
                persona = persona->next;
            }
            if (sinTareasActivas) {
                cout << "No hay personas sin tareas activas." << endl;
            }
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));

            break;
        }
        case 4:{
            int ced;
            cout<<"Lista de personas:\n";
            Hola.MostrarPersona();
            cout<<"\nDe cual persona deseas ver las tareas activas (ingrese la cedula): ";
            cin>>ced;
            Hola.MostrarTareasActivasDePersona(ced);
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));

            break;
        }
        case 5:{
            int mes, dia, anio; 
            cout << "Indique la fecha que desea buscar: "<<endl;
            cout << "Indique el dia: "<<endl; 
            cin >> dia; 
            cout << "Indique el mes: "<<endl; 
            cin >> mes; 
            cout << "Indique el año: "<<endl; 
            cin >> anio; 
            Hola.TareasProximasAVencer(anio, mes, dia); 
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break;
        }
        case 6:{
            int idTipoTareas, idPersona; 
            cout << "Lista de personas: " <<endl; 
            Hola.MostrarPersona();
            cout << "\n"; 
            cout << "Indique el id de la persona que desea buscar: "; 
            cin >> idPersona; 
            cout << "Indique el id de la tarea que desea buscar: "; 
            cin >> idTipoTareas; 
            Hola.ImprimirSubtareas(idTipoTareas, idPersona); 
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
            break; 
        }
        case 7:{
            string nombre, apellido; 
            cout << "Lista de personas: " <<endl; 
            Hola.MostrarPersona();
            cout << "\n";
            cin.ignore(); 
            cout << "Indique el nombre de la persona: "; 
            getline(cin, nombre); 
            cout << "Indique el apellido de la persona: "; 
            getline(cin, apellido); 
            Hola.TareasRealizadas(nombre, apellido);
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5)); 
            break;
        }
        case 8:{
            Hola.TareasCompletadasAl100(); 
            cout<<"\nVolviendo al Menu...";
            this_thread::sleep_for(chrono::seconds(5));
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

/*Menú principal */
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
            cout << "\nLa persona ha sido insertada con exito. "<<endl; 
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
            cout << "\nLa pesona ha sido eliminada con exito." <<endl; 
            Menu();
            break;
        }
        case 3:{
            int id;
            string nombreDeTipoDeTarea, descripcion;
            cin.ignore();
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
            cout << "Lista de personas ya registradas: " << endl; 
            Hola.MostrarPersona(); 
            cout <<"\n";
            cin.ignore(); 
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cin.ignore(); 
            cout<<"Ingrese la descripcion de la tarea: ";
            getline(cin, Descripcion);
            cout<<"Ingrese el nivel de importancia de la tarea: ";
            getline(cin, NivelDeImportancia);
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
            cout << "Lista de personas ya registradas: " << endl; 
            Hola.MostrarPersona(); 
            cout <<"\n";
            cin.ignore();
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
            cout << "Lista de personas ya registradas: " << endl; 
            Hola.MostrarPersona(); 
            cout <<"\n";
            cin.ignore();
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
            cout << "Lista de personas ya registradas: " << endl; 
            Hola.MostrarPersona(); 
            cout <<"\n";
            cin.ignore();
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cout<<"Ingrese el nombre de la subtarea: ";
            getline(cin, nombre);
            cout<<"Ingrese los comentarios de la subtarea: ";
            getline(cin, comentarios);
            cout<<"Ingrese el porcentaje de avance de la subtarea: ";
            cin>>avanze;
            Hola.InsertarSubTareaEnTareaActiva(cedula,idTipoTarea,nombre,comentarios,avanze);
            Menu();
            break;
        }
        case 8:{
            int cedula, idTipoTarea;
            string nombre;
            cout << "Lista de personas ya registradas: " << endl; 
            Hola.MostrarPersona(); 
            cout <<"\n";
            cin.ignore();
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cout<<"Ingrese el nombre de la subtarea: ";
            getline(cin, nombre);
            Hola.BorrarSubTareaDeTareaActiva(cedula,idTipoTarea,nombre);
            Menu();
            break;
        }
        case 9:{
            int cedula, idTipoTarea, nuevoAvanze;
            string nombreDeSubtarea;
            cout << "Lista de personas ya registradas: " << endl; 
            Hola.MostrarPersona(); 
            cout <<"\n";
            cin.ignore();
            cout<<"Ingrese la cedula de la persona: ";
            cin>>cedula;
            cout<<"Ingrese el id de la tarea: ";
            cin>>idTipoTarea;
            cin.ignore(); 
            cout<<"Ingrese el nombre de la subtarea: ";
            getline(cin, nombreDeSubtarea);
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

/* Main se encarga de iniciar con la ejecución del programa*/
int main(){
    cargarDatos();
    Menu();

    return 0;
}