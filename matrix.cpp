#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <math.h>
using namespace std;
mt19937 mt2(time(0));

class Matrix{
    public:
        int rows;
        int cols;
        vector<vector<double>> data;
        //vector<vector<double>> result;
        Matrix(){
        //this is useless and usefull in the sme time  don't touch it please
        }
        Matrix(int rows1,int cols1,bool dorandom=true){
            rows=rows1;
            cols=cols1;
            data.resize(rows, vector<double>(cols,0));
            if(dorandom){
            randomize();
        }}
        void randomize(int min =0,int max=10){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    double randNum=10;
                    while(randNum<-1 || randNum>1){
                    randNum =(mt2()%(999999999+100000000+1)-100000000);
                    randNum=randNum/100000000;
                }
                    data[i][j]=randNum;
                }}}
        void multiply(double scaler){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    data[i][j]*=scaler;
                }}}
        void multiply(Matrix scaler){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    data[i][j]*=scaler.data[i][j];
                }}}
         void map1( double (*f)(double)){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    double h=data[i][j];
                    data[i][j]=f(h);
                }}}
         static Matrix map1(Matrix a ,double (*f)(double)){
            Matrix result(a.rows,a.cols,false);
            for(int i=0;i<a.rows;i++){
                for(int j=0;j<a.cols;j++){
                    double h=a.data[i][j];
                    result.data[i][j]=f(h);
                }}
                return result;
                }

         void add(Matrix scaler1){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    data[i][j]+=scaler1.data[i][j];
                }}}
         void add(double scaler1){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    data[i][j]+=scaler1;
                }}}
        static Matrix fromarray(double arr[],int size){
            Matrix m(size,1,false);
            //cout<<(sizeof(arr)/sizeof(*arr))<<endl;
            for(int i=0;i<size;i++ ){
                m.data[i][0]=arr[i];
            }
            //m.print();
            return m;
        }
        static Matrix subtract(Matrix scaler1,Matrix scaler2){
            Matrix m(scaler1.rows,scaler1.cols,false);
            //cerr<<"New matrix Created"<<scaler1.rows <<" " <<scaler1.cols <<"\n";
            for(int i=0;i<scaler1.rows;i++){
                for(int j=0;j<scaler1.cols;j++){
                    /*double calc1=scaler1.data[i][j]*100000000;
                    double calc2=scaler2.data[i][j]*100000000;
                    double result=calc1-calc2;
                    result=result/100000000;
                    cerr<<result<<" "<<scaler1.data[i][j]-scaler2.data[i][j]<<endl;*/
                    m.data[i][j]=scaler1.data[i][j]-scaler2.data[i][j];
                   // cerr<<"data at i="<<i<< " j="<<j<<" Written\n";
                }}
            return m;
        }
        static Matrix fromarray(vector<vector<double>> arr){
            Matrix m(arr.size(),arr[0].size(),false);
            //cout<<(sizeof(arr)/sizeof(*arr))<<endl;
            for(int i=0;i<arr.size();i++ ){
                for(int j=0;j<arr[0].size();j++){
                m.data[i][j]=arr[i][j];
            }}
            //m.print();
            return m;
        }
        /*double* toarray(){//It is not working please reapair it
            double arr[rows];
            //cout<<(sizeof(arr)/sizeof(*arr))<<endl;
            for(int i=0;i<rows;i++ ){
                    arr[i]=data[i][0];
                
            }
            //m.print();
            return arr;
        }*/
        static Matrix multiply(Matrix scaler1,Matrix scaler2){
            if(scaler1.cols!=scaler2.rows){
                cerr<<"Error:Get out of here your rows must equal my cols\n";
                scaler1.print();
                scaler2.print();
                return scaler2;
            }
            Matrix result(scaler1.rows,scaler2.cols,false);
             for(int i = 0; i < result.rows; ++i){
                for(int j = 0; j < result.cols; ++j){
                    for(int k = 0; k < scaler1.cols; ++k){
                result.data[i][j] += scaler1.data[i][k] * scaler2.data[k][j];
            }}}
            return result;
        }
        void resize1(int rows1,int cols1, bool dorandom1=true){
            data.resize(rows1, vector<double>(cols1,0));
            rows=rows1;
            cols=cols1;
            if(dorandom1){
                randomize();
            }}
        static Matrix transpose(Matrix a){
            Matrix result(a.cols,a.rows);
            for(int i=0;i<a.rows;i++){
                for(int j=0;j<a.cols;j++){
                    result.data[j][i]=a.data[i][j];
                }}
            return result;
        }
        void print(){
            for(int i=0;i<data.size();i++){
                for(int j=0;j<data[i].size();j++){
                    cout<<data[i][j]<<" ";
                }
            cout<<endl;
            }
            cout<<endl;
        }
};