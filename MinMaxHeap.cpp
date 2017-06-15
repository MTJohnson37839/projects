//Michael Johnson
//
//File: MinMaxHeap.h
//
//email: mjohns12@umbc.edu
//
//CMSC 341
//
//Description: This is the source file for the min max class

#ifndef _MinMaxHeap_CPP_
#define _MinMaxHeap_CPP_


#include "MinMaxHeap.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//################//
//PUBLIC FUNCTIONS//
//################//

//HEAP CLASS CONSTRUCTOR

template <typename T>
heapObj<T>::heapObj ( bool ( *compareItems ) ( const T& , const T& ) ) 
{ 
  twinPos = 0 ; 
  compItems = compareItems ;
}


//CLASS CONSTRUCTOR

template <typename T> 
MinMaxHeap<T>::MinMaxHeap ( int capacity ) :
  heapOne( &isGreaterThan ),
  heapTwo( &isLessThan )
{
  heapOne.heapObjArray = new T* [ capacity ] ;
  heapTwo.heapObjArray = new T* [ capacity ] ;
  m_curArrayPos = 0 ;
  m_capacity = capacity ;
}

//COPY CONSTRUCTOR}

template <typename T>
MinMaxHeap<T>::MinMaxHeap ( const MinMaxHeap<T>& other ) : heapOne ( &isGreaterThan ),
							   heapTwo ( &isLessThan ) 
{ 
  m_capacity = other.m_capacity ;
  m_curArrayPos = 0 ;

  heapOne.heapObjArray = new T* [ m_capacity ] ;
  heapTwo.heapObjArray = new T* [ m_capacity ] ;

  for ( int i = 0 ; i < other.m_curArrayPos ; i++ )
    {
      insert ( *other.heapOne.heapObjArray [ i ] ) ;
    }

  heapOne.twinPos = findTwin ( *heapTwo.heapObjArray [ 0 ] , heapOne ) ;
  heapTwo.twinPos = findTwin ( *heapOne.heapObjArray [ 0 ] , heapTwo ) ;
}

//DESTRUCTOR
  
template <typename T>
MinMaxHeap<T>::~MinMaxHeap ( )
{
  
  for ( int i = m_curArrayPos ; i >= 0 ; i-- )
    {
      delete heapOne.heapObjArray [ i ];
      heapOne.heapObjArray [ i ] = NULL ;
    }
  
  delete[] heapOne.heapObjArray ;
  delete[] heapTwo.heapObjArray ;
  
}
 
//OVERLOADED ASSIGNMENT OPERATOR

template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator= ( const MinMaxHeap<T>& rhs )
{
  if (this == &rhs )
    {
      return *this ;
    }
  
  cout << "MCUR = " << m_curArrayPos << endl;  

  for ( int i = m_curArrayPos - 1  ; i >= 0 ; i-- )
    {
      delete heapOne.heapObjArray [ i ];
      heapOne.heapObjArray [ i ] = NULL ;
      heapTwo.heapObjArray [ i ] = NULL ;
    }
  
  delete[] heapOne.heapObjArray ;
  delete[] heapTwo.heapObjArray ;
  
  m_capacity = rhs.m_capacity ;
  cout << "MCAP " << rhs.heapOne.twinPos  << endl ;
  m_curArrayPos = 0 ;  

  heapOne.heapObjArray = new T* [ m_capacity ] ;
  heapTwo.heapObjArray = new T* [ m_capacity ] ;
  
  while ( m_curArrayPos < rhs.m_curArrayPos  )
    {
      insert ( *rhs.heapOne.heapObjArray [ m_curArrayPos ] ) ;
    }

  
  heapOne.twinPos = findTwin ( *heapTwo.heapObjArray [ 0 ] , heapOne ) ;
  heapTwo.twinPos = findTwin ( *heapOne.heapObjArray [ 0 ] , heapTwo ) ;
    
  return *this ;
}

//COPY MAKER

