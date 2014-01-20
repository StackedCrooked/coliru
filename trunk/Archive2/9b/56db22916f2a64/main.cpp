scene->addToScene(make_unique<Rectangle>(Vec3<double>{ -25, 25, 0 + 10 }, Vec3<double>{ 50, 0, 0 }, Vec3<double>{ 0, -50, 0 }, Vec3<double>{ 0, 0, 1 })); // Front
scene->addToScene(make_unique<Rectangle>(Vec3<double>{ -25 - 10, 25, 0 }, Vec3<double>{ 0, 0, -50 }, Vec3<double>{ 0, -50, 0 }, Vec3<double>{ 1, 0, 0 })); // Left
scene->addToScene(make_unique<Rectangle>(Vec3<double>{ -25, 25 + 10, 0 }, Vec3<double>{ 0, 0, -50 }, Vec3<double>{ 50, 0, 0 }, Vec3<double>{ 0, -1, 0 })); // Top

scene->addToScene(make_unique<Rectangle>(Vec3<double>{ 25, -25, -50 - 10 }, Vec3<double>{ -50, 0, 0 }, Vec3<double>{ 0, 50, 0 }, Vec3<double>{ 0, 0, -1 })); // Back
scene->addToScene(make_unique<Rectangle>(Vec3<double>{ 25 + 10, -25, -50 }, Vec3<double>{ 0, 50, 0 }, Vec3<double>{ 0, 0, 50 }, Vec3<double>{ -1, 0, 0 })); // Right
scene->addToScene(make_unique<Rectangle>(Vec3<double>{ 25, -25 - 10, -50 }, Vec3<double>{ -50, 0, 0 }, Vec3<double>{ 0, 0, 50 }, Vec3<double>{ 0, 1, 0 })); // Bottom