#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Train {
    string date;
    string destination;
    string departureTime;
    int availableSeats;
};

// Функция для создания нового файла данных
void createFile() {
    ofstream file("trains.dat", ios::binary);
    if (!file) {
        cout << "Ошибка при создании файла." << endl;
        return;
    }

    Train trains[5];

    trains[0] = { "2023-06-01", "Город 1", "09:00", 50 };
    trains[1] = { "2023-06-01", "Город 2", "12:30", 30 };
    trains[2] = { "2023-06-02", "Город 1", "10:15", 20 };
    trains[3] = { "2023-06-02", "Город 3", "14:45", 40 };
    trains[4] = { "2023-06-03", "Город 2", "11:30", 35 };

    file.write(reinterpret_cast<char*>(trains), sizeof(trains));

    file.close();

    cout << "Файл создан успешно." << endl;
}

void viewFile() {
    ifstream file("trains.dat", ios::binary);
    if (!file) {
        cout << "Ошибка при открытии файла." << endl;
        return;
    }

    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    int numRecords = fileSize / sizeof(Train);

    Train* trains = new Train[numRecords];

    file.seekg(0, ios::beg);
    file.read(reinterpret_cast<char*>(trains), fileSize);

    for (int i = 0; i < numRecords; i++) {
        cout << "Дата: " << trains[i].date << endl;
        cout << "Пункт назначения: " << trains[i].destination << endl;
        cout << "Время отправления: " << trains[i].departureTime << endl;
        cout << "Свободные места: " << trains[i].availableSeats << endl;
        cout << "---------------------" << endl;
    }

    //delete[] trains;

    file.close();
}



// Функция для добавления записи в файл данных
void addRecord() {
    ofstream file("trains.dat", ios::binary | ios::app);
    if (!file) {
        cout << "Ошибка при открытии файла." << endl;
        return;
    }

    Train train;

    cout << "Введите дату: ";
    cin >> train.date;

    cout << "Введите пункт назначения: ";
    cin >> train.destination;

    cout << "Введите время отправления: ";
    cin >> train.departureTime;

    cout << "Введите количество свободных мест: ";
    cin >> train.availableSeats;

    file.write(reinterpret_cast<char*>(&train), sizeof(train));

    file.close();

    cout << "Запись добавлена успешно." << endl;
}

// Функция для линейного поиска в файле данных
void linearSearch() {
    ifstream file("trains.dat", ios::binary);
    if (!file) {
        cout << "Ошибка при открытии файла." << endl;
        return;
    }

    int key;
    cout << "Введите количество свободных мест для поиска: ";
    cin >> key;

    Train train;

    bool found = false;

    while (file.read(reinterpret_cast<char*>(&train), sizeof(train))) {
        if (train.availableSeats == key) {
            cout << "Найден поезд:" << endl;
            cout << "Дата: " << train.date << endl;
            cout << "Пункт назначения: " << train.destination << endl;
            cout << "Время отправления: " << train.departureTime << endl;
            cout << "Свободные места: " << train.availableSeats << endl;
            cout << "---------------------" << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "Поезд с указанным количеством свободных мест не найден." << endl;
    }

    file.close();
}

// Функция для сортировки массива (файла) методом прямого выбора
void selectionSort() {
    ifstream file("trains.dat", ios::binary | ios::ate);
    if (!file) {
        cout << "Ошибка при открытии файла." << endl;
        return;
    }

    streampos fileSize = file.tellg();
    int numRecords = fileSize / sizeof(Train);

    Train* trains = new Train[numRecords];

    file.seekg(0, ios::beg);
    file.read(reinterpret_cast<char*>(trains), fileSize);

    for (int i = 0; i < numRecords - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < numRecords; j++) {
            if (trains[j].availableSeats < trains[minIndex].availableSeats) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Train temp = trains[i];
            trains[i] = trains[minIndex];
            trains[minIndex] = temp;
        }
    }

    file.close();

    ofstream outFile("sorted_trains.dat", ios::binary);
    outFile.write(reinterpret_cast<char*>(trains), fileSize);
    outFile.close();

   // delete[] trains;

    cout << "Файл успешно отсортирован методом прямого выбора." << endl;
}

