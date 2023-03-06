#include "funkcijos.h"
int main() {

    srand(time(NULL));

    vector<Studentas> studentai;

    char pasirinkimas;
    cout << "Ar norite, jog duomenis butu nuskaityti is failo? (taip - t, ne - n): ";
    cin >> pasirinkimas;
    cin.ignore();
    checkInputChar(pasirinkimas);

    if (pasirinkimas == 't') {
        readFile(studentai);
        cout << "Failo duomenys nuskaityti" << endl;
        sort(studentai.begin(), studentai.end(), palyginimas);
        output(studentai);

    }
    else {
        while (true) {
            input(studentai);

            cout << "Ar norite prideti dar viena studenta?(t/n): ";
            cin >> pasirinkimas;
            cin.ignore();
            checkInputChar(pasirinkimas);
            if (pasirinkimas == 'n') {
                break;
            }
        }
        output(studentai);
    }
}