#include <fmt/core.h>

int main(){
    char x = 'a';
    fmt::print("{} -> {}\n", x, sizeof(x));
}