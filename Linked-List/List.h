#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <iostream>
#include <string>

namespace linked_list {

    template<typename T>
    class List
    {
        /*
        Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse
        List kann ein Stapel oder Warteschlange realisiert werden.
        */
    private:
        struct form
        {
            std::string start = "<< ";
            std::string zwischen = ", ";
            std::string ende = " >>\n";
        } list_form;
        Node<T>* head_tail; // Zeiger auf Kopf- und End-Element -> next der 1. Knoten;
                         // -> prev der letzte Knoten
        int  list_size;  // Länge der Kette
        bool temp; // normalerweise false; ist true, wenn es sich um eine temor�re
                   // Liste handelt die innerhalb der überladenen Operatoren
                   // angelegt wird
    public:
        List();
        List(const List& _List);            // Kopie Konstruktor
        ~List();
        void insertFront(T key);            // Einfügen eines Knotens am Anfang
        void insertFront(List<T>& _List);   // Einfügen einer vorhandenen Liste am Anfang
        void insertBack(T key);             // Einfügen eines Knotesn am Ende
        void insertBack(List<T>& _List);    // Einfügen einer vorhandenen Liste am Ende
        bool getFront(T& key);              // Entnehmen eines Knoten am Anfang
        bool getBack(T& key);               // Entnehmen eines Knoten am Ende
        bool del(T key);                    // löschen eines Knotens [key]
        bool search(T key);                 // Suchen eines Knoten
        bool swap(T key1, T key2);          // Knoten in der Liste vertauschen
        int  size(void);                    // Größe der Lise (Anzahl der Knoten)
        bool test(void);                    // Überprüfen der Zeigerstruktur der Liste
        void format(const std::string& start,
            const std::string& zwischen,
            const std::string& ende);
        // Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
        // start: stirng vor der Ausgabe der Liste
        // zwischen: string zwischen Listenknoten
        // ende: string am Ende der Liste
        List& operator=(const List& _List); // Zuweisungsoperator definieren
        List&
            operator+(const List& List_Append); // Listen zusammenführen zu einer Liste
        //friend std::ostream& operator<<(std::ostream& stream, List const& Liste); // Ausgabeoperator überladen
        friend Node<T>* get_anker(List& l);
        friend int   get_AnzahlNodes(List& l);
        template <typename Tf>
        friend std::ostream& operator << (std::ostream& stream, const List<Tf>& Liste);

    };

    template<typename T>
    List<T>::List()
    {
        // Konstruktor für eine leere Liste
        head_tail = new Node<T>;
        list_size = 0;
        temp = false;
        head_tail->next = head_tail;
        head_tail->prev = head_tail;
    }

    template<typename T>
    List<T>::List(const List<T>& _List)
    {
        // Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
        // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
        // sollen.
        list_form = _List.list_form;
        head_tail = new Node<T>;
        list_size = 0;
        temp = _List.temp;
        head_tail->next = head_tail;
        head_tail->prev = head_tail;
        Node<T>* tmp_node;
        tmp_node = _List.head_tail->next;
        while (tmp_node != _List.head_tail)
        {
            head_tail->prev =
                new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
            head_tail->prev->prev->next = head_tail->prev;
            list_size++;
            tmp_node = tmp_node->next;
        }
        if (_List.temp)
            delete& _List; // ist die übergebene Liste eine temporäre Liste? -> aus
                           // Operator +
    }

    template<typename T>
    List<T>::~List()
    {
        // Dekonstruktor
        // Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht
        // wird.
        Node<T>* tmp = head_tail->next;
        while (tmp != head_tail)
        {
            tmp = tmp->next;
            delete tmp->prev;
        }
        delete head_tail;
    }

    template<typename T>
    void List<T>::insertFront(T key)
    {
        // Einfuegen eines neuen Knotens am Anfang der Liste
    /*
        Einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
    */
        this->list_size++;                          //Länge der List anpassen
        Node<T>* newNode = new Node<T>;             //Neuen Knoten Erstellen
        newNode->key = key;                         //Wert zuweisen

        Node<T>* tmp = this->head_tail->next;       // Pointer neu zuweisen
        this->head_tail->next = newNode;            // "
        newNode->prev = this->head_tail;            // "
        newNode->next = tmp;                        // "
        tmp->prev = newNode;                        // "
    }

