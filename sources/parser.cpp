// Copyright 2020 Boryabes <box.bern@yandex.ru>

#include "parser.hpp"

#include "boost/filesystem.hpp"
#include "iomanip"
#include "iostream"
#include "regex"
parserOfDir::parserOfDir(std::string pathForParse) { //передаем путь к папке которую будем парсить
    const std::regex regularExp(                    //создаем констант объект класса реджекс(реджекс отвечает за регулярные выражения)
            "^(balance_)\\d\\d\\d\\d\\d\\d\\d\\d_\\d\\d\\d\\d\\d\\d\\d\\d"); //с помощью спец символов описываю шаблон строки и сравниваю все строки с шаблоном
                                                                            //^ - ознначает с чего должно начинаться(с баланс_ ) 8 d - 8 цифрд
                                                                            // два слэша первый экранирует второй
    const boost::filesystem::path pathObj{pathForParse};           //создаю объекст класса пассОбжект, с конструкторе класса пасс передаем путь к директории, Класс пасс позволяет смотреть родительскую директорию, расширения файла,полный путь к нему и тд
    if (boost::filesystem::exists(pathObj)) {                      //с помощью метода экзист проверяем существование директории
        for (auto itEntry =                                          //рекурсивно проходим по всем папкам в директории(взял из документации)
                boost::filesystem::recursive_directory_iterator(pathObj);
             itEntry != boost::filesystem::recursive_directory_iterator(); //выполняем пока не закончатся папки в директории
             ++itEntry) {
            if (boost::filesystem::is_regular_file(itEntry->path())) { //проверяет не директория ли это(в аргумент передают путь к файлу(-> обращаемся по указателя к методу объекта итЭнтри) //если обычный файл идем дальше
                if ((itEntry->path().stem().extension() == "")) { //проверяем что расширение одно (не тхт.докикс) последнее расширение откидываем
                    if (itEntry->path().extension() == ".txt") { //проверяем что расширение тээкстэ
                        if (std::regex_search(itEntry->path().stem().string(), //сравниваю с регулярным выражением, если подходит шаблону то  файл добавляем в массив файлс
                                              regularExp)) {
                            files.push_back(itEntry->path());
                            accountsStrings.insert(                         //добавляю в множество новый объекст методом инсерт (в скобках указываю номер аккаунта)
                                    itEntry->path().stem().string().substr(8, 8)); //беру путь к файлу,отрезаю расширение, остается баланс_8цифр_8цифр, преобразую к строке, сабстр выделяет подстроку в строке(вырезаем номер счета)
                        }                                                          //вырезаем с 9 элемента, второй аргумент это сколько вырезаем (вырезаем 8 цифр)
                    }
                }
            }   //здесь мы имеем массив со всеми файлами с фининфой и множество с номерами лицевых счетов

            if (boost::filesystem::is_symlink(itEntry->path())) {    //тоже самое что и выше только для ссылок
                for (auto itEntrySymLink =
                        boost::filesystem::recursive_directory_iterator(
                                itEntry->path());
                     itEntrySymLink !=
                     boost::filesystem::recursive_directory_iterator();
                     ++itEntrySymLink) {
                    if (boost::filesystem::is_regular_file(itEntry->path())) {
                        if ((itEntry->path().stem().extension() == "")) {
                            if (itEntry->path().extension() == ".txt") {
                                if (std::regex_search(itEntry->path().stem().string(),
                                                      regularExp)) {
                                    files.push_back(itEntry->path());
                                    accountsStrings.insert(
                                            itEntry->path().stem().string().substr(8, 8));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



std::string parserOfDir::printFormatted() {
    std::stringstream ss;
    for (auto file : files) {
        ss << file.parent_path().filename().string() << " "
           << file.filename().string() << std::endl;
    }
    for (auto acc : accounts){
        ss<<"broker:"<<acc.getBrocker()<<" "<<"account:"<<
          acc.getAccountNum()<<" "<<"files:"<<acc.getFileSum()<<
          " "<<"lastdate:"<<acc.getLastDate()<<std::endl;
    }
    return ss.str();
}


void parserOfDir::assembleFilesForAcc() {
    for (auto acc : accountsStrings) { //иду по каждому номеру лицевого счета в множестве
        account tempAcc;           //временная переменная типа аккаунт
        tempAcc.setAccountNumber(acc); //устанавливаю номер счета в аккаунте, обходим приватность таким образом, т.к. все поля класса аккаунт приватны
        int lastDate = 0;
        for (auto file : files) { //иду по каждому файлу, вырезаем лицевой номер, если он совпадает с номером лицевого счета в множестве то инкрементирую счетчик количества файлов принадлежащих аккаунт
            if (file.filename().string().substr(8, 8) == acc) {

                tempAcc.incFilesSum();
                tempAcc.addFile(file); //добавляю файл в массив файлов принадлежащих акаунту
                tempAcc.setBrocker(file.parent_path().filename().string()); //названием брокера явл родителськая директория файла( устанавливаю поле брокер)
                if (std::stoi(file.filename().stem().string().substr(17, 8)) > lastDate) { //считываю последнюю дату (СТОИ преобразует строку в число)
                    lastDate = std::stoi(file.filename().stem().string().substr(17, 8));  //записываем в ластдейт большее число полученное при сравнении
                }
            }
        }
        tempAcc.setLastDate(lastDate); //прошел по всем файлам и устанавливаю ластдейт
        accounts.push_back(tempAcc);   //добавляю аккаунт в массив аккаунтов

    }

}