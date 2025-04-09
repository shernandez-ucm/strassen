#include <iostream>

#include <Eigen/Dense>
#include <chrono>

using namespace Eigen;
using namespace std;
using namespace std::chrono;

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

int main(int argc, char* argv[]){
  int n=atoi(argv[1]);
  MatrixXd A=MatrixXd::Random(n,n);
  MatrixXd B=MatrixXd::Random(n,n);
  auto start1=high_resolution_clock::now();
  MatrixXd C=A*B;
  auto end1=high_resolution_clock::now();
  auto eigen_time=duration_cast<milliseconds>(end1-start1).count();
  std::cout << "Tiempo Eigen : "  << eigen_time << "[ms]" <<std::endl; 
  auto start2=high_resolution_clock::now();
  MatrixXd C_iterativo=multiply(A,B);
  auto end2=high_resolution_clock::now();
  auto iterative_time=duration_cast<milliseconds>(end2-start2).count();
  std::cout << "Tiempo Iterativo : "  << iterative_time << "[ms]" <<std::endl; 
  std::cout << "Norma C: " << std::endl << C.norm() << std::endl;
  std::cout << "Norma C iterativo: " << std::endl << C_iterativo.norm() << std::endl;
}
