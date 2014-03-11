  (Concurrency::index<1> idx) restrict(amp) {
                Ray ray;
                ray.origin = camera.getEye();
                Color resultColor{bg};
                Vec2<double> pixel;
                for (int sample = 0; sample < Settings::NumSamples; ++sample) {
                    auto samplePoint = g_Samples[g_Offsets[idx] * Settings::NumSamples + g_Indices[sample + g_Offsets[idx] * Settings::NumSamples]];
                    pixel.x = (idx[0] % Settings::HRes) - 0.5 * Settings::HRes + samplePoint.x;                    
                    pixel.y = (idx[0] / Settings::HRes) - 0.5 * Settings::VRes + samplePoint.y;
                    ray.direction = camera.inferRayDirection(pixel);
                    auto hit = g_hitAllObjects(ray, g_Spheres, g_Planes, g_Rectangles, numSpheres, numPlanes, numRects);
                    resultColor += hit.hasHit ? hit.material.shade(ray, hit.normal, hit.hitPoint,
                                                                   ambientLight, g_DirectionalLights, g_PointLights,
                                                                   numDirLights, numPointLights)
                                              : bg; 
                }
                resultColor *= oneOverNumSamples;
                g_Result[idx] = resultColor;
            });