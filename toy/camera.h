#pragma once
#include "vector.h"
namespace toy {
    class  Camera
    {
    public:
        //默认参数的相机
        Camera();
        Camera(const float3& eye, const float3& lookat, const float3& up, float fovY, float aspectRatio);
        void UVWFrame(float3& U, float3& V, float3& W);
    private:
        float3 m_eye;
        float3 m_lookat;
        float3 m_up;
        float m_fovY;
        float m_aspectRatio;
    };

    Camera::Camera()
    {
        m_eye = make_float3(1.0f);
        m_lookat = make_float3(0.0f);
        m_up = make_float3(0.0f, 1.0f, 0.0f);
        m_fovY=45.f;
        m_aspectRatio=1.f;
    };
    Camera::Camera(const float3& eye, const float3& lookat, const float3& up, float fovY, float aspectRatio) {
        m_eye = eye;
        m_lookat = lookat;
        m_up = up;
        m_fovY = fovY;
        m_aspectRatio = aspectRatio;
    }

    void Camera::UVWFrame(float3& U, float3& V, float3& W) {
        W = m_lookat - m_eye; // Do not normalize W -- it implies focal length
        float wlen = length(W);
        U = normalize(cross(W, m_up));
        V = normalize(cross(U, W));

        float vlen = wlen * tanf(0.5f * m_fovY * M_PIf / 180.0f);
        V *= vlen;
        float ulen = vlen * m_aspectRatio;
        U *= ulen;
    }
}
