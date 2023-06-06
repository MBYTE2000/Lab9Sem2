#include <iostream>
#include <fstream>
#include <cstring>

const int MAX_TRAINS = 100;

struct Train {
    char date[20];
    char destination[50];
    char departureTime[10];
    int availableSeats;
};

// Функция для создания нового файла данных
void createFile() {
    std::ofstream file("trains.txt");
    file.close();
}

// Функция для добавления новой записи в файл данных
void addTrain(const Train& train) {
    std::ofstream file("trains.txt", std::ios::app);
    file.write(reinterpret_cast<const char*>(&train), sizeof(Train));
    file.close();
}

// Функция для просмотра содержимого файла данных
void viewTrains() {
    std::ifstream file("trains.txt");
    Train train;
    while (file.read(reinterpret_cast<char*>(&train), sizeof(Train))) {
        std::cout << "Date: " << train.date << std::endl;
        std::cout << "Destination: " << train.destination << std::endl;
        std::cout << "Departure Time: " << train.departureTime << std::endl;
        std::cout << "Available Seats: " << train.availableSeats << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
    file.close();
}

// Функция для выполнения линейного поиска в файле данных
void linearSearch(const char* destination) {
    std::ifstream file("trains.txt");
    Train train;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&train), sizeof(Train))) {
        if (strcmp(train.destination, destination) == 0) {
            std::cout << "Train found!" << std::endl;
            std::cout << "Date: " << train.date << std::endl;
            std::cout << "Destination: " << train.destination << std::endl;
            std::cout << "Departure Time: " << train.departureTime << std::endl;
            std::cout << "Available Seats: " << train.availableSeats << std::endl;
            std::cout << "--------------------------" << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Train not found!" << std::endl;
    }
    file.close();
}

// Функция для сортировки массива методом прямого выбора
void selectionSort() {
    std::ifstream file("trains.txt");
    Train trains[MAX_TRAINS];
    int numTrains = 0;

    while (file.read(reinterpret_cast<char*>(&trains[numTrains]), sizeof(Train))) {
        numTrains++;
    }
    file.close();

    for (int i = 0; i < numTrains - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < numTrains; j++) {
            if (trains[j].availableSeats < trains[minIndex].availableSeats) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(trains[i], trains[minIndex]);
        }
    }

    std::ofstream outputFile("sorted_trains.txt");
    for (int i = 0; i < numTrains; i++) {
        outputFile.write(reinterpret_cast<const char*>(&trains[i]), sizeof(Train));
    }
    outputFile.close();
    std::cout << "Array sorted and saved to 'sorted_trains.txt'" << std::endl;
}

// Функция для разделения массива при выполнении QuickSort
int partition(Train trains[], int low, int high) {
    Train pivot = trains[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (trains[j].availableSeats < pivot.availableSeats) {
            i++;
            std::swap(trains[i], trains[j]);
        }
    }
    std::swap(trains[i + 1], trains[high]);
    return i + 1;
}

// Функция для выполнения QuickSort
void quickSort(Train trains[], int low, int high) {
    if (low < high) {
        int pivot = partition(trains, low, high);
        quickSort(trains, low, pivot - 1);
        quickSort(trains, pivot + 1, high);
    }
}

// Функция для сортировки массива методом QuickSort
void quickSortWrapper() {
    std::ifstream file("trains.txt");
    Train trains[MAX_TRAINS];
    int numTrains = 0;

    while (file.read(reinterpret_cast<char*>(&trains[numTrains]), sizeof(Train))) {
        numTrains++;
    }
    file.close();

    quickSort(trains, 0, numTrains - 1);

    std::ofstream outputFile("sorted_trains.txt");
    for (int i = 0; i < numTrains; i++) {
        outputFile.write(reinterpret_cast<const char*>(&trains[i]), sizeof(Train));
    }
    outputFile.close();
    std::cout << "Array sorted and saved to 'sorted_trains.txt'" << std::endl;
}

// Функция для выполнения двоичного поиска в отсортированном массиве
void binarySearch(const char* destination, int requiredSeats) {
    std::ifstream file("sorted_trains.txt");
    Train train;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&train), sizeof(Train))) {
        if (strcmp(train.destination, destination) == 0 && train.availableSeats >= requiredSeats) {
            std::cout << "Train found!" << std::endl;
            std::cout << "Date: " << train.date << std::endl;
            std::cout << "Destination: " << train.destination << std::endl;
            std::cout << "Departure Time: " << train.departureTime << std::endl;
            std::cout << "Available Seats: " << train.availableSeats << std::endl;
            std::cout << "--------------------------" << std::endl;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Train not found or required seats not available!" << std::endl;
    }
    file.close();
}

int main() {
    createFile();

    Train train1;
    strcpy_s(train1.date, "2023-06-06");
    strcpy_s(train1.destination, "City A");
    strcpy_s(train1.departureTime, "10:00");
    train1.availableSeats = 50;

    Train train2;
    strcpy_s(train2.date, "2023-06-07");
    strcpy_s(train2.destination, "City B");
    strcpy_s(train2.departureTime, "12:30");
    train2.availableSeats = 30;

    Train train3;
    strcpy_s(train3.date, "2023-06-08");
    strcpy_s(train3.destination, "City A");
    strcpy_s(train3.departureTime, "09:00");
    train3.availableSeats = 20;

    addTrain(train1);
    addTrain(train2);
    addTrain(train3);

    std::cout << "Viewing all trains:" << std::endl;
    viewTrains();

    std::cout << "Performing linear search for destination 'City B':" << std::endl;
    linearSearch("City B");

    std::cout << "Performing selection sort:" << std::endl;
    selectionSort();

    std::cout << "Performing binary search for destination 'City A' and 10 required seats:" << std::endl;
    binarySearch("City A", 10);

    return 0;
}
