/*!
 * @file RayCar.inl
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2015 by Rocco Martino                                   *
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
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _OOD_RAYCAR_INL
#define _OOD_RAYCAR_INL




/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::RayCar::setUpVersor( const osg::Vec3& up_versor )
{
    m_up_versor = up_versor ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline osg::Vec3&
ood::RayCar::getUpVersor(void)
{
    return m_up_versor ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Vec3&
ood::RayCar::getUpVersor(void) const
{
    return m_up_versor ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::RayCar::setFrontVersor( const osg::Vec3& front_versor )
{
    m_front_versor = front_versor ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline osg::Vec3&
ood::RayCar::getFrontVersor(void)
{
    return m_front_versor ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Vec3&
ood::RayCar::getFrontVersor(void) const
{
    return m_front_versor ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::RayCar::setEngine( Engine* engine )
{
    m_engine = engine ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::Engine*
ood::RayCar::getEngine(void)
{
    return m_engine ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::Engine*
ood::RayCar::getEngine(void) const
{
    return m_engine ;
}
/* ....................................................................... */
/* ======================================================================= */






/* ======================================================================= */
/* ....................................................................... */
inline void
ood::RayCar::setBody( RigidBody* body )
{
    m_body = body ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::RigidBody*
ood::RayCar::getBody(void)
{
    return m_body ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::RigidBody*
ood::RayCar::getBody(void) const
{
    return m_body ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::RayCar::setSuspensionList( const SuspensionList& suspension_list )
{
    m_suspension_list = suspension_list ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::RayCar::SuspensionList&
ood::RayCar::getSuspensionList(void)
{
    return m_suspension_list ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::RayCar::SuspensionList&
ood::RayCar::getSuspensionList(void) const
{
    return m_suspension_list ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::RayCar::setDrive( ooReal drive )
{
    m_drive = drive ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::RayCar::getDrive(void) const
{
    return m_drive ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::RayCar::setSteer( ooReal steer )
{
    m_steer = steer ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::RayCar::getSteer(void) const
{
    return m_steer ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::RayCar::setBottom( ooReal bottom )
{
    m_bottom = bottom ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ooReal
ood::RayCar::getBottom(void) const
{
    return m_bottom ;
}
/* ....................................................................... */
/* ======================================================================= */








#endif /* _OOD_RAYCAR_INL */
