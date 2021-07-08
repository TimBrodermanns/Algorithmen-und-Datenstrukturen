/*************************************************
 * ADS Praktikum 2.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include <queue>
#include "catch.h"
#include <string>

namespace Red_Black_Tree {

    class Tree
    {

    private:
        ///////////////////////////////////////
        // Ihr Code hier:
        TreeNode* anker;
        int currentNodeChronologicalID;

        void balance(TreeNode* StartPoint);
        bool split4Node(TreeNode* NodeToSplit);
        int  proofRBCriterion(TreeNode* StartPoint);
        int  proofRB(TreeNode* StartPoint);
        bool rotateTreeRight(TreeNode* left, TreeNode* right);
        bool rotateTreeLeft(TreeNode* left, TreeNode* right);

        //
        ////////////////////////////////////

    public:
        ///////////////////////////////////////
        // Ihr Code hier:
        Tree();
        ~Tree();
        void addNode(string name, int age, double income, int postCode);
        //bool deleteNode(int ID);
        bool searchNode(std::string name);
        void printAll();
        void printLevelOrder();
        void printLevelOrder(int pos);

        //
        ////////////////////////////////////
        // friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
        // bleiben!
        friend TreeNode* get_anker(Tree& TN);
    };


    void printHead();
    void printFooter();

    void getLeafes(TreeNode* anker, queue<TreeNode*>& q);
    void bottemUpHeigth(TreeNode* leaf, int& heigth);
}