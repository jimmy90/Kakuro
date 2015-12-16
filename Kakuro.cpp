
//
//  Kakuro.cpp
//  Kakuro
//
//  Created by Jimmy Padonou on 10/12/2015.
//  Copyright © 2015 Jimmy Padonou. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Kakuro.h"
#include <fstream>
#include <sstream>

using namespace std;

int Kakuro::getSumCol(int col) const{
    return this->col[col];
}

int Kakuro::getSumRow(int row) const{
    return this->row[row];
}

int Kakuro::evalSumCol(int col,int** grid) {
    int sum=0;
    for (int i=0;i<row.size();i++)
        sum+=grid[i][col];
    return sum;
}

int Kakuro::evalSumRow(int row,int** grid)  {
    int sum=0;
    for (int i=0;i<col.size();i++)
        sum+=grid[row][i];
    return sum;
}

/*
 Somme minimal pour un nombre de case s dispo
 */
int Kakuro::minSum(int s){
    if (s==1) {
        return 1;
    }else if (s>1)
        return s + minSum(s-1);
    return 0;
}

int Kakuro::maxPossible(int cs_col, int cs_row, int row, int col) {
    if (limite)
        return 9;
    return std::min(this->col[col]-cs_col-this->minSum(this->row.size()-row-1),
            this->row[row]-cs_row-this->minSum(this->col.size()-col-1));
}


void Kakuro::initTabCol(int min) {
    cout << "Saisir les sommes de colonnes" << endl;
    for (int i=0; i<col.size();i++){
        cout << "Col" << i+1 << ": " ;
        do{
            col[i]=insererNbr();
        }while(col[i]<min);
    }
}

void Kakuro::initTabRow(int min) {
    cout << "Saisir les sommes de lignes" << endl;
    for (int i=0; i<row.size();i++){
        cout << "Row" << i+1 << ": " ;
        do{
            row[i]=insererNbr();
        }while(row[i]<min);
    }
}

int Kakuro::insererNbr() {
    int x;
    cin >> x;
    while (cin.fail()||x<2) {
        cout << "Saisir de nouveau" << endl;
        cin >> x;
    }
    return x;
}

int Kakuro::nombreAleatoire(int a, int b){
    return rand()%(b-a) +a;
}

void Kakuro::lireFichier(string name)
{
    string ligne;
    int cpt=0;
    ifstream fichier(name.c_str(), ios::in); // on ouvre en lecture
    cout << " Lecture du fichier " << name <<endl;
    
    if (fichier) // si l'ouverture a fonctionné
    {
        while (getline(fichier, ligne)) // tant que l'on peut mettre la ligne dans "contenu"
        {           
            //On supprime les espaces
            ligne.erase( remove( ligne.begin(), ligne.end(), ' ' ), ligne.end() );
            cpt++;
            parseLigne(ligne,cpt);
                  
        }
          fichier.close();
    } else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }


void Kakuro::genererSomme(){
    cout << "Saisir la taille de la grille: ligne puis colonne" << endl;
    int r,c;
    r=insererNbr();
    c=insererNbr();
    row=vector<int>(r);
    col=vector<int>(c);
    grid = new int* [c];
     for (int i=0; i < r; i++)
      grid[i] = new int[c];
    for(int i=0; i < r; ++i) {
        for(int j=0; j < c; ++j) {        
                grid[i][j]= 0;
        }
    }
    minSumCol=minSum((this->row.size()));
    minSumRow=minSum((this->col.size()));
    
     for (int i=0; i<col.size();i++){
         col[i]=nombreAleatoire( minSumCol,60);
     }
     
    for (int i=0; i<row.size();i++){
        row[i]=nombreAleatoire(minSumRow,60);
     }
    
    
    
}

void Kakuro::parseLigne(string ligne, int cpt){
    
    
   vector<string>tab=split(ligne,';');
   int var;
   if(cpt==1){
      // cout<<ligne;
       row=vector<int>(tab.size());
        for (int i=0; i<tab.size();i++){
            std::istringstream istr(tab[i]);
            istr >> var;
           // cout<<var<<end;
            row[i]=var;
        }
   }else if(cpt==2){
        //cout<<ligne;
       col=vector<int>(tab.size());
       for (int i=0; i<tab.size();i++){
            std::istringstream istr(tab[i]);
            istr >> var;
           // cout<<var.<<end;
            col[i]=var;
        }
   }
   
    
}

 vector<string> Kakuro::split(const string& s, char delim){
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
 }

