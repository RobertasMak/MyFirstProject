#include "funkcijos.h"

void input(vector<Studentas>& studentai) {
    Studentas st;
    string vardas, pavarde;
    int n = 0;
    int egzaminas;
    char tn;

    cout << "Iveskite studento varda: ";
    getline(cin, st.vardas);
    cout << "Iveskite studento pavarde: ";
    getline(cin, st.pavarde);

    cout << "Toliau iveskite studento " << st.vardas << " " << st.pavarde << " prasomus duomenis" << endl;
    cout << "Ar yra zinomas tikslus namu darbu skaicius?(t/n): ";
    cin >> tn;
    checkInputChar(tn);

    if (tn == 't') {
        cout << "Iveskite tikslu namu darbu skaiciu: ";
        cin >> n;
        while (cin.fail()) {
            cout << "Turite ivesti skaiciu: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> n;
        }

        cout << "Ar norite, jog studento rezultatai butu sugeneruoti atsitiktinai?(t/n): ";
        cin >> tn;
        checkInputChar(tn);

        if (tn == 't') {
            for (int i = 0; i < n; i++) {
                st.pazymiai.push_back(rand() % 10 + 1);
                cout << i + 1 << "-ojo namu darbo rezultatas: " << st.pazymiai[i] << endl;
            }

            st.egzaminas = rand() % 10 + 1;
            cout << "Egzamino rezultatas: " << st.egzaminas << endl;
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

                st.pazymiai.push_back(input);
            }
            cout << "Iveskite egzamino rezultata: ";
            int egzas;
            cin >> egzas;

            while (egzas < 0 || egzas > 10 || cin.fail()) {
                cin.clear();
                cout << "Ivedete netinkama reiksme, iveskite rezultata is naujo (1-10): ";
                cin >> egzas;
            }

            st.egzaminas = egzas;
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

            st.pazymiai.push_back(input);

            if (input == 0 && n > 0) {
                st.pazymiai.pop_back();
                cout << "Iveskite egzamino rezultata: ";
                int egzas;
                cin >> egzas;

                while (egzas < 0 || egzas > 10 || cin.fail()) {
                    cin.clear();
                    cout << "Ivedete netinkama reiksme, iveskite rezultata is naujo (1-10): ";
                    cin >> egzas;
                }

                st.egzaminas = egzas;
                studentai.push_back(st);
                break;

            }
            else if (st.pazymiai.size() == 0 && n == 0) {
                cout << "Turi buti ivestas bent vienas namu darbo rezultatas!" << endl;
            }
            else n++;
        }

    }
};

void checkInputChar(char& tn) {
    while (tn != 't' && tn != 'n') {
        cout << "Galimas pasirinkimas tik taip(t) arba ne(n)!" << endl;
        cout << "Pakartokite pasirinkima (taip - t, ne - n): ";
        cin >> tn;
    }
}

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
            student.egzaminas = n;
            student.vardas = vardas;
            student.pavarde = pavarde;
            student.pazymiai = grades;
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


    //
    input.close();
};

bool palyginimas(const Studentas& pirmas, const Studentas& antras) {
    if (pirmas.pavarde == antras.pavarde) return pirmas.vardas < antras.vardas;
    return pirmas.pavarde < antras.pavarde;
};

void countAvg(vector<Studentas>& studentai) {
    for (int i = 0; i < studentai.size(); i++) {
        double galutinisvid = 0;

        for (int j = 0; j < studentai[i].pazymiai.size(); j++)
            galutinisvid += studentai[i].pazymiai[j];

        galutinisvid = galutinisvid / studentai[i].pazymiai.size();
        studentai[i].vidurkis = galutinisvid * 0.4 + studentai[i].egzaminas * 0.6;
    }
}

