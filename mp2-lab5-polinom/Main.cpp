#include <iostream>

/*#include <sstream>
#include <fstream>
#include "TPolinom.h"

using namespace std;

void write_to_file(const string& file_path, const TPolinom& polinomchik) {
	ofstream file(file_path);
	file << polinomchik;
	file.close();
}
const TPolinom read_from_file(string file_path) {
	TPolinom polinomchik;
	ifstream file(file_path);
	file >> polinomchik;
	file.close();
	return polinomchik;
}*/

#include <vector>
#include <list>

template<class T>
class VectorList
{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const&) = default;
    VectorList(VectorList&&) = default;

    VectorList& operator=(VectorList&&) = default;
    VectorList& operator=(VectorList const&) = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q) // определена снаружи
    {
        if (p != q)
            data_.push_back(VectT(p,q));
    }


    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const
    {
        size_t _size = 0;
        for (auto i = begin(); i != end(); i++, _size++);
        return _size;
    }

    // определите const_iterator
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
    {
        friend VectorList;
    public:
        const_iterator() = default;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
        ~const_iterator() = default;

        T const& operator*() const { return *vector_const_iter_; }
        T const* operator->() const { return &(*vector_const_iter_); }
        bool operator!=(const_iterator const& a) const
        {
            return !(*this == a);
        }
        bool operator==(const_iterator const& a) const
        {
            return vector_const_iter_ == a.vector_const_iter_ && list_const_iter_ == a.list_const_iter_;
        }
        const_iterator& operator++() // prefix
        {
            if (++vector_const_iter_ == (*list_const_iter_).end())
            {
                if (*this == vector_list->end())
                    return *this;
                ++list_const_iter_;
                vector_const_iter_ = (*list_const_iter_).begin();
            }
            return *this;
        }
        const_iterator& operator--() // prefix
        {
            if (vector_const_iter_ == (*list_const_iter_).begin())
            {
                if (*this == vector_list->begin())
                    return *this;
                --list_const_iter_;
                vector_const_iter_ = (*list_const_iter_).end();
            }
            --vector_const_iter_;
            return *this;
        }
        const_iterator operator++(int) // postfix
        {
            const_iterator res(*this);
            ++(*this);
            return res;
        }
        const_iterator operator--(int) // postfix
        {
            const_iterator res(*this);
            --(*this);
            return res;
        }
    private:
        VectorList const* vector_list = nullptr;

        using list_const_iterator = typename std::list<std::vector<T>>::const_iterator;
        using vector_const_iterator = typename std::vector<T>::const_iterator;

        list_const_iterator list_const_iter_;
        vector_const_iterator vector_const_iter_;

        const_iterator(VectorList const* vl, list_const_iterator list_const_iter, vector_const_iterator vector_const_iter) : vector_list(vl), list_const_iter_(list_const_iter), vector_const_iter_(vector_const_iter) {}
    };

    // определите методы begin / end
    const_iterator begin() const
    {
        return const_iterator(this, data_.begin(), data_.begin()->begin());
    }
    const_iterator end() const
    {
        return const_iterator(this, --data_.end(), (--data_.end())->end());
    }

    // определите const_reverse_iterator
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend()   const { return const_reverse_iterator(begin()); }

private:
    ListT data_;
};

int main() {
    const VectorList<int> check_const_compile;
    auto check_const_equals_compile = check_const_compile.begin();
    check_const_equals_compile == check_const_equals_compile;

    VectorList<std::vector<int>> check_arrow_vl;
    std::vector<int> vint1 = { 1, 2, 3 };
    std::vector<int> vint2 = { 4, 5, 6 };
    std::vector<std::vector<int>> vecs;
    vecs.push_back(vint1);
    vecs.push_back(vint2);
    check_arrow_vl.append(vecs.begin(), vecs.end());
    auto it_f = check_arrow_vl.begin();
    assert(it_f->size() == 3);

    VectorList<char> vec_list;

    std::vector<char> v1;
    v1.push_back('A');
    v1.push_back('B');
    v1.push_back('C');
    vec_list.append(v1.begin(), v1.end());

    std::vector<char> v2;
    v2.push_back('D');
    v2.push_back('E');
    v2.push_back('F');
    v2.push_back('G');
    vec_list.append(v2.begin(), v2.end());

    assert(vec_list.size() == 7);
    assert(std::distance(vec_list.begin(), vec_list.end()) == 7);

    auto it = vec_list.begin();
    assert(*it == 'A'); ++it;
    assert(*it == 'B'); ++it;
    assert(*it == 'C'); ++it;
    assert(*it == 'D'); ++it;
    assert(*it == 'E'); ++it;
    assert(*it == 'F'); ++it;
    assert(*it == 'G'); ++it;
    assert(it == vec_list.end());

    it = vec_list.begin();
    assert(*it == 'A'); it++;
    assert(*it == 'B'); it++;
    assert(*it == 'C'); it++;
    assert(*it == 'D'); it++;
    assert(*it == 'E'); it++;
    assert(*it == 'F'); it++;
    assert(*it == 'G'); it++;

    it = vec_list.end(); it--;
    assert(*it == 'G'); it--;
    assert(*it == 'F'); it--;
    assert(*it == 'E'); it--;
    assert(*it == 'D'); it--;
    assert(*it == 'C'); it--;
    assert(*it == 'B'); it--;
    assert(*it == 'A');

    it = vec_list.end(); --it;
    assert(*it == 'G'); --it;
    assert(*it == 'F'); --it;
    assert(*it == 'E'); --it;
    assert(*it == 'D'); --it;
    assert(*it == 'C'); --it;
    assert(*it == 'B'); --it;
    assert(*it == 'A');

    auto r_it = vec_list.rbegin();
    assert(*r_it == 'G'); r_it++;
    assert(*r_it == 'F'); r_it++;
    assert(*r_it == 'E'); r_it++;
    assert(*r_it == 'D'); r_it++;
    assert(*r_it == 'C'); r_it++;
    assert(*r_it == 'B'); r_it++;
    assert(*r_it == 'A'); r_it++;
    assert(r_it == vec_list.rend());

    r_it = vec_list.rbegin();
    assert(*r_it == 'G'); ++r_it;
    assert(*r_it == 'F'); ++r_it;
    assert(*r_it == 'E'); ++r_it;
    assert(*r_it == 'D'); ++r_it;
    assert(*r_it == 'C'); ++r_it;
    assert(*r_it == 'B'); ++r_it;
    assert(*r_it == 'A'); ++r_it;
    assert(r_it == vec_list.rend());

    r_it = vec_list.rend(); --r_it;
    assert(*r_it == 'A'); --r_it;
    assert(*r_it == 'B'); --r_it;
    assert(*r_it == 'C'); --r_it;
    assert(*r_it == 'D'); --r_it;
    assert(*r_it == 'E'); --r_it;
    assert(*r_it == 'F'); --r_it;
    assert(*r_it == 'G');

    r_it = vec_list.rend(); r_it--;
    assert(*r_it == 'A'); r_it--;
    assert(*r_it == 'B'); r_it--;
    assert(*r_it == 'C'); r_it--;
    assert(*r_it == 'D'); r_it--;
    assert(*r_it == 'E'); r_it--;
    assert(*r_it == 'F'); r_it--;
    assert(*r_it == 'G');

    VectorList<int> check_empty;
    assert(check_empty.size() == 0);
    assert(check_empty.begin() == check_empty.end());
    assert(check_empty.rbegin() == check_empty.rend());

    return 0;
}
