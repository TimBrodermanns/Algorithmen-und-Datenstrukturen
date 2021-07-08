/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>

 ////////////////////////////////////
 // Ihr Code hier:


namespace Red_Black_Tree {

    TreeNode::TreeNode(int  _NodeOrderID, int _NodeChronolgicalID, std::string _Name, int _Age, double _Income, int _PostCode, bool red, TreeNode* parent) {
        this->NodeOrderID = _NodeOrderID;
        this->NodeChronolgicalID = _NodeChronolgicalID;
        this->Name = _Name;
        this->Age = _Age;
        this->Income = _Income;
        this->PostCode = _PostCode;
        this->red = red;
        this->parent = parent;
    }

    int TreeNode::getNodeOrderID() {
        return this->NodeOrderID;
    }

    void TreeNode::setNodeOrderID(int ordID) {
        this->NodeOrderID = ordID;
    }

    int TreeNode::getNodeChronologicalID() {
        return this->NodeChronolgicalID;
    }

    void TreeNode::setNodeChronologicalID(int chrID) {
        this->NodeChronolgicalID = chrID;
    }

    std::string TreeNode::getName() {
        return this->Name;
    }

    void TreeNode::setName(std::string name) {
        this->Name = name;
    }

    int TreeNode::getAge() {
        return this->Age;
    }

    void TreeNode::setAge(int age) {
        this->Age = age;
    }

    double TreeNode::getIncome() {
        return this->Income;
    }

    void TreeNode::setIncome(double income) {
        this->Income = income;
    }

    int TreeNode::getPostCode() {
        return this->PostCode;
    }

    void TreeNode::setPostCode(int pcode) {
        this->PostCode = pcode;
    }

    TreeNode* TreeNode::getLeft() {
        return this->left;
    }

    void TreeNode::setLeft(TreeNode* Left) {
        this->left = Left;
    }

    TreeNode* TreeNode::getRight() {
        return this->right;
    }

    void TreeNode::setRight(TreeNode* Right) {
        this->right = Right;
    }


    bool TreeNode::getRed() {
        return this->red;
    }
    void TreeNode::setRed(bool newRed) {
        this->red = newRed;
    }

    TreeNode* TreeNode::getParent() {
        return this->parent;
    }
    void TreeNode::setParent(TreeNode* newParent) {
        this->parent = newParent;
    }

    void TreeNode::print() {
        std::cout << this->getNodeOrderID() << " | " << this->getNodeChronologicalID() << " \t\t\t| " << this->getName() << " \t| " << this->getAge() << " \t| " << this->getIncome() << " \t| " << this->getPostCode() << "\t\t| " << this->getNodeOrderID() << " \t| " << this << " | " << this->getLeft() << " | " << this->getRight() << " | " << this->getParent() << std::endl;
    }

    bool TreeNode::isLeaf() {
        return this->getLeft() == nullptr && this->getRight();
    }

    // recrusive funktions /////////////////////////////////////////////////////////////////////////

    bool NodeHasChildren(TreeNode* Node) {
        return (Node->getLeft() != ENDOFTREE || Node->getRight() != ENDOFTREE);
    }

    bool isEnd(TreeNode* Node) {
        return Node == ENDOFTREE;
    }


    void ValueInTree(TreeNode* Node, string search, bool& gefunden) {
        if (Node->getName() == search) {
            Node->print();
            gefunden = true;
        }
        if (!isEnd(Node->getLeft()))  ValueInTree(Node->getLeft(), search, gefunden);
        if (!isEnd(Node->getRight()))  ValueInTree(Node->getRight(), search, gefunden);
    }

    void PrintNode(TreeNode* Node) {
        Node->print();
        if (!isEnd(Node->getLeft())) PrintNode(Node->getLeft());
        if (!isEnd(Node->getRight())) PrintNode(Node->getRight());
    }

    void addToTree(TreeNode* anker, TreeNode* newNode) {
        TreeNode* jmp = anker;
        while (true) {
            if (jmp->getNodeOrderID() < newNode->getNodeOrderID()) {
                if (jmp->getRight()) {
                    jmp = jmp->getRight();
                }
                else {
                    jmp->setRight(newNode);
                    newNode->setParent(jmp);
                    break;
                }
            }
            else {
                if (jmp->getLeft()) {
                    jmp = jmp->getLeft();
                }
                else {
                    jmp->setLeft(newNode);
                    newNode->setParent(jmp);
                    break;
                }
            }
        }
    }

    bool searchAndGetSmallest(TreeNode* start, TreeNode*& smallest) {
        if (!isEnd(start)) {
            if (isEnd(start->getLeft())) return searchAndGetSmallest(start->getLeft(), smallest);
            else {
                start->print();
                smallest = start;
                return true;
            }
        }
        else
            return false;
    }

    // Others //////////////////////////////////////////////////////


