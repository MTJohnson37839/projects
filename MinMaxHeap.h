//Michael Johnson
//
//File: MinMaxHeap.h
//
//email: mjohns12@umbc.edu
//
//CMSC 341
//
//Description: This is the source file for the min max class

#ifndef _MinMaxHeap_H_
#define _MinMaxHeap_H_

template <typename T>
class heapObj {
 public:
  heapObj ( bool ( *compItems ) ( const T& , const T& ) ) ;
  T** heapObjArray ;
  T twinElement ;
  int twinPos ;
  

  bool ( *compItems ) ( const T& , const T& ) ;

};

template <typename T>
class MinMaxHeap
{
 public:

  //CLASS CONSTRUCTOR
  MinMaxHeap ( int capacity ) ;

  //COPY CONSTRUCTOR
  MinMaxHeap ( const MinMaxHeap<T>& other ) ;
  
  //DESTRUCTOR
  ~MinMaxHeap ( ) ;

  //ASSIGNMENT OPERATOR
  const MinMaxHeap<T>& operator= ( const MinMaxHeap <T>& rhs ) ;

  void copy ( MinMaxHeap<T>* mmHeap ) ;

  //SIZE GETTER
  int size ( ) ;

  //DUMP FUNCTION
  void dump ( ) ;

  //FINDTWIN FUNCTION
  int findTwin ( T data , heapObj<T> heap ) ;

  //LOCATEMIN FUNCTION
  void locateMin ( int pos , T& data , int& index ) ;

  //LOCATEMAX FUNCTION
  void locateMax ( int pos , T& data , int& index ) ;

  //INSERT FUNCTION
  void insert ( const T& data ) ;

  //BUBBLEUP FUNCTION
  void bubbleup ( int pos , heapObj<T>& heap) ;

  //TRICKELDOWN
  void trickleDown ( int pos , heapObj<T>& heap ) ;

  //DELETEMAX FUNCTION
  T deleteMax ( ) ;

  //DELETEMINFUNCTION
  T deleteMin ( ) ;

 private :

  int m_capacity ;

  int m_curArrayPos;

  heapObj<T> heapOne ;

  heapObj<T> heapTwo ;

};

template <typename T>
bool isGreaterThan ( const T& first , const T& second )
{
  if (first > second )
    {
      return true ;
    }
  else
    {
      return false ;
    }
}

template <typename T>
bool isLessThan ( const T& first , const T& second )
{
  if (first < second )
    {
      return true ;
    }
  else
    {
      return false ;
    }
}

#include "MinMaxHeap.cpp"

#endif
