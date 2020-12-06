#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() {
  root = nullptr;
}

void movieTreeHelper(MovieNode *node){ 
  if(node == nullptr) return;
  movieTreeHelper(node->left);
  movieTreeHelper(node->right);
  delete node;
}

MovieTree::~MovieTree() {
  movieTreeHelper(root);
}

void printMovieInventoryHelper(MovieNode *node){
  if(node == nullptr)
    return;
  printMovieInventoryHelper(node->left);
  cout << "Movie: " << node->title << " " << node->rating << endl;
  printMovieInventoryHelper(node->right);
}

void MovieTree::printMovieInventory() {
   if(root == nullptr)
    cout << "Tree is Empty. Cannot print" << endl;
  else
    printMovieInventoryHelper(root);
}

void addMovieNodeHelper(MovieNode *newNodeParent, MovieNode *newNode) {
  if(newNodeParent->title > newNode->title) //go to left
    if(newNodeParent->left == nullptr)
      newNodeParent->left = newNode;
    else
      addMovieNodeHelper(newNodeParent->left, newNode);
  else //go to right
    if(newNodeParent->right == nullptr) 
      newNodeParent->right = newNode;
    else
      addMovieNodeHelper(newNodeParent->right, newNode);
    
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  MovieNode *newNode = new MovieNode;
  newNode->title = title;
  newNode->ranking = ranking;
  newNode->rating = rating;
  newNode->year = year;
  newNode->left = nullptr;
  newNode->right = nullptr;
  if(root == nullptr)
    root = newNode;
  else
    addMovieNodeHelper(root, newNode);
}

bool findMovieHelper(MovieNode *node, string title){
  if(node == nullptr)
    return false;
  if(node->title == title){
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << node->ranking << endl;
    cout << "Title  :" << node->title << endl;
    cout << "Year   :" << node->year << endl;
    cout << "rating :" << node->rating << endl;
    return true;
  }
  bool res1 = findMovieHelper(node->left, title);
  if(res1)
    return true;
  return findMovieHelper(node->right, title);
}

void MovieTree::findMovie(string title) {
  if(!findMovieHelper(root, title))
    cout << "Movie not found." << endl;
}

void queryMoviesHelper(MovieNode *node, float rating, float year){
  if(node == nullptr)
    return;
  if(node->rating >= rating && node->year >= year)
    cout << node->title << "(" << node->year << ") " << node->rating << endl;
  queryMoviesHelper(node->left, rating, year);
  queryMoviesHelper(node->right, rating, year);
}

void MovieTree::queryMovies(float rating, int year) {
   cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
   queryMoviesHelper(root, rating, year);
}

void averageRatingHelper(MovieNode *node, int &numOfMovies, float &ratingsSum){
  if(node == nullptr)
    return;
  numOfMovies++;
  ratingsSum += node->rating;
  averageRatingHelper(node->left, numOfMovies, ratingsSum);
  averageRatingHelper(node->right, numOfMovies, ratingsSum);
}

void MovieTree::averageRating() {
  int numOfMovies = 0;
  float ratingsSum = 0; //avg = ratingsSum/numOfMovies
  averageRatingHelper(root, numOfMovies, ratingsSum);
  if(numOfMovies == 0)
    cout << "Average rating:0.0" << endl;
  else
    cout << "Average rating:" << ratingsSum/numOfMovies << endl;
}

void printLevelNodesHelper(MovieNode *node, int k){
  if(node == nullptr)
    return;
  if(k == 0)
    cout << "Movie: " << node->title << " " << node->rating << endl;
  else if(k > 0){
    printLevelNodesHelper(node->left, k - 1);
    printLevelNodesHelper(node->right, k - 1);
  }
}

void MovieTree::printLevelNodes(int k) {
  printLevelNodesHelper(root, k);
}
