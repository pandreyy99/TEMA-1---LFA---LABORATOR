#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <cstring>
#include <utility>
#include <C:\Users\Andrei\Desktop\C-lion\LFA\cmake-build-debug\AFN.h>

using namespace std;

int main()
{
    int i , n , q , nr , *StF , j ;
    char word[100] ;
    queue < int > MultimeStari ;
    AFN *T ;

    citire_automat( T , n , q , StF , nr ) ;

    /**for( i = 0 ; i < n ; i++ ){
      cout << '\n' << "Starea " << i+1 << " : " ;
      for( j = 0 ; j < T[i].nrchr ; j++ ){
        cout << '\n' << "Starile in care putem ajunge cu caracterul " << T[0].chr[j] << " sunt : " ;
          while( !T[i].StareFin[j].empty() ){
            cout << " " << T[i].StareFin[j].front() ;
            T[i].StareFin[j].pop_front() ;
          }
      }
      cout << '\n' ;
    }*/

    MultimeStari.push( q ) ;
    cout << "Dati un cuvant : ";
    cin >> word ;
    if( delta( T , n , StF , nr , MultimeStari , word ) == 1 ) cout << '\n' << "Cuvant acceptat!" << '\n' ;
    else cout << '\n' << "Cuvant neacceptat!" << '\n' ;
    return 0;
}
