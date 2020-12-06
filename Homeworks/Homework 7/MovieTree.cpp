#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}
/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}
/* ------------------------------------------------------ */

void _grader_inorderTraversal(TreeNode * root) {
		if (root == NULL) {
			return;
		}

		_grader_inorderTraversal(root->leftChild);
		cout << root->titleChar << " ";
		_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}



TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

void showMovieCollectionHelper(TreeNode *node){ //inorder traveral of bst
	if(node == nullptr)
		return;
	showMovieCollectionHelper(node->leftChild);
	LLMovieNode *temp = node->head;
	cout << "Movies starting with letter: " << node->titleChar << endl;
	while(temp != nullptr){ //print out the LL of the BST node
		cout << " >> " << temp->title << " " << temp->rating << endl;
		temp = temp->next;
	}
	showMovieCollectionHelper(node->rightChild);
}

void MovieTree::showMovieCollection(){
	showMovieCollectionHelper(root);
}


TreeNode *newTreeNode(TreeNode *parentNode, LLMovieNode *treeNodeHead){
	TreeNode *newNode 	= new TreeNode();
	newNode->parent 	= parentNode;
	newNode->titleChar 	= treeNodeHead->title[0];
	newNode->head 		= treeNodeHead;
	newNode->leftChild 	= nullptr;
	newNode->rightChild = nullptr;
	return newNode;
}

void insertMovieHelper(TreeNode *currentRoot, LLMovieNode *newMovie){
	if(currentRoot->titleChar == newMovie->title[0]){ //check if the current root's char matches the newMovie's title char
		if(currentRoot->head == nullptr || currentRoot->head->title >= newMovie->title){
			newMovie->next = currentRoot->head;
			currentRoot->head = newMovie;
		}
		else{
			LLMovieNode *curr = currentRoot->head;
			while (curr->next != nullptr && curr->next->title < newMovie->title)
				curr = curr->next;
			newMovie->next = curr->next;
			curr->next = newMovie;
		}
	}
	else if(currentRoot->titleChar > newMovie->title[0]){ //go left in BST
		if(currentRoot->leftChild == nullptr){ //left child does not exist
			TreeNode *newNode 		= newTreeNode(currentRoot, newMovie);
			newNode->head 			= newMovie;
			currentRoot->leftChild 	= newNode;
		}
		else 
			insertMovieHelper(currentRoot->leftChild, newMovie);
	}
	else if(currentRoot->titleChar < newMovie->title[0]){ //go right  in BST
		if(currentRoot->rightChild == nullptr){ //right child does not exist
			TreeNode *newNode 		= newTreeNode(currentRoot, newMovie);
			newNode->head 			= newMovie;
			currentRoot->rightChild = newNode;
		}
		else 
			insertMovieHelper(currentRoot->rightChild, newMovie);
	}
}

void MovieTree::insertMovie(int ranking, std::string title, int year, float rating){
	if(root == nullptr)
		root = newTreeNode(nullptr, getLLMovieNode(ranking, title, year, rating));
	else
		insertMovieHelper(root, getLLMovieNode(ranking, title, year, rating));
}

void MovieTree::leftRotation(TreeNode* curr){
	if(curr->rightChild == nullptr)
		return;
	TreeNode *temp = curr->rightChild;
	if(curr == root)
		root = temp;
	else if(curr->parent->leftChild == curr)
		curr->parent->leftChild = temp;
	else
		curr->parent->rightChild = temp;
	curr->rightChild = temp->leftChild;
	if(temp->leftChild)
		temp->leftChild->parent = curr;
	temp->leftChild = curr;
	temp->parent = curr->parent;
	curr->parent = temp;
}

TreeNode *minValueNode(TreeNode *node){
	TreeNode *curr = node;
	while(curr && curr->leftChild != nullptr)
		curr = curr->leftChild;
	return curr;
}

TreeNode *deleteNode(TreeNode *node, string title, char titleChar){
	if(!node)
		return nullptr;
	if(titleChar < node->titleChar)
		node->leftChild = deleteNode(node->leftChild, title, titleChar);
	else if(titleChar > node->titleChar)
		node->rightChild = deleteNode(node, title, titleChar);
	else{
		if(!node->leftChild){
			TreeNode *temp = node->rightChild;
			delete node;
			return temp;
		}
		else if(!node->rightChild){
			TreeNode *temp = node->leftChild;
			delete node;
			return temp;
		}
		TreeNode *temp = minValueNode(node->rightChild);

		node->titleChar = temp->titleChar;
		//copy the rest of the data too
		node->rightChild = deleteNode(node->rightChild, title, titleChar);
	}
	return node;
	
}

TreeNode* removeMovieRecordHelper(TreeNode* node, string title){
	if (node == NULL){
		cout << "Movie not found." << endl;
		return node;
	}
	else{
		if (title[0] < node->titleChar)
			node->leftChild = removeMovieRecordHelper(node->leftChild, title);
		else if (title[0] > node->titleChar)
			node->rightChild = removeMovieRecordHelper(node->rightChild, title);
		else if (title[0] == node->titleChar){
			LLMovieNode* curr = node->head;
			LLMovieNode* prev = NULL;
			while (curr && curr->title != (title)){
				prev = curr;
				curr = curr->next;
			}
			if (!curr){
				cout << "Movie not found." << endl;
				return node;
			}
			if (!prev && node->head->next){
				LLMovieNode *temp = node->head->next;
				delete node->head;
				node->head = temp;     
				return node;
			}
			if (prev && curr){
				prev->next = curr->next;     
				delete curr;     
				return node;
			}
			if (!node->leftChild && !node->rightChild){
				delete node->head;
				delete node;
				node = NULL;
			}
			else if (!node->leftChild){
				TreeNode *tempNode = node;
				node->rightChild->parent = node->parent;
				node = node->rightChild;          
				delete tempNode->head;
				delete tempNode;
			}
			else if (!node->rightChild){
				TreeNode *tempNode = node;
				node->leftChild->parent = node->parent;
				node = node->leftChild;          
				delete tempNode;
			}
			else{
				TreeNode* minValueNode = node->rightChild;
				while (minValueNode->leftChild)
					minValueNode = minValueNode->leftChild;
				node->head = minValueNode->head;
					node->titleChar = minValueNode->titleChar;
				node->rightChild = removeMovieRecordHelper(node->rightChild, minValueNode->head->title);
			}
		}
	}
  	return node;
}

void MovieTree::removeMovieRecord(std::string title){
	root = removeMovieRecordHelper(root, title);
}


void deleteTree(TreeNode *node){
	if(!node)
		return;
	LLMovieNode *curr = node->head;
	while (curr){
		node->head = curr->next;
		delete curr;
		curr = node->head;
	}
	delete node->head;
	deleteTree(node->leftChild);	
	deleteTree(node->rightChild);	
	delete node;
}

MovieTree::~MovieTree(){
	deleteTree(root);
	root = nullptr;
}