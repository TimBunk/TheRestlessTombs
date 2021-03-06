/**
 * @file psychoOrc.h
 *
 * @brief The psychoOrc header file.
 */

#ifndef PSYCHOORC_H
#define PSYCHOORC_H

#include "enemy.h"

/**
 * @brief The PsychoOrc class
 */
class PsychoOrc : public Enemy {
public:
	/// @brief Constructor of the PsychoOrc takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param player The enemy needs to know of the player so that it always can raycast towards the player
	/// @param lineOfSight is a maximum distance for the raycast
	/// @param rm The ResourceManager is used for getting the right textures and shaders for your person
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	PsychoOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the PsychodOrc
	virtual ~PsychoOrc();

	/// @brief Update makes a call to LookForPlayer and also makes sure the weapon is used right
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Apply damage to a PsychoOrc the damage goes minus the health
	/// @param damage The amount of damage the person will take the damage goes minus the health
	/// @return void
	void TakeDamage(int damage);

	/// @brief Reset the PsychoOrc to it's begin values
	/// @return void
	void Reset();
private:
	Weapon* sword; ///< @brief sword Is the weapon used by the PsychoOrc
};

#endif //!PSYCHOORC_H
