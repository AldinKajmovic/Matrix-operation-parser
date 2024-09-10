#ifndef MATRICA_H
#define MATRICA_H
#include <vector>
#include <iostream>
using namespace std;

class Matrica{

private:
    bool jeLiCifra(char znak)const;
    bool jeLiOtvorena(char znak)const;
    bool jeLiZatvorena(char znak)const;
    bool jeLiOp(char znak)const;
    void oduzmi(Matrica &A, Matrica &B, Matrica &C);
    void dodaj( Matrica &A,  Matrica &B,  Matrica &C);
    void pomnoziBrojem(int broj, Matrica &matrica);
    void transponuj(Matrica &matrica);
    void stepenuj(Matrica &matrica, int stepen);
    Matrica jedinicnaMatrica(Matrica matrica);
    void izvrsiOperaciju( Matrica &A, Matrica &B,char operacija);
    void izvrsiOperaciju(Matrica &matrica,char operacija, int broj);
    void inverzMatrice(Matrica &matrica);
    int nextpowerof2(int k);
    void Strassen_algorithm(Matrica &A, Matrica &B, int m, int n, int a, int b);
    void Strassen_algorithmA(Matrica &A, Matrica &B, Matrica &C);


public:
    friend double determinanta(vector<vector<double>> A);
    vector<vector<double>> elementi;
    friend ostream& operator<<(ostream& ispis, const Matrica& matrica);
    friend istream& operator>>(istream& ispis, Matrica &matrica);
    Matrica& operator=(vector<vector<double>> &matrica);
    Matrica():elementi({}){}
    Matrica(int red, vector<double>(kolone)):elementi(red, vector<double>(kolone)){}


};



#endif
