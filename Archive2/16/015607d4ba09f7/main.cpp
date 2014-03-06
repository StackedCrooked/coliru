        template <typename T>
        void addLight(T&& light) {
            _dispatchAddLight(std::forward<T>(light));
        }

        void _dispatchAddLight(PointLight&& light) {
            pointLights.emplace_back(std::move(light));
        }

        void _dispatchAddLight(DirectionalLight&& light) {
            directionalLights.emplace_back(std::move(light));
        }