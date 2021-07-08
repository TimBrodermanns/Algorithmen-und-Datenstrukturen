/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <queue>
#include <iomanip>
#include <iostream>


using namespace std;

////////////////////////////////////
// Ihr Code hier:
// Private start 
namespace Red_Black_Tree {

	Tree::Tree() {
		this->anker = nullptr;
		this->currentNodeChronologicalID = 0;
	}

	Tree::~Tree() {
		while (!this->anker) _deleteNode(this->anker, this->anker->getNodeOrderID());
	}

	int computeHeight(TreeNode* p) {
		// traversiere den Baum in Postorder
		if (p == nullptr) {
			return 0; // nicht existierende Knoten haben die Höhe -1 (= ein Niveau unter dem Blattknoten)
		}
		int height = 0;
		int leftHeight = computeHeight(p->getLeft());
		int rightHeight = computeHeight(p->getRight());

		// Höhe des Knotens bestimmen

		height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

		return height;
	}

	bool is4Node(TreeNode* Node) {
		if (!Node->getRed())
			if (Node->getLeft())
				if (Node->getRight())
					if (Node->getRight()->getRed())
						if (Node->getLeft()->getRed())
							return true;
		return false;
	}

	bool Tree::split4Node(TreeNode* split) {
		if (split->getRed() == false) {
			if (split->getLeft() != nullptr && split->getRight() != nullptr) {
				if (split->getRight()->getRed() && split->getLeft()->getRed()) {
					split->setRed(true);
					if (split == anker) {
						split->setRed(false);
					}
					else {
						split->setRed(true); // Parent wird auf rot gesetzt
					}
					split->getLeft()->setRed(false);
					split->getRight()->setRed(false);
					return true;
				}
			}
		}
		return false;
	}


	int Tree::proofRBCriterion(TreeNode* StartPoint) {
		int ret = proofRB(this->anker);
		if (ret > 0) {
			cout << "Höhe: " << ret << endl;
		}
		else {
			cout << "Baum Korrupt" << endl;
		}
		return ret;
	}

	int Tree::proofRB(TreeNode* p) {

		if (p == nullptr) {
			return -1;
		}

		TreeNode* lc = p->getLeft();
		TreeNode* rc = p->getRight();

		if (!lc && rc) {														// Nur rechtes Kind
			int rightHeight = proofRB(rc);
			return rc->getRed() ? rightHeight : rightHeight + 1;
		}
		else if (lc && !rc) {												// Nur Linkes Kind
			int leftHeight = proofRB(lc);
			return lc->getRed() ? leftHeight : leftHeight + 1;
		}
		else if (!lc && !rc) return 0;										// Kein Kind
		else if (lc && rc) {
			if (lc->getRed() && rc->getRed()) {								// Beide Kinder Rot
				int leftHeight = proofRB(lc);
				int rightHeight = proofRB(rc);
				if (leftHeight == rightHeight) return leftHeight;
			}

			else if (!lc->getRed() && !rc->getRed()) {						//Beide Kinder schwarz
				int leftHeight = proofRB(lc);
				int rightHeight = proofRB(rc);
				if (leftHeight == rightHeight) return leftHeight + 1;
			}

			else if (!lc->getRed() && rc->getRed()) {						// Ein Kind Rot
				int heightOfRedChild = proofRB(rc);
				int heightOfBlackChild = proofRB(lc);
				if (heightOfRedChild - heightOfBlackChild == 1) return heightOfRedChild;
			}
			else if (lc->getRed() && !rc->getRed()) {	//Das ander Kind ist Rot
				int heightOfRedChild = proofRB(lc);
				int heightOfBlackChild = proofRB(rc);
				if (heightOfRedChild - heightOfBlackChild == 1) return heightOfRedChild;
			}
		}
	}

	void Tree::balance(TreeNode* tree) {

		if (tree != nullptr) {
			balance(tree->getLeft());
			balance(tree->getRight());

			if (tree->getRed() && tree->getParent()->getRed()) {

				TreeNode* p2 = tree;                            // wenn Rot
				TreeNode* p1 = tree->getParent();               // wenn rot 
				TreeNode* pp = tree->getParent()->getParent();

				if (pp->getRight() == p1 && p1->getRight() == p2) { //Einfache Linksrotation
					rotateTreeLeft(pp, p1);
				}
				if (pp->getLeft() == p1 && p1->getLeft() == p2) { //Einfache Rechtsrotation
					rotateTreeRight(pp, p1);
				}
				if (pp->getLeft() == p1 && p1->getRight() == p2) { //Links-Rechts Rotation 
					rotateTreeLeft(p1, p2);
					rotateTreeRight(pp, p2);
				}
				if (pp->getRight() == p1 && p1->getLeft() == p2) { //Rechts-Links Rotation 
					rotateTreeRight(p1, p2);
					rotateTreeLeft(pp, p2);
				}
			}
		}
	}

