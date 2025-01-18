#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <conio.h>



using namespace std;

class Student {
private:
    string* ad;                 
    string* ogr_no;             
    float* ara_sinav;          
    float* sinav_2;            
    float* odev;               
    float* final;              
    int* devam_sayisi; 


    float* ortalamalar;        
    int num_students;          

public:
    Student();
    ~Student();

    void readFromCSV();
    float average(string no);
    void print();
    void print(int b);
    void print(string b);
    void ogrenci_sayisi_al();

    void ortalama_kaydet();
    void menu();
};

Student::Student(){
    ogrenci_sayisi_al();

    ad = new string[num_students];
    ogr_no = new string[num_students];
    ara_sinav = new float[num_students];
    sinav_2 = new float[num_students];
    odev = new float[num_students];
    final = new float[num_students];
    devam_sayisi = new int[num_students];
    ortalamalar = new float[num_students];
    
    readFromCSV();
}

Student::~Student() {
    delete[] ad;
    delete[] ogr_no;
    delete[] ara_sinav;
    delete[] sinav_2;
    delete[] odev;
    delete[] final;
    delete[] devam_sayisi;
    delete[] ortalamalar;
}

void Student::ogrenci_sayisi_al(){
      string satir;
      int i=0;

      ifstream say("girdi.csv");
      getline(say,satir);
      while (getline(say,satir)) i++;
      say.close();
      num_students=i;

}

void Student::readFromCSV() {
    string satir, kelime;
    int i=0;
    ifstream oku("girdi.csv");

    getline(oku, satir); 
    getline(oku, satir); 

    while (getline(oku, satir)) {

        if (satir.back() == ',') 
             devam_sayisi[i] = 0;

        stringstream s(satir);
        int syc = 0;

        while (getline(s, kelime, ',')) {
            switch (syc) {
            case 0:
                ad[i] = kelime;
                syc++;
                break;
            case 1:
                ogr_no[i] = kelime;
                syc++;
                break;
            case 2:
                ara_sinav[i] = stof(kelime);
                syc++;
                break;
            case 3:
                sinav_2[i] = stof(kelime);
                syc++;
                break;
            case 4:
                odev[i] = stof(kelime);
                syc++;
                break;
            case 5:
                final[i] = stof(kelime);
                syc++;
                break;
            case 6:   
                  devam_sayisi[i] = stoi(kelime);  
                  syc = 0;
                break;
            default:
                break;
            }
        }
        i++;
    }
    oku.close();
    ortalama_kaydet();
}

float Student::average(string no) {
    int num = -1;
    float ort;

    for (int i = 0; i < num_students; i++) {
        if (no == ogr_no[i]) {
            num = i;
            break;
        }
    }
    if (num == -1) {
        cout << no << " numarali ogrenci bulunamadi.." << endl;
        return num;
    }
    else {
        ort = (0.2 * ara_sinav[num]) + (0.2 * sinav_2[num]) + (0.2 * odev[num]) + (0.4 * final[num]);
        return ort;
    }
}

void Student::ortalama_kaydet() {
    for (int i = 0; i < num_students; i++) {
        float ort = average(ogr_no[i]);
        ortalamalar[i] = ort;
    }
}

void Student::print() {
    cout << "Ogrenci Numarasi-----Ogrenci Adi-----Arasinav-----2.Sinav-----Odev-----Final-----Devam Sayisi" << endl;
    for (int i = 0; i < num_students; i++) {
        int syc=0;
        for(int k=0;k<i;k++){
            if(ogr_no[i]==ogr_no[k]){
                syc=1;
                break;
            }
        }
        if(syc==0){
        cout <<setw(6)<<" "<< setw(16) <<left<<ogr_no[i] 
        <<setw(16)<<ad[i] 
        <<setw(13)<<ara_sinav[i]
        <<setw(12)<<sinav_2[i]
        <<setw(10)<<odev[i]
        <<setw(10)<<final[i]
        <<devam_sayisi[i]<<endl;
        }
    }
        
}

