//
// Created by Andrei on 16-Mar-18.
//

#ifndef LFA_AFN_H
#define LFA_AFN_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <cstring>
#include <utility>

using namespace std;

class AFN
{
public:
    AFN();
    AFN ( const AFN& C );
    virtual ~AFN();
    friend void citire_automat( AFN *&T , int &n , int &q , int *&StF , int &nr ) ;
    friend bool delta( AFN *T , int n , int *StF , int nr , queue < int > &MultimeStari , char word[100]) ;
    friend void delta_prim( AFN *T , int n , queue < int >& MultimeStari , char character ) ;

protected:

private:
    unsigned int StareInit ;
    unsigned int nrchr ;
    char chr[100] ;
    unsigned int nrstf ;
    vector < list < int > > StareFin ;
};

#endif //LFA_AFN_H
