#pragma once
#include <vector>
#include <algorithm>

template <typename Iterator>
class IteratorRange{
public:
    IteratorRange(Iterator begin, Iterator end) 
        : begin_(begin), end_(end){
    }

    Iterator begin() const {
        return begin_;
    }

    Iterator end() const {
        return end_;
    }

private:
    Iterator begin_;
    Iterator end_;
};

template <typename Iterator>
class Paginator{
public:
    Paginator(Iterator begin, Iterator end, size_t page_size){
        for (auto it = begin; it < end; it += page_size){
            Iterator page_begin = it;
            Iterator page_end = next(it, std::min(page_size, static_cast<size_t>(distance(it, end))));
            pages_.push_back(IteratorRange(page_begin, page_end));
        } 
    }   
    
    auto begin() const {
        return pages_.begin();
    }

    auto end() const{
        return pages_.end();
    }
    
private:
    std::vector<IteratorRange<Iterator>> pages_;
};

template <typename DocumentIterator>
std::ostream& operator<<(std::ostream& out, const IteratorRange<DocumentIterator> range){
    for (auto it = range.begin(); it != range.end(); ++it){
        out << *it;
    }
    return out;
}

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}