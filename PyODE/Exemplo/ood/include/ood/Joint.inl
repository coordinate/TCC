/*!
 * @file Joint.inl
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2010 by Rocco Martino                                   *
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

#ifndef _OOD_JOINT_INL
#define _OOD_JOINT_INL

/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setJointEnabled(bool flag)
{
    flag ?
        dJointEnable(m_ODE_joint)
        :
        dJointDisable(m_ODE_joint) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline bool
ood::Joint::getJointEnabled(void) const
{
    return dJointIsEnabled(m_ODE_joint) != 0 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::RigidBody*
ood::Joint::getBody1(void)
{
    return m_body1.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::RigidBody*
ood::Joint::getBody1(void) const
{
    return m_body1.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::RigidBody*
ood::Joint::getBody2(void)
{
    return m_body2.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::RigidBody*
ood::Joint::getBody2(void) const
{
    return m_body2.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline dJointID
ood::Joint::getODEJoint(void)
{
    return m_ODE_joint ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setODEJointInternal(dJointID j)
{
    m_ODE_joint = j ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::checkBodiesInternal(void)
{
    if( getWorld() ) {
        finalize() ;
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setJointFeedback(JointFeedback* feedback)
{
    m_feedback = feedback ;

    if(m_ODE_joint && feedback) {
        dJointSetFeedback(m_ODE_joint, m_feedback->getODEJointFeedbackInternal()) ;
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::JointFeedback*
ood::Joint::getJointFeedback(void) const
{
    return m_feedback.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::JointFeedback*
ood::Joint::getOrCreateJointFeedback(void)
{
    if( ! m_feedback.valid() ) {
        setJointFeedback(new JointFeedback()) ;
    }

    return m_feedback.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setAnchor1(const osg::Vec3& anchor)
{
    setAnchor1Implementation(anchor) ;
    m_anchor1 = anchor ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setAnchor2(const osg::Vec3& anchor)
{
    setAnchor2Implementation(anchor) ;
    m_anchor2 = anchor ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setAxis1(const osg::Vec3& axis)
{
    setAxis1Implementation(axis) ;
    m_axis1 = axis ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setAxis2(const osg::Vec3& axis)
{
    setAxis2Implementation(axis) ;
    m_axis2 = axis ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setAxis3(const osg::Vec3& axis)
{
    setAxis3Implementation(axis) ;
    m_axis3 = axis ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::Joint::setParam(int param, ooReal value)
{
    setParamImplementation(param, value) ;
    m_param_map[param] = value ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Vec3&
ood::Joint::getAnchor1(void)
{
    readAnchor1Implementation(m_anchor1) ;

    return m_anchor1 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Vec3&
ood::Joint::getAnchor2(void)
{
    readAnchor2Implementation(m_anchor2) ;

    return m_anchor2 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Vec3&
ood::Joint::getAxis1(void)
{
    readAxis1Implementation(m_axis1) ;

    return m_axis1 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Vec3&
ood::Joint::getAxis2(void)
{
    readAxis2Implementation(m_axis2) ;

    return m_axis2 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Vec3&
ood::Joint::getAxis3(void)
{
    readAxis3Implementation(m_axis3) ;

    return m_axis3 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::Joint::getParam(int param)
{
    return m_param_map[param] ;
}
/* ....................................................................... */
/* ======================================================================= */




#endif /* _OOD_JOINT_INL */
