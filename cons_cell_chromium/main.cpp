
#include <iostream>
#include "cons.h"
#include "variant.hpp"
typedef typename mpark::variant<int, std::string> m_var;

struct unary {
    int operator()(int & i) const
    {
        //std::cout << i << std::endl;
        return 0;
    }
    int operator()(const std::string & s) const {
         std::cout << s << std::endl;
        return 1;
    }
};  // unary

int main(int argc, const char * argv[]) {
    // insert code here...
    //Cons<m_var> m;
    List<m_var> m_list = Cons(m_var(1),Cons(m_var("a"), List<m_var>()));
    ListIterator<m_var> iter(m_var);
    
    for (auto & elt : m_list) {
        mpark::visit(unary{}, elt);
    }
    //iter++;
    //auto &ret = *iter;
    //std::cout << ret << std::endl;
    //List<char> b = Cons('b', Cons('a', List<char>()));
    return 0;
}
