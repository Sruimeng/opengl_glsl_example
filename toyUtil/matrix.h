#pragma once
#include "vector.h"

#define MAT_DECL template <unsigned int M, unsigned int N>

namespace toyUtil {

	template <unsigned int TYPE> struct VectorType{};

	template <> struct VectorType<3> { typedef float3 Vector; };
	template <> struct VectorType<4> { typedef float4 Vector; };
	//
	MAT_DECL class Matrix
	{
	public:
		typedef typename VectorType<M>::Vector floatM;//��
		typedef typename VectorType<N>::Vector floatN;//��

		Matrix();

		Matrix(const Matrix& m);

		//�Ľ�/����/����������
		static Matrix<M, M> identity();

	private:
		//����ľ�������
		float m_elements[M * N];
	};

	template <unsigned int M, unsigned int N> 
	Matrix<M,N>::Matrix()
	{
	}

	template <unsigned int M, unsigned int N>
	Matrix<M, N>::Matrix(const Matrix<M,N>& m)
	{
		for (size_t i = 0; i < M*N; i++)
		{
			m_elements[i] = m[i];
		}
	}

	//�½�M�׵ĵ�λ����
	template <unsigned int M, unsigned int N>
	inline  Matrix<M, M> Matrix<M, N>::identity() {
		float temp[M * M];
		for (size_t i = 0; i < M*M; i++)
		{
			temp[i] = 0.0f;
		}
		for (size_t i = 0; i < M * M; i++)
		{
			temp[i * M + i] = 1.0f;
		}
		return Matrix<M, M>(temp);
	}


	typedef Matrix<4, 4> Matrix4x4;
}


#undef MAT_DECL