    template<typename T>
    void List<T>::insertFront(List<T>& _List)
    {
        // Einfuegen der Liste _List am Anfang an einer vorhandenen Liste 
        /*
        Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
        Die einzufuegende Liste _List ist anschließend leer.
        Es darf keine Schleife und kein new benutzt werden.
        */
        if (head_tail == _List.head_tail) return;			// gleiches Objekt -> keine Aktion
    /*
        Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
        Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
        Die Liste _List ist danach leer, aber vorhanden.
    */

        Node<T>* tmp = this->head_tail->next;                       // erstes Element zwischenspeichern
        this->head_tail->next = _List.head_tail->next;              // das erste Element der _List in this list einfügen
        _List.head_tail->next->prev = this->head_tail;              // Das Erste Element der _List verweist nun über ->Prev auf Headtail der this liste
        _List.head_tail->prev->next = tmp;
        tmp->prev = _List.head_tail->prev;
        _List.head_tail->next = _List.head_tail;
        _List.head_tail->prev = _List.head_tail;
        this->list_size = this->list_size + _List.list_size;        // Länge der this Liste auf neuen wert setzen
        _List.list_size = 0;                                        // _List ist nun leer daher soll size 0 sein
    }

    template<typename T>
    void List<T>::insertBack(T key)
    {
        // Einfuegen eines neuen Knotens am Ende der Liste
    /*
        Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
    */
        this->list_size++;
        Node<T>* newNode = new Node<T>;             // Erstellen des Neuen Knoten
        newNode->key = key;

        Node<T>* tmp = this->head_tail->prev;       // Pointer neu zuweisen
        this->head_tail->prev = newNode;            // "
        tmp->next = newNode;                        // "
        newNode->prev = tmp;                        // "
        newNode->next = this->head_tail;            // "

    }

    template<typename T>
    void List<T>::insertBack(List<T>& _List)
    {
        // Einfuegen der Liste _List am Ende einer vorhandenen Liste
        /*
        Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
        Die einzufuegende Liste _List ist anschließend leer.
        Es darf keine Schleife und kein new benutzt werden.
        */
        if (head_tail == _List.head_tail) return;			// gleiches Objekt -> keine Aktion
    /*
        Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
        Diese Knoten (koplette Kette) werden an den Ende der Liste (this) übertragen ohne sie zu kopieren!
        Die Liste _List ist danach leer, aber vorhanden.
    */

        Node<T>* lastInThisList = this->head_tail->prev;        // zwischenspeichern der letzten NOde in der this liste
        lastInThisList->next = _List.head_tail->next;           // anhängen der neuen liste an die letzten 
        _List.head_tail->next->prev = lastInThisList;           // Anfang der neune liste auf ende der this liste verwiesen
        _List.head_tail->prev->next = this->head_tail;          // Ende der Neune liste auf anfang der this Liste verweisen
        this->head_tail->prev = _List.head_tail->prev;
        this->list_size = this->list_size + _List.list_size;    // Neue länge brechnen
        _List.list_size = 0;                                    // Angehängte Liste auf 0 setzen

        _List.head_tail->next = _List.head_tail;                // Head und tail Pointer der neuen liste richtig setzen
        _List.head_tail->prev = _List.head_tail;                // "

    }

    template<typename T>
    bool List<T>::getFront(T& key)
    {
        // entnehmen des Knotens am Anfang der Liste
        // der Wert wird als Parameter zurueckgegeben
        // der Knoten wird entnommen
        // im Fehlerfall wird false zurückgegeben
        if (!list_size) return false;	// leere Liste -> kein Wert
        /*
            Der Wert des vorderen Knotens wird rückgegeben und der Knoten gelöscht.
            Die Methode del(key) darf nicht zum löschen benutzt werden.
        */

        key = this->head_tail->next->key;                           // Value in Parameter abspeichern

        Node<T>* newFirstElement = this->head_tail->next->next;     // Neues erste element zwichenspeichern

        delete this->head_tail->next;                               // Element Speichern

        this->head_tail->next = newFirstElement;                    // Zwischengespeichertes Element als neunen ersten knoten
        newFirstElement->prev = this->head_tail;                    // "
        this->list_size--;                                          // neue Länge anpassen

        return true;
    }

