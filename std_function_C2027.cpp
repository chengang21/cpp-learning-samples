#include "stdafx.h"

#include <string>
#include <iostream> 
#include <functional>  

class Vector3
{
   Vector3(){}
   ~Vector3(){}
};

class Actor
{
public:
   Actor( );
   virtual ~Actor();

   void setPosition(double x, double y, double z) { }
   void setPosition(const Vector3& position) { }
};

typedef void Proxy_Function;

/*1*/ template <typename T>
Proxy_Function fun(T t) { std::cout << "fun(T t)" << std::endl; };

/*2*/ template <typename T> // 第一个的特化
Proxy_Function fun(const std::function< T > &f) { std::cout << "fun(const std::function< T > &f)" << std::endl; };

/*3*/ template <typename T, typename Q>
Proxy_Function fun(T t, const Q &q) { std::cout << "fun(T t, const Q &q)" << std::endl; };

/*4*/ template <typename T, typename Q, typename R>
Proxy_Function fun(T t, const Q &q, const R &r) { std::cout << "fun(T t, const Q &q, const R &r)" << std::endl; };

void foo() {};

// https://stackoverflow.com/questions/25488297/binding-functions-with-multiple-arguments-results-in-c2027

int main()
{
   fun(foo);  // OK; output: fun(T t)
   // fun(&Actor::setPosition);  // error C2672: “fun”: 未找到匹配的重载函数 //CG   类成员函数 不匹配 简单类型 T
   /*
      error C2780 : “Proxy_Function fun(T, const Q &)” : 应输入 2 个参数，却提供了 1 个
      error C2784 : “Proxy_Function fun(const std::function<_Fty> &)” : 未能从“void(__cdecl Actor::*)(const Vector3 &)”为“const std::function<_Fty>”推导 模板 参数
      error C2784 : “Proxy_Function fun(const std::function<_Fty> &)” : 未能从“void(__cdecl Actor::*)(double, double, double)”为“const std::function<_Fty>”推导 模板 参数
      error C2784 : “Proxy_Function fun(const std::function<_Fty> &)” : 未能从“overloaded - function”为“const std::function<_Fty> &”推导 模板 参数
      error C2783 : “Proxy_Function fun(T)” : 未能为“T”推导 模板 参数
   */

   // fun<void (Actor::*)(const Vector3&)>(&Actor::setPosition);
   /*
   functional(461): error C2027: 使用了未定义类型“std::_Get_function_impl<_Fty>”
             with
             [
                 _Fty=void (__cdecl Actor::* )(const Vector3 &)
             ]
     note: 参见对正在编译的类 模板 实例化“std::function<void (__cdecl Actor::* )(const Vector3 &)>”的引用

     see reference to class template instantiation 'std::function<void (__thiscall Actor::* )(const Vector3 &)>' being compiled 

   */

   fun((void(Actor::*)(const Vector3&))&Actor::setPosition); //  OK; output: fun(T t)

   fun(static_cast<void (Actor::*)(double, double, double)>( &Actor::setPosition ));  //  OK; output: fun(T t)

   std::function< void(void)> functor = foo;
   fun(functor); //  OK; output: fun(const std::function< T > &f)

   char tmp;
   std::cin >> tmp;
   return 0;
}
