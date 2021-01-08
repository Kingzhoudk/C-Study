#include "Box2D/Box2D.h"

int main() {
  /* 创建垂直世界 */
  b2Vec2  gravity(0.0f, -10.0f);     //定义重力，以10替代9.8,易于计算
  b2World world(gravity);            //定义重力，以10替代9.8,易于计算
  world.SetAllowSleeping(true);      //允许静止的物体休眠,不参与物理运算
  world.SetContinuousPhysics(true);  //开启连续物理检测，使模拟更加的真实

  /* 创建刚体，用来模拟地面 */
  b2BodyDef groundBodyDef;
  groundBodyDef.type          = b2_staticBody;  //默认参数，可不写
  groundBodyDef.linearDamping = 0.2;
  groundBodyDef.position.Set(0.0f, 0.0f);
  b2Body* ground_body = world.CreateBody(&groundBodyDef);

  /* 创建一条边线，模拟地面的形状 */
  b2EdgeShape bodyShape;
  b2Vec2      point1(0, 0), point2(10, 0);
  bodyShape.Set(point1, point2);

  /* 创建夹具，将形状绑定到刚体上，形成具象的物体 */
  b2FixtureDef fixtureDef;
  fixtureDef.shape       = &bodyShape;  //shape为边线
  fixtureDef.density     = 1.0f;        //密度
  fixtureDef.friction    = 0.5f;        //摩擦力系数，0为理论上的光滑
  fixtureDef.restitution = 1.0f;        //弹性系数,用于刚体碰撞后能量的损失计算。取值通常在区间[0, 1]
  ground_body->CreateFixture(&fixtureDef);

  /* 创建一个球，模拟ball掉落在地面上弹起来 */
  b2BodyDef ball;
  ball.type          = b2_dynamicBody;
  ball.linearDamping = 0.2;
  ball.position.Set(0.0f, 4.0f);
  b2Body* ball_body = world.CreateBody(&ball);

  b2CircleShape ballShape;
  b2Vec2        point3(4, 0);
  ballShape.m_p      = point3;  //设定坐标
  ballShape.m_radius = 0.1;     //设定半径

  b2FixtureDef ball_fixtureDef;
  ball_fixtureDef.shape    = &ballShape;  //shape为圆
  ball_fixtureDef.density  = 1.0f;        //密度
  ball_fixtureDef.friction = 0.5f;        //摩擦力系数，0为理论上的光滑
  ball_body->CreateFixture(&ball_fixtureDef);

  float timeStep           = 1.0f / 60.0f;  //时间步
  int32 velocityIterations = 6;             //速度迭代次数[控制约束求解器中遍历多少次世界中的接触和关节]
  int32 positionIterations = 6;             //位置迭代次数[迭代次数越高，模拟越逼真，但是越耗性能。]
  for (int32 i = 0; i < 120; ++i) {
    world.Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = ball_body->GetPosition();
    float  angle    = ball_body->GetAngle();
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
  }

  return 0;
}