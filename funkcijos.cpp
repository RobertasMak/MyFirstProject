#include "funkcijos.h"

void checkInputChar(char& pasirinkimas) {
    while (pasirinkimas != 't' && pasirinkimas != 'n') {
        cout << "Galima pasirinkti tik taip arba ne! (taip - t, ne - n)" << endl;
        cout << "Pakartokite savo pasirinkima! (t arba n): ";
        cin >> pasirinkimas;
    }
}

void input(vector<Studentas>& studentai) {
    Studentas st;
    string vardas, pavarde;
    int n = 0;
    int egzaminas;
    char pasirinkimas;

    cout << "Iveskite studento varda: ";
    getline(cin, st.vardas);
    cout << "Iveskite studento pavarde: ";
    getline(cin, st.pavarde);

    cout << "Toliau iveskite studento " << st.vardas << " " << st.pavarde << " kitus duomenis" << endl;
    cout << "Ar yra zinomas tikslus namu darbu skaicius? (taip - t, ne - n): ";
    cin >> pasirinkimas;
    checkInputChar(pasirinkimas);

    if (pasirinkimas == 't') {
        cout << "Iveskite tikslu namu darbu skaiciu: ";
        cin >> n;
        while (cin.fail()) {
            cout << "Turite ivesti skaiciu: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> n;
        }

        cout << "Ar norite, kad studento rezultatai butu sugeneruoti atsitiktinai? (taip - t, ne - n): ";
        cin >> pasirinkimas;
        checkInputChar(pasirinkimas);

        if (pasirinkimas == 't') {
            for (int i = 0; i < n; i++) {
                st.namudarbai.push_back(rand() % 10 + 1);
                cout << i + 1 << "-ojo namu darbo rezultatas: " << st.namudarbai[i] << endl;
            }

            st.egz_pazymys = rand() % 10 + 1;
            cout << "Egzamino rezultatas: " << st.egz_pazymys << endl;
            studentai.push_back(st);
        }
        else {
            for (int i = 0; i < n; i++) {
                int input;
                cout << "Iveskite " << i + 1 << "-ojo namu darbo rezultata: ";
                cin >> input;

                while (input < 0 || input > 10 || cin.fail()) {
                    cin.clear();
                    cout << "Ivedete netinkama reiksme, iveskite rezultata is naujo (1-10): ";
                    cin >> input;
                }

                st.namudarbai.push_back(input);
            }
            cout << "Iveskite egzamino rezultata: ";
            int egz;
            cin >> egz;

            while (egz < 0 || egz > 10 || cin.fail()) {
                cin.clear();
                cout << "Ivedete netinkama reiksme, iveskite rezultata is naujo (1-10): ";
                cin >> egz;
            }

            st.egz_pazymys = egz;
            studentai.push_back(st);
        }
    }
    else {
        cout << "Noredami sustabdyti namu darbu ivedima irasykite 0" << endl;

        while (true) {
            cout << "Iveskite " << n + 1 << "-ojo namu darbo rezultata: ";
            int input;
            cin >> input;

            while (input < 0 || input > 10 || cin.fail()) {
                cin.clear();
                cout << "Ivedete netinkama reiksme, iveskite rezultata is naujo (1-10): ";
                cin >> input;
            }

            st.namudarbai.push_back(input);

            if (input == 0 && n > 0) {
                st.namudarbai.pop_back();
                cout << "Iveskite egzamino rezultata: ";
                int egzas;
                cin >> egzas;

                while (egzas < 0 || egzas > 10 || cin.fail()) {
                    cin.clear();
                    cout << "Ivedete netinkama reiksme, iveskite rezultata is naujo (1-10): ";
                    cin >> egzas;
                }

                st.egz_pazymys = egzas;
                studentai.push_back(st);
                break;

            }
            else if (st.namudarbai.size() == 0 && n == 0) {
                cout << "Turi buti ivestas bent vienas namu darbu rezultatas!" << endl;
            }
            else n++;
        }

    }
};

void readFile(vector<Studentas>& studentai) {
    Studentas student;
    string line, vardas, pavarde;
    vector<int> grades;

    ifstream input;

    try
    {
        string pavadinimas = "kursiokai.txt";
        input.open(pavadinimas);
        if (!input.is_open())
            throw 1;
        else cout << "Failas atidarytas..." << endl;
    }
    catch (int error)
    {
        std::cout << "Failas nerastas... Patikrinkite ar failo teisingas failo pavadinimas ir formatas (kursiokai.txt)" << endl;
        cout << "Programa stabdoma";
        exit(0);
    }

    input.ignore(256, '\n');

    try
    {
        while (true) {
            input >> vardas >> pavarde;
            getline(input, line);

            stringstream ndpazymiai(line);
            int n;
            while (ndpazymiai >> n) {
                grades.push_back(n);
            }

            grades.pop_back();
            student.egz_pazymys = n;
            student.vardas = vardas;
            student.pavarde = pavarde;
            student.namudarbai = grades;
            studentai.push_back(student);
            grades.clear();

            if (input.eof())
                break;
        }
    }
    catch (std::bad_alloc& exception)
    {
        std::cout << "Faile yra klaidu" << endl;
        input.ignore(256, '\n');
    }
           
    input.close();
};

bool palyginimas(const Studentas& pirmas, const Studentas& antras) {
    if (pirmas.pavarde == antras.pavarde) return pirmas.vardas < antras.vardas;
    return pirmas.pavarde < antras.pavarde;
};

void output(vector<Studentas>& studentai) {
    char pasirinkimas;
    cout << "Pradedami isvesti duomenys..." << endl;
    cout << "Ar norite, jog jusu galutinis rezultatas butu pazymiu mediana? (taip - t, ne - n): ";
    cin >> pasirinkimas;
    checkInputChar(pasirinkimas);

    if (pasirinkimas == 'n') {
        cout << left << setw(20) << "Pavarde"
            << setw(15) << "Vardas"
            << setw(10) << "Galutinis (Vid.)" << endl;
        cout << string(65, '-') << endl;

        for (int i = 0; i < studentai.size(); i++) {
            double galutinisvid = 0;

            for (int j = 0; j < studentai[i].namudarbai.size(); j++)
                galutinisvid += studentai[i].namudarbai[j];

            galutinisvid = galutinisvid / studentai[i].namudarbai.size();
            galutinisvid = galutinisvid * 0.4 + studentai[i].egz_pazymys * 0.6;

            cout << left << setw(20) << studentai[i].pavarde
                << setw(15) << studentai[i].vardas
                << setw(10) << setprecision(2) << galutinisvid << endl;
        }

    }
    else {
        cout << left << setw(20) << "Pavarde"
            << setw(15) << "Vardas"
            << setw(10) << "Galutinis (Med.)" << endl;
        cout << string(65, '-') << endl;

        for (int i = 0; i < studentai.size(); i++) {
            sort(studentai[i].namudarbai.begin(), studentai[i].namudarbai.end());

            double mediana = 0;

            if (studentai[i].namudarbai.size() % 2 == 1)
                mediana = studentai[i].namudarbai[studentai[i].namudarbai.size() / 2];

            else mediana = ((double)studentai[i].namudarbai[studentai[i].namudarbai.size() / 2] + (double)studentai[i].namudarbai[studentai[i].namudarbai.size() / 2 - 1]) / 2;

            double galutinis = mediana * 0.4 + studentai[i].egz_pazymys * 0.6;

            cout << left << setw(20) << studentai[i].pavarde
                << setw(15) << studentai[i].vardas
                << setw(10) << setprecision(2) << galutinis << endl;
        }
    }
}

