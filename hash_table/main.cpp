#include <iostream>
#include "./hash_table.hpp"

int main() {
    HashTable<const char*> ht(1, "__NOT_FOUND__");
    ht.set("foo", "FOO");
    printf("%s\n", ht.get("foo"));
    ht.set("bar", "BAR");
    printf("%s\n", ht.get("bar"));
    printf("%s\n", ht.get("foo"));
    printf("%s\n", ht.get("fooo"));
}