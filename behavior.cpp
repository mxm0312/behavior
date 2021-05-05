#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Array.h"
#include "Bayes.h"

using namespace std;

Array HarmfulBehavior::attributes;
Array UnharmfullBehavior::attributes;
int HarmfulBehavior::k = 0;
int UnharmfullBehavior::k = 0;


int main() {
    
    ifstream myFile;
    myFile.open("behavior.csv");
    if (!myFile.is_open()) {
        cout << "Файл не найден" << endl;
    }
    
    /* Читаем первую строку, чтобы определить количество признаков в классах Байесовского классификатора */
    string first_line;
    getline(myFile, first_line);
    string word;
    stringstream s_first(first_line);
    
    int col = 0; // количество столбцов в табоице
    
    while (getline(s_first, word, ',')) {
        col += 1;
    }
    /* заполняю нулями количество
     вхождений признаков в каждый класс классификации */
    for (int i = 0; i < col-2; i++) { // признаки не содержатся в 1 и последнем стобце, поэтому -2
        HarmfulBehavior::attributes.push_back(0);
        UnharmfullBehavior::attributes.push_back(0);
    }
    
    while (myFile.good()) { /* начало обучения */
        
        string line; /* строка из который будет извлекаться количество действий,
                      соответствующих i-му столбцу данной таблицы */
        getline(myFile, line); // читаем строку и записываем её в line
        
        string word; /* количество действий соответсвующее столбцу */
        stringstream s(line); // это нам нужно чтобы выделять из line отдельные признаки поведения пользователя
        
        
        /* проверка на tag. Если он 0, то признаки учитываются в UnharmfullBehavior, если 1, то он учитывается в HarmfulBehavior :) */
        if ((int)(line[line.length() - 2]) - 48 == 0) { /* -48 для корректного приведения чара в инт */
            // Не вредоносные признаки
            int i = 0;
            UnharmfullBehavior::k += 1;
            getline(s, word, ','); // самое первое слово нас не интересует!
            while (getline(s, word, ',')) {
               
                if (i < col-1) {
                    UnharmfullBehavior::attributes.getArray()[i] += stoi(word); // прибавляем количество вхождений признака в класс безопасного поведения
                }
                i += 1;
                
            }
            
        } else {
            // Вредоносные признаки
            int i = 0;
            HarmfulBehavior::k += 1;
            getline(s, word, ','); // самое первое слово нас не интересует!
            while (getline(s, word, ',')) {
                
                if (i < col-1) { // так как последним в line идет tag
                    HarmfulBehavior::attributes.getArray()[i] += stoi(word); // прибавляем количество вхождений признака в класс вредоносного поведения
                }
                i += 1;
            }
        }
        
       
    } /* Конец обучения */
    
    myFile.close();

    // Создаю новые файлы, в которые перенесутся данные, полученные после обучения!
    ofstream out1;
    out1.open("Harmful.txt");
    if (out1.is_open()) {
        for (int i = 0; i < HarmfulBehavior::attributes.lenght(); i++) {
            if (i == HarmfulBehavior::attributes.lenght() - 1) {
                out1 << HarmfulBehavior::attributes.getArray()[i] << endl;
            } else {
                out1 << HarmfulBehavior::attributes.getArray()[i] << ",";
            }
        }
    }
    ofstream out2;
    out2.open("Unharmful.txt");
    for (int i = 0; i < UnharmfullBehavior::attributes.lenght(); i++) {
        if (i == UnharmfullBehavior::attributes.lenght() - 1) {
            out2 << UnharmfullBehavior::attributes.getArray()[i] << endl;
        } else {
            out2 << UnharmfullBehavior::attributes.getArray()[i] << ",";
        }
    }
    
    /* Проверка модели на тестовой выборке */
    int rightPredictions = 0;
    int amount = 0;
    
    Bayes model; // Создаем экземпляр класса Байеовского классификатора
    
    
    myFile.open("behavior.csv");
    if (!myFile.is_open()) {
        cout << "Файл не найден" << endl;
    }
    
    getline(myFile, first_line);
   

    while (myFile.good()) {
        string line;
        Array inputAtt;
        string word;
        getline(myFile, line);
        stringstream s(line);
        getline(s, word, ',');

        while (getline(s, word, ',')) {
          
            int i = 0;
            if (i < col-1) {
                inputAtt.push_back(stoi(word));
            }
            i += 1;
            
        }
        bool prediction = model.prediction(inputAtt);
        if ((prediction == true && (int)(line[line.length() - 2]) - 48 == 0) || (prediction == false && (int)(line[line.length() - 2]) - 48 == 1)) {

            rightPredictions += 1;
        }
        amount += 1;
    }

    cout << "Точность модели: " << (float)rightPredictions/amount << endl;
    cout << "Вредоносных пользователей: " << HarmfulBehavior:: k << endl;
    cout << "Не вредоносных пользователей: " << UnharmfullBehavior::k << endl;
    

    
    return 0;
}
