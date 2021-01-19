// Copyright 2020 Boryabes <box.bern@yandex.ru>


#include "iostream"
#include "parser.hpp"
int main(int argc, char *argv[]) { //интаргси количество аргументов, чараргви массив с аргументами
    std::string path; //создаю строку пас

    if (argc == 1) { //если количество аргументов 1(просто название скрипта) то устанавливаю путь в текущую директорию
        path = "."; //. где я нахожусь сейчас(текущая директория)

    } else {
        path = argv[1]; //если аргументов больше единицы, то путь это второй аргумент
    }

    parserOfDir parser(path); //парсю все директории, передаю в аргументы путь к папке которую буду парсить
    parser.assembleFilesForAcc(); //собираю файлы для аккаунтов
    std::cout<<parser.printFormatted(); //вывожу
}