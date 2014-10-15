#include "physics/physics.hpp"

#define GLM_FORCE_RADIANS
#include "glm/gtc/matrix_transform.hpp"

#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

//TODO remove this
void print_vector(const char* s, glm::vec3 v){
   std::cout << s << v[0] << ", " << v[1] << ", " << v[2] << std::endl;
}

void print_forces(std::vector<const glm::vec3*> forces){
   for(size_t i = 0; i < forces.size(); i++){
      print_vector("", *(forces[i]));
   }
}

namespace phosphorus {
   namespace physics{
      ///Keep track of all objects in world
      std::vector<PhysicalObject> physObjects = std::vector<PhysicalObject>();

      ///Gravity vector
      glm::vec3 gravity_force = glm::vec3(0, -9.8, 0);

      /**
       * Constructor
       * @param matrix the initial position of the object
       * @param velocity the initial velocity vector of the object
       * @param gravity whether gravity should affect this object
       * @param mass the mass of the object
       */
      PhysicalObject::PhysicalObject(
         const glm::vec3& position,
         const glm::vec3& velocity,
         const bool& gravity,
         const float& mass
      ){
         pos = position;
         vel = velocity;
         m = mass;

         if(gravity){
            this->apply_force(&gravity_force);
         }
      }

      /**
       * Update the object's position, according to the time passed and the forces on the object
       * @param dt time passed in seconds
       */
      void PhysicalObject::update_position(float dt){
         glm::vec3 acc;
         glm::vec3 sum_f;

         if(m == std::numeric_limits<float>::max()){
            acc = glm::vec3(0, 0, 0);
         } else {
            sum_f = this->sum_forces();
            acc = sum_f/m;
         }

         //Calculate change in position
         glm::vec3 dp = dt * vel + (dt*dt)/2 * (acc);

         //Calculate change in velocity
         glm::vec3 dv = (acc) * dt;

         //Update the position
         pos = pos + dp;
         //Update velocity
         vel = vel + dv;
      }

      /** Apply a force to an object
       * @param the force vector
       */
      void PhysicalObject::apply_force(const glm::vec3* f){
         if(f != NULL)
            forces.push_back(f);
      }

      /** Remove a force from an object
       * @param the pointer to the force to be removed
       */
      void PhysicalObject::remove_force(glm::vec3* f){
         forces.erase(std::remove(forces.begin(), forces.end(), f), forces.end());
      }

      ///Set the position of the object
      void PhysicalObject::set_position(glm::vec3 position){
         pos = position;
      }

      ///Get the position of the object
      const glm::vec3& PhysicalObject::position(){
         return pos;
      }

      ///Get the velocity of the object
      const glm::vec3& PhysicalObject::velocity(){
         return vel; //TODO don't return actual object?
      }

      ///Get the acceleration of the object
      glm::vec3 PhysicalObject::acceleration(){
         if(m == std::numeric_limits<float>::max())
            return glm::vec3(0, 0, 0);
         else {
            glm::vec3 sum_f = this->sum_forces();
            return sum_f/m;
         }
      }

      ///Get the sum of the forces acting on the object
      glm::vec3 PhysicalObject::sum_forces(){
         glm::vec3 sum_f = glm::vec3(0, 0, 0);
         for(size_t i = 0; i < forces.size(); i++){
            sum_f += *forces[i]; // TODO do we need to lock the forces?
         }
         return sum_f;
      }

      /**
       * Get the furthest point in a shape in a 3D direction
       * @param shape a vector of the points in the shape
       * @param dir the direction to look in
       */
      glm::vec3 furthest_point(const std::vector<glm::vec3>& shape, const glm::vec3& dir){
         float max = -std::numeric_limits<float>::max(); //-Infinity
         glm::vec3 out;
         //Get furthest point in shape in direction dir
         int m = shape.size();
         for(int i = 0; i < m; i++){
            float dot = glm::dot(dir, shape[i]);
            if(dot > max){
               out = shape[i];
               max = dot;
            }
         }
         return out;
      }

      /**
       * Return the point p1 - p2 where
       * p1 is the furthest point in shape 1 in the direction dir
       * p2 is the furthest point in shape 2 in the direction -dir
       */
      glm::vec3 GJK_support(const std::vector<glm::vec3>& shape1, const std::vector<glm::vec3>& shape2, const glm::vec3& dir){
         //float max = -std::numeric_limits<float>::max(); //-Infinity
         glm::vec3 out;
         glm::vec3 p1;
         glm::vec3 p2;
         //Get furthest point in shape 1 in direction dir
         p1 = furthest_point(shape1, dir);

         glm::vec3 opp = -dir;
         p2 = furthest_point(shape2, opp);

         out = p1 - p2;

         return out;
      }

