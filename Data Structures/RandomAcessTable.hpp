//
//  RandomAcessTable.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 01/06/22.
//

#ifndef RandomAcessTable_hpp
#define RandomAcessTable_hpp

#include <unordered_set>
#include <chrono>
#include <stdio.h>
#include <vector>
#include <utility>
#include <iostream>
#include <random>
#include <algorithm>

template <typename Elem>
class RandomAcessTable
{
public:
  RandomAcessTable(std::size_t initial_size)
   : data_(initial_size) , count_(0)
  { }

  RandomAcessTable &push_back(const Elem &elem){
    if (count_ < data_.size())
      data_[count_++] = elem;
    else {
      data_.push_back(elem);
      ++count_;
    }
    set_.insert(elem);
    return *this;
  }

    RandomAcessTable &remove(const std::size_t index){
        set_.erase(data_[index]);
        if (index < count_){
          std::swap(data_[index],data_[count_-1]);
          --count_;
        }
        return *this;
    }

    void clear(){
        count_ = 0;
    }
    
    bool find(int index){
        return set_.find(index) != set_.end();
    }
    
    const Elem &operator[](const std::size_t index) const
    { return data_[index]; }

    Elem &operator[](const std::size_t index)
    { return data_[index]; }

    std::size_t size() const
    { return count_; }
    
    void shuffle(){
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0; i < count_; i++){
            std::swap(data_[i], data_[std::uniform_int_distribution<int>(0, i)(rng)]);
        }
    }

private:
  std::unordered_set<Elem> set_;
  std::vector<Elem>  data_;
  std::size_t        count_;
};
#endif /* RandomAcessTable_hpp */
