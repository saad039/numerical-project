#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include"util.h"
#include<cassert>

using std::cout;
using std::endl;
using std::string;
using std::cin;

using size_t = uint64_t;
using precision_type = double;
using dynamic_container = std::vector<precision_type>;
using std::begin;
using std::end;

constexpr size_t N = 20;
constexpr size_t dp =3;

int main(int argc, char const *argv[]){

    precision_type s;
    cout<<"Enter s: ";
    cin>> s;
    assert(s>=0 && s<=1);
    const auto denominator = arc_length_a_b_n_2(static_cast<precision_type>(0.0),static_cast<precision_type>(1.0));
    const auto expr1 = sqrt(pow(xPrime_t(static_cast<precision_type>(0.0)),2)+pow(yPrime_t(static_cast<precision_type>(0.0)),2));

    const auto expr2 = [](const auto t){
        return static_cast<precision_type>(16.52625*pow(t,4) - 31.14*pow(t,3) + 12.69*pow(t,2) + 2.88*t + 0.18);
    };
    const auto expr3 = [](const auto t){
        return static_cast<precision_type>(264.42*pow(t,4) - 249.12*pow(t,3) + 50.76*pow(t,2) + 5.76*t + 0.18);
    };

    const auto expr = [=](const auto t,const auto s){
        return static_cast<precision_type>(((0.5*t)/3 * (expr1 + 4*sqrt(expr2(t)) + sqrt(expr3(t)))  ) - (denominator*s));
    };

    const auto t_star = bisection_method(expr,s,dp);

    const auto generator = [s](const auto i,const size_t N){
        return static_cast<precision_type>(i) * (s/N);
    };

    auto get_val = std::bind(generator,std::placeholders::_1,N);
    dynamic_container vals;
    for(size_t i = 0 ; i <= N; ++i)
        vals.push_back(get_val(i));

    const auto total_path_len = arc_length_a_b_n_2(static_cast<precision_type>(0.0),t_star);
    cout<<"Arc length from 0 to t* = "<<t_star<<" = "<<total_path_len<<endl;
    std::ofstream out("points.txt");
    if(out.is_open()){
        std::for_each(begin(vals),end(vals),[&](auto s){
            auto ts = bisection_method(expr,s,dp);
            out<<(ts)<<endl;
            out<<(ts)<<endl;
        });
        out.close();
    }
    auto len = static_cast<precision_type>(0.0);
    for(size_t i = 0 ; i < N ; ++i){
        const auto t = arc_length_a_b_n_2(vals[i],vals[i+1]);
        len+=t;
        cout<<"Interval ("<<vals[i]<<','<<vals[i+1]<<") len = "<<t<<endl;
    }

    cout<<"Arc length by partitioning s into "<<N<<" intervals= "<<len<<endl;
    cout<<"Denomination: "<<denominator<<endl;
    return 0;
}


