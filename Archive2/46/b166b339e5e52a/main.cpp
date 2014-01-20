Vec3<double> inferRayDirection(const Vec2<double>& pixel) const restrict(cpu, amp) {
            auto direction = pixel.x * cameraX + pixel.y * cameraY - viewPlaneDistance * cameraZ;
            direction.normalize();
            return direction;
        }