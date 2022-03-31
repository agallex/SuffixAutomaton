#include <iostream>
#include "suffix_automaton.h"

int main() {
    // Тест с конструктором от строки
    {
        std::string str = "abcd efghi jkmnlpo jdslkajdlka";
        SuffixAutomaton text(str);
        assert(text.FirstOccurrence("fgh") == 7); // начинается с 7-го символа
        assert(text.FirstOccurrence("ab") == 1); // начинается с 1-го символа
        assert(text.FirstOccurrence(" ") == 5); // начинается с 5-го символа
        assert(text.FirstOccurrence("  ") == -1); // такой подстроки нет
        assert(text.FirstOccurrence("skldfj") == -1); // такой подстроки нет
        assert(text.FirstOccurrence("ddfdf") == -1); // такой подстроки нет
        assert(text.FirstOccurrence(" jk") == 11); // начинается с 11-го символа
        assert(text.IsIncluded("kajd")); // такая подстрока есть
        assert(!text.IsIncluded("kslfjdfsd")); // такой подстроки нет
    }
    // Тест с конструктором от файла
    {
        std::ifstream fin;
        fin.open("/Users/aleksandragafonov/CLionProjects/1c/big_file.txt"); // здесь нужно вставить путь до файла
        if(!fin.is_open()) { // проверка открыт ли файл
            std::cout << "File not open!\n";
            exit(1);
        }
        SuffixAutomaton text(fin);
        assert(text.FirstOccurrence("Katherine") == 1); // начинается с 1-го символа
        assert(text.FirstOccurrence("age") == 244); // начинается с 244-го символа
        assert(text.FirstOccurrence("led") == 458); // начинается с 458-го символа в слове сalled
        assert(text.FirstOccurrence("  ") == -1); // такой подстроки нет
        assert(text.FirstOccurrence("skldfj") == -1); // такой подстроки нет
        assert(text.FirstOccurrence("ddfdf") == -1); // такой подстроки нет
        assert(text.IsIncluded("Rosemary")); // такая подстрока есть
        assert(text.IsIncluded("only")); // такая подстрока есть
        assert(text.IsIncluded("girl")); // такая подстрока есть
        assert(!text.IsIncluded("girls")); // такая подстроки нет
        assert(text.IsIncluded("rightene")); // такая подстрока есть в слове frightened
        assert(!text.IsIncluded("kajd")); // такой подстроки нет
    }
    return 0;
}