void Student::print(int b) {
    switch (b) {
    case 0:
        cout << "******Kalan ogrenciler******" << endl << endl;
        cout << "Ogrenci numarasi     Ogrenci adi     Ortalama" << endl;
        for (int i = 0; i < num_students; i++) {
            int syc=0;
            for(int k=0;k<i;k++){
                if(ogr_no[i]==ogr_no[k]){
                    syc=1;
                    break;
                }
            }
            if(syc==0){
              if (ortalamalar[i] < 50) {
                cout << setw(6) << " " << setw(16) << left << ogr_no[i] << setw(15) << ad[i] << ortalamalar[i] << endl;
              }
            }
        }
        break;
    case 1:
        cout << "******Gecen ogrenciler******" << endl << endl;
        cout << "Ogrenci numarasi     Ogrenci adi     Ortalama" << endl;
        for (int i = 0; i < num_students; i++) {
            int syc=0;
            for(int k=0;k<i;k++){
                if(ogr_no[i]==ogr_no[k]){
                    syc=1;
                    break;
                }
            }
            if(syc==0){
               if (ortalamalar[i] >= 50) {
                cout << setw(6) << " " << setw(16) << left << ogr_no[i] << setw(15) << ad[i] << ortalamalar[i] << endl;
                }
            }
        }
        break;
    default:
        break;
    }
}

void Student::print(string b) {
    ofstream yaz(b);

    yaz << "Gecen ogrenciler: " << endl << endl;

    for (int i = 0; i < num_students; i++) {
         int syc=0;
            for(int k=0;k<i;k++){
                if(ogr_no[i]==ogr_no[k]){
                    syc=1;
                    break;
                }
            }
            if(syc==0){
                 if (ortalamalar[i] >= 50) {
            yaz << setw(15) << left << ogr_no[i] << setw(15) << ad[i] << ortalamalar[i] << endl;
                 }
            }
    }
    yaz << endl;
    yaz << "Kalan ogrenciler:" << endl << endl;

    for (int i = 0; i < num_students; i++) {
        int syc=0;
            for(int k=0;k<i;k++){
                if(ogr_no[i]==ogr_no[k]){
                    syc=1;
                    break;
                }
            }
            if(syc==0){
                 if (ortalamalar[i] < 50) {
                 yaz << setw(15) << left << ogr_no[i] << setw(15) << ad[i] << ortalamalar[i] << endl;
                }
            }
    }

    yaz.close();
    cout << endl;
    cout << "Sonuclar " << b << " adli dosyaya kaydedildi.." << endl;
}

void Student::menu() {
    int giris , tutucu;
    string dosya_adi, num;

    cout << endl;
    cout << "1 - Ogrencilerin listesi" << endl;
    cout << "2 - Gecen ve kalan ogranciler listesi" << endl;
    cout << "3 - Ogrenci ortalamalarinin goruntulenmesi" << endl;
    cout << "4 - Sonuclarin dosyaya kaydedilmesi" << endl << endl;
    cout << "0 - cikis" << endl;
    cout << "giris: ";
    cin >> giris;

    switch (giris) {
    case 1:
        system("cls");
        print();
        _getch();
        system("cls");
        menu();
        break;

    case 2:
        system("cls");
        cout << "Kalan ogrenciler icin : 0" << endl;
        cout << "Gecen ogrenciler icin : 1" << endl;
        cin >> tutucu;
        if(tutucu == 0 || tutucu == 1){
            print(tutucu);
        }
        else{
            cout<< "Gecersiz secim yaptiniz. Lutfen Gecerli Secim yapiniz.";
        }
       
        _getch();
        system("cls");
        menu();
        break;
    case 3:
        system("cls");
        cout << "Ortalamasini ogrenmek istediginiz ogrenci numarasi: ";
        cin >> num;
        if (average(num) >= 0) {
            cout << num << " numarali ogrencinin ortalamasi: " << average(num) << endl;
        }
        _getch();
        system("cls");
        menu();
        break;
    case 4:
        system("cls");
        cout << "Dosya adini yazin: ";
        cin >> dosya_adi;
        print(dosya_adi);
        _getch();
        system("cls");
        menu();
        break;
    case 0:
        cout << "CIKIS YAPTINIZ!" << endl;
        break;
    default:
        cout << "\nYanlis tuslama yaptiniz..";
        _getch();
        system("cls");
        menu();
        break;
    }
}

int main() {
    Student s;
    s.menu();
    return 0;
}

