//
// Created by Tojima Tatsuya on 15/06/29.
//

#include "Human.h"

Human::Human(std::string name) {
    this->name_ = name;
}

Human::~Human() {
}

void Human::SayHello() {
    std::cout << "Hello, my name is " << name_ << "." << std::endl;
}