#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <iostream>

struct TokenPosition {
    int paragraphIndex;
    int wordIndex;
};

struct TokenInfo {
    std::string token;
    std::vector<TokenPosition> positions;

    // Less than operator
    bool operator<(const TokenInfo& other) const {
        return token < other.token;
    }

    // Greater than operator
    bool operator>(const TokenInfo& other) const {
        return token > other.token;
    }

    // Less than or equal to operator
    bool operator<=(const TokenInfo& other) const {
        return !(*this > other);
    }

    // Greater than or equal to operator
    bool operator>=(const TokenInfo& other) const {
        return !(*this < other);
    }

    // Equality operator
    bool operator==(const TokenInfo& other) const {
        return token == other.token && positions == other.positions;
    }

    // Not equal operator
    bool operator!=(const TokenInfo& other) const {
        return !(*this == other);
    }
};
#endif