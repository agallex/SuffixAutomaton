//
// Created by Александр Агафонов on 31.03.2022.
//

#ifndef INC_1C_SUFFIX_AUTOMATON_H
#define INC_1C_SUFFIX_AUTOMATON_H


#include <vector>
#include <map>
#include <fstream>

// Создадим структуру суффиксного дерева, для быстрого нахождения строки в подстроке
class SuffixAutomaton {
    // Создадим структуру, которая будет хранить всю информацию о конкретном переходе
    struct Condition {
        int64_t len;
        int64_t link;
        std::map<char, int> next;
        int64_t first_pos;
    };
    // Теперь создадим массив структур

    std::vector<Condition> state_;

    // size_ - размер, last_ — состояние, соответствующее всей строке на данный момент.
    int64_t size_;
    int64_t last_;
    void Init(size_t sz);
    void AddSymbol(char symbol);
public:
    explicit SuffixAutomaton(std::ifstream& fin);
    explicit SuffixAutomaton(const std::string& str);
    int64_t FirstOccurrence(const std::string& str);
    bool IsIncluded(const std::string& str);
    ~SuffixAutomaton() = default;
};


#endif //INC_1C_SUFFIX_AUTOMATON_H
