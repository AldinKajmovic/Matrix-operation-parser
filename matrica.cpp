#include "matrica.h"
#include <iostream>
#include <vector>
#include<stack>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>

using namespace std;

ostream & operator << (ostream & ispis, const Matrica & matrica) {
  for (int i = 0; i < matrica.elementi.size(); i++) {
    for (int j = 0; j < matrica.elementi[i].size(); j++) {
      ispis << matrica.elementi[i][j] << " ";
    }
    ispis << endl;
  }
  return ispis;
}

Matrica & Matrica::operator = (vector<vector<double>> & matrica) {
  elementi = matrica;
  return * this;
}

void Matrica::dodaj(Matrica & A, Matrica & B, Matrica & C) {
  if (A.elementi.size() != B.elementi.size() || A.elementi[0].size() != B.elementi[0].size()) {
    throw "Ne mogu se sabirati matrice koje imaju razlicite dimenzije.";
  }
  int i, j;
  for (i = 0; i < A.elementi.size(); i++) {
    for (j = 0; j < A.elementi[i].size(); j++) {
      C.elementi[i][j] = A.elementi[i][j] + B.elementi[i][j];
    }
  }
}

void Matrica::oduzmi(Matrica & A, Matrica & B, Matrica & C) {
  if (A.elementi.size() != B.elementi.size() || A.elementi[0].size() != B.elementi[0].size()) {
    throw "Ne mogu se sabirati matrice koje imaju razlicite dimenzije kolona.";
  }
  int i, j;
  for (i = 0; i < A.elementi.size(); i++) {
    for (j = 0; j < A.elementi[i].size(); j++) {
      C.elementi[i][j] = A.elementi[i][j] - B.elementi[i][j];
    }
  }
}

void Matrica::pomnoziBrojem(int broj, Matrica & matrica) {
  for (int i = 0; i < matrica.elementi.size(); i++) {
    for (int j = 0; j < matrica.elementi[i].size(); j++)
      matrica.elementi[i][j] *= broj;
  }
}

void Matrica::transponuj(Matrica & matrica) {
  if (matrica.elementi.size() == 0) //Ne moze se transponovati prazna matrica
    return;
  vector <vector<double>> temp(matrica.elementi[0].size(), vector<double>());
  for (int i = 0; i < matrica.elementi.size(); i++) {
    for (int j = 0; j < matrica.elementi[i].size(); j++) {
      temp[j].push_back(matrica.elementi[i][j]);
    }
  }
  matrica = temp;
}

Matrica Matrica::jedinicnaMatrica(Matrica matrica) {
  vector<vector<double>> temp(matrica.elementi.size(), vector <double>(matrica.elementi.size()));
  for (int i = 0; i < temp.size(); i++) {
    for (int j = 0; j < temp[i].size(); j++) {
      if (i == j) {
        temp[i][j] = 1;
      } else
        temp[i][j] = 0;
    }
  }
  Matrica TEMP;
  TEMP=temp;
  return TEMP;
}

void Matrica::izvrsiOperaciju(Matrica & A, Matrica & B, char operacija) {
  Matrica C(A.elementi.size(), vector<double>(A.elementi.size()));
  if (operacija == 'T') {
    transponuj(A);
  }
  if (operacija == '+') {
    dodaj(A, B, C);
    A = C;
    C.elementi.clear();
  }
  if (operacija == '-') {
    oduzmi(A, B, C);
    A = C;
    C.elementi.clear();
  }
  if (operacija == '*') {
    Strassen_algorithm(A, B, A.elementi.size(), A.elementi[0].size(), B.elementi.size(), B.elementi[0].size());
  }
  B.elementi.clear();
}

