/*!
 * @file SwaybarJoint.inl
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2013 by Rocco Martino                                   *
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

#ifndef _OOD_SWAYBARJOINT_INL
#define _OOD_SWAYBARJOINT_INL

/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::SwaybarJoint::setReferenceBody(RigidBody* body)
{
    m_reference_body = body ;


    if( m_reference_body.valid() ) {

        dVector3    result ;
        dBodyVectorFromWorld( m_reference_body->getODEBody(), m_reference_axis.x(), m_reference_axis.y(), m_reference_axis.z(), result ) ;

        m_reference_axis_local.set( result[0], result[1], result[2] ) ;

    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::RigidBody*
ood::SwaybarJoint::getReferenceBody(void)
{
    return m_reference_body.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::RigidBody*
ood::SwaybarJoint::getReferenceBody(void) const
{
    return m_reference_body.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::SwaybarJoint::setReferenceAxis(const osg::Vec3& axis)
{
    if( m_reference_body.valid() ) {

        dVector3    result ;
        dBodyVectorFromWorld( m_reference_body->getODEBody(), axis.x(), axis.y(), axis.z(), result ) ;

        m_reference_axis_local.set( result[0], result[1], result[2] ) ;

    } else {

        m_reference_axis_local = axis ;

    }


    m_reference_axis = axis ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Vec3&
ood::SwaybarJoint::getReferenceAxis(void) const
{
    return m_reference_axis ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::SwaybarJoint::setRigidity(ooReal rigidity)
{
    setParam(dParamStopCFM, -1.0  +  1.0 / rigidity) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::SwaybarJoint::getRigidity(void) const
{
    const ooReal    c = const_cast<SwaybarJoint*>(this)->getParam(dParamStopCFM) ;

    return 1 / (c + 1) ;
}
/* ....................................................................... */
/* ======================================================================= */




#endif /* _OOD_SWAYBARJOINT_INL */
