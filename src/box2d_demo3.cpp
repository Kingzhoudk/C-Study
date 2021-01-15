#include "box2d_data.h"

int main() {
  b2World world = b2World(b2Vec2(0, -10));
  MyContactListener listener;
  world.SetContactListener(&listener);

  //地面
  b2BodyDef groud_body;
  groud_body.type = b2_staticBody;
  b2EdgeShape groud_shape;
  groud_shape.Set(b2Vec2(0, 0), b2Vec2(10, 0));
  b2FixtureDef groud_fixture;
  groud_fixture.density = 1.0f;
  groud_fixture.friction = 0.5f;
  groud_fixture.restitution = 1.0f;
  groud_fixture.shape = &groud_shape;
  b2Body* groud = world.CreateBody(&groud_body);
  groud->CreateFixture(&groud_fixture);

  //球
  b2BodyDef ball_body;
  ball_body.type = b2_dynamicBody;
  ball_body.position = b2Vec2(1.5, 4);
  b2CircleShape ball_shape;
  ball_shape.m_radius = 0.1;
  b2FixtureDef ball_fixture;
  ball_fixture.density = 1.0f;
  ball_fixture.friction = 0.5f;
  ball_fixture.restitution = 1.0f;
  ball_fixture.shape = &ball_shape;
  b2Body* ball = world.CreateBody(&ball_body);
  ball->CreateFixture(&ball_fixture);

  //创建一个sensor
  b2BodyDef sensor_body;
  sensor_body.type = b2_staticBody;
  b2PolygonShape sensor_shape;
  b2Vec2 vertices[4];
  vertices[0].Set(0, 1);
  vertices[1].Set(3, 1);
  vertices[2].Set(3, 2);
  vertices[3].Set(0, 2);
  sensor_shape.Set(vertices, 4);
  b2FixtureDef sensor_fixture;
  sensor_fixture.isSensor = true;
  sensor_fixture.shape = &sensor_shape;
  b2Body* sensor = world.CreateBody(&sensor_body);
  sensor->CreateFixture(&sensor_fixture);

  const float timeStep = 1.f / 60.f;
  const int32 velocityIterations = 6;
  const int32 positionIterations = 2;
  for (int i = 0; i < 120; i++) {
    world.Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = ball->GetPosition();
    float angle = ball->GetAngle();
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
  }
  return 0;
}