void Kakuro::save(){
    string name;
    cout<<"Saisir nom du fichier pour enregistrer"<<endl;
    cin>>name;
    ofstream fichier(name.c_str(), ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
 
        if(fichier)
        {
            
            for (int c=0;c<col.size();c++){
        //cout << setw(5) << "Col" << c+1 ;
                fichier << setw(5) << col[c] ;
            }
                    for (int l=0;l<row.size();l++){
                fichier << endl;
               // cout << "Row " << l+1 << ":";
                fichier<< row[l]; 
                for (int c=0;c<col.size();c++){
                  fichier << setw(5) << grid[l][c] ;
                }
                fichier << endl;
            }
            
            cout<<"Resulat de la grille bien enregistrée dans le fichier:"<<name<<endl;
                fichier.close();
        }
        else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
}


void Kakuro::initTabSums() {
    
    cout << "Saisir la taille de la grille: ligne puis colonne" << endl;
    int r,c;
    r=insererNbr();
    c=insererNbr();
    row=vector<int>(r);
    col=vector<int>(c);
    grid = new int* [r];
    for (int i=0; i < r; i++)
      grid[i] = new int[c];
    for(int i=0; i < r; ++i) {
        for(int j=0; j < c; ++j) {        
                grid[i][j]= 0;
        }
    }
    minSumCol=minSum((this->row.size()));
    minSumRow=minSum((this->col.size()));
    initTabCol(minSumCol);
    initTabRow(minSumRow);
}

void Kakuro::displayMenu1(int response, string mainQuestion){

     // while (response!=2)
    //{
        //string question ;
    cout<<endl;
    cout<<endl;
        switch (response)
        {
            case 1:
                if (isValid(grid,0)){
                    cout << "Solution trouvee" << endl;
                    display();
                    if(mainQuestion=="fichier"){
                        save();
                    }
                    displayMenu();
                }else
                {
                    cout << "Pas de solution" << endl;
                    displayMenu();
                }
                break;
            case 2:
                displayMenu();
                break;                
            default:
                break;
        }
       // dialogue(response, mainQuestion);
        
   // }
}


void Kakuro::display() const {
    cout << " ";
    for (int c=0;c<col.size();c++){
        //cout << setw(5) << "Col" << c+1 ;
        cout << setw(5) << col[c] ;
    }
    for (int l=0;l<row.size();l++){
        cout << endl;
       // cout << "Row " << l+1 << ":";
        cout<< row[l]; 
        for (int c=0;c<col.size();c++){
          cout << setw(5) << grid[l][c] ;
        }
        cout << endl;
    }
}


void Kakuro::displayMenu(){
    /*int choix;
    cout << "---- MENU ----" << endl;
    cout << "1. Generer des sommes aléatoires" << endl;
    cout << "2. Renseigner les sommes" << endl;
    cout << "3. Resolution" << endl;
    cout << "4. Quitter" << endl;*/
    cout<<endl;
    cout<<endl;
    string file;
     int selection,selection1;
    cout << "<saisir domaine de solution " << endl;
    cout << "un entier inferieur ou égale à 9 pour mettre la limite a 9" << endl;
    limite = insererNbr()<=9;
    cout << "Que souhaitez-vous faire ?\n\t1. Generer des sommes aléatoires\n\t2. Saisir les sommes lignes et colonnes\n\t3.A partir d'un fichier\n\t4.Quitter"<<endl;
    cin >> selection;
    string mainQuestion= "Que souhaitez-vous faire ?\n\t1. Resolution\n\t2.Quitter (saisir <<close>>)";
    cout << endl;
    switch (selection)
    {
        case 1:
            genererSomme();
            display();
            cout<< "Que souhaitez-vous faire ?\n\t1. Resolution\n\t2.Quitter (saisir <<close>>)"<<endl;
            cin>>selection1;
            displayMenu1(selection1,mainQuestion);
            break ;
        case 2:
            initTabSums();
            display();
            cout<< "Que souhaitez-vous faire ?\n\t1. Resolution\n\t2.Quitter (saisir <<close>>)"<<endl;
            cin>>selection1;
            displayMenu1(selection1,mainQuestion);
            break ;
        case 3:
            cout<< "Saisir le nom du fichier à lire"<<endl;
            cin>>file;
            lireFichier(file);
            grid = new int* [row.size()];
            for (int i=0; i < row.size(); i++)
                 grid[i] = new int[col.size()];

               for(int i=0; i < row.size(); ++i) {
                   for(int j=0; j < col.size(); ++j) {        
                           grid[i][j]= 0;
                   }
               }
            display();
            cout<< "Que souhaitez-vous faire ?\n\t1. Resolution\n\t2.Quitter (saisir <<close>>)"<<endl;
            cin>>selection1;
            displayMenu1(selection1,"fichier");
            /*if (isValid(grid,0)){
                    cout << "Solution trouvee" << endl;
                    display();
                }else
                    cout << "Pas de solution" << endl;*/
                break;
        default:
             break;
    }
}

//Saisir la taille de la grille
void Kakuro::init(){
    initTabSums();
}

void Kakuro::game() {
    cout << "KAKURO" << endl;
    /*menu();
    init();
    display();
    cout << "Fin"  << endl;
    if (isValid(grid,0)){
        cout << "Solution trouvee" << endl;
        display();
    }else
        cout << "Pas de solution" << endl;*/
    displayMenu();
}

bool Kakuro::absentSurLigne(int val, int** grid, int row) {
    for (int i=0;i<col.size();i++){
        if (grid[row][i]==val)
            return false;
    }
    return true;
}

bool Kakuro::absentSurColonne(int val, int** grid, int col) {
    for (int i=0;i<row.size();i++){
        if (grid[i][col]==val)
            return false;
    }
    return true;
}

bool Kakuro::isCheckedSumCol(int** grid, int col,int k) {
    return (evalSumCol(col,grid)+k) <= getSumCol(col);
}

bool Kakuro::isCheckedSumRow(int** grid, int row,int k) {
    return (evalSumRow(row,grid)+k) <= getSumRow(row);
}


bool Kakuro::isCheckedSumColFinal(int** grid, int col,int k) {
    if (limite)
        return (evalSumCol(col,grid)+k) == getSumCol(col) && k<=9;
    return (evalSumCol(col,grid)+k) == getSumCol(col);
}

bool Kakuro::isCheckedSumRowFinal(int** grid, int row,int k) {
    if (limite)
        return (evalSumRow(row,grid)+k) == getSumRow(row) && k <=9;
    return (evalSumRow(row,grid)+k) == getSumRow(row);
}


bool Kakuro::correctRules(int k, int col, int row, int** grille){
    return absentSurLigne(k,grille,row) && absentSurColonne(k,grille,col) && isCheckedSumCol(grille,col,k) && isCheckedSumRow(grille,row,k);
}

bool Kakuro::correctRulesFin(int k, int col, int row, int** grille){
    
    if (row+1==this->row.size()&&col+1==this->col.size()){
        return absentSurLigne(k,grille,row) && absentSurColonne(k,grille,col) &&
                isCheckedSumRowFinal(grille,row,k)&& isCheckedSumColFinal(grille,col,k);
    }
    if (row+1==this->row.size()){
        return absentSurLigne(k,grille,row) && absentSurColonne(k,grille,col) &&
                isCheckedSumColFinal(grille,col,k) ;
    }
    if (col+1==this->col.size()){
        return absentSurLigne(k,grille,row) && absentSurColonne(k,grille,col) &&
                isCheckedSumRowFinal(grille,row,k);
    }
    return false;
}

bool Kakuro::isValid (int ** grille, int position)
{
    if (position == (this->row.size()*this->col.size())){
        this->grid=grille;
        return true;
    }
    int row = position/this->col.size(), col = position%this->col.size();
    if (grille[row][col] != 0)
        return isValid(grille, position+1);
    if (row+1==this->row.size() || col+1==this->col.size()){
        int f=0;
        if (row+1==this->row.size()){
            f = getSumCol(col)-evalSumCol(col,grille);
        }
        if (col+1==this->col.size()){
            f = getSumRow(row)-evalSumRow(row,grille);
        }
        if (correctRulesFin(f,col,row,grille)){
            grille[row][col] = f;
            if ( isValid (grille, position+1) )
                return true;
        }
    }
    for (int k=1; k <= maxPossible(evalSumCol(col,grille),evalSumRow(row,grille),row,col); k++)
    {
        if(row+1==this->row.size()){
            
        }else if (col+1==this->col.size()){
            
        }else{
            if (correctRules(k,col,row,grille))
            {
                grille[row][col] = k;
                if ( isValid (grille, position+1) )
                    return true;
            }
        }
    }
    grille[row][col] = 0;
    return false;
}