// Функция для сортировки массива (файла) методом QuickSort
void quickSort(Train* trains, int left, int right) {
    int i = left;
    int j = right;
    int pivot = trains[(left + right) / 2].availableSeats;

    while (i <= j) {
        while (trains[i].availableSeats < pivot) {
            i++;
        }

        while (trains[j].availableSeats > pivot) {
            j--;
        }

        if (i <= j) {
            Train temp = trains[i];
            trains[i] = trains[j];
            trains[j] = temp;

            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(trains, left, j);
    }

    if (i < right) {
        quickSort(trains, i, right);
    }
}

void quickSortWrapper() {
    ifstream file("trains.dat", ios::binary | ios::ate);
    if (!file) {
        cout << "Ошибка при открытии файла." << endl;
        return;
    }

    streampos fileSize = file.tellg();
    int numRecords = fileSize / sizeof(Train);

    Train* trains = new Train[numRecords];

    file.seekg(0, ios::beg);
    file.read(reinterpret_cast<char*>(trains), fileSize);

    quickSort(trains, 0, numRecords - 1);

    file.close();

    ofstream outFile("sorted_trains.dat", ios::binary);
    outFile.write(reinterpret_cast<char*>(trains), fileSize);
    outFile.close();

    delete[] trains;

    cout << "Файл успешно отсортирован методом QuickSort." << endl;
}

// Функция для двоичного поиска в отсортированном массиве
void binarySearch() {
    ifstream file("sorted_trains.dat", ios::binary);
    if (!file) {
        cout << "Ошибка при открытии файла." << endl;
        return;
    }

    int key;
    cout << "Введите количество свободных мест для поиска: ";
    cin >> key;

    Train train;

    int left = 0;
    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    int right = fileSize / sizeof(Train) - 1;
    int foundIndex = -1;

    while (left <= right) {
        int mid = (left + right) / 2;
        file.seekg(mid * sizeof(Train), ios::beg);
        file.read(reinterpret_cast<char*>(&train), sizeof(train));

        if (train.availableSeats == key) {
            foundIndex = mid;
            break;
        }
        else if (train.availableSeats < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (foundIndex != -1) {
        file.seekg(foundIndex * sizeof(Train), ios::beg);
        file.read(reinterpret_cast<char*>(&train), sizeof(train));

        cout << "Найден поезд:" << endl;
        cout << "Дата: " << train.date << endl;
        cout << "Пункт назначения: " << train.destination << endl;
        cout << "Время отправления: " << train.departureTime << endl;
        cout << "Свободные места: " << train.availableSeats << endl;
    }
    else {
        cout << "Поезд с указанным количеством свободных мест не найден." << endl;
    }

    file.close();
}

// Функция для бронирования мест в поездах
void bookSeats() {
    ifstream file("trains.dat", ios::binary | ios::ate);
    if (!file) {
        cout << "Ошибка при открытии файла." << endl;
        return;
    }

    streampos fileSize = file.tellg();
    int numRecords = fileSize / sizeof(Train);

    Train* trains = new Train[numRecords];

    file.seekg(0, ios::beg);
    file.read(reinterpret_cast<char*>(trains), fileSize);

    string destination;
    cout << "Введите пункт назначения: ";
    cin >> destination;

    string date;
    cout << "Введите дату: ";
    cin >> date;

    int dayOfWeek;
    cout << "Введите номер дня недели (1-7): ";
    cin >> dayOfWeek;

    int maxHours;
    cout << "Введите максимальное время отправления (в часах): ";
    cin >> maxHours;

    bool found = false;

    for (int i = 0; i < numRecords; i++) {
        if (trains[i].destination == destination &&
            trains[i].date == date &&
            trains[i].departureTime <= to_string(maxHours) + ":00" &&
            dayOfWeek == 3) {
            cout << "Время отправления: " << trains[i].departureTime << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Невозможно выполнить заказ." << endl;
    }

    file.close();
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(static_cast<unsigned int>(time(nullptr)));

    int choice;

    cout << "Выберите способ заполнения файла данных:" << endl;
    cout << "1. Ручной ввод" << endl;
    cout << "2. Случайное заполнение" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    if (choice == 1) {
        createFile();
    }
    else if (choice == 2) {
        ofstream file("trains.dat", ios::binary);
        if (!file) {
            cout << "Ошибка при создании файла." << endl;
            return 0;
        }

        int numRecords;
        cout << "Введите количество записей: ";
        cin >> numRecords;

        Train* trains = new Train[numRecords];

        for (int i = 0; i < numRecords; i++) {
            trains[i].date = "2023-06-" + to_string(rand() % 7 + 1);
            trains[i].destination = "Город " + to_string(rand() % 5 + 1);
            trains[i].departureTime = to_string(rand() % 24) + ":" + to_string(rand() % 60);
            trains[i].availableSeats = rand() % 100 + 1;
        }

        file.write(reinterpret_cast<char*>(trains), numRecords * sizeof(Train));

        file.close();

        delete[] trains;

        cout << "Файл создан успешно." << endl;
    }
    else {
        cout << "Некорректный выбор." << endl;
        return 0;
    }

    while (true) {
        cout << "---------------------" << endl;
        cout << "Меню:" << endl;
        cout << "1. Просмотреть файл данных" << endl;
        cout << "2. Добавить запись" << endl;
        cout << "3. Выполнить линейный поиск" << endl;
        cout << "4. Отсортировать файл методом прямого выбора" << endl;
        cout << "5. Отсортировать файл методом QuickSort" << endl;
        cout << "6. Выполнить двоичный поиск" << endl;
        cout << "7. Забронировать места в поездах" << endl;
        cout << "8. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewFile();
            break;
        case 2:
            addRecord();
            break;
        case 3:
            linearSearch();
            break;
        case 4:
            selectionSort();
            break;
        case 5:
            quickSortWrapper();
            break;
        case 6:
            binarySearch();
            break;
        case 7:
            bookSeats();
            break;
        case 8:
            return 0;
        default:
            cout << "Некорректный выбор." << endl;
        }
    }

    return 0;
}
