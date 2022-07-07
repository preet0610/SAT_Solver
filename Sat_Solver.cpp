#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

void display_vector (vector<vector<int>> vec);

int unit_propagation(vector<vector<int>>& current, int *var, int nvar){
    //  cout<<"u_p";
    int x=0,y=0;
    int unit, rem = 0, empty_clause = 0, found = 0;
    for(int i =0; i< current.size(); i++){
        if(current[i].size() == 1){ 
            found = 1;
            unit = current[i][0];
            if(unit < 0) var[(-unit)-1] = -1;
            else var[unit-1] = 1;
            for(int j=0; j< current.size(); j = j +1 - y){
                y = 0;
                //vector<int> v1 ;
                rem = 0;
                for(int k=0; k< current[j].size(); k= k+1-x){
                    x = 0;
                    if(current[j][k] == -unit){ 
                        current[j].erase(current[j].begin()+k);
                        x++;
                    }
                    if(current[j][k] == unit){ 
                        rem = 1;
                        break;
                    }
                }
                if(rem) {
                    current.erase(current.begin()+j); 
                    y++;
                }
            }
        }
        
    }
    // if(!found){
    //     for(int j=0; j< current.size(); j++){
    //             vector<int> v2 ;
    //             for(int k=0; k< current[j].size(); k++){
    //                     v2.push_back(current[j][k]);
    //                 }
    //                    fresh.push_back(v2);
    //             }
    //  }
     // cout <<"u_p";
    // cout<<"\nNOW\n";
    // display_vector(current);
    return empty_clause;
}

int DPLL(vector<vector<int>> clauses, int *var, int nvar){
    // display_vector(clauses);
    int res;
    vector<vector<int>> fresh_clauses;
    int check =0;

    check = unit_propagation(clauses,var,nvar);
    if(clauses.size() == 0){ 
        return 1;
    }
    for(int i =0; i < clauses.size(); i++){
        if(clauses[i].size() == 0) return 0;
    }
    
    // check = unit_propagation(clauses,var,nvar);
    // // cout<< check;
    // if(check) return 0;
    
    fresh_clauses = clauses;
    fresh_clauses.insert(fresh_clauses.begin(),{fresh_clauses[0][0]});
    //display_vector(fresh_clauses);
    res = DPLL(fresh_clauses,var,nvar);
    if(res) return 1;
    fresh_clauses = clauses;
    fresh_clauses.insert(fresh_clauses.begin(),{-fresh_clauses[0][0]});
   // display_vector(fresh_clauses);
    res = DPLL(fresh_clauses,var,nvar);
    if(res) return 1;
    return 0;
}

void display_vector (vector<vector<int>> vec){
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j] << " ";
        cout << endl;
    }
}

int main(){
    string fileName, duh;
    char c;
    int nvar = 0, lit = 1;
    ifstream fin;
    cout<< "Enter the name of the DIMACS file (with extension): ";
    cin >> fileName;
    fin.open(fileName);
    
    c = fin.get();
    while(c == 'c'){
        while(c != '\n') c = fin.get();
        c = fin.get();
    }
    //fin >> duh;
    fin >> duh;
    fin >> duh; 
    nvar = stoi(duh); 
    fin >> duh;

    vector< vector <int> > clauses;
    int var[nvar]; //-1 if false, 1 if true
    for(int i=0; i < nvar; i++){var[i] = 0;}

    fin >> duh;
    lit = stoi(duh);
    while(fin){
        vector <int> v;
        while(lit){
            v.push_back(lit);
            fin >> duh;
            lit = stoi(duh);
        }
        clauses.push_back(v);
        fin >> duh;
        lit = stoi(duh);
    }
    //  display_vector(clauses); 

    int res = DPLL(clauses,var,nvar);
    if(res){
    cout <<  "SAT\n";
    for(int i=0; i<nvar; i++){
        if(var[i]== -1) cout<< -(i+1) <<" ";
        else cout<< i+1 <<" ";
        //cout << var[i] <<", ";
    }
    }
    else 
    cout<< "UNSAT";
    return 0;
}