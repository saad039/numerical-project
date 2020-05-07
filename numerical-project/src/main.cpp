#include<iostream>
#include"xtensor/xarray.hpp"


namespace np = xt;

using std::cout;
using std::endl;
using std::string;

int main(int argc, char const *argv[])
{
    
    np::xarray<double> arr {{1,2,3,0},{4,5,6,0},{7,8,9,0}};

    for(auto& e : arr){
        cout<<e<<',';
    }

    
    return 0;
}
