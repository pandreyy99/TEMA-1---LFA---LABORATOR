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
    StareInit = -1 ;
    nrchr = 0 ;
    nrstf = 0 ;
    chr[nrchr] = '\0' ;
    ///StareFin = new vector < list < int > >;
}

AFN::AFN( const AFN& other )
{
    ///copy ctor
    if(this != &other){
        StareInit = other.StareInit ;
        nrchr = other.nrchr ;
        strcpy(chr , other.chr);
        nrstf = other.nrstf ;
        StareFin.resize(nrstf + 1);
        StareFin = other.StareFin ;
    }
}

AFN::~AFN()
{
    ///dtor
    StareInit = -1 ;
    nrchr = 0 ;
    nrstf = 0 ;
}

void citire_automat( AFN *&T , int &n , int &q , int *&StF , int &nr )
{   int i , j , x ;
    ifstream f( "C:\\Users\\Andrei\\Desktop\\C-lion\\LFA\\cmake-build-debug\\automat.ini" ) ;
    /**cout << "Dati starea initiala : " ;
    cin >> i ;*/
    f >> i ;
    q = i ;
    /**cout << '\n' << "Dati nr de stari finale : " ;
    cin >> i ;*/
    f >> i ;
    nr = i ;
    StF = new int[nr+1] ;
    ///cout << '\n' << "Dati starile finale : " ;
    for( i = 0 ; i < nr ; i++ ){
        /**cout << '\n' << "Stare finala " << i+1 << " = " ;
        cin >> StF[i] ;*/
        f >> StF[i] ;
    }
    /**cout << '\n' << "Dati nr de stari : " ;
    cin >> i ;*/
    f >> i ;
    n = i ;
    T = new AFN[n+1] ;
    for( i = 0 ; i < n ; i++ ){
        T[i].StareInit = i+1 ;
        /**cout << '\n' << "Dati nr de caractere cu care putem pleca din starea " << i+1<<" : " ;
        cin >> T[i].nrchr ;*/
        f >> T[i].nrchr ;
        T[i].StareFin.resize(T[i].nrchr) ;
        ///cout << '\n' << "Dati caracterele : " ;
        for( j = 0 ; j < T[i].nrchr ; j++ ){
            /**cout << '\n' << "Caracterul " << j+1 << " = " ;
            cin >> T[i].chr[j] ;*/
            f >> T[i].chr[j] ;
            /**cout << "Cu acest caracter putem pleca in starile ( Se vor citi stari pana la intalnirea valorii -1 ) : " << '\n' ;
            cin >> x ;*/
            f >> x ;
            while( x!=-1 ){
                T[i].StareFin[j].push_back( x ) ;
                ///cin >> x ;
                f >> x ;
            }
        }
    }
    cout << "Automat citit!" << '\n' ;
}

void delta_prim( AFN *T , int n , queue < int >& MultimeStari , char character )
{
    queue < int > C_temp ;
    while( !MultimeStari.empty() ){
        int x = MultimeStari.front() ;
        MultimeStari.pop() ;
        for( int i = 0 ; i < n ; i++ ){
            if( T[i].StareInit == x ){
                for( int j = 0 ; j < T[i].nrchr ; j++ ){
                    if( T[i].chr[j] == character ){
                        list < int > L ;
                        L = T[i].StareFin[j] ;
                        while( !L.empty() ){
                            int x = L.front() ;
                            C_temp.push( x ) ;
                            L.pop_front() ;
                        }
                    }
                }
            }
        }
    }
    MultimeStari = C_temp ;
}

bool delta( AFN *T , int n , int *StF , int nr , queue < int > &MultimeStari , char word[100])
{
    int i , j , x ;
    if( word[0] == '\0' ){
        for( i = 0 ; i < MultimeStari.size() ; i++ ){
            x = MultimeStari.front() ;
            MultimeStari.pop() ;
            for( j = 0 ; j < nr ; j++ )
                if( x == StF[j] )
                    return true ;
        }
        return false ;
    }
    else {
        if( MultimeStari.empty() )
            return false ;
        else {
            char x = word[0] ;
            strcpy( word , word + 1 ) ;
            delta_prim( T , n , MultimeStari , x ) ;
            return delta( T , n , StF , nr , MultimeStari , word ) ;
        }
    }
}