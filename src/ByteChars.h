//
// Created by tattsun on 15/07/04.
//

#ifndef DUST_BYTECHARS_H
#define DUST_BYTECHARS_H

#include <iostream>
#include <stddef.h>

namespace dust {

    class ByteChars {

    public:
        ByteChars();
        ByteChars(const char* cs, size_t len); // len is c length of char*.
        ByteChars(const std::string& str);
        ByteChars(const ByteChars& o);

        ByteChars& operator=(const ByteChars& rhs);

        ~ByteChars();

        const char* c_str() const;
        size_t length() const;

        void Append(const ByteChars& o);
        size_t FindCharFirstPos(char ch) const;
        ByteChars Substr(size_t index, size_t len) const;
        ByteChars Substr(size_t index) const;
    private:
        // len is c length of char*.
        void init(const char* cs, size_t len);

        char* _cs;
        size_t _len; // ignore the length of \0

    };

}


#endif //DUST_BYTECHARS_H
