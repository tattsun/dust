//
// Created by tattsun on 15/07/04.
//

#include "ByteChars.h"
#include <iostream>
#include <assert.h>
#include <string.h>
#include <iomanip>

namespace dust {

    ByteChars::ByteChars()
    : _str() {
    }

    ByteChars::ByteChars(const char *cs, size_t len)
    : _str(cs, len) {
    }

    ByteChars::ByteChars(char c)
    : _str() {
        char *cs = (char*)malloc(2);
        cs[0] = c;
        _str = std::string(cs, 1);
        free(cs);
    }

    ByteChars::ByteChars(const std::string &str)
    : _str(str) {
    }

    ByteChars::~ByteChars() {
    }

    const char* ByteChars::c_str() const {
        return _str.c_str();
    }

    size_t ByteChars::length() const {
        return _str.length();
    }

    void ByteChars::Append(const ByteChars &o) {
        _str += o.get_str_ref();
    }

    size_t ByteChars::FindCharFirstPos(char ch) const {
        return _str.find_first_of(ch);
    }

    ByteChars ByteChars::Substr(size_t index, size_t len) const {
        return ByteChars(_str.substr(index, len));
    }

    ByteChars ByteChars::Substr(size_t index) const {
        return ByteChars(_str.substr(index));
    }

    const std::string& ByteChars::get_str_ref() const {
        return _str;
    }

    std::ostream& operator<<(std::ostream& os, const ByteChars& bc) {
        const char* cs = bc.c_str();
        size_t len = bc.length();

        for(int i=0; i < len; i++) {
            os << std::hex
               << std::showbase
               << std::setw(2)
               << (int)cs[i];
            os << ' ';
        }
        return os;
    }



}