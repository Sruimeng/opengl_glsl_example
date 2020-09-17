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

    void Camera::UVNFrame(float3& U, float3& V, float3& N) {
        N = m_lookat - m_eye; // Do not normalize W -- it implies focal length
        float wlen = length(N);
        U = normalize(cross(N, m_up));
        V = normalize(cross(U, N));

        float vlen = wlen * tanf(0.5f * m_fovY * M_PIf / 180.0f);//«Û ”æ‡
        V *= vlen;
        float ulen = vlen * m_aspectRatio;
        U *= ulen;
    }

}
