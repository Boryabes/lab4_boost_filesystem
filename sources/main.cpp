// Copyright 2020 Boryabes <box.bern@yandex.ru>


#include "iostream"
#include "parser.hpp"
int main(int argc, char *argv[]) {
    std::string path;

    if (argc == 1) {
        path = ".";

    } else {
        path = argv[1];
    }

    parserOfDir parser(path);
    parser.assembleFilesForAcc();
    std::cout<<parser.printFormatted();
}
