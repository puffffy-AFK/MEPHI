#ifndef CUSTOM_HASH_TABLE_HPP
#define CUSTOM_HASH_TABLE_HPP

#include <vector>
#include <functional>
#include "hash.hpp"

using namespace std;

template <typename K, typename V>
class CustomHashTable {
private:
    static constexpr double LOAD_FACTOR_THRESHOLD = 0.7;

    struct Entry {
        K key;
        V value;
        Entry* next;

        Entry(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    vector<Entry*> hashTable;
    size_t capacity;
    size_t size;

    void rehash() {
        capacity *= 2;
        vector<Entry*> newHashTable(capacity, nullptr);
        for (auto& entry : hashTable) {
            Entry* current = entry;
            while (current != nullptr) {
                size_t hashValue = hashFunction(current->key);
                Entry* nextEntry = current->next;
                current->next = newHashTable[hashValue];
                newHashTable[hashValue] = current;
                current = nextEntry;
            }
        }
        hashTable.swap(newHashTable);
    }

public:
    CustomHashTable(size_t initialCapacity = 10) : capacity(initialCapacity), size(0) {
        hashTable.resize(capacity, nullptr);
    }

    ~CustomHashTable() {
        for (auto& entry : hashTable) {
            Entry* current = entry;
            while (current != nullptr) {
                Entry* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t hashFunction(const K& key) const {
        MyHash<K> hasher;
        return hasher(key) % capacity;
    }

    void insert(const K& key, const V& value) {
        if (size >= capacity * LOAD_FACTOR_THRESHOLD) {
            rehash();
        }
        size_t hashValue = hashFunction(key);
        Entry* entry = new Entry(key, value);
        entry->next = hashTable[hashValue];
        hashTable[hashValue] = entry;
        size++;
    }

    void remove(const K& key) {
        size_t hashValue = hashFunction(key);
        Entry* current = hashTable[hashValue];
        Entry* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    hashTable[hashValue] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                size--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    const V& operator[](const K& key) const {
        size_t hashValue = hashFunction(key);
        Entry* current = hashTable[hashValue];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }

            current = current->next;
        }

        static const V default_value = V();
        return default_value;
    }

    V& operator[](const K& key) {
        size_t hashValue = hashFunction(key);
        Entry* current = hashTable[hashValue];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }

            current = current->next;
        }

        insert(key, V());
        return hashTable[hashFunction(key)]->value;
    }

    bool contains(const K& key) const {
        size_t hashValue = hashFunction(key);
        Entry* current = hashTable[hashValue];

        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    public:
    class iterator {
    public:
        iterator(vector<Entry*>& table, size_t index = 0, Entry* entry = nullptr)
            : hashTable(table), idx(index), currentEntry(entry) {
            if (currentEntry == nullptr && idx < hashTable.size()) {
                advanceToNextValidEntry();
            }
        }

        pair<K, V>& operator*() {
            kv.first = currentEntry->key;
            kv.second = currentEntry->value;
            return kv;
        }

        iterator& operator++() {
            if (currentEntry) {
                currentEntry = currentEntry->next;
            }
            advanceToNextValidEntry();
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return idx != other.idx || currentEntry != other.currentEntry;
        }

        pair<K, V>* operator->() {
            return &(operator*());
        }

    private:
        vector<Entry*>& hashTable;
        size_t idx;
        Entry* currentEntry;
        pair<K, V> kv;

        void advanceToNextValidEntry() {
            while (idx < hashTable.size() && currentEntry == nullptr) {
                currentEntry = hashTable[idx++];
            }
        }
    };

    class const_iterator {
    public:
        const_iterator(const vector<Entry*>& table, size_t index = 0, Entry* entry = nullptr)
            : hashTable(table), idx(index), currentEntry(entry) {
            if (currentEntry == nullptr && idx < hashTable.size()) {
                advanceToNextValidEntry();
            }
        }

        const pair<K, V>& operator*() const {
            kv.first = currentEntry->key;
            kv.second = currentEntry->value;
            return kv;
        }

        const_iterator& operator++() {
            if (currentEntry) {
                currentEntry = currentEntry->next;
            }
            advanceToNextValidEntry();
            return *this;
        }

        bool operator!=(const const_iterator& other) const {
            return idx != other.idx || currentEntry != other.currentEntry;
        }

        const pair<K, V>* operator->() const {
            return &(operator*());
        }

    private:
        const vector<Entry*>& hashTable;
        size_t idx;
        Entry* currentEntry;
        mutable pair<K, V> kv;

        void advanceToNextValidEntry() {
            while (idx < hashTable.size() && currentEntry == nullptr) {
                currentEntry = hashTable[idx++];
            }
        }
    };

    iterator begin() {
        return iterator(hashTable);
    }

    iterator end() {
        return iterator(hashTable, hashTable.size());
    }

    const_iterator begin() const {
        return const_iterator(hashTable);
    }

    const_iterator end() const {
        return const_iterator(hashTable, hashTable.size());
    }

};

#endif

