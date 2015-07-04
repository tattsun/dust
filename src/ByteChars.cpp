//
// Created by tattsun on 15/07/04.
//

#include "ByteChars.h"

namespace dust {

    ByteChars::ByteChars() {
        _cs = (char*)malloc(0);
        _len = 0;
    }

    ByteChars::ByteChars(const char *cs, size_t len) {
        _cs = (char*)malloc(len);
        strcpy(_cs, cs);
        _len = len;
    }

    ByteChars::ByteChars(std::string& str) {
        _cs = (char*)malloc(str.length());
        strcpy(_cs, str.c_str());
        _len = str.length();
    }

    ByteChars::ByteChars(const ByteChars &o) {
        _cs = (char*)malloc(o.length());
        strcpy(_cs, o.c_str());
        _len = o.length();
    }

    ByteChars& ByteChars::operator=(const ByteChars &rhs) {
        _cs = (char*)malloc(rhs.length());
        strcpy(_cs, rhs.c_str());
        _len = rhs.length();

        return (*this);
    }

    ByteChars::~ByteChars() {
        free(_cs);
    }

    const char* ByteChars::c_str() const {
        return _cs;
    }

    size_t ByteChars::length() const {
        return _len;
    }

    void ByteChars::Append(const ByteChars &o) {
        char* oldcs = _cs;
        size_t newlen = length() + o.length() + 1;
        _cs = (char*)malloc(newlen);
        _len = newlen;
        strcat(oldcs, o.c_str());
        free(oldcs);
    }

}