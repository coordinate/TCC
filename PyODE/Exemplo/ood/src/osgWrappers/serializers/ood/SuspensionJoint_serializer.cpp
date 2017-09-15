/*!
 * @file SuspensionJoint_serializer.cpp
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2012 by Rocco Martino                                   *
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
#include <ood/SuspensionJoint>

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
REGISTER_OBJECT_WRAPPER( SuspensionJoint,
                         new ood::SuspensionJoint,
                         ood::SuspensionJoint,
                         "osg::Object ood::ODEObject ood::Transformable ood::Joint ood::Hinge2Joint ood::SuspensionJoint" )
{
    ADD_REAL_SERIALIZER(Spring, 1.0) ;
    ADD_REAL_SERIALIZER(DamperBound, 0.0) ;
    ADD_REAL_SERIALIZER(DamperRebound, 0.0) ;
    ADD_REAL_SERIALIZER(Preload, 0.0) ;
    ADD_REAL_SERIALIZER(SteerAngle, 0.0) ;
}
/* ....................................................................... */
/* ======================================================================= */
