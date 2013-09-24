case sf::Keyboard::Key::Left: {
    eye += glm::vec3(0.0, 0.0, 1.0);
    lookingAt += glm::vec3(0.0, 0.0, 1.0);
    view = glm::lookAt(eye, lookingAt, up);
    break;
}
case sf::Keyboard::Key::Up: {
    lookingAt -= glm::normalize(eye) * glm::vec3(3.0);
    eye -= glm::normalize(eye) * glm::vec3(3.0);
    view = glm::lookAt(eye, lookingAt, up);
    break;
}
case sf::Keyboard::Key::Down: {
    lookingAt += glm::normalize(eye) * glm::vec3(3.0);
    eye += glm::normalize(eye) * glm::vec3(3.0);
    view = glm::lookAt(eye, lookingAt, up);
    break;
}