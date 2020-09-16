#pragma once
#include "vector.h"
namespace toy {
    class  Camera
    {
    public:
        //默认参数的相机
        Camera();
        Camera(const float3& eye, const float3& lookat, const float3& up, float fovY, float aspectRatio);
        void UVNFrame(float3& U, float3& V, float3& N);
    private:
        float3 m_eye;
        float3 m_lookat;
        float3 m_up;
        float m_fovY;
        float m_aspectRatio;
    };

    
}
