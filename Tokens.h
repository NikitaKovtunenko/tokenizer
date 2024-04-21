//
// Created by Никита Ковтуненко on 17.04.2024.
//

#ifndef TOKENIZER_TOKENS_H
#define TOKENIZER_TOKENS_H

struct OpeningBrasket{};
struct CloseBrasket{};
struct Plus{};
struct Minus{};
struct Multiply{};
struct Divide{};
struct Number{
    int num;
};
struct UnknowToken{
    std::string value;
};
struct MinToken{};
struct AbsToken{};
struct MaxToken{};
struct SqrToken{};
struct Modulo{};

#endif //TOKENIZER_TOKENS_H
