#ifndef HASH_HPP_
#define HASH_HPP_

#include <list>
#include <vector>
#include <iterator>

class HashSet {
 private:
  // the number of buckets must be one of the
  // values in sizes.  After 1, they are prime numbers
  // to promote uniform hashing.  We won't test your solution
  // with more than 1'000'000 elements
  const std::vector<std::size_t> sizes {1ul, 13ul, 59ul, 127ul, 257ul, 541ul,
    1'109ul, 2'357ul, 5'087ul, 10'273ul, 20'753ul, 42'043ul,
    85'229ul, 172'933ul, 351'061ul, 712'697ul, 1'447'153ul, 2'938'679ul};
  // define the member variables you need for your solution here
    std::size_t cPrimeSize {0}; //Index of current bucket size in 'sizes'
    std::size_t numElements {}; // Total number of elements in the hash set
    std::vector<std::list<int>> buckets; 
    float maxLF; //Maximum load factor
  
 public:
  // we include this line to ensure compilation with the level 2 signatures
  // you can change the way Iterator is implemented if you want
  //*** Constructors, Destructor, Assignment
  //Iterator class
  class Iterator { 
    private:
      std::vector<std::list<int>>* bPtr; //Pointer to buckets

      // Function to go to next non-empty bucket
      void nextBucket() {
        auto& buckets = *bPtr;

        // Moves buckets until a non-empty one
        while (bIndex < buckets.size() && element == buckets[bIndex].end()) {
          ++bIndex;

          if (bIndex < buckets.size()) {
            element = buckets[bIndex].begin();
          } else {
            element = std::list<int>::iterator();
            break;
          }
        }
      }

      // Function to go to previous non-empty bucket
      void prevBucket() {
        auto& buckets = *bPtr;

        if (bIndex >= buckets.size()) {
          bIndex = buckets.size() - 1;
          element = buckets[bIndex].end();
        }

        // Moves backwards until a non-empty bucket
        while (bIndex > 0) {
          if (element == buckets[bIndex].begin()) {
            --bIndex;
            element = buckets[bIndex].end();
          } else {
            break;
          }
        }

        if (element == buckets[bIndex].begin()) {
          element = buckets[0].end();
        } else {
          --element;
        }
      }

    public:
    // Required iterator traits (see w4 tutorial)
      using iterator_category = std::bidirectional_iterator_tag; // bi-directional iterator
      using value_type = int;
      using difference_type = std::ptrdiff_t;
      using pointer = int*;
      using reference = int&;
      
      std::size_t bIndex; // Current bucket index, which bucket
      std::list<int>::iterator element; // Iterator to current element in bucket

      // Constructor iterator function - pointer to buckets, index, element
      Iterator(std::vector<std::list<int>>* bPtr, std::size_t bIndex, std::list<int>::iterator element)
        : bPtr(bPtr), bIndex(bIndex), element(element) {
          nextBucket();
        }

      // Dereference operator
      int& operator*() {
        return *element;
      }

      // Increment operator prefix
      Iterator& operator++() {
        ++element;
        nextBucket();
        return *this;
      }

    // Decrement operator prefix
      Iterator& operator--() {
        prevBucket(); //Call function to go to the previous non empty bucket
        return *this;
      }

      // Comparison operators
      bool operator==(const Iterator& other) const {
        return bIndex == other.bIndex && element == other.element;
      }

      bool operator !=(const Iterator& other) const {
        return !(*this == other);
      }
  };

  // default constuctor
  HashSet();

  // copy constructor
  HashSet(const HashSet&);

  // assignment operator
  HashSet& operator=(HashSet);

  // destructor
  ~HashSet();

  //*** Core Level 1 functionality

  void insert(int key);

  bool contains(int key) const;

  void erase(int key);

  // increase number of buckets to at least newSize
  // and rehash all elements into the new buckets
  void rehash(std::size_t newSize);

  //*** Core Level 2 functionality

  Iterator find(int key);

  Iterator erase(Iterator it);

  //*** Utility functions

  // return the number of elements
  std::size_t size() const;

  // return whether or not the hash set is empty
  bool empty() const;

  // return the number of buckets, i.e. the size of the underlying array
  std::size_t bucketCount() const;

  // return the number of elements in the bucket b
  std::size_t bucketSize(std::size_t b) const;

  // return which bucket key would go in
  std::size_t bucket(int key) const;

  // return the load factor
  float loadFactor() const;

  // return the load factor threshold that provokes a rehash
  float maxLoadFactor() const;

  // set the load factor threshold
  void maxLoadFactor(float maxLoad);

  //*** Iterator Functionality  
  Iterator begin();
  Iterator end();
};

#endif      // HASH_HPP_
