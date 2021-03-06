/*!
 * @file Space.cpp
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2010 - 2012 by Rocco Martino                            *
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
#include <ood/Space>
#include <ood/RigidBody>
#include <ood/OverlappingPair>
#include <ood/DefaultNearCallback>
#include <ood/Notify>
#include <ood/ScopedTimer>
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




using namespace ood ;




/* ======================================================================= */
/* ....................................................................... */
static void
_defaultOverlappingPairsDispatcher(void* void_near_callback, dGeomID o1, dGeomID o2)
{

    Collidable* collidable1 = static_cast<Collidable*>(dGeomGetData(o1)) ;
    Collidable* collidable2 = static_cast<Collidable*>(dGeomGetData(o2)) ;



    osg::ref_ptr<OverlappingPair>   overlapping_pair = new OverlappingPair() ;

    overlapping_pair->setCollidables(collidable1, collidable2) ;



    PS_ASSERT1( void_near_callback != NULL ) ;


    //! @note   need to avoid this static_cast from void*

    NearCallback*   near_callback = static_cast<NearCallback*>(void_near_callback) ;

    if( near_callback->collide(overlapping_pair) > 0 ) {

        // OK, a collision occours

        collidable1->setLastCollisionFrame( collidable1->getWorld()->getCurrentFrame() ) ;
        collidable2->setLastCollisionFrame( collidable2->getWorld()->getCurrentFrame() ) ;



        // call the collision callbacks

        CollisionCallback*  collision_callback1 = collidable1->getCollisionCallback() ;
        CollisionCallback*  collision_callback2 = collidable2->getCollisionCallback() ;


        if(collision_callback1) {
            (*collision_callback1)(collidable1, collidable2, near_callback) ;
        }


        if(collision_callback2) {
            (*collision_callback2)(collidable2, collidable1, near_callback) ;
        }
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
Space::Space(void):
    m_overlapping_pairs_dispatcher(_defaultOverlappingPairsDispatcher),
    m_near_callback( new DefaultNearCallback() )
{

    m_ODE_space = dHashSpaceCreate(NULL) ;

    // The ood::Space will remove the bodies by itself
    dSpaceSetCleanup(m_ODE_space, 0) ;

    dGeomSetData((dGeomID)m_ODE_space, this) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
Space::Space(const Space& other, const osg::CopyOp& copyop):
    World(other, copyop),
    m_overlapping_pairs_dispatcher(other.m_overlapping_pairs_dispatcher),
    m_near_callback(other.m_near_callback.get())
{

    m_ODE_space = dHashSpaceCreate(NULL) ;

    _cloneODESpace(other.m_ODE_space, m_ODE_space) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
Space::~Space(void)
{
    removeAllObjects() ;

    dSpaceDestroy(m_ODE_space) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
Space::update(ooReal step_size)
{
    advanceInternal( step_size ) ;
    collide() ;
    step( step_size ) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
Space::threadUpdate(ooReal step_size)
{
    advanceInternal( step_size ) ;
    collide() ;
    threadStep( step_size ) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
Space::collide(void)
{
    PS_DBG3("ood::Space::collide(%p)", this) ;




    if( m_near_callback.valid() ) {

        m_near_callback->reset() ;

        {
            PS_DBG3("ood::Space::collide(%p): dSpaceCollide", this) ;
            PS_SCOPED_TIMER("dSpaceCollide") ;

            dSpaceCollide(m_ODE_space, (void*)m_near_callback, m_overlapping_pairs_dispatcher) ;
        }
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
Space::copySpace(const Space* other)
{
    this->copyWorld(other) ;


    m_overlapping_pairs_dispatcher = other->m_overlapping_pairs_dispatcher ;

    m_near_callback = other->m_near_callback.get() ;


    _cloneODESpace(other->m_ODE_space, m_ODE_space) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
Space::_cloneODESpace(dSpaceID src, dSpaceID dst)
{
    PS_DBG2("ood::Space::_cloneODESpace(src=%p, dst=%p)", src, dst) ;

    dSpaceSetCleanup(dst, dSpaceGetCleanup(src)) ;
    dSpaceSetSublevel(dst, dSpaceGetSublevel(src)) ;

    {
        int l1, l2 ;

        dHashSpaceGetLevels( src, &l1, &l2 ) ;

        dHashSpaceSetLevels( dst, l1, l2 ) ;
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
Space*
Space::asSpace(void)
{
    return this ;
}
/* ....................................................................... */
/* ======================================================================= */
