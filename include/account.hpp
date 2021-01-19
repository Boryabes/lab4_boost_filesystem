// Copyright 2020 Boryabes <box.bern@yandex.ru>

#include "boost/filesystem.hpp"
#include "iostream"
class account {
private:
    std::string brocker;
    std::string accountNumber;
    std::vector<boost::filesystem::path> files;
    size_t filesSum = 0;
    int lastDate;

public:
    void addFile(boost::filesystem::path); //добавить файл в массив файлов(передаем объекст класса пас)
    void incFilesSum();
    void setLastDate(int); //устанавливаю значение(передаю число он поле ластдайт делает равным этому числу
    void setBrocker(std::string);
    void setAccountNumber(std::string);
    std::string getBrocker(); //гетброкер получаю поле брокер
    std::string getAccountNum();
    std::size_t getFileSum();
    int getLastDate();
};