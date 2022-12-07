/*
 References: Julian Beloiu's submission for Project 1 - AVL Tree, Module 4 Balanced Trees Slides,
 Solution to stepik 5.2a, stepik 5.1a, Sets, Maps, and Hash table slides, cpp reference
 */

#include <iostream>
#include <tuple>
#include <chrono>
#include <vector>
#include "Movie.h"
#include "HashMap.h"
#include "Map.h"
#include <iomanip>
using namespace std;
using namespace std::chrono;

void LoadTitles(HashMap& hm, Map& om);
void LoadActors(vector<pair<string, vector<int>>>& actorVector);
void displayVector(HashMap& hm, vector<pair<double,int>> vec, int n);
void displayOrderedVector(Map& om, vector<pair<double,Movie*>> vec, int n);

int main()
{
    HashMap moviesHashMap(80000, 0.80);

    Map orderedMap;
    LoadTitles(moviesHashMap, orderedMap);
    cout << "Titles loaded" << endl;

    // format for this is pair<actor's name, vector of strings for all movies>
    // when iterating:
    // actorVector[i].first accesses each actor's name. For example, actorVector[i] might be "Brad Pitt"
    // actorVector[i].second[j] accesses their movies ex: Mr. & Mrs. Smith or
    vector<pair<string, vector<int>>> actorVector;
    LoadActors(actorVector);
    cout << "Actors loaded" << endl;

    cout << "---------------------------------" << endl
         << "Welcome to the DSA and Chill menu!" << endl
         << "---------------------------------" << endl;

    int menuInput, menuInput2, yearInput;
    menuInput = menuInput2 = yearInput = 0;
    string selectionInput;
    string titleInput;

    while (true)
    {
        if(menuInput < 0 || menuInput > 5)
            cout << endl << "Invalid choice. Please try again." << endl << endl;

        cout << "What would you like to do?" << endl
             << "1: Find Top Movies By Genre" << endl
             << "2: Find Top Movies by Actor" << endl
             << "3: Find Top Movies by Year" << endl
             << "4: Search All Movies for Title" << endl
             << "5: Exit Menu\n" << endl
             << "Your Selection:" << endl;

        cin >> menuInput;

        if (menuInput == 1)
        {
            cout << endl << "Enter Genre:" << endl;
            cin >> selectionInput;

            cout << endl << "What data structure would you like to use?" << endl
                 << "1: Hash Table" << endl
                 << "2: Ordered Map" << endl << endl
                 << "Your Selection:" << endl;
            cin >> menuInput2;

            if (menuInput2 == 1)
            {
                auto start = steady_clock::now();
                vector<pair<double, int>> genreTitles;
                genreTitles = moviesHashMap.searchByGenre(selectionInput);
                displayVector(moviesHashMap,genreTitles, 20);
                auto end = steady_clock::now();
                cout<<endl<<"SearchbyGenre time for HashMap: "
                    << duration_cast<chrono::milliseconds>(end - start).count()<<" ms."<< endl;
            }
            else if (menuInput2 == 2)
            {
                auto start = steady_clock::now();
                vector<pair<double, Movie*>> genreTitles;
                orderedMap.SearchByGenre(selectionInput, genreTitles);
                sort(genreTitles.begin(), genreTitles.end(), greater<>());
                displayOrderedVector(orderedMap, genreTitles, 20);
                auto end = steady_clock::now();
                cout<<endl<< "SearchbyGenre time for Ordered Map: "
                    << duration_cast<milliseconds>(end - start).count()<<" ms."<<endl;
            }
        }
        else if (menuInput == 2)
        {
            cout << endl << "Enter Actor Name: " << endl;
            cin.ignore();
            getline(cin, selectionInput, '\n');

            cout <<endl<< "What data structure would you like to use?" << endl
                 << "1: Hash Table" << endl
                 << "2: Ordered Map" << endl << endl
                 << "Your Selection: "<<endl;
            cin >> menuInput2;

            if (menuInput2 == 1)
            {
                // Hash table
                vector<pair<double, int>> actorMovies;
                auto start = steady_clock::now();
                for (auto a: actorVector)
                {
                    if(a.first==selectionInput)
                    {
                        for(auto s: a.second)
                        {
                            Movie m=moviesHashMap.searchByTconst(s);
                            actorMovies.push_back(make_pair(m.getRating(), m.getTconst()));
                        }
                    }
                }
                sort(actorMovies.begin(), actorMovies.end(),greater<>());
                displayVector(moviesHashMap,actorMovies,4);
                auto end = steady_clock::now();
                cout<<endl<< "SearchbyActor time for Hash Map: "
                    << duration_cast<milliseconds>(end - start).count()<<" ms."<<endl;
            }
            else if (menuInput2 == 2)
            {
                vector<pair<double, Movie*>> actorMovies;
                auto start = steady_clock::now();
                for (auto a: actorVector)
                {
                    if(a.first==selectionInput)
                    {
                        for(auto s: a.second)
                        {
                            auto m = orderedMap.SearchByTConst(s);
                            if(m.second == nullptr)
                                continue;
                            actorMovies.push_back(m);
                        }
                    }
                }
                displayOrderedVector(orderedMap,actorMovies,4);
                auto end = steady_clock::now();
                cout<<endl<< "SearchbyActor time for Ordered Map: "
                    << duration_cast<milliseconds>(end - start).count()<<" ms."<<endl;
            }
        }
        else if (menuInput == 3)
        {
            cout << endl << "Enter Year:" << endl;
            cin >> yearInput;

            cout << "What data structure would you like to use?" << endl
                 << "1: Hash Table" << endl
                 << "2: Ordered Map" << endl << endl
                 << "Your Selection:" << endl;

            cin >> menuInput2;

            if (menuInput2 == 1)
            {
                // Hash table
                vector<pair<double, int>>yearTitles;
                auto start = steady_clock::now();
                yearTitles = moviesHashMap.searchByYear(yearInput);
                displayVector(moviesHashMap,yearTitles, 20);
                auto end = steady_clock::now();
                cout<<endl<< "searchByYear time for Hash Map: "<< duration_cast<chrono::milliseconds>(end - start).count()<<" ms."<<endl;
            }
            else if (menuInput2 == 2)
            {
                vector<pair<double, Movie*>> yearTitles; // this is the vector with all of the year titles

                auto start = steady_clock::now();
                orderedMap.SearchByYear(yearInput, yearTitles);

                sort(yearTitles.begin(), yearTitles.end(), greater<>());
                displayOrderedVector(orderedMap, yearTitles, 20);
                auto end = steady_clock::now();
                cout<<endl<< "searchByYear time for Ordered Map: "<< duration_cast<chrono::milliseconds>(end - start).count()<<" ms."<<endl;
            }
        }
        else if (menuInput == 4)
        {
            cout << "Movie Title: " << endl;
            cin.ignore();
            getline(cin, selectionInput, '\n');
            cout << endl << "What data structure would you like to use?" << endl
                 << "1: Hash Table" << endl
                 << "2: Ordered Map" << endl << endl;
            cin >> menuInput2;

            if (menuInput2 == 1)
            {
                auto start = steady_clock::now();
                Movie movie = moviesHashMap.searchByTitle(selectionInput);

                cout << "Title: " << movie.getTitle() << endl
                     << "Rating: " << movie.getRating() << endl
                     << "Year: " << movie.getYear() << endl
                     << "Runtime (minutes): " << movie.getRuntime() << endl
                     << "Genres: ";

                string delimiter = " ";
                for(auto iterator : movie.getGenres())
                {
                    cout << delimiter << iterator;
                    delimiter = ", ";
                }

                auto end = steady_clock::now();
                cout<<endl<< "searchByTitle time for HashMap: "<< duration_cast<chrono::milliseconds>(end - start).count()<<" ms."<<endl;
                cout << endl << endl;
            }
            else if (menuInput2 == 2)
            {
                auto start = steady_clock::now();
                Movie* movie = orderedMap.SearchByName(selectionInput);
                if(movie == nullptr)
                    continue;

                cout << "Title: " << movie->getTitle() << endl
                     << "Rating: " << movie->getRating() << endl
                     << "Year: " << movie->getYear() << endl
                     << "Runtime (minutes): " << movie->getRuntime() << endl
                     << "Genres: ";

                string delimiter = " ";
                for(auto iterator : movie->getGenres())
                {
                    cout << delimiter << iterator;
                    delimiter = ", ";
                }
                auto end = steady_clock::now();
                cout<<endl<< "searchByTitle time for Ordered Map: "<< duration_cast<chrono::milliseconds>(end - start).count()<<" ms."<<endl;
                cout << endl << endl;
            }
        }
        else if (menuInput == 5)
        {
            cout << endl << "Thank you for using our services!" << endl;
            exit(0);
        }
    }
    return 0;
}

