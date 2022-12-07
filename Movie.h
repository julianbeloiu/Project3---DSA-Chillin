#pragma once
#include <iostream>
#include<vector>
using namespace std;

class Movie
{
private:
    int tconst;
    string title;
    int year;
    int runtime;
    vector<string> genres;
    double rating;

public:
    Movie(int tconst, string title, int year, int runtime, vector<string> genres, double rating);
    Movie();
    int getTconst();
    string getTitle();
    int getYear();
    int getRuntime();
    vector<string> getGenres();
    double getRating();

};

Movie::Movie()
{
    this->tconst = 0;
    this->title = "";
    this->year = 0;
    this->runtime = 0;
    this->genres = {};
    this->rating = 0.0;
}

Movie::Movie(int tconst, string title, int year, int runtime, vector<string> genres, double rating)
{
    this->tconst = tconst;
    this->title = title;
    this->year = year;
    this->runtime = runtime;
    this->genres = genres;
    this->rating = rating;
}


int Movie::getTconst()
{
    return this->tconst;
}

string Movie::getTitle()
{
    return this->title;
}

int Movie::getYear()
{
    return this->year;
}
int Movie::getRuntime()
{
    return this->runtime;
}
vector<string> Movie::getGenres()
{
    return this->genres;
}
double Movie::getRating()
{
    return this->rating;
}