void Matrica::Strassen_algorithmA(Matrica & A, Matrica & B, Matrica & C) {

  //Bazni slucaj
  if (A.elementi.size() == 1) {
    C.elementi[0][0] = A.elementi[0][0] * B.elementi[0][0];
    return;
  } else {
    int new_size = A.elementi.size() / 2;
    vector < double > z(new_size);
    Matrica
    a11(new_size, z), a12(new_size, z), a21(new_size, z), a22(new_size, z),
      b11(new_size, z), b12(new_size, z), b21(new_size, z), b22(new_size, z),
      c11(new_size, z), c12(new_size, z), c21(new_size, z), c22(new_size, z),
      p1(new_size, z), p2(new_size, z), p3(new_size, z), p4(new_size, z),
      p5(new_size, z), p6(new_size, z), p7(new_size, z),
      aResult(new_size, z), bResult(new_size, z);

    int i, j;

    //Podjela matrica na manje matrice
    for (i = 0; i < new_size; i++) {
      for (j = 0; j < new_size; j++) {
        a11.elementi[i][j] = A.elementi[i][j];
        a12.elementi[i][j] = A.elementi[i][j + new_size];
        a21.elementi[i][j] = A.elementi[i + new_size][j];
        a22.elementi[i][j] = A.elementi[i + new_size][j + new_size];

        b11.elementi[i][j] = B.elementi[i][j];
        b12.elementi[i][j] = B.elementi[i][j + new_size];
        b21.elementi[i][j] = B.elementi[i + new_size][j];
        b22.elementi[i][j] = B.elementi[i + new_size][j + new_size];
      }
    }

    // Racunanje p1,p2,p3,p4,p5,p6,p7

    dodaj(a11, a22, aResult); // a11 + a22
    dodaj(b11, b22, bResult); // b11 + b22
    Strassen_algorithmA(aResult, bResult, p1);
    // p1 = (a11+a22) * (b11+b22)

    dodaj(a21, a22, aResult); // a21 + a22
    Strassen_algorithmA(aResult, b11, p2);
    // p2 = (a21+a22) * (b11)

    oduzmi(b12, b22, bResult); // b12 - b22
    Strassen_algorithmA(a11, bResult, p3);
    // p3 = (a11) * (b12 - b22)

    oduzmi(b21, b11, bResult); // b21 - b11
    Strassen_algorithmA(a22, bResult, p4);
    // p4 = (a22) * (b21 - b11)

    dodaj(a11, a12, aResult); // a11 + a12
    Strassen_algorithmA(aResult, b22, p5);
    // p5 = (a11+a12) * (b22)

    oduzmi(a21, a11, aResult); // a21 - a11
    dodaj(b11, b12, bResult);
    // b11 + b12
    Strassen_algorithmA(aResult, bResult, p6);
    // p6 = (a21-a11) * (b11+b12)

    oduzmi(a12, a22, aResult); // a12 - a22
    dodaj(b21, b22, bResult);
    // b21 + b22
    Strassen_algorithmA(aResult, bResult, p7);
    // p7 = (a12-a22) * (b21+b22)

    // Racunanje c21, c21, c11 e c22:

    dodaj(p3, p5, c12); // c12 = p3 + p5
    dodaj(p2, p4, c21); // c21 = p2 + p4

    dodaj(p1, p4, aResult); // p1 + p4
    dodaj(aResult, p7, bResult); // p1 + p4 + p7
    oduzmi(bResult, p5, c11); // c11 = p1 + p4 - p5 + p7

    dodaj(p1, p3, aResult); // p1 + p3
    dodaj(aResult, p6, bResult); // p1 + p3 + p6
    oduzmi(bResult, p2, c22); // c22 = p1 + p3 - p2 + p6

    //Sve rezultate smjestimo u matricu C
    for (i = 0; i < new_size; i++) {
      for (j = 0; j < new_size; j++) {
        C.elementi[i][j] = c11.elementi[i][j];
        C.elementi[i][j + new_size] = c12.elementi[i][j];
        C.elementi[i + new_size][j] = c21.elementi[i][j];
        C.elementi[i + new_size][j + new_size] = c22.elementi[i][j];
      }
    }
  }
}
int Matrica::nextpowerof2(int k) {
  return pow(2, int(ceil(log2(k))));
}
void Matrica::Strassen_algorithm(Matrica & A, Matrica & B, int m, int n, int a, int b) {
  if (A.elementi.size() != B.elementi.size())
    throw "Nije moguce mnoziti matrice koje nemaju iste dimenzije kolona !";
/*
     Treba provjeriti da li su matrice kvadratne i da imaju dimenzije stepena 2. Ako nemaju, matrice se moraju prosiriti i popuniti
     sa nulama kako bi ovaj kriterij bio ispunjen
*/
  int k = max({m,n,a,b});
  int s = nextpowerof2(k);

  vector<double> z(s);
  Matrica Aa(s, z), Bb(s, z), Cc(s, z);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      Aa.elementi[i][j] = A.elementi[i][j];
    }
  }
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
      Bb.elementi[i][j] = B.elementi[i][j];
    }
  }
  Strassen_algorithmA(Aa, Bb, Cc);
  vector<double> temp1(b);
  Matrica C(m, temp1);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < b; j++) {
      C.elementi[i][j] = Cc.elementi[i][j];
    }
  }
  A = C;
  C.elementi.clear();
  B.elementi.clear();
}
void Matrica::stepenuj(Matrica &matrica, int stepen) {
    if (stepen < 0) {
        throw invalid_argument("Stepen ne može biti negativan.");
    }

    if (stepen == 0) {
        // Ako je stepen 0, vraćamo jedinicnu matricu
        *this = jedinicnaMatrica(matrica);
        return;
    }

    // Kreiramo matricu koja će biti rezultat stepenovanja
    int red = matrica.elementi.size();
    int kolona = matrica.elementi[0].size();
    Matrica rezultat(red, vector<double>(kolona, 0)); // Postavljanje na nulti matricu
    rezultat = jedinicnaMatrica(matrica);  // Postavljamo rezultat na jedinicnu matricu

    Matrica tempMatrica = matrica;
    while (stepen > 0) {
        if (stepen % 2 == 1) {
            // Ako je stepen neparan, multipliciramo trenutni rezultat sa tempMatrica
            Matrica tempRezultat(rezultat.elementi.size(), vector<double>(rezultat.elementi[0].size(), 0));
            Strassen_algorithm(tempRezultat, tempMatrica, rezultat.elementi.size(), rezultat.elementi[0].size(), tempMatrica.elementi.size(), tempMatrica.elementi[0].size());
            rezultat = tempRezultat;
        }

        // Kvadriramo tempMatrica
        Matrica tempKvadratnaMatrica(tempMatrica.elementi.size(), vector<double>(tempMatrica.elementi[0].size(), 0));
        Strassen_algorithm(tempKvadratnaMatrica, tempMatrica, tempMatrica.elementi.size(), tempMatrica.elementi[0].size(), tempKvadratnaMatrica.elementi.size(), tempKvadratnaMatrica.elementi[0].size());
        tempMatrica = tempKvadratnaMatrica;

        stepen /= 2;
    }

    // Postavljamo rezultat u trenutni objekat
    *this = rezultat;
}