void LoadTitles(HashMap& hm,  Map& om)
{
    fstream inFile("moviesTSV.tsv");
    if (inFile.is_open())
    {
        // Column titles
        string lineFromFile;
        int i = 0;

        getline(inFile, lineFromFile);

        while (getline(inFile, lineFromFile))
        {
            istringstream stream(lineFromFile);

            string index;
            string tconst;
            int tconstNum;
            string primaryTitle;
            string startYear;
            int year;
            string runTimeMinutes;
            int runtime;
            string genresList;
            string tempGenre; // push this into genreVector
            vector<string> genreVector;
            string averageRating;
            double rating;

            getline(stream, index, '\t');
            getline(stream, tconst, '\t');
            tconstNum= stoi(tconst.substr(2));
            getline(stream, primaryTitle, '\t');
            getline(stream, startYear, '\t');
            year = stoi(startYear);
            getline(stream, runTimeMinutes, '\t');
            runtime = stoi(runTimeMinutes);
            getline(stream, genresList, '\t');
            // need to split up genres
            getline(stream, averageRating, '\t');
            rating = stod(averageRating);

            int commaCounter = 0;
            for (int i = 0; i < genresList.size(); i++)
            {
                if (genresList[i] == ',')
                    commaCounter++;
            }

            istringstream s(genresList);
            for (int i = 0; i < commaCounter + 1; i++)
            {
                getline(s, tempGenre, ',');
                genreVector.push_back(tempGenre);
            }

            // create movie object
            Movie newMovie(tconstNum, primaryTitle, year, runtime, genreVector, rating);
            // insert into hash map
            hm.insert(newMovie);

            if(i++ < 300000)
            {
                // insert into ordered map
                om.Insert(newMovie, tconstNum);
            }
        }
    }
}

