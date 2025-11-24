#ifndef BMSTU_DICTIONARY_H
#define BMSTU_DICTIONARY_H
#include <iostream>
#include <vector>
#include <list>
#include <functional>

using namespace std;


template<typename K, typename V>
class Dict {
private:
    struct KeyValue {
        K key;
        V value;

        KeyValue(const K& k, const V& v) : key(k), value(v) {}
    };

    vector<list<KeyValue>> buckets;
    int itemCount;
    double loadFactorThreshold;

    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % buckets.size();
    }

    void rehash() {
        vector<list<KeyValue>> oldBuckets = buckets;
        buckets.clear();
        buckets.resize(oldBuckets.size() * 2);
        itemCount = 0;

        for (const auto& bucket : oldBuckets) {
            for (const auto& kv : bucket) {
                insert(kv.key, kv.value);
            }
        }
    }

public:
    Dict(int initialSize = 16, double loadFactor = 0.75)
    : buckets(initialSize), itemCount(0), loadFactorThreshold(loadFactor) {}

    ~Dict() {
        clear();
    }

    Dict(const Dict& other)
    : buckets(other.buckets.size()), itemCount(0), loadFactorThreshold(other.loadFactorThreshold) {
        for (const auto& bucket : other.buckets) {
            for (const auto& kv : bucket) {
                insert(kv.key, kv.value);
            }
        }
    }

    Dict& operator=(const Dict& other) {
        if (this != other) {
            clear();
            buckets.resize(other.buckets.size());
            loadFactorThreshold = other.loadFactorThreshold;
            for (const auto& bucket : other.buckets) {
                for (const auto& kv : bucket) {
                    insert(kv.key, kv.value);
                }
            }
        }
        return *this;
    }

    void insert(const K& key, const V& value) {
        if (static_cast<double>(itemCount) / buckets.size() > loadFactorThreshold) {
            rehash();
        }

        size_t index = hash(key);
        for (auto& kv : buckets[index]) {
            if (kv.key == key) {
                kv.value = value;
                return;
            }
        }

        buckets[index].emplace_back(key, value);
        itemCount++;
    }

    V& get(const K& key) {
        size_t index = hash(key);
        for (auto& kv : buckets[index]) {
            if (kv.key == key) {
                return kv.value;
            }
        }
        throw runtime_error("Key not found");
    }

    V& operator[](const K& key) {
        try {
            return get(key);
        } catch (runtime_error&) {
            insert(key, V());
            return get(key);
        }
    }

    bool remove(const K& key) {
        size_t index = hash(key);
        auto& bucket = buckets[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                itemCount--;
                return true;
            }
        }
        return false;
    }

    bool contains(const K& key) const {
        size_t index = hash(key);
        for (const auto& kv : buckets[index]) {
            if (kv.key == key) {
                return true;
            }
        }
        return false;
    }

    int size() const {
        return itemCount;
    }

    bool isEmpty() const {
        return itemCount == 0;
    }

    void clear() {
        for (auto& bucket : buckets) {
            bucket.clear();
        }
        itemCount = 0;
    }

    vector<K> keys() const {
        vector<K> result;
        for (const auto& bucket : buckets) {
            for (const auto& kv : bucket) {
                result.push_back(kv.key);
            }
        }
        return result;
    }

    vector<V> values() const {
        vector<V> result;
        for (const auto& bucket : buckets) {
            for (const auto& kv : bucket) {
                result.push_back(kv.value);
            }
        }
        return result;
    }
};


#endif //BMSTU_DICTIONARY_H