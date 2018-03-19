//
// Created by Andrei on 16-Mar-18.
//

#include <C:\Users\Andrei\Desktop\C-lion\LFA\cmake-build-debug\AFN.h>

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <cstring>
#include <utility>

using namespace std;

AFN::AFN()
{
    ///ctor
    stareInit = -1 ;
    nrChr = 0 ;
    nrStF = 0 ;
    chr[nrChr] = '\0' ;
    ///StareFin = new vector < list < int > >;
}

AFN::AFN( const AFN& other )
{
    ///copy ctor
    if(this != &other){
        stareInit = other.stareInit ;
        nrChr = other.nrChr ;
        strcpy(chr , other.chr);
        nrStF = other.nrStF ;
        stareFin.resize(nrStF + 1);
        stareFin = other.stareFin ;
    }
}

AFN::~AFN()
{
    ///dtor
    stareInit = -1 ;
    nrChr = 0 ;
    nrStF = 0 ;
}

/**
 *
 * @param t e un vector de tip AFN ce contine date despre toate tranzitiile posibile ale automatului
 * @param nrStari = numarul total de stari
 * @param q0 = starea initiala
 * @param stFin = vector in care se retin starile finale
 * @param nrStariFin  = numarul de stari finale
 */

void citireAutomat(AFN *&t, int &nrStari, int &q0, int *&stFin, int &nrStariFin)
{
    int indexi , indexj , aux ;
    ifstream f( "automat.ini" ) ;
    /** Citim starea initiala */
    f >> indexi ;
    q0 = indexi ;
    /** Citim nr de stari finale */
    f >> indexi ;
    nrStariFin = indexi ;
    stFin = new int[nrStariFin+1] ;
    /** Citim starile finale */
    for( indexi = 0 ; indexi < nrStariFin ; indexi++ )
        f >> stFin[indexi] ;
    /** Citim nr total de stari */
    f >> indexi ;
    nrStari = indexi ;
    t = new AFN[nrStari+1] ;
    for( indexi = 0 ; indexi < nrStari ; indexi++ ){
        t[indexi].stareInit = indexi+1 ;
        /**Citim nr de caractere cu care putem pleca din starea i+1 */
        f >> t[indexi].nrChr ;
        t[indexi].stareFin.resize(t[indexi].nrChr) ;
        /** Citim caracterele cu care putem realiza tranzitii */
        for( indexj = 0 ; indexj < t[indexi].nrChr ; indexj++ ){
            /** Citim caracterul j+1 pentru starea curenta */
            f >> t[indexi].chr[indexj] ;
            /** Citim starile in care putem ajunge cu caracterul curent , pana la intalnirea valorii -1 */
            f >> aux ;
            while( aux!=-1 ){
                t[indexi].stareFin[indexj].push_back( aux ) ;
                f >> aux ;
            }
        }
    }
    cout << "Automat citit!" << '\n' ;
}

/**
 *
 * @param t = vectorul de tip AFN ce retine date despre tranzitiile automatului
 * @param nrStari = numarul de stari
 * @param multimeStari = multimea de stari din care vom pleca cu tranzitii d*(q,character) . unde q apartine multimestari
 * @param character = caracterul curent ce se aplica functiei delta *(d*)
 */
void deltaPrim(AFN *t, int nrStari, queue<int> &multimeStari, char character)
{
    queue < int > temp ;
    while( !multimeStari.empty() ){
        int aux = multimeStari.front() ;
        multimeStari.pop() ;
        for( int indexi = 0 ; indexi < nrStari ; indexi++ ){
            if( t[indexi].stareInit == aux ){
                for( int j = 0 ; j < t[indexi].nrChr ; j++ ){
                    if( t[indexi].chr[j] == character ){
                        list < int > copie ;
                        copie = t[indexi].stareFin[j] ;
                        while( !copie.empty() ){
                            int x = copie.front() ;
                            temp.push( x ) ;
                            copie.pop_front() ;
                        }
                    }
                }
            }
        }
    }
    multimeStari = temp ;
}

/**
 *
 * @param t = vector de tip AFN ce retine date despre toate tranzitiile posibile in cadrul automatului
 * @param nrStari = numarul total de stari
 * @param stFin = vectorul de stari finale
 * @param nrStariFin = numarul de stari finale
 * @param multimeStari = multimea de stari pe care aplicam functia delta(d)
 * @param word = cuvantul introdus in automat si pe care aplicam functia delta(d)
 * @return true , daca cuvantul este acceptat de automat , false astfel
 */
bool delta( AFN *t , int nrStari , int *stFin , int nrStariFin , queue < int >& multimeStari , char word[100])
{
    int indexi , indexj , aux ;
    if( word[0] == '\0' ){
        for( indexi = 0 ; indexi <= multimeStari.size() ; indexi++ ){
            aux = multimeStari.front() ;
            multimeStari.pop() ;
            for( indexj = 0 ; indexj < nrStariFin ; indexj++ )
                if( aux == stFin[indexj] )
                    return true ;
        }
        return false ;
    }
    else {
        if( multimeStari.empty() )
            return false ;
        else {
            char auxiliar = word[0] ;
            strcpy( word , word + 1 ) ;
            deltaPrim(t, nrStari, multimeStari, auxiliar) ;
            return delta( t , nrStari , stFin , nrStariFin , multimeStari , word ) ;
        }
    }
}