#pragma once
#include "vector.h"
namespace toy {
    class  Camera
    {
    public:
        //Ĭ�ϲ��������
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
