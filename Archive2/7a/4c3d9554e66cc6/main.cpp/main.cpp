    class Camera {
    public:
        Camera(Vec3<double> eyePos, Vec3<double> lookAt, Vec3<double> up, float viewPlaneDistance) restrict(cpu, amp) :
            eyePos{eyePos},
            lookAt{lookAt},
            up{up},
            viewPlaneDistance{viewPlaneDistance} {
            initializeCameraCoordSystem();
        }

        void initializeCameraCoordSystem() restrict(cpu, amp) {
            cameraZ = eyePos - lookAt;
            cameraZ.normalize();
            cameraX = up.crossProduct(cameraZ);
            cameraX.normalize();
            cameraY = cameraZ.crossProduct(cameraX);
        }

        Vec3<double> inferRayDirection(const Vec2<double>& pixel) const restrict(cpu, amp) {
            auto direction = pixel.x * cameraX + pixel.y * cameraY - viewPlaneDistance * cameraZ;
            direction.normalize();
            return direction;
        }

        Vec3<double> cameraX, cameraY, cameraZ;
        Vec3<double> eyePos;
        Vec3<double> lookAt;
        Vec3<double> up;
        float viewPlaneDistance;
    };