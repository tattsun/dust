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
        ByteChars(const char* cs, size_t len);
        ByteChars(std::string& str);
        ByteChars(const ByteChars& o);

        ByteChars& operator=(const ByteChars& rhs);

        ~ByteChars();

        const char* c_str() const;
        size_t length() const;

        void Append(const ByteChars& o);
    private:
        char* _cs;
        size_t _len;

    };

}


#endif //DUST_BYTECHARS_H
