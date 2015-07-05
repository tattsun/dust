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
        ByteChars(char c);
        ByteChars(const std::string& str);

        ~ByteChars();

        const char* c_str() const;
        size_t length() const;

        void Append(const ByteChars& o);
        size_t FindCharFirstPos(char ch) const;
        ByteChars Substr(size_t index, size_t len) const;
        ByteChars Substr(size_t index) const;

        const std::string& get_str_ref() const;

    private:
        std::string _str;
    };

    std::ostream& operator<<(std::ostream& os, const ByteChars& bc);
}


#endif //DUST_BYTECHARS_H