    template<typename T>
    bool List<T>::getBack(T& key)
    { // entnehmen des Knotens am Ende der Liste
        // der Wert wird als Parameter zurueckgegeben
        // der Knoten wird entnommen
        // im Fehlerfall wird false zurückgegeben
        if (!list_size) return false;	// leere Liste -> kein Wert
        /*
            Der Wert des letzten Knotens wird rückgegeben und der Knoten gelöscht.
            Die Methode del(key) darf nicht zum löschen benutzt werden.
        */

        key = this->head_tail->prev->key;                           // Value als parameter abspeichern
        Node<T>* newLastElement = this->head_tail->prev->prev;      // neues letzte element zwischenspeichern
        delete this->head_tail->prev;                               // löschen des letzten elements

        this->head_tail->prev = newLastElement;                     // Zwischengespeicherte Element als neues letzte element
        newLastElement->next = this->head_tail;                     // "

        this->list_size--;                                          // Länge anpassen

        return true;
    }

    template<typename T>
    bool List<T>::del(T key)
    {
        // Loeschen eines gegebenen Knotens
        // im Fehlerfall wird false zurückgegeben
        if (!list_size) return false; // leere Liste -> keine Aktion
    /*
        Löschen des Knotens mit dem Wert value
    */

        Node<T>* ptr = head_tail->next;         // Jumper vorbereiten
        while (ptr != head_tail) {              // bis zum ende der liste durchlaufen
            if (ptr->key == key) {              // * wenn Key des derzeitiegen elementes 
                this->list_size--;              // * Liste verkleinern
                Node* tmpPrev = ptr->prev;      // * prev zwischenspeichern
                Node* tmpNext = ptr->next;      // * next zwischenspeichern
                delete ptr;                     // * Element löschen
                tmpPrev->next = tmpNext;        // * Pointer neu zuweisen
                tmpNext->prev = tmpPrev;        // * Pointer neu zuweisen
                return true;
            }
            ptr = ptr->next;                    // gehe zum nächstem element
        }
        return false;
    }

    template<typename T>
    bool List<T>::search(T key)
    {
        // suchen eines Knotens
        // nicht gefunden -> Rueckgabe: false
        if (!list_size) return false; // leere Liste -> keine Aktion
    /*
        suchen ob ein Knoten mit dem Wert value existiert.
    */
        Node<T>* ptr = head_tail->next;             // jumper ini
        while (ptr != head_tail) {                  // durchlaufen der liste bis man zum ende kommt
            if (ptr->key == key) return true;       // Key erreicht ? return true
            ptr = ptr->next;                        // ptr zu nächstem element der liste setzen
        }
        return false;
    }

    template<typename T>
    bool List<T>::swap(T key1, T key2)
    {
        /*
        Vertauschen von zwei Knoten mit dem key1 und dem key2
        Es dürfen nicht nur einfach die Schlüssel in den Knoten getauscht werden!
        Die Knoten sind in der Kette umzuhängen.
        */
        Node<T>* FirstElement = head_tail->next;
        Node<T>* SecondElement = head_tail->next;

        for (; FirstElement->next != head_tail->next; FirstElement = FirstElement->next)  if (FirstElement->key == key1) break; // Suche nach Key1
        for (; SecondElement->next != head_tail->next; SecondElement = SecondElement->next) if (SecondElement->key == key2) break; // Suche nach Key2

        Node<T>* preFirstElement = FirstElement->prev;         // Prevs und nexts zwischenspeichern           
        Node<T>* postFirstElement = FirstElement->next;        // "
        Node<T>* preSecondElement = SecondElement->prev;       // "
        Node<T>* postSecondElement = SecondElement->next;      // "

        if (FirstElement->prev == SecondElement) {          // FirstElement direkter vorgänger von SecondElement ? 
            preSecondElement->next = FirstElement;          // Verkettung wiederherstellen
            FirstElement->prev = preSecondElement;          // "
            FirstElement->next = SecondElement;             // "
            SecondElement->prev = FirstElement;             // "
            SecondElement->next = postFirstElement;         // "
            postFirstElement->prev = SecondElement;         // "
            return true;
        }
        else if (FirstElement->next == SecondElement) {     // SecondElement direkter vorgänger von FirstElement ? 
            preFirstElement->next = SecondElement;          // Verkettung wiederherstellen
            SecondElement->prev = preFirstElement;          // "
            SecondElement->next = FirstElement;             // "
            FirstElement->prev = SecondElement;             // "
            FirstElement->next = postSecondElement;         // "
            postSecondElement->prev = FirstElement;         // "
            return true;                                    // hat funktioniert also -> true
        }
        else {                                              // Keinen direckten nachbarn ?
            preFirstElement->next = SecondElement;          // Verkettung wiederherstellen
            SecondElement->prev = preFirstElement;          // "
            SecondElement->next = postFirstElement;         // "
            postFirstElement->prev = SecondElement;         // "
            preSecondElement->next = FirstElement;          // "
            FirstElement->prev = preSecondElement;          // "
            FirstElement->next = postSecondElement;         // "
            postSecondElement->prev = FirstElement;         // "
            return true;                                    // hat funktioniert also -> true
        }

        return false;
    }

