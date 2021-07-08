/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>


using namespace std;

////////////////////////////////////
// Ihr Code hier:

namespace BST {

	Tree::Tree() {}
	Tree::~Tree() {}

	void Tree::addNode(string name, int age, double income, int postCode) {
		TreeNode* newTreeNode = new TreeNode(age + income + postCode, this->currentNodeChronologicalID, name, age, income, postCode);
		if (this->currentNodeChronologicalID == 0) {
			this->anker = newTreeNode;
			this->currentNodeChronologicalID++;
			return;
		}
		this->currentNodeChronologicalID++;
		addToTree(this->anker, newTreeNode);
	}

	bool Tree::deleteNode(int OrderID) {
		return _deleteNode(this->anker, OrderID);
	}

	bool Tree::searchNode(std::string name) {
		bool gefunden = false;
		std::cout << " -> Search for: " << name << " <-" << std::endl;
		printHead();
		ValueInTree(this->anker, name, gefunden);
		printFooter();

		return gefunden;
	}
	void Tree::printAll() {
		printHead();
		PrintNode(this->anker);
		printFooter();
	}

	void printHead() {
		std::cout << " +----------------------+---------------+-------+---------------+---------------+---------------+" << std::endl;
		std::cout << " | ChronologicalID \t| Name \t\t| Age	| Income \t| PostCode \t| OrderID \t|" << std::endl;
		std::cout << " +----------------------+---------------+-------+---------------+---------------+---------------+" << std::endl;
	}
	void printFooter() {
		std::cout << " +----------------------+---------------+-------+---------------+---------------+---------------+" << std::endl << std::endl << std::endl;
	}
}
//
////////////////////////////////////