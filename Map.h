#pragma once
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Map
{
private:
    struct Node
    {
        Movie mov;
        int tconst;
        int height;
        Node *left;
        Node *right;
        Node(Movie m, int i) : mov(m), tconst(i), height(1), left(nullptr), right(nullptr){};
    };

    Node *root = nullptr;
    Map::Node *InsertHelper(Node *root, Movie mov, int tconst);
    int height(Node *root);
    Map::Node *RightRotation(Node *root);
    Map::Node *LeftRotation(Node *root);
    void HelperSearchByGenre(Node *root, string genre, vector<pair<double, Movie *>> &genreTitles);
    void HelperSearchByYear(Node *root, int year, vector<pair<double, Movie *>> &yearTitles);
    pair<double, Movie *> HelperSearchByTConst(Map::Node *root, int tconst);
    Movie* HelperSearchByName(Map::Node *root, string name);

public:
    void Insert(Movie mov, int tconst);
    void SearchByGenre(string genre, vector<pair<double, Movie *>> &genreTitles);
    void SearchByYear(int year, vector<pair<double, Movie *>> &yearTitles);
    pair<double, Movie *> SearchByTConst(int tconst);
    Movie* SearchByName(string name);
};

void Map::Insert(Movie mov, int tconst)
{
    this->root = InsertHelper(this->root, mov, tconst);
}

// Citation: Module 4 - Balanced tree slides for logic
Map::Node *Map::InsertHelper(Node *root, Movie mov, int tconst)
{
    if (root == nullptr)
        return new Node(mov, tconst);
    else if (tconst < root->tconst)
        root->left = InsertHelper(root->left, mov, tconst);
    else
        root->right = InsertHelper(root->right, mov, tconst);

    // calculate heights and balance
    root->height = height(root);

    int balanceFactor = height(root->left) - height(root->right);

    // if it is right heavy
    if (balanceFactor < -1)
    {
        // if tree's right subtree is left heavy, do right-left rotation
        if ((height(root->right->left) - height(root->right->right) == 1))
        {
            root->right = RightRotation(root->right);
            return LeftRotation(root);
        }
            // do left rotation
        else
            return LeftRotation(root);
    }
        // if it is left heavy
    else if (balanceFactor > 1)
    {
        if (height(root->left->left) - height(root->left->right) == -1)
        {
            root->left = LeftRotation(root->left);
            return RightRotation(root);
        }
        else
            return RightRotation(root);
    }
    return root;
}

// Citation: Solution to Stepik 5.2a on Canvas
int Map::height(Node *root)
{
    if (root == nullptr)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Citation: Solution to Stepik 5.1a on Canvas
Map::Node *Map::RightRotation(Node *root)
{
    Node *leftChild = root->left;
    root->left = leftChild->right;
    leftChild->right = root;

    root->height = height(root);
    leftChild->height = height(leftChild);

    return leftChild;
}

Map::Node *Map::LeftRotation(Node *root)
{
    Node *rightChild = root->right;
    root->right = rightChild->left;
    rightChild->left = root;

    root->height = height(root);
    rightChild->height = height(rightChild);

    return rightChild;
}

void Map::SearchByGenre(string genre, vector<pair<double, Movie *>> &genreTitles)
{
    HelperSearchByGenre(this->root, genre, genreTitles);
}

void Map::HelperSearchByGenre(Map::Node *root, string genre, vector<pair<double, Movie *>> &genreTitles)
{
    if (root == nullptr)
        cout << "";
    else
    {
        //Push back genres for particular movie:
        HelperSearchByGenre(root->left, genre, genreTitles);
        for (int i = 0; i < root->mov.getGenres().size(); i++)
        {
            if (root->mov.getGenres()[i] == genre)
                genreTitles.push_back(make_pair(root->mov.getRating(), &root->mov));
        }
        HelperSearchByGenre(root->right, genre, genreTitles);
    }
}

void Map::SearchByYear(int year, vector<pair<double, Movie *>> &yearTitles)
{
    HelperSearchByYear(this->root, year, yearTitles);
}

void Map::HelperSearchByYear(Map::Node *root, int year, vector<pair<double, Movie *>> &yearTitles)
{
    if (root != nullptr)
    {
        HelperSearchByYear(root->left, year, yearTitles);

        //Push back all titles for a certain year:
        if (root->mov.getYear() == year)
            yearTitles.push_back(make_pair(root->mov.getRating(), &root->mov));

        HelperSearchByYear(root->right, year, yearTitles);
    }
}

pair<double, Movie *> Map::SearchByTConst(int tconst)
{
    return HelperSearchByTConst(this->root, tconst);
}

pair<double, Movie *> Map::HelperSearchByTConst(Map::Node *root, int tconst)
{
    //Search for ID:
    if (root != nullptr)
    {
        auto var = HelperSearchByTConst(root->right, tconst);

        if (root->mov.getTconst() == tconst)
            return make_pair(root->mov.getRating(), &root->mov);
        if (var.second)
            return var;
        return HelperSearchByTConst(root->left, tconst);
    }

    return make_pair(0, nullptr);
}

Movie *Map::SearchByName(string name)
{
    return HelperSearchByName(this->root, name);
}

Movie *Map::HelperSearchByName(Map::Node *root, string name)
{
    //Search for movie's name in ordered map:
    if (root != nullptr)
    {
        auto var = HelperSearchByName(root->right, name);

        if (root->mov.getTitle() == name)
            return &root->mov;
        if (var)
            return var;
        return HelperSearchByName(root->left, name);
    }

    return nullptr;
}