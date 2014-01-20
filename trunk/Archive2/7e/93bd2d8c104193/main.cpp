cameraZ = eyePos - lookAt;
cameraZ.normalize();
cameraX = up.crossProduct(cameraZ);
cameraX.normalize();
cameraY = cameraZ.crossProduct(cameraX);