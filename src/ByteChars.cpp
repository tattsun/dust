//
// Created by tattsun on 15/07/04.
//

#include "ByteChars.h"
#include <iostream>
#include <assert.h>
#include <string.h>

namespace dust {

    ByteChars::ByteChars() {
        init("", 1);
    }

    ByteChars::ByteChars(const char *cs, size_t len) {
        init(cs, len);
    }

    ByteChars::ByteChars(char c) {
        char* cs = (char*)malloc(2);
        cs[0] = c;
        cs[1] = '\0';
        init(cs, 2);
        free(cs);
    }

    ByteChars::ByteChars(const std::string &str) {
        init(str.c_str(), str.length()+1);
    }

    ByteChars::ByteChars(const ByteChars &o) {
        init(o.c_str(), o.length()+1);
    }

    ByteChars& ByteChars::operator=(const ByteChars &rhs) {
        if (&rhs == this) return (*this);

        free(_cs);
        init(rhs.c_str(), rhs.length()+1);

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
        realloc(_cs, _len + o.length() + 1);
        strcat(_cs, o.c_str());
        _len = _len + o.length();
    }

    size_t ByteChars::FindCharFirstPos(char ch) const {
        for(size_t i=0; i < _len; i++) {
            if (_cs[i] == ch) return i;
        }
        return (size_t)-1;
    }

    ByteChars ByteChars::Substr(size_t index, size_t len) const {
        char* buf = (char*)malloc(len+1);
        for(size_t i=0; i < len; i++) {
            buf[i] = _cs[index+i];
        }
        buf[len] = '\0';
        ByteChars bs(buf, len+1);
        free(buf);
        return bs;
    }

    ByteChars ByteChars::Substr(size_t index) const {
        if(index > _len) return ByteChars();
        return Substr(index, _len-index);
    }

    void ByteChars::init(const char *cs, size_t len) {
        _cs = (char*)malloc(len);
        strcpy(_cs, cs);
        _len = len-1;
    }



}