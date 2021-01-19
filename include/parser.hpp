// Copyright 2020 Boryabes <box.bern@yandex.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include "boost/filesystem.hpp"
#include "string"
#include "map"
#include "account.hpp"
#include "set"

class parserOfDir{
private:
    std::vector<boost::filesystem::path> files; //массив для всех файлов с инфой
    std::set<std::string> accountsStrings; //множества номер аккаунтов (множество имеет только уникальные элементы(повторы удаляются))
    std::vector<account> accounts; //массив объектов клааса акаунт  (broker:ib account:00001234 files:10 lastdate:20181017) вот ета)
public:
    explicit parserOfDir(std::string pathForParse); //заполняет приватные поля( описанные выше), ищет файлы с фининфой и собирает инфу
    void assembleFilesForAcc(); //формирует объект класса аккаунт и добавляет его в массив аккаунтс
    std::string printFormatted(); //вывод данных

};
#endif // INCLUDE_HEADER_HPP_