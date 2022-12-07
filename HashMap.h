#pragma once
#include <iostream>
#include <list>
#include "Movie.h"
#include <algorithm>
#include<bits/stdc++.h>
#include<string>
#include<locale>
#include <cctype>
#include <vector>
#include <chrono>
using namespace std;

class HashMap
{
private:
    vector<list<Movie>> *movieMap;
    double maxLoadFactor;

public:
    int elementCount;
    int mapsize;
    HashMap(int bucketSize, double maxLoadFactor);
    void insert(Movie movie);
    Movie searchByTitle(string title);
    int hashFunction(int key);
    void print();
    vector<pair<double,int>> searchByGenre(string genre);
    vector<pair<double, int>> searchByYear(int year);
    Movie searchByTconst(int id);
    void reHashing();
    double getLoadFactor();
};

//constructor
HashMap::HashMap(int bucketSize, double maxLoadFactor)
{
    this->elementCount=0;
    this->maxLoadFactor=maxLoadFactor;
    this->mapsize=bucketSize;
    movieMap = new vector<list<Movie>>(mapsize, list<Movie>(0));
}
double HashMap::getLoadFactor()
{
    return double(elementCount/mapsize);
}


//hashing function
int HashMap::hashFunction(int key)
{
    return (key % mapsize);
}

void HashMap::reHashing()
{
    int oldMapsize=this->mapsize;
    this->mapsize=this->mapsize*2;
    vector<list<Movie>> *temp =new vector<list<Movie>>(mapsize, list<Movie>(0));

    for(auto b: *movieMap)
    {
        for (auto a: b)
        {
            int index = hashFunction(a.getTconst());
            (*temp)[index].push_back(a);
        }
    }
    delete movieMap;
    movieMap=temp;
}

//insert into hashmap
void HashMap::insert(Movie movie)
{
    int index = hashFunction(movie.getTconst());
    (*movieMap)[index].push_back(movie);
    elementCount++;

    if (double(elementCount/mapsize) >=maxLoadFactor)
        reHashing();
}

//search by title
Movie HashMap::searchByTitle(string title)
{
    for (int i = 0; i < mapsize; i++)
    {
        for (auto x : (*movieMap)[i])
        {
            if (x.getTitle() == title)
                return x;
        }
    }
    Movie nullMovie;
    return nullMovie;
}

//search by genre
vector<pair<double,int>> HashMap::searchByGenre(string genre)
{
    vector<pair<double,int>> temp;

    for (int i = 0; i < mapsize; i++)
    {
        for (auto x : (*movieMap)[i])
            for(auto s: x.getGenres())

                if(s == genre)
                {
                    temp.push_back(make_pair(x.getRating(), x.getTconst()));
                }
    }
    sort(temp.begin(), temp.end(), greater<>());
    return temp;
}

//search by year
vector<pair<double, int>> HashMap::searchByYear(int year)
{
    vector<pair<double, int>> temp;

    for (int i = 0; i < mapsize; i++)
    {
        for (auto x : (*movieMap)[i])
            if(year == x.getYear())
            {
                temp.push_back(make_pair(x.getRating(),x.getTconst()));
            }

    }
    sort(temp.begin(), temp.end(),greater<>());
    return temp;
}

//search by movie_id
Movie HashMap::searchByTconst(int id)
{
    int key= hashFunction(id);

    for (int i = 0; i < mapsize; i++)
    {
        for (auto x : (*movieMap)[i])
            if(id == x.getTconst())
            {
                return x;
            }

    }
    Movie nullMovie;
    return nullMovie;
}
