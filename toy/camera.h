#pragma once
#include "vector.h"
#include "matrix.h"
namespace toy {
    class  Camera
    {
    public:
        //默认参数的相机
        Camera();
        Camera(const float3& eye, const float3& lookat, const float3& up, float fovY, float aspectRatio);

        //set and get
        inline const float3& getEye() const { return m_eye; }
        inline void setEye(const float3& val) { m_eye = val; }
        inline const float3& getLookat() const { return m_lookat; }
        inline void setLookat(const float3& val) { m_lookat = val; }
        inline const float3& getUp() const { return m_up; }
        inline void setUp(const float3& val) { m_up = val; }
        inline const float& getFovY() const { return m_fovY; }
        inline void setFovY(const float& val) { m_fovY = val; }
        inline const float& getAspectRatio() const { return m_aspectRatio; }
        inline void setAspectRatio(const float& val) { m_aspectRatio = val; }
        inline float3 getDirection() const { return normalize(m_lookat - m_eye); }
        inline void setDirection(const float3& dir) { m_lookat = m_eye + dir*length(m_lookat - m_eye); };
        inline const Matrix4x4& getPerspective() const { return m_perspectiveMatrix; }
        void UVNFrame(float3& U, float3& V, float3& N);

        void makePerspective();
    private:
        float3 m_eye;
        float3 m_lookat;
        float3 m_up;
        float m_fovY;
        float m_aspectRatio;
       
        Matrix4x4 m_perspectiveMatrix;
    };

    
}
