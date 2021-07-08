/*************************************************
 * ADS Praktikum 2.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>

namespace BST {

    class Tree
    {

    private:
        ///////////////////////////////////////
        // Ihr Code hier:
        TreeNode* anker;
        int currentNodeChronologicalID;
        //
        ////////////////////////////////////

    public:
        ///////////////////////////////////////
        // Ihr Code hier:
        Tree();
        ~Tree();
        void addNode(string name, int age, double income, int postCode);
        bool deleteNode(int ID);
        bool searchNode(std::string name);
        void printAll();

        //
        ////////////////////////////////////
        // friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
        // bleiben!
        friend TreeNode* get_anker(Tree& TN);
    };


    void printHead();
    void printFooter();
}