#include "Box2D/Box2D.h"
#include <iostream>

class MyContactListener : public b2ContactListener {
 public:
  MyContactListener(){};

 private:
  void BeginContact(b2Contact* contact) {
    b2Vec2 position_a = contact->GetFixtureA()->GetBody()->GetPosition();
    b2Vec2 position_b = contact->GetFixtureB()->GetBody()->GetPosition();
    std::cout << "BeginContactA: " << position_a.x << "," << position_a.y << "\n";
    std::cout << "BeginContactB: " << position_b.x << "," << position_b.y << "\n";
  };
  void EndContact(b2Contact* contact) {
    std::cout << "EndContact\n";
  };
};
