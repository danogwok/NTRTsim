/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 * 
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
*/

/**
 * @file AppBigPuppy.cpp
 * @brief Implementing the Flemons quadruped model.
 * @author Dawn Hustig-Schultz
 * @date April 2015
 * @version 1.0.0
 * $Id$
 */

// This application
#include "BigPuppy.h"
// This library
#include "core/terrain/tgBoxGround.h"
#include "core/terrain/tgHillyGround.h"
#include "core/tgModel.h"
#include "core/tgSimViewGraphics.h"
#include "core/tgSimulation.h"
#include "core/tgWorld.h"
// Bullet Physics
#include "LinearMath/btVector3.h"
// The C++ Standard Library
#include <iostream>

/**
 * The entry point.
 * @param[in] argc the number of command-line arguments
 * @param[in] argv argv[0] is the executable name
 * @return 0
 */

int main(int argc, char** argv)
{
    std::cout << "AppBigPuppy" << std::endl;

    // First create the ground and world. Specify ground rotation in radians

#ifdef SMALL_HILLS
    btVector3 eulerAngles = btVector3(0.0, 0.0, 0.0);
    btScalar friction = 0.5;
    btScalar restitution = 0.0;
    // Size doesn't affect hilly terrain
    btVector3 size = btVector3(0.0, 0.1, 0.0);
    btVector3 origin = btVector3(0.0, 0.0, 0.0);
    size_t nx = 100;
    size_t ny = 100;
    double margin = 0.5;
    double triangleSize = 4.0;
    double waveHeight = 2.0;
    double offset = 0.0;
    const tgHillyGround::Config hillyGroundConfig(eulerAngles, friction, restitution,
                                    size, origin, nx, ny, margin, triangleSize,
                                    waveHeight, offset);

    tgHillyGround* ground = new tgHillyGround(hillyGroundConfig);
#endif

#ifdef LARGE_HILLS
    btVector3 eulerAngles = btVector3(0.0, 0.0, 0.0);
    btScalar friction = 0.5;
    btScalar restitution = 0.0;
    // Size doesn't affect hilly terrain
    btVector3 size = btVector3(0.0, 0.1, 0.0);
    btVector3 origin = btVector3(0.0, 0.0, 0.0);
    size_t nx = 300;
    size_t ny = 300;
    double margin = 0.5;
    double triangleSize = 4.0;
    double waveHeight = 6.0;
    double offset = 3.0;
    const tgHillyGround::Config hillyGroundConfig(eulerAngles, friction, restitution,
                                    size, origin, nx, ny, margin, triangleSize,
                                    waveHeight, offset);

    tgHillyGround* ground = new tgHillyGround(hillyGroundConfig);
#endif

#ifdef FLAT_GROUND
    const double yaw = 0.0;
    const double pitch = 0.0;
    const double roll = 0.0;
    const tgBoxGround::Config groundConfig(btVector3(yaw, pitch, roll));
    // the world will delete this
    tgBoxGround* ground = new tgBoxGround(groundConfig);

#endif

    const tgWorld::Config config(981); // gravity, cm/sec^2 981
    tgWorld world(config, ground);

    // Second create the view
    const double timestep_physics = 0.001; // seconds
    const double timestep_graphics = 1.f/60.f; // seconds
    tgSimViewGraphics view(world, timestep_physics, timestep_graphics);

    // Third create the simulation
    tgSimulation simulation(view);

    BigPuppy* const myModel = new BigPuppy();

    // Add the model to the world
    simulation.addModel(myModel);
    
    simulation.run();

    //Teardown is handled by delete, so that should be automatic
    return 0;
}