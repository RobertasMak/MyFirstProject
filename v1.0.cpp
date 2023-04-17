#include "funkcijos.h"
int main() {

    srand(time(NULL));

    vector<Studentas> studentai;

    char tn;
    cout << "Ar norite, jog duomenis butu sugeneruoti automatiskai ir iskarto nuskaityti? (taip - t, ne - n): ";
    cin >> tn;
    cin.ignore();
    checkInputChar(tn);
    char gen;
    cout << "Ar norite sugeneruoti nauja faila? (taip - t, ne - n): ";
    cin >> gen;
    if (gen == 't') {
        generationNumber();
    }
    else {
        if (tn == 't') {


            cout << "Pasirinkite ar failus nuskaityti i vector, list ar deque konteinerius(v, l, d): ";
            cin >> tn;
            if (tn == 'v') {
                vector<Studentas> studentai;
                int skai = whichRead();
                generatedFileRead(studentai, skai);
                sortStudentsVector(studentai);
            }
            else if (tn == 'l') {
                list<Studentas> studentai;
                int skai = whichRead();
                generatedFileRead(studentai, skai);
                sortStudentsList(studentai);
            }
            else {
                deque<Studentas> studentai;
                int skai = whichRead();
                generatedFileRead(studentai, skai);
                sortStudentsDeque(studentai);
            }
        }
        else if (tn == 'n') {
            cout << "Ar norite, jog duomenis butu nuskaityti is failo? (taip - t, ne - n): ";
            cin >> tn;
            cin.ignore();
            checkInputChar(tn);

            if (tn == 't') {
                readFile(studentai);
                cout << "Failo duomenys nuskaityti" << endl;
                sort(studentai.begin(), studentai.end(), palyginimas);
                output(studentai);

            }
            else {
                while (true) {
                    input(studentai);

                    cout << "Ar norite prideti dar viena studenta? (taip - t, ne - n): ";
                    cin >> tn;
                    cin.ignore();
                    checkInputChar(tn);
                    if (tn == 'n') {
                        break;
                    }
                }
                output(studentai);
            }
        }
    }
}