void output(vector<Studentas>& studentai) {
    char tn;
    cout << "Pradedami isvesti duomenys..." << endl;
    cout << "Ar norite, jog jusu galutinis rezultatas butu pazymiu mediana?(t/n): ";
    cin >> tn;
    checkInputChar(tn);

    if (tn == 'n') {
        cout << left << setw(20) << "Pavarde"
            << setw(15) << "Vardas"
            << setw(10) << "Galutinis (Vid.)" << endl;
        cout << string(65, '-') << endl;

        countAvg(studentai);
        for (int i = 0; i < studentai.size(); i++) {

            cout << left << setw(20) << studentai[i].pavarde
                << setw(15) << studentai[i].vardas
                << setw(10) << setprecision(2) << studentai[i].vidurkis << endl;
        }

    }
    else {
        cout << left << setw(20) << "Pavarde"
            << setw(15) << "Vardas"
            << setw(10) << "Galutinis (Med.)" << endl;
        cout << string(65, '-') << endl;

        for (int i = 0; i < studentai.size(); i++) {
            sort(studentai[i].pazymiai.begin(), studentai[i].pazymiai.end());

            double mediana = 0;

            if (studentai[i].pazymiai.size() % 2 == 1)
                mediana = studentai[i].pazymiai[studentai[i].pazymiai.size() / 2];

            else mediana = ((double)studentai[i].pazymiai[studentai[i].pazymiai.size() / 2] + (double)studentai[i].pazymiai[studentai[i].pazymiai.size() / 2 - 1]) / 2;

            double galutinis = mediana * 0.4 + studentai[i].egzaminas * 0.6;

            cout << left << setw(20) << studentai[i].pavarde
                << setw(15) << studentai[i].vardas
                << setw(10) << setprecision(2) << galutinis << endl;
        }
    }
}

int generationNumber() {
    //vector<Studentas> studentai;
    int skaicius;
    char tn;
    cout << "Pasirinkite kiek studentu generuoti: " << endl
        << "(1) 1000" << endl
        << "(2) 10000" << endl
        << "(3) 100000" << endl
        << "(4) 1000000" << endl
        << "(5) 10000000" << endl;
    cin >> skaicius;
    int number;
    while (true) {
        switch (skaicius)
        {
        case 1:
            number = 1000;

            break;

        case 2:
            number = 10000;

            break;

        case 3:
            number = 100000;

            break;

        case 4:
            number = 1000000;

            break;

        case 5:
            number = 10000000;

            break;

        default:
        {
            cout << "Blogas pasirinkimas. Galimi pasirinkimai nuo 1 iki 7";
            cin >> skaicius;
            continue;
        }
        }
        break;
    }
    return number;
}

void generateFile(int numberStudents) {

    string file;
    int kieknd = rand() % 10 + 5;
    file = "studentai" + to_string(numberStudents) + ".txt";

    cout << "Pradedamas generavimas..." << endl;
    Timer t;

    ofstream generate;
    generate.open(file);

    generate << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 0; i < kieknd; i++) {
        generate << setw(7) << "ND" + to_string(i + 1);
    };
    generate << setw(7) << "Egz." << endl;

    for (int i = 0; i < numberStudents; i++) {
        generate << left << setw(20) << "Vardas" + to_string(i + 1) << setw(20) << "Pavarde" + to_string(i + 1);

        for (int j = 0; j < kieknd; j++) {
            generate << setw(7) << rand() % 10 + 1;
        }
        generate << setw(7) << rand() % 10 + 1;
        if (i != numberStudents - 1) generate << endl;
    }

    generate.close();

    cout << numberStudents << " studentu generavimas baigtas ir uztruko " << t.elapsed() << "s" << endl << endl;
}


void sortStudentsVector(vector<Studentas>& studentai) {
    vector<Studentas> kiektiakai;
    vector<Studentas> vagsiukai;
    cout << "Pradedamas studentu rusiavimas..." << endl;
    Timer t;
    for (int i = 0; i < studentai.size(); i) {

        if (studentai[i].vidurkis >= 5.00) {
            kiektiakai.push_back(studentai[i]);
            studentai.erase(studentai.begin());
        }
        else {
            vagsiukai.push_back(studentai[i]);
            studentai.erase(studentai.begin());
        }

    }
    cout << kiektiakai.size() + vagsiukai.size() << " studentu rusiavimas baigtas ir uztruko " << t.elapsed() << "s" << endl << endl;


    cout << "Studentu duomenis isvedami i failus..." << endl;

    ofstream kiet;
    kiet.open("kiektiakai.txt");

    kiet << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Vidurkis" << endl;

    for (int i = 0; i < kiektiakai.size(); i++) {
        kiet << left << setw(20) << kiektiakai[i].vardas << setw(20) << kiektiakai[i].pavarde << setw(10) << setprecision(3) << kiektiakai[i].vidurkis;
        if (i != kiektiakai.size() - 1) kiet << endl;
    }
    kiet.close();

    ofstream varg;
    varg.open("vagsiukai.txt");

    varg << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Vidurkis" << endl;

    for (int i = 0; i < vagsiukai.size(); i++) {
        varg << left << setw(20) << vagsiukai[i].vardas << setw(20) << vagsiukai[i].pavarde << setw(10) << setprecision(3) << vagsiukai[i].vidurkis;
        if (i != vagsiukai.size() - 1) varg << endl;
    }
    varg.close();

    cout << kiektiakai.size() + vagsiukai.size() << " studentu isvedimas baigtas ir uztruko " << t.elapsed() << "s" << endl;
};



