#pragma once
#include "vector.h"

#define MAT_DECL template <unsigned int M, unsigned int N>

namespace toy {

	template <unsigned int TYPE> struct VectorType{};

	template <> struct VectorType<3> { typedef float3 Vector; };
	template <> struct VectorType<4> { typedef float4 Vector; };
	//
	MAT_DECL class Matrix
	{
	public:
		typedef typename VectorType<M>::Vector floatM;//行
		typedef typename VectorType<N>::Vector floatN;//列
		//重载
		inline float operator[](unsigned int i)const { return m_elements[i]; }

		Matrix();

		Matrix(const Matrix& m);
		Matrix(const std::initializer_list<float>& list);
		float* getElements() { return m_elements; }
		void setElements(const float* val) { m_elements = val; }
		//四阶/三阶/矩阵特征化
		static Matrix<M, M> identity();

	private:
		//矩阵的具体数据
		float m_elements[M * N];
	};

	template <unsigned int M, unsigned int N> 
	Matrix<M,N>::Matrix()
	{
	}
	template <unsigned int M, unsigned int N>
	Matrix<M, N>::Matrix(const std::initializer_list<float>& list) {
		m_elements = list;
	}
	template <unsigned int M, unsigned int N>
	Matrix<M, N>::Matrix(const Matrix<M,N>& m)
	{
		for (size_t i = 0; i < M*N; i++)
		{
			m_elements[i] = m[i];
		}
	}

	//新建M阶的单位矩阵
	template <unsigned int M, unsigned int N>
	inline  Matrix<M, M> Matrix<M, N>::identity() {
		/*float temp[M * M];
		for (size_t i = 0; i < M*M; i++)
		{
			temp[i] = 0.0f;
		}
		for (size_t i = 0; i < M * M; i++)
		{
			temp[i * M + i] = 1.0f;
		}*/
		return Matrix<M, M>();
	}


	typedef Matrix<4, 4> Matrix4x4;
}


#undef MAT_DECL