	bool Tree::rotateTreeRight(TreeNode* pp, TreeNode* p2) {
		TreeNode* pparent = pp->getParent();
		TreeNode* p2back = p2;
		TreeNode* ppback = pp;
		if (pparent == nullptr) {// Wenn der Anker Rotiert werden soll
			if (p2->getRight() != nullptr) {
				p2->getRight()->setParent(ppback);
				ppback->setLeft(p2->getRight());
				ppback->getRight()->setParent(ppback);
			}
			else {
				ppback->setLeft(nullptr);
			}
			p2back->setParent(nullptr);
			p2back->setRight(ppback);
			ppback->setParent(p2back);
			ppback->setRed(true);
			p2back->setRed(false);
			this->anker = p2back;
			return true;
		}
		pp->setLeft(p2->getRight());
		p2->setRight(pp);
		if (pparent->getNodeOrderID() > p2->getNodeOrderID()) {
			pparent->setLeft(p2);
		}
		else {
			pparent->setRight(p2);
		}
		p2->setParent(pparent);
		pp->setParent(p2);
		p2->setRed(false);
		pp->setRed(true);
		return true;
	}

	bool Tree::rotateTreeLeft(TreeNode* p1, TreeNode* p2) {
		TreeNode* Parent = p1->getParent();
		TreeNode* p2back = p2;
		TreeNode* p1back = p1;
		if (Parent == nullptr) {// Wenn der Anker Rotiert werden soll
			if (p2->getLeft() != nullptr) {
				p2->getLeft()->setParent(p1back);
				p1back->setRight(p2->getLeft());
				p1back->getLeft()->setParent(p1back);
			}
			else {
				p1back->setRight(nullptr);
			}
			p2back->setParent(nullptr);
			p2back->setLeft(p1back);
			p1back->setParent(p2back);
			p1back->setRed(true);
			p2back->setRed(false);
			this->anker = p2back;
			return true;
		}
		p2 = p1->getRight();
		p1->setRight(p2->getLeft());
		p2->setLeft(p1);
		if (Parent->getNodeOrderID() > p2->getNodeOrderID()) {
			Parent->setLeft(p2);
		}
		else {
			Parent->setRight(p2);
		}
		p2->setParent(Parent);
		p1->setParent(p2);
		p2->setRed(false);
		p1->setRed(true);

		return true;
	}

	// Private End
	// Public start

	void Tree::addNode(string name, int age, double income, int postCode) {

		if (this->currentNodeChronologicalID == 0) {
			this->currentNodeChronologicalID++;
			this->anker = new TreeNode(age + income + postCode, this->currentNodeChronologicalID, name, age, income, postCode, false);
			return;
		}
		this->currentNodeChronologicalID++;

		TreeNode* newNode = new TreeNode(age + income + postCode, this->currentNodeChronologicalID, name, age, income, postCode);
		TreeNode* temp = this->anker;
		while (true) {
			split4Node(temp);
			if (temp->getNodeOrderID() < newNode->getNodeOrderID()) {
				if (temp->getRight() != nullptr) {
					temp = temp->getRight();
					balance(anker);
				}
				else {
					temp->setRight(newNode);
					newNode->setParent(temp);
					balance(this->anker);
					break;
				}
			}
			else {
				if (temp->getLeft() != nullptr) {
					temp = temp->getLeft();
					balance(anker);
				}
				else {
					temp->setLeft(newNode);
					newNode->setParent(temp);
					balance(this->anker);
					break;
				}
			}
		}
	}

