#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

#ifndef LINEARREGRESION
#define LINEARREGRESION

class LinearRegresion{
    public:
        LinearRegresion(){};
        LinearRegresion(vector<double> data, vector<double>range):y{data}, x{range}{};
        double test(double x);
        void setData(vector<double> xs, vector<double> ys){
            x = xs;
            y = ys;
        }
        //returns a vector with values of the function b0 and b1 in that order
        std::vector<double> optimize(); //get a funtion with the error nearest to 0 posible
        double getJ(double b0, double b1); // return the j for the actual variables B0 and B1 (error/cost function)
    private:
        vector<double> y;
        vector<double> x;
        int maxiter = 100; //max iterations default
        double threshold = 0.01; //stop when reach any threshold or accuracy desired
        double rate = 0.02; //default learning rate
        double actualError;
        double l_b0;
        double l_b1;
};

double mean(vector<double> v){
    double sum = 0;
    for(auto i : v)
        sum += i;
    return sum / v.size();
}

double LinearRegresion::getJ(double b0, double b1){
    double totalerror = 0;
    for(int i = 0; i< x.size(); i++){
        double p = b0 + (b1 * x[i]);
        double error = p- y[i];
        totalerror += error;
    }
    return totalerror;
}

std::vector<double> LinearRegresion::optimize(){
    int i = 0; //counter
    double b0 = 0; //start point
    double b1 = 0; //slope
    double xmean = mean(x);
    while(i < maxiter){
        int idx = i % x.size(); 
        actualError = getJ(b0, b1);
        b0 = b0 - (rate * actualError) / x.size();
        b1 = b1 - ((rate * actualError) / x.size()) * xmean;
        if(abs(actualError) <= threshold){
            i = maxiter;
        }
        i++;
    }
    cout << "Optimization finished, the average error is: " << actualError << '\n';
    l_b0 = b0;
    l_b1 = b1;
    vector<double> result = {b0, b1};
    return result;
}

double LinearRegresion::test(double x){
    return l_b0 + (l_b1 * x);
}
#endif


int main(){
    //--------------//
    //usage//
    //-------------//
    vector<double> x = {1,2,3,4,5,5,6,7,8,9,10,11,12,13,14,15};
    vector<double> y = {4,5,2,3,8,9,12,13,20,17,21,23,30,33,36};
    vector<double> result;
    LinearRegresion l;
    l.setData(x, y);
    result = l.optimize();
    cout << result[0] << ' ' << result[1];
}
