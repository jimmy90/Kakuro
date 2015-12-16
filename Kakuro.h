/* 
 * File:   Kakuro.h
 * Author: Jimmy2xx
 *
 * Created on 11 décembre 2015, 23:46
 */

#ifndef KAKURO_H
#define	KAKURO_H

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Kakuro {
    
private:    
    vector<int> row;
    vector<int> col;
    int ** grid;
    bool limite=false;
    int insererNbr();//ok
    void initTabSums();//ok
    void initTabRow(int min);//ok
    void initTabCol(int min);//ok

public:
    Kakuro(){game();}
    int minSumCol;
    int minSumRow;
    int getSumCol(int col) const;//ok
    int getSumRow(int row) const;//ok
    int evalSumCol(int col, int ** grid);//ok
    int evalSumRow(int row, int ** grid);//ok
    int maxPossible(int cs_col,int cs_row,int row,int col);
    void init();//ok
    void menu() const;//ok
    int minSum(int s);//ok
    bool absentSurLigne(int val,int ** grid,int row);//OK
    bool absentSurColonne(int val,int ** grid,int col);//OK
    bool isCheckedSumCol(int ** grid,int col,int sum);//ok
    bool isCheckedSumRow(int ** grid,int row,int sum);//ok
    bool isCheckedSumColFinal(int ** grid,int col,int sum);//ok
    bool isCheckedSumRowFinal(int ** grid,int row,int sum);//ok
    void display() const;//ok
    bool isValid(int ** grille,int position);//ok
    void game();//ok
    void dialogue(int response , string question);
    void displayMenu();
    void displayMenu1(int response,string mainQuestion);
    void genererSomme();
    int nombreAleatoire(int a,int b);
    bool correctRules(int k,int col,int row,int ** grille);
    bool correctRulesFin(int k,int col,int row,int ** grille);
    void lireFichier(string name);
    void parseLigne(string ligne, int cpt);
    vector<string> split(const string &s, char delim);
    void save();
};


#endif	/* KAKURO_H */