template <typename T>
void MinMaxHeap<T>::copy ( MinMaxHeap<T>* mmHeap )
{
  heapOne = new T* [ m_capacity ] ;
  heapTwo = new T* [ m_capacity ] ;
  for ( int i = 0 ; i < m_curArrayPos ; i++ ) 
    {
      insert ( *mmHeap->heapOne.heapObjArray [ i ] ) ;
    }
} 

//SIZE GETTER FUNCTION

template <typename T>
int MinMaxHeap<T>::size ( ) 
{
  return m_curArrayPos ;
}

//DUMP FUNCTION

template <typename T>
void MinMaxHeap<T>::dump ( ) 
{
  cout << "-------MIN HEAP-------" << endl ;
  for ( int i = 0 ; i < m_curArrayPos ; i++ )
    {
      cout << "["<< i+1 << "]" 
	   << "(" << *heapOne.heapObjArray [ i ] << " , " 
	   << findTwin ( *heapOne.heapObjArray [ i ] , heapTwo ) + 1
	   << ")" << endl ;
    }
 
  cout << "-------MAX HEAP-------" << endl ;  
  for ( int i = 0 ; i < m_curArrayPos ; i++ )
    {
      cout << "["<< i+1 << "]"
           << "(" << *heapTwo.heapObjArray [ i ] << " , "
           << findTwin ( *heapTwo.heapObjArray [ i ] , heapOne ) + 1
           << ")" << endl ;
    }
  cout << endl ;
  
}

//FINDTWIN FUNCTION
template <typename T>
int MinMaxHeap<T>::findTwin ( T data , heapObj<T> heap )
{
  int index = 0 ;
  while ( data != *heap.heapObjArray [ index ] && index < m_curArrayPos ){ index++ ;}
  if ( data != *heap.heapObjArray [ index ] ) 
    { 
      throw out_of_range ( "INDEX OUT OF RANGE : ELEMENT NOT FOUND . . . \n" ) ; 
    }
  return index ;
}

//LOCATEMIN FUNCTION
template <typename T>
void MinMaxHeap<T>::locateMin ( int pos , T& data , int& index )
{
  data = *heapOne.heapObjArray [ pos - 1 ] ;
  index = findTwin ( data , heapTwo ) + 1 ;
}

//LOCATEMAX FUNCTION
template <typename T>
void MinMaxHeap<T>::locateMax ( int pos , T& data , int& index )
{
  data = *heapTwo.heapObjArray [ pos - 1 ] ;
  index = findTwin ( data , heapOne ) + 1 ;
}


//INSERT FUNCTION

template <typename T>
void MinMaxHeap<T>::insert ( const T& data ) 
{
  if ( m_curArrayPos < m_capacity ) 
    {
      T castData = data ;
      T* ptrData = new T ;
      *ptrData = castData ;
      
      heapOne.heapObjArray [ m_curArrayPos ] = ptrData ;
      heapTwo.heapObjArray [ m_curArrayPos ] = ptrData ;
      m_curArrayPos++ ;

      bubbleup ( m_curArrayPos - 1 , heapOne ) ;
      bubbleup ( m_curArrayPos - 1 , heapTwo ) ;

    }
  else
    {
      throw out_of_range ( "INDEX IS FULL : VOIDING INSERTION . . . \n" );
    }
}

//BUBBLEUP FUNCTION

template <typename T>
void MinMaxHeap<T>::bubbleup ( int pos , heapObj<T>& heap )
{
  if ( pos == 0 )
    {
      return ;
    }

  int parentPos = ( pos - 1 ) / 2 ;

  if ( heap.compItems ( *heap.heapObjArray [ parentPos ] , *heap.heapObjArray [ pos ] ) )
    {
      T* tempVal = heap.heapObjArray [ parentPos ] ;
      heap.heapObjArray [ parentPos ] = heap.heapObjArray [ pos ] ;
      heap.heapObjArray [ pos ] = tempVal ;
    
      bubbleup ( parentPos , heap ) ;
    }
}


//COMPARE CHILDREN THEN COMPARE PARENTS TO FIND SWAP

