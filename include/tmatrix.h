// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>


using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz = 0;
    T* pMem = nullptr;
 
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz <= 0) {
          throw out_of_range("should be greater");
      }
      if (sz > MAX_VECTOR_SIZE) {
          throw out_of_range("too large");
          
      }
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
        v.pMem = nullptr;
        v.sz = 0;
    
  }
  ~TDynamicVector()
  {
      delete[] pMem;

  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) {
          return *this;
      }
      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) {
          return *this;
      }
      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      v.sz = 0;
      v.pMem = nullptr;
      return *this;
  }

  size_t size() const noexcept { return sz; }
  
  T* get_pMem() {
      return this->pMem;
  }

  // индексация
  T& operator[](size_t ind) {
      if (ind >= sz) {
          throw out_of_range("Out of range");
      }
      return pMem[ind];
  }

  const T& operator[](size_t ind) const {
      if (ind >= sz) {
          throw out_of_range("Out of range");
      }
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if ((ind >= sz)) {
          throw "Out of range";
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if ((ind >= sz)) {
          throw "Out of range";
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) {
          return false;
      }
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> Sum(this->sz);
      for (int i = 0; i < this->sz; i++) {
          Sum[i] = val + pMem[i];
      }
      return Sum;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector<T> Minus(this->sz);
      for (int i = 0; i < this->sz; i++) {
          Sum[i] = pMem[i] - val;;
      }
      return Minus;
  }

 
  TDynamicVector operator*(double val)
  { 
      TDynamicVector<T> Mul(this->sz);
      for (int i = 0; i < this->sz; i++) {
          Mul[i] = val * pMem[i];
      }
      return Mul;
  }

  

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->sz != v.size()) {
          throw " NOT EQUAL SIZE ";
      }
      TDynamicVector<T> Sum(this->sz);
      for (int i = 0; i < this->sz; i++) {
          Sum[i] = pMem[i] + v[i];
      }
      return Sum;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz != v.size()) {
          throw " NOT EQUAL SIZE ";
      }
      TDynamicVector<T> Minus(this->sz);
      for (int i = 0; i < this->sz; i++) {
          Minus[i] = pMem[i] - v[i];
      }
      return Minus;

  }
  T operator*(const TDynamicVector& v) 
  {
      if (this->sz != v.size()) {
          throw " NOT EQUAL SIZE ";
      }
      T Mul=0;
      for (int i = 0; i < this->sz; i++) {
          Mul += pMem[i] * v[i];
      }
      return Mul;

  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s == 0) {
          throw out_of_range("size should be grater");
      }

      if (s > MAX_MATRIX_SIZE) {
          throw out_of_range("too large");
      }
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  

  TDynamicMatrix(const TDynamicMatrix<T>& m) : TDynamicVector<TDynamicVector<T>>(m)
  {

  }
  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& v) : TDynamicVector<TDynamicVector<T>>(v) {} //Добавил

  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::operator[];

  T& at(size_t ind_str, size_t ind_sto)
  {
      if (ind_str <0 || ind_str > sz - 1 || ind_sto < 0 || ind_sto >sz - ind_str)
      {
          throw "Incorrect index";
      }
      return this->pMem[ind_str][ind_sto];
  }

  const T& at(size_t ind_str, size_t ind_sto) const
  {
      if (ind_str <0 || ind_str > sz - 1 || ind_sto < 0 || ind_sto >sz - ind_str)
      {
          throw "Incorrect index";
      }
      return this->pMem[ind_str][ind_sto];
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this == &m) {
          return true;
      }
      if (sz != m.sz)
          return false;

      for (int i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i])
              return false;
      }

      return true;
  }


  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val) noexcept
  {
      TDynamicMatrix<T> mat(this->sz);
      for (int i = 0; i < this->sz; i++) {
          for (int j = 0; j < this->sz; j++) {
              mat[i] = this->pMem[i][j] * val;
          }
          
      }
      return mat;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.size() != sz) {
          throw "not equal size";
      }
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = 0;
          for (int j = 0; j < sz(); j++) {
              res[i]=res[i]+this->pMem[i][j]*v[j]
          }
          return res;
      }
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) {
      if (sz != m.sz) {
          throw "not equal size";
      }

      TDynamicMatrix<T> res(sz);
          for (size_t i = 0; i < sz; i++) {
              res[i] = pMem[i] + m.pMem[i];
          }
          return res;

      }
  
  TDynamicMatrix operator-(const TDynamicMatrix& m) {
      if (sz != m.sz) {
          throw "not equal size";
      }

      TDynamicMatrix<T> res(sz); 
          for (size_t i = 0; i < sz; i++) {
              res[i] = pMem[i] - m.pMem[i];
          }
          return res;

      }
  
  
  
  TDynamicMatrix operator*(const TDynamicMatrix& m) {
      if (sz != m.sz) {
          throw "not equal size";
      }
      TDynamicMatrix<T> res(sz);
          for (int i = 0; i < sz; i++) {
              for (int j = 0; j < m.sz; j++) {
                  res[i][j] = 0;
                  for (int k = 0; k < sz; k++) {
                      res[i][j] = res[i][j] + pMem[i][k] * m[k][j];
                  }
              }
          }
          return res;
      }
  

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      std::cout << "Enter the matrix";
      for (int i = 0; i < v.sz; i++)
      {
          istr >> v[i];
      }
      return istr;

  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < i; j++)
          {
              ostr << setw(6) << " ";
          }
          for (int j = 0; j < v[i].size(); j++)
          {
              ostr << setw(6) << v[i][j];
          }
          ostr << std::endl;
      }
      return ostr;
  }
};

#endif
