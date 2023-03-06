#pragma once
#include "mylib.h"

struct Studentas
{
    string vardas, pavarde;
    vector<int> namudarbai;
    int egz_pazymys;
};
void checkInputChar(char& pasirinkimas);
void input(vector<Studentas>& studentai);
void readFile(vector<Studentas>& studentai);
bool palyginimas(const Studentas& pirmas, const Studentas& antras);
void output(vector<Studentas>& studentai);