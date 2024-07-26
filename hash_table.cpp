#include <iostream>
#include <vector>
#include <cstring>


template<class T>
class HashTable {
    typedef const char* key_t;
    typedef std::pair<key_t, T> item;
    typedef std::vector<item> bucket;

    private:
        int m_size;
        T m_not_found;
        std::vector<bucket> m_buckets;

        uint64_t _hash(const char *str) {
            uint64_t hash = 5381;
            int c;
            while (c = *str++)
                hash = ((hash << 5) + hash) + c;
            return hash;
        }

    public:
        HashTable(int size, T not_found) {
            m_size = size;
            m_not_found = not_found;
            m_buckets.reserve(size);
        }
        
        void set(key_t k, T v) {
            uint64_t i = _hash(k) % m_size;
            item it(k, v);
            m_buckets[i].push_back(it);
        }
        
        T get(key_t k) {
            uint64_t i = _hash(k) % m_size;
            bucket b = m_buckets[i];
            for (int j = 0; j < b.size(); j++) {
                if (!strcmp(k, b[j].first)) {
                    return b[j].second;
                }
            }
            return m_not_found;
        }
};


int main() {
    HashTable<const char*> ht(1, "__NOT_FOUND__");
    ht.set("foo", "FOO");
    printf("%s\n", ht.get("foo"));
    ht.set("bar", "BAR");
    printf("%s\n", ht.get("bar"));
    printf("%s\n", ht.get("foo"));
    printf("%s\n", ht.get("fooo"));
}