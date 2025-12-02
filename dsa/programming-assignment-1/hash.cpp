#include <utility>
#include <list>
#include <algorithm>
#include <vector>
#include "hash.hpp"

#define BUCKET size_t b = bucket(key);

// Iterator to first element in the hash set
HashSet::Iterator HashSet::begin() {
  // Iterator function from hpp
  return {&buckets, 0, buckets[0].begin()};
}

// Sentinel iterator to end of set
HashSet::Iterator HashSet::end() {
  return {&buckets, buckets.size(), std::list<int>::iterator()};
}

// (Default) Constructor setting starting values
HashSet::HashSet() 
: cPrimeSize(0), buckets(1), maxLF(1.0) {}

// Copy constructor
HashSet::HashSet(const HashSet& other) 
  : cPrimeSize(other.cPrimeSize), numElements(other.numElements), buckets(other.buckets), maxLF(other.maxLF) {}
  
// Assignment operator, swaps all members
HashSet& HashSet::operator=(HashSet other) {
  std::swap(cPrimeSize, other.cPrimeSize);
  std::swap(numElements, other.numElements);
  std::swap(buckets, other.buckets);
  std::swap(maxLF, other.maxLF);
  return *this;
}

// Destructor
HashSet::~HashSet() = default;


void HashSet::insert(int key) {
  BUCKET
  if (std::find(buckets[b].begin(), buckets[b].end(), key) == buckets[b].end()) { // Check if buckets contain key
  buckets[b].push_back(key); // If not, adds key
  ++numElements; // Increase total number of elements
  }
  if (loadFactor() > maxLoadFactor()) { 
    if (cPrimeSize + 1 < sizes.size()) { // If not the last prime number
      rehash(sizes[++cPrimeSize]); // Use next prime number
    } else {
      rehash(sizes.back()*2);
    }
  }
}

bool HashSet::contains(int key) const {
  if (buckets.empty()) return false;
  BUCKET
  // Returns true if key is found
  return std::find(buckets[b].begin(), buckets[b].end(), key) != buckets[b].end(); 
}

HashSet::Iterator HashSet::find(int key) {
  BUCKET
  auto it = std::find(buckets[b].begin(), buckets[b].end(), key);
  if (it == buckets[b].end()){
    return end();
  } 
  return {&buckets, b, it}; // Returns an iterator or end()
}

// Erase element by value
void HashSet::erase(int key) {
  if (buckets.empty()) return;
  BUCKET
  auto it = std::find(buckets[b].begin(), buckets[b].end(), key);
  if (it != buckets[b].end()) {
    buckets[b].erase(it); // Remove key from bucket
    --numElements; // Decrease total number of elements
  }
}

HashSet::Iterator HashSet::erase(HashSet::Iterator it) {
  if (it == end()) return end();
  std::size_t b = it.bIndex;
  auto nextIt = buckets[b].erase(it.element); // Erase
  --numElements;
  return {&buckets, it.bIndex, nextIt}; // Returns next iterator
}

void HashSet::rehash(std::size_t newSize) {
  // New vector of buckets with next size in 'sizes'
  std::vector<std::list<int>> newBuckets(newSize);
  
  // Iterate over each bucket in old set
  for (std::list<int>& prevB : buckets) {
    // Iterate over each element in bucket
    for (auto it = prevB.begin(); it != prevB.end();) {
      int key = *it;
      BUCKET
      auto nextIt = std::next(it);
      // Move element to new bucket, no copies
      newBuckets[b].splice(newBuckets[b].end(), prevB, it); 
      it = nextIt;
    }
  }
  // Replace old buckets with the new ones
  buckets = std::move(newBuckets); 
  }

//Total number of elements
std::size_t HashSet::size() const {
  return numElements;
}

bool HashSet::empty() const {
  return numElements == 0;
}

// Number of buckets
std::size_t HashSet::bucketCount() const {
  return sizes[cPrimeSize];
}

// Returns number of elements in a specific bucket
std::size_t HashSet::bucketSize(std::size_t b) const {
  return buckets[b].size();
}
// Which bucket key would go into (index)
std::size_t HashSet::bucket(int key) const {
  return abs(key) % bucketCount(); //static_cast<std::size_t>(key)
}

// Number of elements/number buckets
float HashSet::loadFactor() const {
  if (bucketCount() == 0) return 0;
  return static_cast<float>(numElements)/buckets.size();
}

float HashSet::maxLoadFactor() const {
  return maxLF;
}

void HashSet::maxLoadFactor(float maxLoad) {
  maxLF = maxLoad;
  if (loadFactor() > maxLoad) {
    // Minimum size required for new load factor
    std::size_t minSize = numElements / maxLoadFactor();
    // Find the smallest size in 'sizes' that meets minSize requirement
    auto sizeIt = std::lower_bound(sizes.begin(), sizes.end(), minSize);

    // Return nothing if no size found
    if (sizeIt == sizes.end()) return;
    // Update the size index
    cPrimeSize = std::distance(sizes.begin(), sizeIt);
    rehash(sizes[cPrimeSize]);
  }
}

