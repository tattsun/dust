//
// Created by Tojima Tatsuya on 15/06/29.
//

#ifndef DUST_HUMAN_H
#define DUST_HUMAN_H

#include <iostream>

class Human {
    std::string name_;
public:
    Human(std::string name);
    ~Human();
    void SayHello();
};


#endif //DUST_HUMAN_H