    template<typename T>
    int List<T>::size(void)
    {
        // Rueckgabe der Anzahl der Knoten in der Liste mit O(1)
    /*
        Anzahl der Knoten in der Liste zurückgeben.
    */
        return this->list_size;	// Hier richtiges Ergebnis zurückgeben
    }

    template<typename T>
    bool List<T>::test(void)
    {
        // Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und
        // zurück Es werden dabei die Anzahl der Knoten gezahlt. Stimmt die Anzahl
        // der Knoten überein liefert die Methode true
        Node<T>* tmp = head_tail->next;
        int   i_next = 0, i_prev = 0;
        while (tmp != head_tail)
        {
            tmp = tmp->next;
            if (i_next > list_size)
                return false;
            i_next++;
        }
        if (i_next != list_size)
            return false;
        tmp = head_tail->prev;
        while (tmp != head_tail)
        {
            tmp = tmp->prev;
            if (i_prev > list_size)
                return false;
            i_prev++;
        }
        return i_prev == i_next;
    }

    template <typename T>
    List<T>& List<T>::operator=(const List<T>& _List)
    {
        // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
        // sollen. Kopiert wird in das Objekt "this"
        if (this == &_List)
            return *this; //  !! keine Aktion notwendig
        list_form = _List.list_form;
        Node<T>* tmp_node;
        if (list_size)
        {
            Node<T>* tmp_del;
            tmp_node = head_tail->next;
            while (tmp_node !=
                head_tail) // Alle eventuell vorhandenen Knoten in this löschen
            {
                tmp_del = tmp_node;
                tmp_node = tmp_node->next;
                delete tmp_del;
            }
            list_size = 0;
            head_tail->next = head_tail;
            head_tail->prev = head_tail;
        }
        tmp_node = _List.head_tail->next; // Die Listen-Knotenwerte werden kopiert
        while (tmp_node != _List.head_tail)
        {
            insertBack(tmp_node->key);
            tmp_node = tmp_node->next;
        }
        if (_List.temp)
            delete& _List; // ist die übergebene Liste eine temporäre Liste? -> aus
                           // Operator +
        return *this;
    }

    template <typename T>
    List<T>& List<T>::operator+(const List<T>& List_Append)
    {
        // Die Methode +
        // Es werden zwei Listen aneinander gehangen.
        // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
        // Ergebnisliste.
        Node<T>* tmp_node;
        List* tmp;
        if (temp)
        { // this ist eine temporäre Liste und kann verändert werden
            tmp = this;
        }
        else
        {
            tmp =
                new List<T>(*this); // this ist keine temporäre Liste -> Kopie erzeugen
            tmp->temp = true;    // Merker setzten, dass es sich um eine temporäre
                                 // Liste handelt
        }
        if (List_Append.list_size)
        { // anhängen der übergebenen Liste an tmp
            tmp_node = List_Append.head_tail->next;
            while (tmp_node != List_Append.head_tail)
            {
                tmp->insertBack(tmp_node->key);
                tmp_node = tmp_node->next;
            }
        }
        if (List_Append.temp)
            delete& List_Append; // wurde eine temporäre Liste übergeben, dann wird
                                 // diese gelöscht
        return *tmp;
    }

    template <typename T>
    void List<T>::format(const std::string& start,
        const std::string& zwischen,
        const std::string& ende)
    {
        // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
        // das Format wird für den überladenen Operator << verwendet
        list_form.start = start;
        list_form.zwischen = zwischen;
        list_form.ende = ende;
    }

    template <typename Tf>
    std::ostream& operator << (std::ostream& stream, const List<Tf>& Liste)
    {
        // Ausgabe der Liste mit cout
        stream << Liste.list_form.start;
        for (Node<Tf>* tmp = Liste.head_tail->next; tmp != Liste.head_tail;
            tmp = tmp->next)
            stream << tmp->key
            << (tmp->next == Liste.head_tail ? Liste.list_form.ende :
                Liste.list_form.zwischen);
        if (Liste.temp)
            delete& Liste; // wurde eine temporäre Liste übergeben, dann wird diese
                           // gelöscht
        return stream;
    }
}
#endif
