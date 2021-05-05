#ifndef Array_
#define Array_

class Array {
    int* p; /* Указатель на первый элемент */
    int n; /* Количество элементов*/
public:
    Array() {
        n = 0;
    }
    ~Array() {
        if (n != 0) {
            free(p);
        }
    }
    void push_back(int val) {
        int* tmp = new int[n+1];
        for (int i = 0; i<n; i++) {
            tmp[i] = p[i];
        }
        tmp[n] = val;
        if (n != 0) {
            free(p);
        }
        n += 1;
        p = tmp;
    }
    int pop() {
        return p[n-1];
    }
    int pop(int i) {
        return p[i];
    }
    int lenght() {
        return n;
    }
    int* getArray() {
        return p;
    }
};

#endif
