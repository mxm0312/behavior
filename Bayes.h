#ifndef B
#define B


/* Наивный Байесовский классификатор будет определять к какому классу относится массив из признаков поведения */

/* Класс вредоносного поведения */
class HarmfulBehavior {
public:
    static int k; // количество пользователей с вредоносным поведением в обучающей выборке
    static Array attributes; /* данный массив хранит число вхождений i-ого признака в данный класс
                           i - ый признак это название признака в i-м столбце данной таблице */
};
// Класс не врндоносного поведения
class UnharmfullBehavior {
public:
    static int k; // количество пользователей с не вредоносным поведением в обучающей выборке
    static Array attributes; /* данный массив хранит число вхождений i-ого признака в данный класс
                             i - ый признак это название признака в i-м столбце данной таблицы */
};

// Этот класс дает предсказание: вредоносное поведение или нет.
class Bayes {
private:
    int alpha = 1; // параметр для сглаживания
    
    // подсчет "вероятности" того, что поведение вредоносное (параметр функции: массив признаков)
    float probabilityOfHarmful(Array &inputAtt) {
        
        float probability = HarmfulBehavior::k/(HarmfulBehavior::k + UnharmfullBehavior::k); // априорная вероятность
        for (int i = 0; i < inputAtt.lenght(); i++) {
            if (inputAtt.getArray()[i] != 0) { // если у массива признаков i-ый признак не нулевой
                probability += (float)(alpha + HarmfulBehavior::attributes.getArray()[i])/(float)(alpha*2*HarmfulBehavior::attributes.lenght() + HarmfulBehavior::attributes.lenght());
            }
        }
        return probability;
    }
    // подсчет "вероятности" того, что поведение не вредоносное (параметр функции: массив признаков)
    float probabilityOfUnharmfull(Array &inputAtt) {
        float probability = UnharmfullBehavior::k/(HarmfulBehavior::k + UnharmfullBehavior::k); // априорная вероятность
        
        for (int i = 0; i < inputAtt.lenght(); i++) {
            if (inputAtt.getArray()[i] != 0) { // если у массива признаков i-ый признак не нулевой
                probability += (float)(alpha + UnharmfullBehavior::attributes.getArray()[i])/(float)(alpha*2*UnharmfullBehavior::attributes.lenght() + UnharmfullBehavior::attributes.lenght());
            }
        }
        return probability;
    }
public:
    // если метод вернет true - поведение не вредоносное
    // если метод вернет false - поведение вредоносное
    bool prediction(Array &inputAttributes) {
        float harm = probabilityOfHarmful(inputAttributes);
        float unharm = probabilityOfUnharmfull(inputAttributes);
        if (harm <= unharm) {
            return true;
        } else {
            return false;
        }
    }
};
#endif