void sortStudentsList(list<Studentas>& studentai) {
    list<Studentas> kiektiakai;
    list<Studentas> vagsiukai;
    cout << "Pradedamas studentu rusiavimas..." << endl;
    Timer t;
    for (auto it = studentai.begin(); it != studentai.end(); ++it) {

        if (it->vidurkis >= 5.00) {
            kiektiakai.push_back(*it);
            studentai.erase(studentai.begin(), it);
        }
        else {
            vagsiukai.push_back(*it);
            studentai.erase(studentai.begin(), it);

        }


    }
    cout << studentai.size() << " studentu rusiavimas baigtas ir uztruko " << t.elapsed() << "s" << endl << endl;


    cout << "Studentu duomenis isvedami i failus..." << endl;

    ofstream kiet;
    kiet.open("kiektiakai.txt");

    kiet << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Vidurkis" << endl;

    for (auto it = kiektiakai.begin(); it != kiektiakai.end(); it++) {
        kiet << left << setw(20) << it->vardas << setw(20) << it->pavarde << setw(10) << setprecision(3) << it->vidurkis << endl;
    }
    kiet.close();

    ofstream varg;
    varg.open("vagsiukai.txt");

    varg << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Vidurkis" << endl;

    for (auto it = vagsiukai.begin(); it != vagsiukai.end(); it++) {
        varg << left << setw(20) << it->vardas << setw(20) << it->pavarde << setw(10) << setprecision(3) << it->vidurkis << endl;
    }
    varg.close();

    cout << kiektiakai.size() + vagsiukai.size() << " studentu isvedimas baigtas ir uztruko " << t.elapsed() << "s" << endl;
};

void sortStudentsDeque(deque<Studentas>& studentai) {
    deque<Studentas> kiektiakai;
    deque<Studentas> vagsiukai;
    cout << "Pradedamas studentu rusiavimas..." << endl;
    Timer t;
    for (int i = 0; i < studentai.size(); i) {

        if (studentai[i].vidurkis >= 5.00) {
            kiektiakai.push_back(studentai[i]);
            studentai.erase(studentai.begin());
        }
        else {
            vagsiukai.push_back(studentai[i]);
            studentai.erase(studentai.begin());
        }
    }
    cout << kiektiakai.size() + vagsiukai.size() << " studentu rusiavimas baigtas ir uztruko " << t.elapsed() << "s" << endl << endl;


    cout << "Studentu duomenis isvedami i failus..." << endl;

    ofstream kiet;
    kiet.open("kiektiakai.txt");

    kiet << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Vidurkis" << endl;

    for (int i = 0; i < kiektiakai.size(); i++) {
        kiet << left << setw(20) << kiektiakai[i].vardas << setw(20) << kiektiakai[i].pavarde << setw(10) << setprecision(3) << kiektiakai[i].vidurkis;
        if (i != kiektiakai.size() - 1) kiet << endl;
    }
    kiet.close();

    ofstream varg;
    varg.open("vagsiukai.txt");

    varg << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Vidurkis" << endl;

    for (int i = 0; i < vagsiukai.size(); i++) {
        varg << left << setw(20) << vagsiukai[i].vardas << setw(20) << vagsiukai[i].pavarde << setw(10) << setprecision(3) << vagsiukai[i].vidurkis;
        if (i != vagsiukai.size() - 1) varg << endl;
    }
    varg.close();

    cout << kiektiakai.size() + vagsiukai.size() << " studentu isvedimas baigtas ir uztruko " << t.elapsed() << "s" << endl;
};