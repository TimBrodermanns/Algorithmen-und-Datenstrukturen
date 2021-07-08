/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

#define ENDOFTREE nullptr

using namespace std;

namespace Red_Black_Tree {

    class TreeNode
    {

    private:
        ///////////////////////////////////////
        // Ihr Code hier:

        int NodeOrderID = 0;
        int NodeChronolgicalID = 0;
        std::string Name = "";
        int Age = 0;
        double Income = 0;
        int PostCode = 0;
        bool red = false;
        TreeNode* left = ENDOFTREE;
        TreeNode* right = ENDOFTREE;
        TreeNode* parent = nullptr;
        //
        ////////////////////////////////////

    public:
        ///////////////////////////////////////
        // Ihr Code hier:

        TreeNode(int _NodeOrderID = 0, int _NodeChronolgicalID = 0, std::string _Name = "", int _Age = 0, double _Income = 0, int _PostCode = 0, bool red = true, TreeNode* parent = nullptr);

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

        bool getRed();
        void setRed(bool newRed);

        TreeNode* getParent();
        void setParent(TreeNode* newParent);

        void print();

        bool isLeaf();

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