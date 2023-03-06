#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <random>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <exception>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

struct Studentas
{
    string vardas, pavarde;
    vector<int> namudarbai;
    int ND, egz_pazymys;
    double galutinis_pazymys;
};

bool isdigits(string& str)
{    return std::all_of(str.begin(), str.end(), ::isdigit);     }

void NamuDarbai(bool PazymiuSkaicius, Studentas& Studentas) {
    bool run = true;
    string pazymys;
    if (PazymiuSkaicius)
    {
        for (int i = 0; i < Studentas.ND; i++)
        {
            do {
                cout << Studentas.namudarbai.size() + 1 << " pazymys: ";
                cin >> pazymys;
                if (isdigits(pazymys) && std::stoi(pazymys) <= 10 && std::stoi(pazymys) >= 0)
                {
                    Studentas.namudarbai.push_back(std::stoi(pazymys));
                    run = false;
                }
                else
                {
                    cout << "Ivestas klaidingas pazymys" << endl;
                    run = true;
                }
            } while (run);
        }
    }
    else
    {
        cout << endl << " Norint baigti pazymiu ivedima, iveskite 'gana' " << endl;
        do {
            cout << Studentas.namudarbai.size() + 1 << " pazymys: ";
            cin >> pazymys;
            if (isdigits(pazymys) && std::stoi(pazymys) <= 10 && std::stoi(pazymys) >= 0)
            {
                Studentas.namudarbai.push_back(std::stoi(pazymys));
            }
            else if (pazymys == "gana")
            {
                Studentas.ND = Studentas.namudarbai.size();
                Studentas.namudarbai.shrink_to_fit();
                run = false;
            }
            else
            {
                cout << "Ivestas neteisingas pazymys!" << endl;
            }

            if (Studentas.namudarbai.empty() && pazymys == "gana")
            {
                cout << "Iveskite bent viena pazymi!" << endl;
                run = true;
            }
        } while (run);
    }
}

bool validateName(string name) {
    for (char i : name)
    {
        if (!isalpha(i))
        {
            cout << "Vardo ivedimui naudokite tik raides!" << endl;
            cout << "Iveskite varda is naujo: ";
            return false;
        }
    }
    return true;
}

