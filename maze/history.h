#ifndef HEADER_HISTORY
#define HEADER_HISTORY

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

vector<vector<float>> readLevel(){
    double time, pathLength;
    vector<vector<string>> data;
    vector<string> row;
    string line, word, temp;
    fstream file ("history.csv", ios::in);
    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ','))
                row.push_back(word);
            data.push_back(row);
        }
    }
    else{
        cout << "Could not open the file\n";
    }
    vector<vector<float>> levelData(data.size(), vector<float>(2));
    for(int i = 0; i < data.size(); i++){
        levelData[stoi(data[i][0])-1][0] = stof(data[i][1]);
        levelData[stoi(data[i][0])-1][1] = stof(data[i][2]);
    }
    return levelData;
}

void updateLevel(int level, float time, float pathLength){
    // level;
    fstream fin, fout;
    fin.open("history.csv", ios::in);
    fout.open("historyNew.csv", ios::out);
    vector<string> row;
    string line, word;
    int count = 0;
    while(!fin.eof()){
        row.clear();
        getline(fin, line);
        stringstream str(line);
        while(getline(str, word, ',')){
            row.push_back(word);
        }
        if(level == stoi(row[0])){
            count = 1;
            if(stof(row[1]) > time){
                stringstream convertTime;
                convertTime << time;
                row[1] = convertTime.str();
            }
            if(stof(row[2]) > pathLength){
                stringstream convertPathLength;
                convertPathLength << pathLength;
                row[2] = convertPathLength.str();
            }
            if(!fin.eof()){
                for(int i = 0; i < row.size()-1; i++){
                    fout << row[i] << ",";
                }
                fout << row[row.size()-1] << "\n";
            }
        }
        else{
            if (!fin.eof()) {
                for (int i = 0; i < row.size() - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row.size() - 1] << "\n";
            }
        }
        if(fin.eof())
            break;
    }
    if(count == 0)
        cout << "Record not found\n";

    fin.close();
    fout.close();
    remove("history.csv");
    rename("historyNew.csv", "history.csv");
}

#endif