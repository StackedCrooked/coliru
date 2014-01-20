boost::optional<RayHit> onRayCast(const Ray& ray) override {
            double t = (point - ray.origin) * normal / (ray.direction * normal);
            if (t <= 0) return {};

            auto temp = ray.origin + t * ray.direction;
            auto tempDir = temp - point;

            auto tempDirDotSide = tempDir * a;
            if (tempDirDotSide > a.lengthSquared() || tempDirDotSide < 0.0) {
                return {};
            }

            tempDirDotSide = tempDir * b;
            if (tempDirDotSide > b.lengthSquared() || tempDirDotSide < 0.0) {
                return {};
            }

            return {{t}};
        }
        
        Vec3<double> point;
        Vec3<double> a, b;
        Vec3<double> normal;