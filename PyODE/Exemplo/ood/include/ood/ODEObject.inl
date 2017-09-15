/*!
 * @file ODEObject.inl
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2010 - 2014 by Rocco Martino                            *
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

#ifndef _OOD_ODEOBJECT_INL
#define _OOD_ODEOBJECT_INL

/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::ODEObject::setUpdateCallback(ood::ODECallback* cbk)
{
    m_update_callback = cbk ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::ODECallback*
ood::ODEObject::getUpdateCallback(void)
{
    return m_update_callback.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::ODECallback*
ood::ODEObject::getUpdateCallback(void) const
{
    return m_update_callback.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::ODEObject::addUpdateCallback(ood::ODECallback* cbk)
{
    if( m_update_callback.valid() ) {
        m_update_callback->addNestedCallback(cbk) ;
    } else {
        setUpdateCallback(cbk) ;
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::ODEObject::removeUpdateCallback(ood::ODECallback* cbk)
{
    if(cbk) {
        if( cbk == m_update_callback.get()) {
            m_update_callback = m_update_callback->getNestedCallback() ;
        } else {
            if( m_update_callback.valid() ) {
                m_update_callback->removeNestedCallback(cbk) ;
            }
        }
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::ODEObject::setPostUpdateCallback(ood::ODECallback* cbk)
{
    m_post_update_callback = cbk ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::ODECallback*
ood::ODEObject::getPostUpdateCallback(void)
{
    return m_post_update_callback.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::ODECallback*
ood::ODEObject::getPostUpdateCallback(void) const
{
    return m_post_update_callback.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::ODEObject::addPostUpdateCallback(ood::ODECallback* cbk)
{
    if( m_post_update_callback.valid() ) {
        m_post_update_callback->addNestedCallback(cbk) ;
    } else {
        setPostUpdateCallback(cbk) ;
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::ODEObject::removePostUpdateCallback(ood::ODECallback* cbk)
{
    if(cbk) {
        if( cbk == m_post_update_callback.get()) {
            m_post_update_callback = m_post_update_callback->getNestedCallback() ;
        } else {
            if( m_post_update_callback.valid() ) {
                m_post_update_callback->removeNestedCallback(cbk) ;
            }
        }
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline unsigned int
ood::ODEObject::getID(void) const
{
    return m_ID ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline ood::World*
ood::ODEObject::getWorld(void)
{
    return m_world.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const ood::World*
ood::ODEObject::getWorld(void) const
{
    return m_world.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::ODEObject::setUserObject(osg::Object* obj)
{
    m_user_object = obj ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline osg::Object*
ood::ODEObject::getUserObject(void)
{
    return m_user_object.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::Object*
ood::ODEObject::getUserObject(void) const
{
    return m_user_object.get() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline const osg::BoundingSphere&
ood::ODEObject::getActorBound(void) const
{
    return m_actor_bound ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline void
ood::ODEObject::setActorBound(const osg::BoundingSphere& bs)
{
    m_actor_bound.set( bs.center(), bs.radius() ) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
inline bool
ood::ODEObject::getActor(void) const
{
    return m_actor ;
}
/* ....................................................................... */
/* ======================================================================= */




#endif /* _OOD_ODEOBJECT_INL */