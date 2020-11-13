#include <iostream>

#include "camera.h"

namespace toy {
    Camera::Camera()
    {
        m_eye = make_float3(1.0f);
        m_lookat = make_float3(0.0f);
        m_up = make_float3(0.0f, 1.0f, 0.0f);
        m_fovY = 45.f;
        m_aspectRatio = 1.f;
    };


    Camera::Camera(const float3& eye, const float3& lookat, const float3& up, float fovY, float aspectRatio) {
        m_eye = eye;
        m_lookat = lookat;
        m_up = up;
        m_fovY = fovY;
        m_aspectRatio = aspectRatio;
    }

    void Camera::makePerspective(){
        /*auto halfFovY = std::tanf(m_fovY / 2);
        m_perspectiveMatrix.identity();
        auto tempElements = m_perspectiveMatrix.getElements();
        tempElements[0] = 1 / (m_aspectRatio * halfFovY);
        tempElements[5] = 1 / halfFovY;*/
       // tempElements[10] = 
    }

    void Camera::UVNFrame(float3& U, float3& V, float3& N) {
        //获得uvn的各个参数 并求出各个方向上的长度
        N = m_lookat - m_eye; // Do not normalize W -- it implies focal length
        float wlen = length(N);
        U = normalize(cross(N, m_up));
        V = normalize(cross(U, N));
         
        float vlen = wlen * tanf(0.5f * m_fovY * M_PIf / 180.0f);//求视距
        V *= vlen;
        float ulen = vlen * m_aspectRatio;
        U *= ulen;
    }

}
