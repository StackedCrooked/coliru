class WaypointNetwork; // <-- Compile Error
class NetworkEdge;
class SceneEntity{};

class Waypoint final : public SceneEntity
{
    // ...
    float GetCostForEdge (const NetworkEdge& edge, const WaypointNetwork* pWaypointNetwork);
};

int main() {}