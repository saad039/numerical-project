#pragma once
#include<iostream>
#include<cmath>
#include<type_traits>
#include<vector>
#include<functional>


template<typename precision_type,
   typename = std::enable_if_t<std::is_floating_point_v<precision_type>>>
inline auto x_t (precision_type t) ->precision_type{
    return 0.5 + 0.3*t + 3.9*t*t -4.7*t*t*t; 
}

template<typename precision_type,
   typename = std::enable_if_t<std::is_floating_point_v<precision_type>>>
inline auto y_t (precision_type t) ->precision_type{
    return 1.5 + 0.3*t + 0.9*t*t - 2.7*t*t*t;
}

template<typename precision_type,
   typename = std::enable_if_t<std::is_floating_point_v<precision_type>>>
inline auto xPrime_t (precision_type t) ->precision_type{
    return 0.3 + 7.8*t - 14.1*t*t;
}

template<typename precision_type,
   typename = std::enable_if_t<std::is_floating_point_v<precision_type>>>
inline auto yPrime_t (precision_type t) -> precision_type{
    return 0.3 + 1.8*t - 8.1*t*t;
}

enum class result_t{
    EQUAL,
    LESS,
    GREATER
};

template<typename precision_type, 
    typename size_t = uint64_t,
   typename = std::enable_if_t<std::is_floating_point_v<precision_type>>>
auto cmp_floats(const precision_type a, const precision_type b, const size_t dp) ->result_t{
    const auto factor = pow(10,dp);
    const auto a1 = static_cast<size_t>(a*factor);
    const auto b1 = static_cast<size_t>(b*factor);
    if (a1 == b1)
        return result_t::EQUAL;
    else if (a1 > b1)
        return result_t::GREATER;
    return result_t::LESS;
}

namespace std{
    template <typename type, typename = std::enable_if_t<std::is_arithmetic_v<type>>>
    auto is_negative(const type t) ->bool{
        t < 0 ? true : false; 
    } 
}
template<typename equation, typename size_t = uint64_t,
    typename precision_type, typename = std::enable_if_t<std::is_floating_point_v<precision_type>>> 
static auto bisection_method(equation eq,const precision_type s ,const size_t dp) ->precision_type   {
   auto a = static_cast<precision_type> (10.0);           //initially positive
   auto b = static_cast<precision_type> (-10.0);          //initially negative 
   decltype(b) old = static_cast<decltype(a)>(0xFFFFFFFF);
   while(true){

       const auto expr = std::bind(eq,std::placeholders::_1,s);
       const auto f_a = expr(a);
       const auto f_b = expr(b);

       const auto p = (a+b)/2;
       const auto f_p = expr(p);
    //    std::cout<<"a: "<<a<<"\tb: "<<b<<"\tp: "<<p<<"\tf(p): "<<f_p<<std::endl;
       if (f_p == 0.0 || cmp_floats(f_p,old,dp) == result_t::EQUAL)       return p;
       if (f_a*f_p > 0) a=p;
       else b = p;
       old = f_p;       
   }
}
 
template<typename precision_type,
   typename = std::enable_if_t<std::is_floating_point_v<precision_type>>>
static auto arc_length_a_b_n_2(const precision_type a, const precision_type b) ->precision_type{
    const auto h = (b-a)/2.0;
    return (h/3.0) * (
        sqrt(pow(xPrime_t(0.0),2) + pow(yPrime_t(0.0),2) )                +
        4 * sqrt(pow(xPrime_t(0.5),2) + pow(yPrime_t(0.5),2) )            +
        sqrt(pow(xPrime_t(1.0),2) + pow(yPrime_t(1.0),2) )
    );
}