void Matrica::inverzMatrice(Matrica & matrica) {
  Matrica jedMat = jedinicnaMatrica(matrica);

  // Gauss-Jordan algorithm za inverznu
  for (int k = 0; k < matrica.elementi.size(); k++) {
    double pivot = matrica.elementi[k][k];
    for (int j = 0; j < matrica.elementi.size(); j++) {
      matrica.elementi[k][j] /= pivot;
      jedMat.elementi[k][j] /= pivot;
    }
    for (int i = 0; i < matrica.elementi.size(); i++) {
      if (i != k) {
        double m = matrica.elementi[i][k];
        for (int j = 0; j < matrica.elementi.size(); j++) {
          matrica.elementi[i][j] -= m * matrica.elementi[k][j];
          jedMat.elementi[i][j] -= m * jedMat.elementi[k][j];
        }
      }
    }
  }

  matrica = jedMat;
  jedMat.elementi.clear();
}

void Matrica::izvrsiOperaciju(Matrica & matrica, char operacija, int broj) {
  if (operacija == '*') {
    pomnoziBrojem(broj, matrica);
  }
  if (operacija == '^') {
    if (broj != -1) stepenuj(matrica, broj);
    else if (broj == -1) {
      inverzMatrice(matrica);
    }
  }

}

bool Matrica::jeLiCifra(char znak) const {
  return znak >= '0' && znak <= '9';
}

bool Matrica::jeLiOtvorena(char znak) const {
  return znak == '(' || znak == '[';
}
bool Matrica::jeLiZatvorena(char znak) const {
  return znak == ')' || znak == ']';
}
bool Matrica::jeLiOp(char znak) const {
  return znak == '+' || znak == '-' || znak == '*' || znak == '^' || znak == 'I' || znak == 'T';
}

