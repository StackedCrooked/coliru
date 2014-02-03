auto flippedDirection = -ray.direction;
auto result = brdfAmbient.rho() * ambientLight.getRadiance();

for (int pointLight = 0; pointLight < numPointLights; ++pointLight) {
    auto direction = pointLights[pointLight].getDirection(hitPoint);
    auto normalDotDirection = normal * direction;
    if (normalDotDirection > 0.0) {
        result += brdfDiffuse.diffuseF() * pointLights[pointLight].getRadiance() * static_cast<float>(normalDotDirection);
    }
}