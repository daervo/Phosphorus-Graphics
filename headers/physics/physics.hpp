#ifndef PHOSPHORUS_PHYSICS_PHYSICS_H_
#define PHOSPHORUS_PHYSICS_PHYSICS_H_

#include <vector>

#include "glm/glm.hpp"

//TODO remove this
void print_vector(const char* s, glm::vec3 v);

namespace phosphorus {
   namespace physics {
      extern glm::vec3 gravity_accel;

      /**
       * Object for physics
       */
      class PhysicalObject {
         private:
            //Velocity and acceleration
            ///Velocity vector
            glm::vec3 vel;
            ///Force vector
            glm::vec3 sum_f;

            //Attributes
            ///Affected by gravity
            bool grav;
            ///Affected by collisions
            bool collides;
            ///Mass of object
            float m;

            ///The shapes for detecting collisions
            std::vector<std::vector<glm::vec3> > collision_shapes;

         public:
            ///The transformation matrix of the object
            glm::mat4 mat; //TODO this should probably be private

            /**
             * Constructor
             * @param matrix the initial transform matrix of the object
             * @param velocity the initial velocity vector of the object
             * @param acceleration the initial acceleration vector of the object
             * @param gravity whether gravity should affect this object
             * @param mass the mass of the object
             * @param solid whether this object can collide with others
             */
            PhysicalObject(
               glm::mat4 matrix,
               glm::vec3 velocity,
               glm::vec3 acceleration,
               bool gravity,
               float mass,
               bool solid
               );

            /**
             * Update the object's position, according to the time passed and the forces on the object
             * @param dt time passed in seconds
             */
            void update_position(float dt); //TODO allow collision behaviour to be specified

            /** Apply a force to an object
             * @param the force vector, note: the force will persist unless a negative force is applied
             */
            void apply_force(const glm::vec3& f);

            /// Get the position
            glm::vec3 position();

            /// Get the velocity
            glm::vec3 velocity();

            ///Get the acceleration
            glm::vec3 acceleration();
      };

      ///The list of all physObjects
      extern std::vector<PhysicalObject> physObjects;

      /**
       * Collision detection algorithm
       * @param shape1 a vector of all the points in shape1
       * @param shape2 a vector of all the points in shape2
       */
      bool GJK_collision(const std::vector<glm::vec3>& shape1, const std::vector<glm::vec3>& shape2);
   }
}

#endif // PHOSPHORUS_PHYSICS_PHYSICS_H_
