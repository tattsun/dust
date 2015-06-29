//
// Created by tattsun on 15/06/29.
//

#ifndef DUST_TUPLE_H
#define DUST_TUPLE_H

namespace dust {
    template<typename T, typename S>
    class Tuple {
    public:
        Tuple(T fst, S snd)
        :fst(fst)
        ,snd(snd) {
        };

        T fst;
        S snd;
    };
}


#endif //DUST_TUPLE_H
