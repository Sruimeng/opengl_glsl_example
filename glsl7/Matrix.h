#pragma once
#include "VectorType.h"
namespace toy {

	template <int dim> struct VectorDim { };
	template <> struct VectorDim<3> { typedef float3 VectorType; };
	template <> struct VectorDim<4> { typedef float4 VectorType; };

	template <unsigned int M, unsigned int N>
	class Matrix
	{
	public:
		typedef typename VectorDim<N>::VectorType  floatN; /// A row of the matrix
		typedef typename VectorDim<M>::VectorType  floatM; /// A column of the matrix

		Matrix();

		//显式的构造函数
		explicit Matrix(const float data[M*N]) { for (unsigned int i = 0; i < M*N; i++)m_data[i] = data[i]; }
		//通过其他的矩阵创建新矩阵
		Matrix(const Matrix& m);
		//当前矩阵和其他矩阵是否相等
		Matrix& operator=(const Matrix& m);
		//返回矩阵的特定元素
		float operator[](unsigned int i) { return m_data[i]; }
	private:
		float m_data[M*N];
	};
}