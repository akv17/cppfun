#ifndef HASH_TABLE_H
#define HASH_TABLE_H

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

        uint64_t _hash(const char *str);

    public:
        HashTable(int size, T not_found);
        void set(key_t k, T v);
        T get(key_t k);
};

template<class T>
uint64_t HashTable<T>::_hash(const char *str) {
    uint64_t hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

template<class T>
HashTable<T>::HashTable(int size, T not_found) {
    m_size = size;
    m_not_found = not_found;
    m_buckets.reserve(size);
}

template<class T>
void HashTable<T>::set(key_t k, T v) {
    uint64_t i = _hash(k) % m_size;
    bucket &b = m_buckets[i];
    item it(k, v);
    b.push_back(it);
}

template<class T>
T HashTable<T>::get(key_t k) {
    uint64_t i = _hash(k) % m_size;
    bucket &b = m_buckets[i];
    for (int j = 0; j < b.size(); j++) {
        if (!strcmp(k, b[j].first)) {
            return b[j].second;
        }
    }
    return m_not_found;
}

#endif