template <typename T>
void MinMaxHeap<T>::trickleDown ( int pos , heapObj<T>& heap )
{

  bubbleup ( pos ,  heap ) ;

  int childPosLeft = (2 * pos) + 1 ;
  int childPosRight = (2 * pos) + 2 ;
  int childToSwap = -1 ;
 
  if ( childPosLeft < m_curArrayPos && childPosRight < m_curArrayPos ) 
  {
    if ( heap.compItems ( *heap.heapObjArray [ childPosLeft ] , *heap.heapObjArray [ childPosRight ] ) )
      {
	childToSwap = childPosRight ;
      }
    else
      {
	childToSwap = childPosLeft ;
      }
  }
  
  else if ( childPosLeft < m_curArrayPos && childPosRight >= m_curArrayPos )
    {
      childToSwap = childPosLeft ;
    }
    
  if ( childToSwap != -1  &&  heap.compItems ( *heap.heapObjArray [ pos ] , *heap.heapObjArray [ childToSwap ] ))
      
      {
	T* ptrRoot = heap.heapObjArray [ pos ] ;
	heap.heapObjArray [ pos ] = heap.heapObjArray [ childToSwap ] ;
	heap.heapObjArray [ childToSwap ] = ptrRoot ;
	trickleDown ( childToSwap , heap ) ;
	return ;
      }
    
  else
    {
      return ;
    }
}

//DELETE MAX FUNCTION

template <typename T>
T MinMaxHeap<T>::deleteMax ( )
{

  if ( heapTwo.heapObjArray [ 0 ] )
    {

      heapOne.twinPos = findTwin ( *heapTwo.heapObjArray [ 0 ] , heapOne ) ;

      T* ptrRoot = heapTwo.heapObjArray [ 0 ] ;
      T returnVal = *heapTwo.heapObjArray [ 0 ] ;

      heapTwo.heapObjArray [ 0 ] = heapTwo.heapObjArray [ m_curArrayPos - 1 ] ;
      heapOne.heapObjArray [ heapOne.twinPos ] = heapOne.heapObjArray [ m_curArrayPos - 1 ] ;
      heapTwo.heapObjArray [ m_curArrayPos - 1 ] = NULL ;
      heapOne.heapObjArray [ m_curArrayPos - 1 ] = NULL ;
      delete ptrRoot ;
      --m_curArrayPos ;

      trickleDown ( 0 , heapTwo ) ;
    
      if ( heapOne.twinPos != m_curArrayPos )
	{
	  trickleDown ( heapOne.twinPos , heapOne ) ;
	}
      return returnVal ;
    }
  else
    {
      throw out_of_range ( "LIST IS EMPTY " );
    }
}
    

//DELETE MIN FUNCTION

template <typename T>
T MinMaxHeap<T>::deleteMin ( )
{

 if ( heapOne.heapObjArray [ 0 ] )
    {
      heapTwo.twinPos = findTwin ( *heapOne.heapObjArray [ 0 ] , heapTwo ) ;

      T* ptrRoot = heapOne.heapObjArray [ 0 ] ;
      T returnVal = *heapOne.heapObjArray [ 0 ] ;

      heapOne.heapObjArray [ 0 ] = heapOne.heapObjArray [ m_curArrayPos - 1 ] ;      
      heapTwo.heapObjArray [ heapTwo.twinPos ] = heapTwo.heapObjArray [ m_curArrayPos - 1 ] ;
      heapOne.heapObjArray [ m_curArrayPos - 1 ] = NULL ;
      heapTwo.heapObjArray [ m_curArrayPos - 1 ] = NULL ;
      delete ptrRoot ;
      --m_curArrayPos ;

      trickleDown ( 0 , heapOne ) ;
 
      if ( heapTwo.twinPos != m_curArrayPos )
        {
	  trickleDown ( heapTwo.twinPos , heapTwo ) ;
	}

      return returnVal ;
    }
  else
    {
      throw out_of_range ( "LIST IS EMPTY " );
    }
}

#endif