      /**
       * Checks to see if the origin is contained in a simplex, updates the direction to check next if not
       */
      bool GJK_contains_origin(std::vector<glm::vec3>& simplex, glm::vec3& dir){
         int m = simplex.size();

         //Get last point in simplex
         glm::vec3 a = simplex[0];

         //Get vector from point to origin
         glm::vec3 ao = -a;

         if(m == 2){ //Line case
            glm::vec3 b = simplex[1];

            glm::vec3 ab = b - a; // Get vector from a to b

            //Set direction to perpendicular to ab in the direction of the origin ie ao cross ab cross ab
            dir = ao * glm::dot(ab, ab) - ab * glm::dot(ab, ao); //see triple product expansion
         } else if (m == 3){ //Triangle case
            glm::vec3 b = simplex[1];
            glm::vec3 c = simplex[2];

            glm::vec3 ab = b-a;
            glm::vec3 ac = c-a;


            glm::vec3 normal = glm::cross(ab, ac);

            //Set direction to the normal to the triangle, in the direction of the origin
            if(glm::dot(ao, normal) < 0){
               dir = -normal;
            } else {
               dir = normal;
            }
         } else if (m == 4){ //Tetrahedron case
            glm::vec3 b = simplex[1];
            glm::vec3 c = simplex[2];
            glm::vec3 d = simplex[3];

            glm::vec3 ab = b - a;
            glm::vec3 ac = c - a;
            //glm::vec3 abc_norm = glm::cross(ac, ab);

            //Origin already lies in front of abc (in direction of d)
            //Check abd in direction of c
            glm::vec3 ad = d - a;
            glm::vec3 abd_norm = glm::cross(ab, ad);
            bool forwards = glm::dot(ac, abd_norm) > 0;
            float dot = glm::dot(ao, abd_norm);
            if(dot <= 0 && forwards){
               //Remove C
               simplex.erase(simplex.begin()+2);
               dir = -abd_norm;
            } else if (dot >= 0 && !forwards) {
               simplex.erase(simplex.begin()+2);
               dir = abd_norm;
            } else {
               //Check acd in direction of b
               glm::vec3 acd_norm = glm::cross(ad, ac);
               forwards = glm::dot(ab, acd_norm) > 0;
               dot = glm::dot(ao, acd_norm);
               if(dot <= 0 && forwards){
                  //Remove B
                  simplex.erase(simplex.begin()+1);
                  dir = -acd_norm;
               } else if(dot >= 0 && !forwards){
                  simplex.erase(simplex.begin()+1);
                  dir = acd_norm;
               } else {
                  //Check bcd in direction of a
                  glm::vec3 ba = a-b;
                  glm::vec3 bo = -b;
                  glm::vec3 bc = c-b;
                  glm::vec3 bd = d-b;
                  glm::vec3 bcd_norm = glm::cross(bc, bd);
                  forwards = glm::dot(ba, bcd_norm) > 0;
                  dot = glm::dot(bo, bcd_norm);
                  if(dot <= 0 && forwards){
                     //Remove A
                     simplex.erase(simplex.begin());
                     dir = -bcd_norm;
                  } else if(dot >= 0 && !forwards){
                     simplex.erase(simplex.begin());
                     dir = bcd_norm;
                  } else {
                     //Inside tetrahedron
                     return true;
                  }
               }
            }
         }
         return false;
      }

      bool GJK_collision(const std::vector<glm::vec3>& shape1, const std::vector<glm::vec3>& shape2){
         //Initialize simplex


         std::vector<glm::vec3> simplex = std::vector<glm::vec3>();

         //Set direction vector
         glm::vec3 dir = glm::vec3(0, 1, 0);
         //Get the first point (the furthest point in direction dir
         simplex.push_back(GJK_support(shape1, shape2, dir));

         dir = -dir;

         int count = 0;
         while(true){
            //Get furthest point in direction

            glm::vec3 p = GJK_support(shape1, shape2, dir);

            //Check if the returned point is on the + side of the origin (in direction dir)
            if(glm::dot(p, dir) <= 0){
               //If not then the minowski sum cannot possibly contain the origin and we can't have a collision
               return false;
            }

            simplex.push_back(p);

            //Check if resulting simplex contains the origin (indicates overlapping shapes)
            if(GJK_contains_origin(simplex, dir)){
               return true;
            }

            count++;
         }

         return false;
      }

   }
}