string getDigits() {
    bool valid;
    string number;
    do {
        cin >> number;
        cout << endl;
        if (!isdigits(number))
        {
            cout << "Pazymio ivedimui naudokite tik skaicius!" << endl;
            cout << "Iveskite pazymi is naujo: ";
            valid = false;
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    return number;
}

int getExam() {
    int pazymys;
    bool valid = false;
    do
    {
        pazymys = std::stoi(getDigits());
        if (pazymys > 10 || pazymys <= 0)
        {
            cout << "Egzamino pazymys ivestas neteisingai!" << endl;
            cout << "Iveskite egzamino pazymi is naujo: ";
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    return pazymys;
}

void randomgrades(bool PazymiuSkaicius, Studentas& Student) {
    using chronoClock = std::chrono::high_resolution_clock;
    unsigned seed = static_cast<long unsigned int> (chronoClock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 10);

    if (!PazymiuSkaicius)
    {
        std::uniform_int_distribution<int> distributionSize(1, 15);
        Student.ND = distributionSize(generator);
    }

    cout << "Atsitiktinai sugeneruoti " << Student.ND << " namu darbu pazymiai: ";
    for (int i = 0; i < Student.ND; i++)
    {
        Student.namudarbai.push_back(distribution(generator));
        cout << Student.namudarbai[i] << " ";
    }
    Student.egz_pazymys = distribution(generator);
    cout << endl << "Sugeneruotas egzamino pazymys: " << Student.egz_pazymys << endl << endl;

}

void galutinis(vector<Studentas>& group, int n) {
    double vidurkis;
    for (int i = 0; i < n; i++)
    {
        vidurkis = 0;
        for (int j = 0; j < group[i].ND; j++)
        {
            vidurkis = vidurkis + group[i].namudarbai[j];
        }
        vidurkis = vidurkis / group[i].ND;
        group[i].galutinis_pazymys = (vidurkis * 0.4) + (group[i].egz_pazymys * 0.6);
    }
}

void mediana(vector<Studentas>& group, int n) {
    double mediana;
    for (int i = 0; i < n; i++)
    {
        std::sort(group[i].namudarbai.begin(), group[i].namudarbai.end());
        mediana = group[i].namudarbai[(group[i].ND / 2)];
        if (group[i].ND % 2 == 0)
        {
            mediana = (mediana + group[i].namudarbai[(group[i].ND / 2) - 1]) / 2;
        }
        group[i].galutinis_pazymys = (mediana * 0.4) + (group[i].egz_pazymys * 0.6);
    }
}

void print(vector<Studentas>& group, int n, bool isMedian) {
    cout << endl;
    if (isMedian)
    {
        cout << "Vardas          Pavarde           Mediana" << endl;
        cout << "----------------------------------------------------------" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << std::setprecision(2) << std::fixed << group[i].vardas << string(20 - group[i].vardas.length(), ' ')
                << group[i].pavarde << string(21 - group[i].pavarde.length(), ' ') << group[i].galutinis_pazymys << endl;
        }
    }
    else
    {
        cout << "Vardas          Pavarde           Vidurkis" << endl;
        cout << "-----------------------------------------------------------" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << std::setprecision(2) << std::fixed << group[i].vardas << string(20 - group[i].vardas.length(), ' ')
                << group[i].pavarde << string(21 - group[i].pavarde.length(), ' ') << group[i].galutinis_pazymys << endl;
        }
    }
}

//  //

bool palygintiPavardes(const Studentas& a, const Studentas& b) {
    return a.pavarde < b.pavarde;
}

void bufferRead(vector<Studentas>& group) {
    string eil;
    std::stringstream startBuffer;
    std::stringstream lines;
    Studentas temp;
    int j = 0;
    int k;
    auto start = std::chrono::high_resolution_clock::now();
    std::fstream input("studentai.txt"); 
    std::getline(input, eil);
    startBuffer << input.rdbuf();
    input.close();
    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start; 
    std::cout << "Failu skaitymas uztruko " << diff.count() << " sekundziu" << endl;


    auto start2 = std::chrono::high_resolution_clock::now();
    while (startBuffer) {
        if (!startBuffer.eof()) {
            std::getline(startBuffer, eil);
            lines << eil;

            lines >> temp.vardas >> temp.pavarde;

            while (!lines.eof())
            {
                lines >> k;
                temp.namudarbai.push_back(k);
            }
            lines.clear();
            temp.egz_pazymys = temp.namudarbai[temp.namudarbai.size() - 1];
            temp.namudarbai.pop_back();
            temp.namudarbai.shrink_to_fit();
            temp.ND = temp.namudarbai.size();
            group.push_back(temp);
            temp = {};
        }
        else break;
    }
    startBuffer.clear();

    std::sort(group.begin(), group.end(), palygintiPavardes);
    std::chrono::duration<double> diff2 = std::chrono::high_resolution_clock::now() - start2;
    std::cout << "Duomenu apdorojimas uztruko " << diff2.count() << " sekundziu." << endl;
}

void failoRasymas(vector<Studentas>& group, int n, bool isMedian) {
    std::ofstream output("rez.txt");
    std::stringstream endBuffer;
    if (isMedian)
    {
        endBuffer << "Vardas          Pavarde           Mediana" << endl;
        endBuffer << "----------------------------------------------------------" << endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
        {
            endBuffer << std::setprecision(2) << std::fixed << group.at(i).vardas << string(20 - group.at(i).vardas.length(), ' ')
                << group.at(i).pavarde << string(21 - group.at(i).pavarde.length(), ' ') << group.at(i).galutinis_pazymys << endl;
        }
        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
        std::cout << "Rasymas i buffer'i uztruko " << diff.count() << " sekundziu" << endl;
    }
    else
    {
        endBuffer << "Vardas          Pavarde           Mediana" << endl;
        endBuffer << "----------------------------------------------------------" << endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
        {
            endBuffer << std::setprecision(2) << std::fixed << group.at(i).vardas << string(20 - group.at(i).vardas.length(), ' ')
                << group.at(i).pavarde << string(21 - group.at(i).pavarde.length(), ' ') << group.at(i).galutinis_pazymys << endl;
        }
        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
        std::cout << "Rasymas i buffer'i uztruko " << diff.count() << " sekundziu" << endl;
    }

    output << endBuffer.str();
    output.close();
}

int main() {
    vector<Studentas> group;  
    int n;                  
    bool run = true;      
    bool PazymiuSkaicius;       
    string atsakymas_skait;
    string atsakymas_mediana;
    cout << "Ar ivesti duomenis is failo? (taip - t, ne - n) ";
    do {
        cin >> atsakymas_skait;
        if (atsakymas_skait == "T" || atsakymas_skait == "t")
        {
            cout << "Ar galutiniam pazymiui naudoti mediana? (taip - t, ne - n) ";
            do {
                cin >> atsakymas_mediana;
                if (atsakymas_mediana == "T" || atsakymas_mediana == "t")
                {
                    bufferRead(group);
                    mediana(group, group.size());
                    auto start3 = std::chrono::high_resolution_clock::now();
                    failoRasymas(group, group.size(), true);
                    run = false;
                    std::chrono::duration<double> diff3 = std::chrono::high_resolution_clock::now() - start3;
                    std::cout << "Rasymas i faila uztruko " << diff3.count() << " sekundziu" << endl;
                }
                else if (atsakymas_mediana == "N" || atsakymas_mediana == "n")
                {
                    bufferRead(group);
                    galutinis(group, group.size());
                    auto start3 = std::chrono::high_resolution_clock::now();
                    failoRasymas(group, group.size(), false);
                    run = false;
                    std::chrono::duration<double> diff3 = std::chrono::high_resolution_clock::now() - start3;
                    std::cout << "Rasymas i faila uztruko " << diff3.count() << " sekundziu" << endl;
                }
                else
                {
                    cout << endl;
                    cout << "Neteisingas ivedimas! Iveskite savo pasirinkima dar karta (t, n) " << endl;
                    run = true;
                }
            }             while (run);

            run = false;
        }
        else if (atsakymas_skait == "N" || atsakymas_skait == "n")
        {
            cout << "Iveskite studentu skaiciu: ";
            n = std::stoi(getDigits());
            for (int i = 0; i < n; i++)
            {
                group.push_back(Studentas());

                cout << "Iveskite studento varda: ";
                do {
                    cin >> group[i].vardas;
                    cout << endl;
                } while (!validateName(group[i].vardas));

                cout << "Iveskite studento pavarde: ";
                do {
                    cin >> group[i].pavarde;
                    cout << endl;
                } while (!validateName(group[i].pavarde));

                string ansGrade;
                cout << "Ar zinomas studento pazymiu kiekis? Jei taip, spauskite 't', jei ne, spauskite 'n' ";
                do {
                    cin >> ansGrade;
                    if (ansGrade == "T" || ansGrade == "t")
                    {
                        int temp;
                        cout << "Iveskite pazymiu kieki: ";
                        do {
                            temp = std::stoi(getDigits());
                            if (temp > 0)
                            {
                                group[i].ND = temp;
                                run = false;
                            }
                            else
                            {
                                cout << "Ivestas negalimas pazymiu kiekis" << endl << "Iveskite is naujo: ";
                                run = true;
                            }
                        }                         while (run);
                        PazymiuSkaicius = true;
                    }
                    else if (ansGrade == "N" || ansGrade == "n")
                    {
                        cout << endl;
                        PazymiuSkaicius = false;
                        run = false;
                    }
                    else
                    {
                        cout << endl;
                        cout << "Klaidingas ivedimas" << endl;
                        cout << "Iveskite is naujo (taip - 't', ne - 'n') ";
                        run = true;
                    }
                }                 while (run);

                string atsakymas_rng;
                cout << "Ar pazymius generuoti atsitiktiniu budu ? Jei taip, spauskite 't', jei ne, spauskite 'n' ";
                do {
                    cin >> atsakymas_rng;
                    if (atsakymas_rng == "T" || atsakymas_rng == "t")
                    {
                        cout << endl;
                        randomgrades(PazymiuSkaicius, group[i]);
                        run = false;
                    }
                    else if (atsakymas_rng == "n" || atsakymas_rng == "N")
                    {
                        NamuDarbai(PazymiuSkaicius, group[i]);
                        cout << endl << "Iveskite egzamino pazymi: ";
                        group[i].egz_pazymys = getExam();
                        run = false;
                    }
                    else
                    {
                        cout << endl;
                        cout << "Pazymys ivestas neteisingai!" << endl;
                        cout << "Iveskite is naujo:  ";
                        run = true;
                    }
                }                 while (run);
            }
            group.shrink_to_fit();

            cout << "Ar norite rezultata matyti mediana? Jei taip, spauskite 't', jei ne, spauskite 'n' ";
            do {
                cin >> atsakymas_mediana;
                if (atsakymas_mediana == "t" || atsakymas_mediana == "T")
                {
                    mediana(group, n);
                    print(group, n, true);
                    run = false;
                }
                else if (atsakymas_mediana == "n" || atsakymas_mediana == "N")
                {
                    galutinis(group, n);
                    print(group, n, false);
                    run = false;
                }
                else
                {
                    cout << endl;
                    cout << "Ivesta neteisingai!" << endl;
                    cout << "Iveskite is naujo:   ";
                    run = true;
                }
            }             while (run);
            run = false;
        }
        else
        {
            cout << endl;
            cout << "Ivesta neteisingai!" << endl;
            cout << "Iveskite is naujo:   ";
        }
    }     while (run);

    system("pause");

    return 0;
}
