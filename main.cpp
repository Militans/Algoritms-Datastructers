#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <typeinfo>
#include <algorithm>




using namespace std;


void sort(int *arr, int size) {
    auto start = chrono::high_resolution_clock::now();
    int bound = size, t = 0;
    if (size == 1) {
        return;
    }

    do {
        t = 0;
        for (int j = 0; j < bound - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                t = j + 1;
            }

        }
        if (t == 0) {
            break;
        } else {
            bound = t;
        }
    } while (1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout << "Duration " << duration.count() * 1000000 << endl;

}

void shekerSort(int *mass, int count) {

    int left = 0, right = count - 1; // левая и правая границы сортируемой области массива
    int flag = 1;  // флаг наличия перемещений
    // Выполнение цикла пока левая граница не сомкнётся с правой
    // и пока в массиве имеются перемещения
    auto start = chrono::high_resolution_clock::now();
    while ((left < right) && flag > 0) {
        flag = 0;
        for (int i = left; i < right; i++)  //двигаемся слева направо
        {
            if (mass[i] > mass[i + 1]) // если следующий элемент меньше текущего,
            {             // меняем их местами
                double t = mass[i];
                mass[i] = mass[i + 1];
                mass[i + 1] = t;
                flag = 1;      // перемещения в этом цикле были
            }
        }
        right--; // сдвигаем правую границу на предыдущий элемент
        for (int i = right; i > left; i--)  //двигаемся справа налево
        {
            if (mass[i - 1] > mass[i]) // если предыдущий элемент больше текущего,
            {            // меняем их местами
                double t = mass[i];
                mass[i] = mass[i - 1];
                mass[i - 1] = t;
                flag = 1;    // перемещения в этом цикле были
            }
        }
        left++; // сдвигаем левую границу на следующий элемент
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout << "Duration " << duration.count() * 1000000 << endl;
}

int comp(const int *i, const int *j) {
    return *i - *j;
}

bool Check(int *arr, int size) {
    int flag = 0;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            flag = 1;
            break;
        }
    }
    return flag == 0;
}


int main(int argc, char *argv[]) {


    if (argc == 1) {
        cout << "Using: \n";
        cout << "Parameters must be 3\n";
        cout << "First - name of the program\nSecond - name of the file which be read\n"
                "Third - name of the function which you want use" << endl;
        cout << endl;
        cout << "List of the txt files: \n"
                "[d16.txt, d100.txt, d500.txt, d1000.txt, d5000.txt]\n"
                "the number in the name of the file gets us the count of the numbers which will be sorted\n" << endl;
        cout << "List of the functions: \n"
                "qsort - default std function of sort\n"
                "sort - it has written at the lab (the main func)\n"
                "shekerSort - another func of sort\n";

        system("pause");


        return 0;
    }

    if (argc != 3) {
        cout << "Wrong count of arguments; the count must be 3; try again";
        return 0;

    }


    string line;

    string lists[] = {"d16.txt", "d100.txt", "d500.txt", "d1000.txt", "d5000.txt"};

    int arr[5000];

    bool exists = find(begin(lists), end(lists), argv[1]) != end(lists);
    if (!exists) {
        cout << "wrong file check the check the description" << endl;
        system("pause");
        return 0;
    }

    ifstream file(argv[1]);
    int indx = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            arr[indx] = stoi(line);
            indx += 1;
        }
    }
    file.close();
    cout << "From the file " << string(argv[1]) << " were getting " << indx << " elements" << endl;

    //display the array
    if (indx == 16){
        cout << "An array was received:" << endl;
        for (int i = 0; i < indx; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }


    cout << "============================================\n";

    if (string(argv[2]) == "qsort") {
        auto start = chrono::high_resolution_clock::now();
        qsort(arr, indx, sizeof(arr[2]), (int (*)(const void *, const void *)) comp);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        cout << "Duration " << duration.count() * 1000000 << endl;
    } else if (string(argv[2]) == "sort") {
        sort(arr, indx);
    } else if (string(argv[2]) == "shekerSort") {
        shekerSort(arr, indx);
    } else {
        cout << "wrong function check the description" << endl;
        system("pause");
        return 0;
    }

    string name = "d" + to_string(indx) + "-s.txt";
    ofstream out(name);
    if (out.is_open()) {
        for (int i = 0; i < indx; i++) {
            out << arr[i] << endl;
        }
    }
    out.close();








    //checking arr
    if (Check(arr, indx)) {
        cout << "All good\n";
    } else {
        cout << "Wrong" << endl;
    }


//    displaying the sorted array
    if(indx == 16)
    {
        cout << "sorted array is: " << endl;
        for (int i = 0; i < indx; i++) {
            cout << arr[i] << " ";

        }
        cout << endl;
    }



    cout << "New array is in " << name << endl;


    return 0;
}
