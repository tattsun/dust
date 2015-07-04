//
// Created by tattsun on 15/07/04.
//

#include "ByteChars.h"
#include <iostream>
#include <assert.h>
#include <string.h>
#include <iomanip>
#include <malloc/malloc.h>

namespace dust {

    ByteChars::ByteChars() {
        init("", 1);
    }

    ByteChars::ByteChars(const char *cs, size_t len) {
        init(cs, len);
    }

    ByteChars::ByteChars(char c) {
        char* cs = (char*)malloc(sizeof(char)*2);
        cs[0] = c;
        cs[1] = '\0';
        init(cs, 2);
        free(cs);
        assert(malloc_zone_check(NULL));
    }

    ByteChars::ByteChars(const std::string &str) {
        init(str.c_str(), str.length()+1);
    }

    ByteChars::ByteChars(const ByteChars &o) {
        init(o.c_str(), o.length()+1);
    }

    ByteChars& ByteChars::operator=(const ByteChars &rhs) {
        if (&rhs == this) return (*this);

        //free(_cs);
        init(rhs.c_str(), rhs.length()+1);

        return (*this);
    }

    ByteChars::~ByteChars() {
        free(_cs);
        assert(malloc_zone_check(NULL));
    }

    const char* ByteChars::c_str() const {
        return _cs;
    }

    size_t ByteChars::length() const {
        return _len;
    }

    void ByteChars::Append(const ByteChars &o) {
        realloc(_cs, _len + o.length() + 1);
        for(size_t i=0; i < o.length(); i++) {
            _cs[_len+i] = o.c_str()[i];
        }
        _cs[_len+o.length()] = '\0';
        _len = _len + o.length();
    }

    size_t ByteChars::FindCharFirstPos(char ch) const {
        for(size_t i=0; i < _len; i++) {
            if (_cs[i] == ch) return i;
        }
        return (size_t)-1;
    }

    ByteChars ByteChars::Substr(size_t index, size_t len) const {
        if (len <= 0) { return ByteChars(); }

        std::cout << "Substr: " << len << std::endl;
        char* buf = (char*)malloc(sizeof(char) * (len+1));
        for(size_t i=0; i < len; i++) {
            buf[i] = _cs[index+i];
        }
        buf[len] = '\0';
        ByteChars bs(buf, len+1);
        free(buf);
        std::cout << "ZONECHK" << std::endl;

        assert(malloc_zone_check(NULL));
        std::cout << "OKAY" << std::endl;
        return bs;
    }

    ByteChars ByteChars::Substr(size_t index) const {
        if(index >= _len) return ByteChars();
        std::cout << "n" << _len - index << std::endl;
        return Substr(index, _len-index);
    }

    void ByteChars::init(const char *cs, size_t len) {
        std::cout << "ByteChars::init: " << len << std::endl;
        _cs = (char*)malloc(sizeof(char) * len);
        std::cout << "ByteChars::init: malloced" << std::endl;
        for(size_t i=0; i < len; i++) {
            _cs[i] = cs[i];
        }
        _cs[len-1] = '\0';
        _len = len-1;
        std::cout << "ByteChars::init: inited" << std::endl;
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