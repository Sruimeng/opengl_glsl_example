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

		//��ʽ�Ĺ��캯��
		explicit Matrix(const float data[M*N]) { for (unsigned int i = 0; i < M*N; i++)m_data[i] = data[i]; }
		//ͨ�������ľ��󴴽��¾���
		Matrix(const Matrix& m);
		//��ǰ��������������Ƿ����
		Matrix& operator=(const Matrix& m);
		//���ؾ�����ض�Ԫ��
		float operator[](unsigned int i) { return m_data[i]; }
	private:
		float m_data[M*N];
	};
}