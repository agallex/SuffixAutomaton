//
// Created by Александр Агафонов on 31.03.2022.
//

#include "suffix_automaton.h"

void SuffixAutomaton::Init(size_t sz) {
    state_.resize(2 * sz);
    size_ = 0;
    last_ = 0;
    state_[0].len = 0;
    state_[0].link = -1;
    state_[0].first_pos = -1;
    ++size_;

}

SuffixAutomaton::SuffixAutomaton(std::ifstream& fin) {
    std::string str;
    std::string line;
    while (getline(fin, line)) {
        str.append(line + '\n');
    }
    Init(str.size());
    for (auto elem_str: str) {
        AddSymbol(elem_str);
    }
}

SuffixAutomaton::SuffixAutomaton(const std::string& str) {
    Init(str.size());
    for (auto elem_str: str) {
        AddSymbol(elem_str);
    }
}

void SuffixAutomaton::AddSymbol(const char symbol) {
    int64_t current = size_++;
    state_[current].len = state_[last_].len + 1;
    state_[current].first_pos = state_[current].len - 1;
    int64_t i;
    for (i = last_; i != -1 && !state_[i].next.count(symbol); i = state_[i].link) {
        state_[i].next[symbol] = current;
    }
    if (i == -1) {
        state_[current].link = 0;
    }
    else {
        int64_t j = state_[i].next[symbol];
        if (state_[i].len + 1 == state_[j].len)
            state_[current].link = j;
        else {
            int64_t clone = size_++;
            state_[clone].len = state_[i].len + 1;
            state_[clone].next = state_[j].next;
            state_[clone].link = state_[j].link;
            state_[clone].first_pos = state_[j].first_pos;
            for (; i != -1 && state_[i].next[symbol] == j; i=state_[i].link) {
                state_[i].next[symbol] = clone;
            }
            state_[j].link = state_[current].link = clone;
        }
    }
    last_ = current;
}

int64_t SuffixAutomaton::FirstOccurrence(const std::string& str) {
    Condition current = state_[0];
    int64_t first_pos = -1;
    for (auto symbol : str) {
        if (current.next.contains(symbol)) {
            current = state_[current.next[symbol]];
            first_pos = current.first_pos;
        }
        else {
            return -1;
        }
    }
    return first_pos - str.size() + 2;
}

bool SuffixAutomaton::IsIncluded(const std::string& str) {
    return FirstOccurrence(str) != -1;
}
