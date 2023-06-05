#include <iostream>
#include <clocale>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <list>
#include <cmath>


using namespace std;

struct Film {

    string name;
    string rejiser;
    string strana;

    int year;
    int stoimost;
    int sbori;
};



int menu() {

    cout << "\n Выберите действие: \n";
    cout << "1. Добавить новый фильм; \n";
    cout << "2. Удалить первый в списке фильм; \n";
    cout << "3. Просмотреть все фильмы; \n";
    cout << "4. Редактирование данных выбранного фильма; \n";
    cout << "5. Выход. \n";

    int a; //ввести в a
    cin >> a;
    return a; // для работы меню все эти 3 строки(типа чел ввёл какую-то цифру)

}

const int MAX_SIZE = 5;

class CircularQueue { // Класс для организации циклической очереди
private:
    int front, rear; // указатели на первый и последний элементы
    Film queue[MAX_SIZE];

public:
    CircularQueue() { // Конструктор пустой очереди
        front = -1;
        rear = -1;
    }

    bool isEmpty() { // проверка что очередь пуста
        return (front == -1 && rear == -1);
    }

    bool isFull() { // проверка что очередь полна
        return ((rear + 1) % MAX_SIZE == front);
    }




    bool enqueue(Film data) { // Добавление нового элемента
        if (isFull()) {
            cout << "Очередь полна!" << endl;
            return false;
        }

        if (isEmpty()) { // Если очередь пуста, то ставим указатель начала и конца на первый элемент
            front = 0;
            rear = 0;
        }
        else {
            rear = (rear + 1) % MAX_SIZE; // Сдвиагепм конец очереди на один вправо
        }

        queue[rear] = data;
        return true;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Очередь пуста, удалять нечего!" << endl;
            return;
        }
        if (front == rear) { // если начало и конец равны, то у нас один элемент
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % MAX_SIZE; // Сдвигаем начало очереди на один вправо
        }
    }

    bool change(string name, int par, string val) {
        for (int i = 0; i <= rear; i++) {
            if (queue[i].name == name) {
                switch (par) {
                case 1:
                    queue[i].name = val;
                    break;
                case 2:
                    queue[i].rejiser = val;
                    break;
                case 3:
                    queue[i].strana = val;
                    break;
                case 4:
                    queue[i].year = stoi(val);
                    break;
                case 5:
                    queue[i].stoimost = stoi(val);
                    break;
                case 6:
                    queue[i].sbori = stoi(val);
                    break;
                }
                return true;
            }

        }
        cout << endl << "Нет такого фильма" << endl;
        return false;
    }




    void display() {
        if (isEmpty()) {
            cout << "Очередь пуста!" << endl;
            return;
        }

        cout << "Элементы очереди: ";
        int i = front;
        int j = 1;
        while (i != rear) {
            cout << "Номер фильма: " << to_string(j++) << endl;
            cout << "Название фильма: " << queue[i].name << endl;
            cout << "Режисcер: " << queue[i].rejiser << endl;
            cout << "Страна: " << queue[i].strana << endl;
            cout << "Год: " << queue[i].year << endl;
            cout << "Стоимость производства: " << queue[i].stoimost << endl;
            cout << "Кассовые сборы: " << queue[i].sbori << endl << endl;
            i = (i + 1) % MAX_SIZE;
        }
        cout << "Номер фильма: " << to_string(j++) << endl;
        cout << "Название фильма: " << queue[rear].name << endl;
        cout << "Режисcер: " << queue[rear].rejiser << endl;
        cout << "Страна: " << queue[rear].strana << endl;
        cout << "Год: " << queue[rear].year << endl;
        cout << "Стоимость производства: " << queue[rear].stoimost << endl;
        cout << "Кассовые сборы: " << queue[rear].sbori << endl << endl;
    }
};

int main() {
    system("chcp 1251"); // настраиваем кодировку консоли

    CircularQueue queue;
    Film f1 = { "Мстители","Джо Руссо","США",2012,220000000,1518812988 };
    queue.enqueue(f1);
    Film f2 = { "Бойцовский клуб","Дэвид Финчер","США",1999,63000000,100853753 };
    queue.enqueue(f2);
    Film f3 = { "Муха","Дэвид Кроненберг","США",1986,15000000,60629159 };
    queue.enqueue(f3);

    int a = menu(); //вывели меню
    while (a != 5) {

        if (a == 1) {
            Film NewFilm;
            cout << "\n Выбран режим добавления нового фильма" << endl;
            cout << "Введите название фильма: ";
            cin.ignore();
            getline(cin, NewFilm.name);
            cout << "Введите Режиссера фильма: ";
            getline(cin, NewFilm.rejiser);
            cout << "Введите Страну производства: ";
            getline(cin, NewFilm.strana);
            cout << "Введите год производства: ";
            cin >> NewFilm.year;
            cout << "Введите стоимость производства: ";
            cin >> NewFilm.stoimost;
            cout << "Введите Кассовые сборы: ";
            cin >> NewFilm.sbori;
            if (queue.enqueue(NewFilm) == true) {
                cout << "Фильм успешно добавлен" << endl;
            }

        }
        if (a == 2) {
            queue.dequeue();
            cout << endl << "Фильм под номером 1 успешно удален из списка" << endl;
        }

        if (a == 3) {
            queue.display();
        }

        if (a == 4) {
            string fName, fVal;
            int x;
            cout << endl << "Введите название фильма, параметры которого вы хотите изменить: ";
            cin.ignore();
            getline(cin, fName);

            cout << "Какой элемент вы бы хотели редактировать." << endl << "1.Название" << endl << "2.Режиссер" << endl << "3.Страна" << endl << "4.Год" << endl << "5.Стоимость производства" << endl << "6.Кассовые сборы" << endl << "Введите число, параметр которого вы хотите изменить: ";
            cin >> x;

            cout << "Введите новые данные: ";
            cin.ignore();
            getline(cin, fVal);


            if (queue.change(fName, x, fVal) == true) {
                cout << endl << "Данные изменены";
            };

        }

        if (a == 5) {
            break;
        }


        a = menu();
    }
}