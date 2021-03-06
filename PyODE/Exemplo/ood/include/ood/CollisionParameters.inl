/*!
 * @file CollisionParameters.inl
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

#ifndef _OOD_COLLISIONPARAMETERS_INL
#define _OOD_COLLISIONPARAMETERS_INL

/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setMode(int mode)
{
    m_mode = mode ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline int
ood::CollisionParameters::getMode(void) const
{
    return m_mode  ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setMu(ooReal mu)
{
    m_mu = mu ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getMu(void) const
{
    return m_mu  ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setMu2(ooReal mu2)
{
    m_mu2 = mu2 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getMu2(void) const
{
    return m_mu2  ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setBounce(ooReal bounce)
{
    m_bounce = bounce ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getBounce(void) const
{
    return m_bounce  ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setBounceVel(ooReal bounce_vel)
{
    m_bounce_vel = bounce_vel ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getBounceVel(void) const
{
    return m_bounce_vel  ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setSoftERP(ooReal soft_erp)
{
    m_soft_erp = soft_erp ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getSoftERP(void) const
{
    return m_soft_erp  ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setSoftCFM(ooReal soft_cfm)
{
    m_soft_cfm = soft_cfm ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getSoftCFM(void) const
{
    return m_soft_cfm ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setMotion1(ooReal motion1)
{
    m_motion1 = motion1 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getMotion1(void) const
{
    return m_motion1 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setMotion2(ooReal motion2)
{
    m_motion2 = motion2 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getMotion2(void) const
{
    return m_motion2 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setMotionN(ooReal motionN)
{
    m_motionN = motionN ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getMotionN(void) const
{
    return m_motionN ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setSlip1(ooReal slip1)
{
    m_slip1 = slip1 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getSlip1(void) const
{
    return m_slip1 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setSlip2(ooReal slip2)
{
    m_slip2 = slip2 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::CollisionParameters::getSlip2(void) const
{
    return m_slip2 ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setMaxContactNum(unsigned int max_contact_num)
{
    m_max_contact_num = max_contact_num ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline unsigned int
ood::CollisionParameters::getMaxContactNum(void) const
{
    return m_max_contact_num ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setCollideConnected(bool flag)
{
    m_collide_connected = flag ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline bool
ood::CollisionParameters::getCollideConnected(void) const
{
    return m_collide_connected ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::CollisionParameters::setCollisionsEnabled(bool flag)
{
    m_collisions_enabled = flag ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline bool
ood::CollisionParameters::getCollisionsEnabled(void) const
{
    return m_collisions_enabled ;
}
/* ....................................................................... */
/* ======================================================================= */




#endif /* _OOD_COLLISIONPARAMETERS_INL */
