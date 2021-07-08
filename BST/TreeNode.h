/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

#define ENDOFTREE nullptr

using namespace std;

namespace BST{

    class TreeNode
    {

    private:
        ///////////////////////////////////////
        // Ihr Code hier:

        int NodeOrderID;
        int NodeChronolgicalID;
        std::string Name;
        int Age;
        double Income;
        int PostCode;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        //
        ////////////////////////////////////

    public:
        ///////////////////////////////////////
        // Ihr Code hier:
    
        TreeNode(int _NodeOrderID, int _NodeChronolgicalID, std::string _Name, int _Age, double _Income, int _PostCode);

        int getNodeOrderID();
        void setNodeOrderID(int ordID);

        int getNodeChronologicalID();
        void setNodeChronologicalID(int chrID);

        std::string getName();
        void setName(std::string name);

        int getAge();
        void setAge(int age);

        double getIncome();
        void setIncome(double income);

        int getPostCode();
        void setPostCode(int pcode);

        TreeNode* getLeft();
        void setLeft(TreeNode* Left);

        TreeNode* getRight();
        void setRight(TreeNode* Right);

        void print();

        //
        ////////////////////////////////////
    };

    bool _deleteNode(TreeNode*& Node, int ID);
    bool NodeHasChildren(TreeNode* Node);
    bool isEnd(TreeNode* Node);
    void ValueInTree(TreeNode* Node, string search, bool& gefunden);
    void PrintNode(TreeNode* Node);
    void addToTree(TreeNode* Node, TreeNode* newNode); 
    bool searchAndGetSmallest(TreeNode* start, TreeNode*& smallest);

}