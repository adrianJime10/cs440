#include "Map.hpp"

#include <cassert>
#include <iostream>

// basically an int wrapper
class MyKeyType {
    private:
        int val;

    public:
        //not default constructable, not copy assignable, not move assignable
        MyKeyType() = delete;
        MyKeyType& operator=(const MyKeyType&) = delete;
        MyKeyType& operator=(MyKeyType&&) = delete;

        // copy constructable and move assignable
        MyKeyType(MyKeyType&&) = default;
        MyKeyType(const MyKeyType&) = default;
        ~MyKeyType() = default;

        MyKeyType(int i) : val(i) { }

        bool operator<(const MyKeyType& other) const { 
            return this->val < other.val;
        }

        bool operator==(const MyKeyType &other) const {
            return this->val == other.val;
        }
};

// same as keytype except no operator<
class MyValueType {
    private:
        int val;

    public:
        //not default constructable, not copy assignable, not move assignable
        MyValueType() = delete;
        MyValueType& operator=(const MyValueType&) = delete;
        MyValueType& operator=(MyValueType&&) = delete;

        // copy constructable and move assignable
        MyValueType(MyValueType&&) = default;
        MyValueType(const MyValueType&) = default;
        ~MyValueType() = default;

        MyValueType(int i) : val(i) { }

        bool operator==(const MyValueType &other) const {
            return this->val == other.val;
        }
};

class MyDefaultConstructible {

        friend bool operator<(const MyDefaultConstructible &o1, const MyDefaultConstructible &o2) {
            return o1.val < o2.val;
        }

    private:
        int val = 0;

    public:
        // not copy assignable, not move assignable
        MyDefaultConstructible& operator=(const MyDefaultConstructible&) = delete;
        MyDefaultConstructible& operator=(MyDefaultConstructible&&) = delete;

        // default constructable, copy constructable and move assignable
        MyDefaultConstructible() = default;
        MyDefaultConstructible(MyDefaultConstructible&&) = default;
        MyDefaultConstructible(const MyDefaultConstructible&) = default;
        ~MyDefaultConstructible() = default;

        MyDefaultConstructible(int i) : val(i) { }

        bool operator==(const MyDefaultConstructible &other) const {
            return this->val == other.val;
        }
};


class MyAssignable {
    private:
        int val = 0;

    public:
        MyAssignable() = default;
        MyAssignable(int i) : val(i) { }
        bool operator==(const MyAssignable &other) const {
            return this->val == other.val;
        }
};

// manual instantiation, instantiates every member function instead of 
// just the ones called
template class cs540::Map<int, int>;


int main() {
    cs540::Map<int, int> m{{3, 5}};//something wrong with first insert, fix insert function again...
    m.insert({{2}, {3}});
    //std::cout << m.sentinel->next[0]->value->first << "\n";
    //std::cout << m.sentinel->next[0]->next[0]->value->second << "\n";
    m.insert({{1}, {3}});
    m.insert({{5}, {3}});
    m.insert({{7}, {3}});
    m.clear();
    std::cout << m.size();
    //std::cout << m.sentinel->next[0]->value->first << "\n";
    /*std::cout << m.sentinel->next[0]->value->first << "\n";
    std::cout << m.sentinel->next[0]->next[0]->value->first << "\n";
    std::cout << m.sentinel->next[0]->next[0]->next[0]->value->first << "\n";
    std::cout << m.sentinel->next[0]->next[0]->next[0]->next[0]->value->first << "\n";
    std::cout << m.sentinel->next[0]->next[0]->next[0]->next[0]->next[0]->value->first << "\n";
    std::cout<<m.size() << "here";
    m.at(2);
    auto iter = m.find(2);
    //auto iter = m.begin();
    //std::cout << (iter).it->value->first;
    m.erase(iter);
    std::cout << m.sentinel->next[0]->value->first << "\n";
    std::cout << m.sentinel->next[0]->next[0]->value->first << "\n";
    std::cout << m.sentinel->next[0]->next[0]->next[0]->value->first << "\n";
    std::cout << m.sentinel->next[0]->next[0]->next[0]->next[0]->value->first << "\n";
    //std::cout << m.sentinel->next[0]->next[0]->next[0]->next[0]->next[0]->value->first << "\n";
    //std::cout << m.sentinel->next[0]->value->first << "\n";
    std::cout<<m.size() << "here\n";
    //m.erase(iter);
    auto m_copy = m;
    std::cout << m_copy.size() << "yoooo\n";
    std::cout << m_copy.sentinel->next[0]->value->first << "\n";
    std::cout << m_copy.sentinel->next[0]->next[0]->value->first << "\n";
    std::cout << m_copy.sentinel->next[0]->next[0]->next[0]->value->first << "\n";
    std::cout << m_copy.sentinel->next[0]->next[0]->next[0]->next[0]->value->first << "\n";
    assert(m_copy == m);

    cs540::Map<int, int> m2{{8, 9}};
    m2[10]; // should default construct these values
    m2[15];

    cs540::Map<int, int> m3{{6, 7}};
    m3[20] = {5}; // move assign
    //MyAssignable ma{1};
    //m3[10] = ma; //copy assign*/

    return 0;
}