void LoadActors(vector<pair<string, vector<int>>>& actorVector)
{
    fstream inFile("names.tsv");

    if (inFile.is_open())
    {
        // Column titles
        string lineFromFile;
        getline(inFile, lineFromFile);

        while (getline(inFile, lineFromFile))
        {
            istringstream stream(lineFromFile);

            string index;
            string name;
            string moviesList;
            string tempMovie;
            vector<int> movieVector;

            getline(stream, index, '\t');
            getline(stream, name, '\t');
            getline(stream, moviesList, '\t');

            int commaCounter = 0;
            for (int i = 0; i < moviesList.size(); i++)
            {
                if (moviesList[i] == ',')
                    commaCounter++;
            }

            istringstream s(moviesList);
            for (int i = 0; i < commaCounter + 1; i++)
            {
                getline(s, tempMovie, ',');
                int intTempMovie;
                if (tempMovie=="\\N" || tempMovie=="")
                    intTempMovie= -1;
                else
                    intTempMovie = stoi(tempMovie.substr(2));
                movieVector.push_back(intTempMovie);
            }
            actorVector.push_back(make_pair(name, movieVector));
        }
    }
}

//Display top 20 movie recommendations in ordered map:
void displayOrderedVector(Map& om, vector<pair<double,Movie*>> vec, int n)
{
    if (vec.size()<n)
        n=vec.size();

    cout<<setw(50)<< "Movie Title  "<<setw(5)<< "Rating "<<setw(6)<<"Year "<< setw(10)<<"  Runtime (min)"<<endl;
    cout << setfill('-') << setw(100) << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < n; i++)
    {
        cout << setw(50)<<vec[i].second->getTitle() << setw(5) <<vec[i].first<<setw(6)<< vec[i].second->getYear()<<setw(10)<< vec[i].second->getRuntime() <<endl;
    }
    cout << endl;
}

//Display top 20 movie recommendations in unordered map:
void displayVector(HashMap& hm, vector<pair<double,int>> vec, int n)
{
    if (vec.size()<n)
    {
        n=vec.size();
    }
    cout<<setw(50)<< "Movie Title  "<<setw(5)<< "Rating "<<setw(6)<<"Year "<< setw(10)<<"  Runtime (min)"<<endl;
    cout << setfill('-') << setw(100) << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < n; i++)
    {
        cout << setw(50)<<hm.searchByTconst(vec[i].second).getTitle() << setw(5) <<vec[i].first<<setw(6)<< hm.searchByTconst(vec[i].second).getYear()<<setw(10)<< hm.searchByTconst(vec[i].second).getRuntime() <<endl;
    }
    cout << endl;
}