	bool Tree::searchNode(std::string name) {
		bool gefunden = false;
		cout << " -> Search for: " << name << " <-" << std::endl;
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

	void Tree::printLevelOrder() {

		cout << this->proofRB(anker) << endl;

		// BST wird in Levelorder mit Hilfe einer Queue ausgegeben

		TreeNode* root = anker;

		// 2 Queues instanzieren (1 Punkt)
		std::queue<TreeNode*> q;
		std::queue<int> nq;
		if (root == nullptr) {
			cout << "BST ist leer" << std::endl;
			return;
		}
		// Wurzelknoten und Startniveau in die Queues pushen (1 Punkt)
		q.push(root);
		nq.push(0);

		// vorheriges Niveau merken bzw. den Niveauwechsel irgendwie mitbekommen (1 Punkt)
		int prev_niveau = -1;
		int niveau;

		// Schleife 6 Punkte
		while (!q.empty()) {
			// Entnahme aus den Queues und löschen (2 Punkte)
			TreeNode* curr = q.front();
			q.pop();
			niveau = nq.front();
			nq.pop();


			// Ausgabe Niveauwechsel (1 Punkt)
			if (prev_niveau != niveau) {
				cout << std::endl << "Niveau " << niveau << ": ";
				prev_niveau = niveau;
			}

			cout << "( " << ((curr->getLeft()) ? to_string(curr->getLeft()->getNodeOrderID()) + " | " : "") << curr->getNodeOrderID() << ((curr->getRight()) ? " | " + to_string(curr->getRight()->getNodeOrderID()) : "") << " ) ";

			if (!curr->getRed()) {
				if (curr->getLeft() && curr->getLeft()->getLeft()) {
					q.push(curr->getLeft()->getLeft());
					nq.push(niveau + 1);
				}
				if (curr->getLeft() && curr->getLeft()->getRight()) {
					q.push(curr->getLeft()->getRight());
					nq.push(niveau + 1);
				}
				if (curr->getRight() && curr->getRight()->getLeft()) {
					q.push(curr->getRight()->getLeft());
					nq.push(niveau + 1);
				}
				if (curr->getRight() && curr->getRight()->getRight()) {
					q.push(curr->getRight()->getRight());
					nq.push(niveau + 1);
				}
			}
			else {
				if (curr->getLeft()) {
					q.push(curr->getLeft());
					nq.push(niveau + 1);
				}
				if (curr->getRight()) {
					q.push(curr->getRight());
					nq.push(niveau + 1);
				}
			}
		}
		cout << endl;
		return;
	}

	void Tree::printLevelOrder(int pos) {

		// BST wird in Levelorder mit Hilfe einer Queue ausgegeben

		TreeNode* root = anker;

		// 2 Queues instanzieren (1 Punkt)
		std::queue<TreeNode*> q;
		std::queue<int> nq;
		if (root == nullptr) {
			cout << "BST ist leer" << std::endl;
			return;
		}
		// Wurzelknoten und Startniveau in die Queues pushen (1 Punkt)
		q.push(root);
		nq.push(0);

		// vorheriges Niveau merken bzw. den Niveauwechsel irgendwie mitbekommen (1 Punkt)
		int prev_niveau = -1;
		int niveau;

		// Schleife 6 Punkte
		while (!q.empty()) {
			// Entnahme aus den Queues und löschen (2 Punkte)
			TreeNode* curr = q.front();
			q.pop();
			niveau = nq.front();
			nq.pop();


			// Ausgabe Niveauwechsel (1 Punkt)
			if (prev_niveau != niveau) {
				if (niveau == pos) cout << std::endl << "Niveau " << niveau << ": ";
				prev_niveau = niveau;
			}

			if (niveau == pos) cout << "( " << ((curr->getLeft()) ? to_string(curr->getLeft()->getNodeOrderID()) + " | " : "") << curr->getNodeOrderID() << ((curr->getRight()) ? " | " + to_string(curr->getRight()->getNodeOrderID()) : "") << " ) ";
			if (niveau > pos) return;

			if (!curr->getRed()) {
				if (curr->getLeft() && curr->getLeft()->getLeft()) {
					q.push(curr->getLeft()->getLeft());
					nq.push(niveau + 1);
				}
				if (curr->getLeft() && curr->getLeft()->getRight()) {
					q.push(curr->getLeft()->getRight());
					nq.push(niveau + 1);
				}
				if (curr->getRight() && curr->getRight()->getLeft()) {
					q.push(curr->getRight()->getLeft());
					nq.push(niveau + 1);
				}
				if (curr->getRight() && curr->getRight()->getRight()) {
					q.push(curr->getRight()->getRight());
					nq.push(niveau + 1);
				}
			}
			else {
				if (curr->getLeft()) {
					q.push(curr->getLeft());
					nq.push(niveau + 1);
				}

				if (curr->getRight()) {
					q.push(curr->getRight());
					nq.push(niveau + 1);
				}
			}
		}
		cout << endl;
		return;
	}

	// public end
	// HelpFunktions

	void printHead() {
		cout << " +----------------------+---------------+-------+---------------+---------------+---------------+" << std::endl;
		cout << " | ChronologicalID \t| Name \t\t| Age	| Income \t| PostCode \t| OrderID \t| Address \t| Left address| Rigth Address| Parent Address|" << std::endl;
		cout << " +----------------------+---------------+-------+---------------+---------------+---------------+" << std::endl;
	}

	void printFooter() {
		cout << " +----------------------+---------------+-------+---------------+---------------+---------------+" << std::endl << std::endl << std::endl;
	}

	//
	////////////////////////////////////
}