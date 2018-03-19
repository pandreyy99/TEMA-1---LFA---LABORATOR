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
    friend void citireAutomat(AFN *&t, int &nrStari, int &q0, int *&stFin, int &nrStariFin) ;
    friend bool delta( AFN *t , int nrStari , int *stFin , int nrStariFin , queue < int > &multimeStari , char word[100]) ;
    friend void deltaPrim(AFN *t, int nrStari, queue<int> &multimeStari, char character) ;

protected:

private:
    unsigned int stareInit ;
    unsigned int nrChr ;
    char chr[100] ;
    unsigned int nrStF ;
    vector < list < int > > stareFin ;
};

#endif //LFA_AFN_H
