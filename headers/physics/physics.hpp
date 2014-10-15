#ifndef PHOSPHORUS_PHYSICS_PHYSICS_H_
#define PHOSPHORUS_PHYSICS_PHYSICS_H_

#include <vector>

#include "glm/glm.hpp"

//TODO remove this
void print_vector(const char* s, glm::vec3 v);

void print_forces(std::vector<const glm::vec3*> forces);

namespace phosphorus {
   namespace physics {
      extern glm::vec3 gravity_force;

      /**
       * Object for physics
       */
      class PhysicalObject {
         private:
            ///The position of the object
            glm::vec3 pos;
            ///Velocity vector
            glm::vec3 vel;

            //Attributes
            ///Affected by collisions
            bool collides;
            ///Mass of object
            float m;

            ///The shapes for detecting collisions
            std::vector<std::vector<glm::vec3> > collision_shapes;

         public:

            ///Force vectors
            std::vector<const glm::vec3*> forces; //TODO make private

            /**
             * Constructor
             * @param position the initial position of the object
             * @param velocity the initial velocity vector of the object
             * @param gravity whether gravity should affect this object
             * @param mass the mass of the object
             */
            PhysicalObject(
               const glm::vec3& position,
               const glm::vec3& velocity,
               const bool& gravity,
               const float& mass
               );

            /**
             * Update the object's position, according to the time passed and the forces on the object
             * @param dt time passed in seconds
             */
            void update_position(float dt);

            /** Apply a force to an object
             * @param the force vector, note: the force will persist unless a negative force is applied
             */
            void apply_force(const glm::vec3* f);

            /** Remove a force from an object
             * @param a pointer to the force to remove
             */
            void remove_force(glm::vec3* f);


            /// Set the position
            void set_position(glm::vec3 position);

            /// Get the position
            const glm::vec3& position();

            /// Get the velocity
            const glm::vec3& velocity();

            ///Get the acceleration
            glm::vec3 acceleration();

            glm::vec3 sum_forces();
      };

      /**
       * Collision detection algorithm
       * @param shape1 a vector of all the points in shape1
       * @param shape2 a vector of all the points in shape2
       */
      bool GJK_collision(const std::vector<glm::vec3>& shape1, const std::vector<glm::vec3>& shape2);
   }
}

#endif // PHOSPHORUS_PHYSICS_PHYSICS_H_
