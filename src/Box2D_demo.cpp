#include "Box2D/Box2D.h"

int main() {
  /* 1、创建世界 */
  b2Vec2  gravity(0.0f, -10.0f);  //定义重力，以10替代9.8,易于计算
  b2World world(gravity);         //定义重力，以10替代9.8,易于计算

  /* 2、创建地面 */
  b2BodyDef groundBodyDef;                   //创建一个物体[box]
  groundBodyDef.position.Set(0.0f, -10.0f);  //定义位置
  /*
     * 传递给world定义出实体,世界对象不保留对实体定义的引用。
     * 默认情况下，实体是静态的。静止物体不会与其他静止物体碰撞，并且是不可移动的。
     */
  b2Body*        groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;          //创建一个地面
  groundBox.SetAsBox(50.0f, 10.0f);  //使用SetAsBox快捷方式将地面多边形形成一个长方体形状，长方体以父体的原点为中心
  groundBody->CreateFixture(&groundBox, 0.0f);

  /* 3、创建动态物体 */
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 4.0f);
  b2Body*        body = world.CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  //密度
  fixtureDef.density = 1.0f;
  //摩擦力系数
  fixtureDef.friction = 0.3f;
  groundBody->CreateFixture(&fixtureDef);

  return 0;
}