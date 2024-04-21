#include <iostream>
#include <vector>
#include <variant>
#include <string>
#include "Tokens.h"
#include <unordered_map>

// (10 + 20) * 6 / 2 - (7 * 7)
using Token = std::variant<OpeningBrasket,CloseBrasket,Multiply,Plus,Minus,Divide,UnknowToken,AbsToken,Number, Modulo, MinToken,MaxToken,SqrToken>;
const std::unordered_map<unsigned char,Token> kSymbolToToken{{'+',Plus{}}, {'-',Minus{}},
                                                             {'*',Multiply{}}, {'/', Divide{}},
                                                             {'%',Modulo{}}, {'(',OpeningBrasket{}}, {')',CloseBrasket{}}};

const std::unordered_map<std::string,Token> kStringTotoken{{"abs",AbsToken{}},{"min",MinToken{}},{"max",MaxToken{}},{"sqr",SqrToken{}}};

Number ParseNum(const std::string & str, size_t& pos){
    auto symbol = static_cast<unsigned char>(str[pos]);
    int result = 0;
    while (std::isdigit(symbol))
    {
        result = result * 10 + (symbol - '0');

        if(pos == str.size() -1 )
            break;

        symbol = static_cast<unsigned char>(str[++pos]);
    }
    return Number{result};
}

Token ParseFunc(const std::string& str, size_t& pos )
{
    auto symbol = static_cast<unsigned char>(str[pos]);
    std::string func;
    while(std::isalpha(symbol))
    {
        func += symbol;
        symbol = static_cast<unsigned char>(str[++pos]);
    }
    if(auto it = kStringTotoken.find(func); it != kStringTotoken.end())
    {
        return it->second;
    }

    return UnknowToken{std::move(func)};
}

std::vector<Token> Tokenize(const std::string& expr){

   std::vector<Token> tokens;
   const size_t size = expr.size();
   size_t pos = 0;

   while(pos < size)
   {
       unsigned char symbol = static_cast<unsigned char>(expr[pos]);

       if(std::isspace(symbol)){
           ++pos;
       }else if(std::isdigit(symbol)){
           tokens.emplace_back(ParseNum(expr,pos));
       }else if (auto it = kSymbolToToken.find(symbol); it != kSymbolToToken.end()){
           tokens.push_back(it->second);
           ++pos;
       }else if(std::isalpha(symbol)){
           tokens.push_back(ParseFunc(expr,pos));
       }else {
           ++pos;
       }
   }
    return tokens;
}



int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string str("20 + 20 * max(30,20) + dsad + abs(234) * 32 % 3331 % min(2321) * sqr(774) / 234 + ()");
    auto tokens = Tokenize(str);

    return 0;
}
