/**
 * @file MCMF.hpp
 * @author HourunLi
 * @brief MCMF template
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __MCMF_HPP__
#define __MCMF_HPP__
#include "../../basic.hpp"
#include "../../graph.hpp"

class MCMF : DirectedGraph {
private:
    int s, t;
public:
    MCMF(int n, int m, int s, int t) : DirectedGraph(n, 2*m), s(s), t(t) {

    }

    

};
#endif // !__MCMF_HPP__

