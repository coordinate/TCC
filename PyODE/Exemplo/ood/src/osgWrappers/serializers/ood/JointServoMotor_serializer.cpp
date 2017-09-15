/*!
 * @file JointServoMotor_serializer.cpp
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2014 - 2017 by Rocco Martino                            *
 *   martinorocco@gmail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/* ======================================================================= */
/* ....................................................................... */
#include <ood/JointServoMotor>
#include <ood/Joint>

#include <osgDB/Registry>

#include "real_serializer"
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
REGISTER_OBJECT_WRAPPER( JointServoMotor,
                         new ood::JointServoMotor,
                         ood::JointServoMotor,
                         "osg::Object ood::ODECallback ood::ServoMotor ood::JointServoMotor" )
{
    ADD_REAL_SERIALIZER( Position, 0.0 ) ;
    ADD_REAL_SERIALIZER( Force, 0.0 ) ;
    ADD_REAL_SERIALIZER( MaxVel, -1.0 ) ;
    ADD_INT_SERIALIZER( Axis, (int)ood::Joint::AXIS1 ) ;
}
/* ....................................................................... */
/* ======================================================================= */