double determinanta(Matrica A) {
    int N = A.elementi.size();
    int M = A.elementi[0].size();
    if(M!=N) throw "Matrica nije kvadratna !";
    vector<vector<double>> L(N, vector<double>(N));
    vector<vector<double>> U(N, vector<double>(N));
    double det = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j < i)
                L[j][i] = 0;
            else {
                L[j][i] = A.elementi[j][i];
                for (int k = 0; k < i; k++) {
                    L[j][i] = L[j][i] - L[j][k] * U[k][i];
                }
            }
        }
        for (int j = 0; j < N; j++) {
            if (j < i)
                U[i][j] = 0;
            else if (j == i)
                U[i][j] = 1;
            else {
                U[i][j] = A.elementi[i][j] / L[i][i];
                for (int k = 0; k < i; k++) {
                    U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {

        det *=  L[i][i];
    }
    return det;
}



istream & operator >> (istream & ispis, Matrica & matrica) {
  try {
    stack<char> operacije;
    stack<int> pomocniBrojevi;
    Matrica Privremena;
    vector<double> pomocniNiz;
    vector<vector<double>> pomocnaMatrica;
    string broj = "";
    string broj2 = "";
    enum Simbol {
      otvorenaZ,
      zatvorenaZ,
      op,
      cifra,
      pocetniSimbol
    };
    Simbol prethodni(pocetniSimbol);

    while (ispis.peek() != '\n') {

      char znak = ispis.peek();
      if (matrica.jeLiOtvorena(znak)) {
        prethodni = otvorenaZ;
        broj = "";
        ispis.get();
        while (true) {
          if (ispis.peek() == ' ') { // U unosu [12 3 4; 5 61 7] uzimace sve cifre npr(12) i poslati u pomocni niz, omogucava da obuhvati vise cifara
            if (broj != "") {
              pomocniNiz.push_back(stod(broj));
              broj = "";
            }
          }
          if (matrica.jeLiCifra(ispis.peek()) || ispis.peek() == '.' || ispis.peek() == '-') { // Na pomocnu varijablu dodaje cifre, kao i znakove '.' ukoliko se radi o double tj decimalnom i znak '-' ukoliko je broj negativan
            broj += ispis.peek();
          }
          if (ispis.peek() == ';') {
            pomocniNiz.push_back(stod(broj));//Dodaje u pomocni niz zadnju cifru koja se nalazila pored ;
            broj = "";
            pomocnaMatrica.push_back(pomocniNiz); //Dodaje niz cifara u matricu
            pomocniNiz.clear(); //Ocisti
          }
          if (matrica.jeLiZatvorena(ispis.peek())) {
            prethodni = zatvorenaZ;
            if (broj != "") pomocniNiz.push_back(stod(broj));
            broj = "";
            pomocnaMatrica.push_back(pomocniNiz);
            pomocniNiz.clear();
            Privremena.elementi = pomocnaMatrica;
            if (matrica.elementi.size() == 0) { //Nailazimo na prvu matricu i kreiramo je

              matrica = Privremena;
              pomocnaMatrica.clear();
            }
            if (!pomocniBrojevi.empty()) {//Pozove se funkcija koja ukljucuje 2 stacka za operacije poput stepenovanja
              matrica.izvrsiOperaciju(matrica, operacije.top(), pomocniBrojevi.top());
              pomocniBrojevi.pop();
              operacije.pop();
            }
            if (pomocniBrojevi.empty() && !operacije.empty()) {//Pozove se funkcija koja ukljucuje 2 matrice za operacije poput sabiranja
              matrica.izvrsiOperaciju(matrica, Privremena, operacije.top());
              operacije.pop();
            }
            break;
          }
          ispis.get();
        }
      }

      if (matrica.jeLiCifra(znak)) { //Ukoliko se desi situacija -321*[1 2;3 4], ovaj uslov ce to omoguciti da se pravilno obradi
        prethodni = cifra;
        while (true) {
          if (matrica.jeLiCifra(ispis.peek())) {
            broj2 += ispis.peek();
            prethodni = cifra;
          }
          if (ispis.peek() == '*') { //Uzima cifre sve dok ne naidje na znak * prije matrice
            prethodni = op;
            operacije.push('*');
            break;
          }
          ispis.get();
        }
        pomocniBrojevi.push(stoi(broj2));

      }

      if (matrica.jeLiOp(znak)) {
        operacije.push(znak);
        if (prethodni == zatvorenaZ) {

          if (znak == '^') {
            broj2 = "";
            ispis.get(); // sada je u obradi ^
            ispis.get(); // sada je u obradi (
            if (ispis.peek() == '-') {
              broj2 += ispis.peek(); //Kada se stepenuje to je u obliku [1 2;3 4]^(2) i potrebno je da skloni znakove i da pokupi cifru
              ispis.get();

            }
            while (true) {
              if (matrica.jeLiOp(ispis.peek())) {
                prethodni = op;
                break;
              }
              if (ispis.peek() == '\n') break;
              if (matrica.jeLiCifra(ispis.peek())) {
                broj2 += ispis.peek();
                prethodni = cifra;
              }

              ispis.get();
            }
            if(stoi(broj2) < -1 || stoi(broj2) == 0)  throw "Ne moze stepen biti nula ili manji od -1";
            if (broj2 != "") pomocniBrojevi.push(stoi(broj2));
            matrica.izvrsiOperaciju(matrica, operacije.top(), pomocniBrojevi.top());
            operacije.pop();
            pomocniBrojevi.pop();
            operacije.push(ispis.peek()); // ovo se doda ukoliko na steku imamo vec operatora
          }

          if (pomocniBrojevi.empty() && znak == 'T') {
            matrica.izvrsiOperaciju(matrica, Privremena, operacije.top());
            operacije.pop();
          }

        }
        prethodni = op;

        if (znak == '-') { //Minus ispred npr -245*[1 2;3 4]
          broj2 += znak;
        }

      }

      ispis.get();
    }
  } catch (const char poruka[]) {
    cout << poruka << endl;
    cin.ignore(1000, '\n');
  }
  return ispis;
}
