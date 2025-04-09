#include <iostream>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <chrono>
#include <future>

using namespace Eigen;
using namespace std;
using namespace std::chrono;

constexpr int BASE_CASE = 64;

MatrixXd multiply(const MatrixXd& A, const MatrixXd& B){
  int n=A.rows();
  int m=B.cols();
  int v=A.cols();
  MatrixXd C=MatrixXd::Zero(n,m);
  for (int i=0;i<n;i++){
    for (int j=0;j<m;j++){
      for (int k=0;k<v;k++){
	C(i,j)+=A(i,k)*B(k,j);
      }
    }
  }
  return C;
}

MatrixXd recursive_multiply(const MatrixXd& A, const MatrixXd& B){
  int n=A.rows();
  int k=n/2;
  if (n<=BASE_CASE){
    //MatrixXd C(1,1);
    //C(0,0)=A(0,0)*B(0,0);
      MatrixXd C=multiply(A,B); 
    return C;
  }
  MatrixXd A11=A.topLeftCorner(k,k);
  MatrixXd A12=A.topRightCorner(k,k);
  MatrixXd A21=A.bottomLeftCorner(k,k);
  MatrixXd A22=A.bottomRightCorner(k,k);
  MatrixXd B11=B.topLeftCorner(k,k);
  MatrixXd B12=B.topRightCorner(k,k);
  MatrixXd B21=B.bottomLeftCorner(k,k);
  MatrixXd B22=B.bottomRightCorner(k,k);
  MatrixXd C11=recursive_multiply(A11,B11)+recursive_multiply(A12,B21);
  MatrixXd C12=recursive_multiply(A11,B12)+recursive_multiply(A12,B22);
  MatrixXd C21=recursive_multiply(A21,B11)+recursive_multiply(A22,B21);
  MatrixXd C22=recursive_multiply(A21,B12)+recursive_multiply(A22,B22);
  MatrixXd C=MatrixXd::Zero(n,n);
  C.topLeftCorner(k,k)=C11;
  C.topRightCorner(k,k)=C12;
  C.bottomLeftCorner(k,k)=C21;
  C.bottomRightCorner(k,k)=C22;
  return C;
}

MatrixXd parallel_recursive_multiply(const MatrixXd& A, const MatrixXd& B){
    int n=A.rows();
    int k=n/2;
    if (n==1){
      MatrixXd C(1,1);
      C(0,0)=A(0,0)*B(0,0);
      return C;
    }
    MatrixXd A11=A.topLeftCorner(k,k);
    MatrixXd A12=A.topRightCorner(k,k);
    MatrixXd A21=A.bottomLeftCorner(k,k);
    MatrixXd A22=A.bottomRightCorner(k,k);
    MatrixXd B11=B.topLeftCorner(k,k);
    MatrixXd B12=B.topRightCorner(k,k);
    MatrixXd B21=B.bottomLeftCorner(k,k);
    MatrixXd B22=B.bottomRightCorner(k,k);
  
    auto M1 = async(&recursive_multiply, A11, B11);
    auto M2 = async(&recursive_multiply, A12, B21);
    auto M3 = async(&recursive_multiply, A11, B12);
    auto M4 = async(&recursive_multiply, A12, B22);
    auto M5 = async(&recursive_multiply, A21, B11);
    auto M6 = async(&recursive_multiply, A22, B21);
    auto M7 = async(&recursive_multiply, A21, B11);
    auto M8 = async(&recursive_multiply, A22, B22);
    
    MatrixXd m1 = M1.get();
    MatrixXd m2 = M2.get();
    MatrixXd m3 = M3.get();
    MatrixXd m4 = M4.get();
    MatrixXd m5 = M5.get();
    MatrixXd m6 = M6.get();
    MatrixXd m7 = M7.get();
    MatrixXd m8 = M8.get();
  
    MatrixXd C11=m1+m2;
    MatrixXd C12=m3+m4;
    MatrixXd C21=m5+m6;
    MatrixXd C22=m7+m8;
    MatrixXd C=MatrixXd::Zero(n,n);
    C.topLeftCorner(k,k)=C11;
    C.topRightCorner(k,k)=C12;
    C.bottomLeftCorner(k,k)=C21;
    C.bottomRightCorner(k,k)=C22;
    return C;
  }

  



int main(int argc, char* argv[]){
  int n=atoi(argv[1]);
  MatrixXd A=MatrixXd::Random(n,n);
  MatrixXd B=MatrixXd::Random(n,n);
  auto start1=high_resolution_clock::now();
  MatrixXd C=A*B;
  auto end1=high_resolution_clock::now();
  auto eigen_time=duration_cast<milliseconds>(end1-start1).count();
  std::cout << "Tiempo Eigen : "  << eigen_time << "[ms]" << std::endl;
  auto start2=high_resolution_clock::now();
  MatrixXd C_recursivo=parallel_recursive_multiply(A,B);
  auto end2=high_resolution_clock::now();
  auto recursive_time=duration_cast<milliseconds>(end2-start2).count();
  std::cout << "Tiempo Recursivo : "  << recursive_time << "[ms]" << endl;
  std::cout << "Norma C: " << std::endl << C.norm() << std::endl;
  std::cout << "Norma C recursivo: " << std::endl << C_recursivo.norm() <<endl;
}
