#include "listexercises.h"
#include "exercises.h"
#include "exerciseslink.h"
#include "mainwindow.h"
#include <string.h>
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <exception>
#include <cmath>

//конструктор инициализации
ListExercises::ListExercises(const int n) {
    if (n > 0) {
        objects = new Exercises *[n];
        for (int i = 0; i < n; i++) {
                objects[i] = NULL;
        }
        n_ = n;
        allocated = 0;
    }
    else
        throw std::out_of_range("n is not suitable");
};

int ListExercises::NumberOfExercises() const {
    return allocated;
};


 //Шаблон, сортировка массива (можно использовать для сортировки массива упражнений)
template <class T>
bool sorting(T* array, int size, std::function<bool(T, T)> compare) {
    bool is_sorted = true;
    for (int i = 0; i<size-1; i++)
        for (int j = i+1; j<size; j++)
            if (compare(array[i], array[j])) {
                is_sorted = false;
                T tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
    }
    return !is_sorted;
}

//Сортировка QVector
template <class T>
bool vector_sorting(QVector<T>& array, std::function<bool(T, T)> compare) {
    bool is_sorted = true;
    int size = array.size();
    for (int i = 0; i<size-1; i++)
        for (int j = i+1; j<size; j++)
            if (compare(array[i], array[j])) {
                is_sorted = false;
                array.swapItemsAt(i, j);
    }
    return !is_sorted;
}

//конструктор копирования
ListExercises::ListExercises(const ListExercises &list) {
    n_ = list.getLength();
    allocated = list.NumberOfExercises();
    objects = new Exercises *[n_];
    for (int i = 0; i < n_; i++) {
            if (list.GetExercise(i)) {
                Exercises *exercise = list.GetExercise(i);
                if (exercise->getType() == 0)
                    objects[i] = new Exercises(*exercise);
                else
                {
                    ExercisesLink *exer_1 = (ExercisesLink*)exercise;
                    objects[i] = new ExercisesLink(*exer_1);
                }
            }
            else objects[i] = NULL;

    }
};

//деструктор
ListExercises::~ListExercises() {
    if (objects) {
        for (int i = 0; i < n_; i++)
                if (objects[i]) {
                    delete objects[i];
                    objects[i]= NULL;
                }

        delete [] objects;
        objects = NULL;
        allocated = 0;
    }
};

void ListExercises::SetExercise(const int x, Exercises *exercise) {
    if ((x >= 0) && (x < n_)) {
        if (objects[x]) {
            delete objects[x];
            allocated--;
        }
        if (exercise) {
            if (exercise->getType() == 0)
                objects[x] = new Exercises(*exercise);
            else {
                ExercisesLink* exerlink = (ExercisesLink*)exercise;
                objects[x] = new ExercisesLink(*exerlink);
            }
            allocated++;
        }
        else
            objects[x] = NULL;
    }
    else
        throw std::out_of_range("Out of range");
};


Exercises *ListExercises::GetExercise(const int x) const {
    if ((x >= 0) && (x <= n_))
        return objects[x];
    else
        throw std::out_of_range("Out of range");
};

void ListExercises::deleteExercise(const int x) {
    if ((x >= 0) && (x < n_)) {
        if (objects[x]) {
            delete objects[x];
            allocated--;
        }
        objects[x] = NULL;
    }
    else
        throw std::out_of_range("Out of range");
}


int ListExercises::getLength() const {
    return n_;
};

void printList(const ListExercises &list) {
    int n = list.getLength();
    for (int i=0; i<n; i++) {
            std::cout << "Number of Exercise:" << i << std::endl;
            if (list.GetExercise(i))
                std::cout<<list.GetExercise(i); //используется перегрузка оператора вывода
            else
                std::cout << "No exercise!" << std::endl;
        }
        std::cout << std::endl;
};

bool ListExercises::isEqual(const ListExercises &list) const {
    if (list.getLength() == n_) {
        for (int i=0; i<n_; i++) {
                Exercises *exer1 = objects[i];
                Exercises *exer2 = list.GetExercise(i);
                if ((!exer1 || !exer2) && exer1 != exer2)
                    return false;
                if (exer1 && exer2) {
                    if (exer1->getType() != exer2->getType())
                        return false;

                    if (exer1->GetName() != exer2->GetName())
                        return false;
                    else
                        if (exer1->GetTime() != exer2->GetTime())
                            return false;
                    else
                            if (exer1->GetCalory() != exer2->GetCalory())
                                return false;

                    if (exer1->getType() == 1 && exer2->getType()==1) {
                        ExercisesLink *link1 = (ExercisesLink*) exer1;
                        ExercisesLink *link2 = (ExercisesLink*) exer2;
                        if (link1->GetLink() != link2->GetLink())
                            return false;
                    }
                }
            }
    }
    else
        return false;
    return true;
};

ListExercises ListFromJson(const QString &string) {
        QFile file(string);
        if (file.open(QFile::ReadOnly)) {
            QJsonDocument json_doc;
            json_doc = QJsonDocument::fromJson(file.readAll());
            QJsonObject body = json_doc.object();
            int n = body["n"].toInt();
            QJsonArray array = body["array"].toArray();
            ListExercises list(n);
            for (int i=0; i<n; i++) {
                    QJsonObject exercise_object = array[i].toObject();
                    QString type = exercise_object["Type"].toString();
                    if (type != "None") {
                        std::string name1 = exercise_object["Name"].toString().toStdString();
                        double time1 = exercise_object["Time"].toDouble();
                        double calory1 = exercise_object["Calories"].toDouble();
                        if (type == "Exercises with links") {
                            std::string link1 = exercise_object["Link"].toString().toStdString();
                            ExercisesLink exer_link(name1, time1, calory1, link1);
                            list.SetExercise(i, &exer_link);
                        }
                        else {
                            Exercises exer(name1, time1, calory1);
                            list.SetExercise(i, &exer);
                        }

                }
            }
            return list;
        }
        else
            throw QJsonParseError();
    }


//Записывает содержимое коллекции в файл формата json
bool ListToJson(const QString &string, const ListExercises &list) {
    QFile file(string);
       if (file.open(QFile::WriteOnly)) {
           int n = list.getLength();
           QJsonArray array;
           for (int i=0; i<n; i++) {
                   Exercises* obj = list.GetExercise(i);
                   QJsonObject exercise;
                   if (obj) {
                       exercise.insert("Name", QString::fromStdString(obj->GetName()));
                       exercise.insert("Time", obj->GetTime());
                       exercise.insert("Calories", obj->GetCalory());
                       if (obj->getType() == 1) {
                           exercise.insert("Type", "Exercises with links");
                           ExercisesLink* link = (ExercisesLink*)obj;
                           exercise.insert("Link", QString::fromStdString(link->GetLink()));
                       }
                       else
                           exercise.insert("Type", "Exercises");
                   }
                   else
                       exercise.insert("Type", "None");
                   array.append(exercise);
               }
           QJsonObject body;
           body["n"] = n;
           body["array"] = array;
           QJsonDocument json_doc;
           json_doc.setObject(body);
           if (file.write(json_doc.toJson()) == -1)
               return false;
           file.close();
           return true;
       }
       else
           return false;
};