    bool _deleteNode(TreeNode*& anker, int OrderID) {
        /*
        * Löschen der Node mit OrderID, falls die TreeNode kinder hat sucht man die kleinste Node im teilbaum ab der zu löschenden Node und erstezt die zu löschende node mit dem
        * gefunden kleinstem Wert
        */
        TreeNode* tmp = anker;                                                                              // wurzel
        if (tmp->getNodeOrderID() == OrderID) {                                                             // wurzel zu loeschen
            if (!isEnd(tmp->getLeft()) && !isEnd(tmp->getRight())) {                                        // zwei kinder
                TreeNode* LeftNode = tmp->getLeft();
                TreeNode* RightNode = tmp->getRight();
                TreeNode* tmp_prev = tmp;
                TreeNode* root = tmp;
                tmp = tmp->getRight();                                                                      //A. eins nach rechts
                if (!isEnd(tmp->getLeft()))
                    while (!isEnd(tmp->getLeft()))                                                          //B.minimum im rechten Baum
                        tmp = tmp->getLeft();
                if (tmp_prev->getRight() != tmp) {
                    tmp_prev = tmp_prev->getRight();
                    while (tmp_prev->getLeft() != tmp) tmp_prev = tmp_prev->getLeft();                      //bis tpm_prev der Parent vom minimum des rechten Baumes ist
                    if (!isEnd(tmp->getRight())) tmp_prev->setLeft(tmp->getRight());                        //minimum hat rechtes kind -> neu ausrichten
                    else tmp_prev->setLeft(ENDOFTREE);
                    tmp->setLeft(LeftNode);                                                                 // Teilbäume neu ausrichten
                    tmp->setRight(RightNode);                                                               // *
                }
                else tmp->setLeft(LeftNode);                                                                // *
                anker = tmp;                                                                                // tmp = new anker
                delete root;                                                                                // alte wurzel löschen
            }
            else {                                                                                          //linkes oder rechtes oder keins
                if (!isEnd(tmp->getLeft()) && isEnd(tmp->getRight())) anker = tmp->getLeft();               // nur linkes Kind
                else if (isEnd(tmp->getLeft()) && !isEnd(tmp->getRight())) anker = tmp->getRight();         // nur rechtes Kind
                else anker = ENDOFTREE;                                                                     // kein Kind
                delete tmp;                                                                                 // löschen
            }
            return true;                                                                                    // Node wurde erfolgreich gelöscht
        }
        else {
            TreeNode* tmp_prev = tmp;
            while (true) {                                                                                  //finde meinen zu loeschenden Knoten
                if (tmp->getNodeOrderID() > OrderID) {
                    if (isEnd(tmp->getLeft())) return false;                                                // nicht gefunden -> false
                    else tmp = tmp->getLeft();                                                              // gehe zur nächsten linken Node
                    if (tmp->getNodeOrderID() == OrderID) break;                                            // Node  gefunden -> break
                }
                else {
                    if (isEnd(tmp->getRight())) return false;                                               // nicht gefunden -> false
                    else tmp = tmp->getRight();                                                             // gehe zur nächsten linken Node
                    if (tmp->getNodeOrderID() == OrderID) break;                                            // Node  gefunden -> break
                }
            }
            while (true) {                                                                                  // finde meinen Parent zum tmp
                if (tmp_prev->getNodeOrderID() > OrderID) {
                    if (tmp_prev->getLeft() == tmp) break;                                                  // Node gefunden -> break
                    tmp_prev = tmp_prev->getLeft();                                                         // wenn nicht zur nächsten linken node
                }
                else {
                    if (tmp_prev->getRight() == tmp) break;
                    tmp_prev = tmp_prev->getRight();
                }
            }
            if (isEnd(tmp->getLeft()) && isEnd(tmp->getRight())) {                                          // kein nachfolger -> Blatt
                if (tmp_prev->getLeft() == tmp) tmp_prev->setLeft(ENDOFTREE);                               // Zweige zu nullptr
                else tmp_prev->setRight(ENDOFTREE);                                                         // *
                delete tmp;                                                                                 // Blatt löschen
                return true;                                                                                // hat funktioniert
            }
            else if (!isEnd(tmp->getLeft()) && isEnd(tmp->getRight())) {                                    // nur Links nachfolger
                if (tmp_prev->getLeft() == tmp) tmp_prev->setLeft(tmp->getLeft());
                else tmp_prev->setRight(tmp->getLeft());
                delete tmp;
                return true;
            }
            else if (isEnd(tmp->getLeft()) && !isEnd(tmp->getRight())) {                                    // nur Rechts nachfolger
                if (tmp_prev->getLeft() == tmp) tmp_prev->setLeft(tmp->getRight());                         // Linker zweig zu rechtem setzen
                else tmp_prev->setRight(tmp->getRight());
                delete tmp;                                                                                 // knoten löschen
                return true;                                                                                // hat funktioniert
            }
            else {                                                                                          // zwei Nachfolger
                TreeNode* links = tmp->getLeft();                                                           // Init start
                TreeNode* rechts = tmp->getRight();                                                         // *
                TreeNode* minimum = tmp->getRight();                                                        // 
                TreeNode* minimum_prev = tmp;                                                               // Init end
                if (!isEnd(minimum->getLeft()))
                    while (!isEnd(minimum->getLeft())) minimum = minimum->getLeft();                        //Suche minimum 
                if (minimum_prev->getRight() != minimum) {                                                  //nur ein rechter knoten
                    minimum_prev = minimum_prev->getRight();
                    while (minimum_prev->getLeft() != minimum) minimum_prev = minimum_prev->getLeft();      // suche parent vom Minimum -> tpm_prev
                }
                if (minimum_prev->getLeft() == minimum) {                                                   // überprüfe -> minimum Parent ist Minimums Parent?
                    if (!isEnd(minimum->getRight())) minimum_prev->setLeft(minimum->getRight());            //minimum hat rechtes kind
                    else minimum_prev->setLeft(ENDOFTREE);
                    minimum->setLeft(links);                                                                // Baum neu richten
                    minimum->setRight(rechts);                                                              // *
                }
                else minimum->setLeft(links);                                                               // *
                if (tmp_prev->getLeft() == tmp) tmp_prev->setLeft(minimum);                                 // *
                else tmp_prev->setRight(minimum);                                                           // *
                delete tmp;                                                                                 // lösche
                return true;                                                                                // hat funktioniert
            }
            return false;                                                                                   // kein knoten oder nicht funktioniert
        }
    }
}

 ////////////////////////////////////
