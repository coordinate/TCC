/*!
 * @file CharacterEx.cpp
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

/* ======================================================================= */
/* ....................................................................... */
#include "CharacterEx"
// #include <ood/CharacterEx>
#include <ood/World>
#include <ood/RigidBody>

#include <osgGA/GUIEventAdapter>
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




using namespace ood ;




/* ======================================================================= */
/* ....................................................................... */
CharacterEx::CharacterEx(void):
    m_sensitivity(0.5),
    m_motion(NO_MOTION),
    m_picked( NULL )
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
CharacterEx::CharacterEx(const CharacterEx& other, const osg::CopyOp& copyop):
    Character(other, copyop),
    m_sensitivity( other.m_sensitivity ),
    m_motion( other.m_motion ),
    m_picked( other.m_picked )
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
CharacterEx::~CharacterEx(void)
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
CharacterEx::handleKeyDown(const int& key, const int& mask, bool& handled)
{


    if( key == 'w' ) {
        m_motion |= MOVE_FRONT ;
        _moveCharacter() ;
        handled = true ;
    }


    else if( key == 's' ) {
        m_motion |= MOVE_BACK ;
        _moveCharacter() ;
        handled = true ;
    }


    else if( key == 'a' ) {
        m_motion |= MOVE_LEFT ;
        _moveCharacter() ;
        handled = true ;
    }


    else if( key == 'd' ) {
        m_motion |= MOVE_RIGHT ;
        _moveCharacter() ;
        handled = true ;
    }






    else if( key == osgGA::GUIEventAdapter::KEY_Space ) {

        if( this->isOnGround()  &&  this->getWorld() != NULL ) {

            this->setJump( osg::Z_AXIS * 1.0e3 / this->getWorld()->getCurrentStepSize(), 0.5 ) ;

        }
        handled = true ;
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
CharacterEx::handleKeyUp(const int& key, const int& mask, bool& handled)
{
    if( key == 'w' ) {
        m_motion &= ~MOVE_FRONT ;
        _moveCharacter() ;
        handled = true ;
    }


    else if( key == 's' ) {
        m_motion &= ~MOVE_BACK ;
        _moveCharacter() ;
        handled = true ;
    }


    else if( key == 'a' ) {
        m_motion &= ~MOVE_LEFT ;
        _moveCharacter() ;
        handled = true ;
    }


    else if( key == 'd' ) {
        m_motion &= ~MOVE_RIGHT ;
        _moveCharacter() ;
        handled = true ;
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
CharacterEx::handleLeftButton(const bool& pressed, const osg::Vec2& ndc, bool& handled)
{
    handled = true ;



    if( m_picked.valid() ) {
        this->detach( m_picked ) ;
    }


    if( pressed ) {

        if( m_picked.valid() ) {
            const osg::Vec3 direction = this->getBody()->getQuaternion() * this->getFrontVersor() ;

            m_picked->addForce( direction * 5.0e4 ) ;

            m_picked = NULL ;
        }

    } else {
    }



    m_picked = NULL ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
CharacterEx::handleRightButton(const bool& pressed, const osg::Vec2& ndc, bool& handled)
{
    handled = true ;



    if( m_picked.valid() ) {
        this->detach( m_picked ) ;
    }



    if( pressed ) {

        m_picked = this->touch( 5 ) ;

        if( m_picked.valid() ) {

            if( m_picked->getKinematic() ) {
                m_picked = NULL ;

            } else {
                this->attach( m_picked ) ;
            }
        }

    } else {
    }
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
CharacterEx::handleMove(const osg::Vec2& pos, bool& handled)
{
    handled = true ;


    float   x = pos.x() * m_sensitivity ;
    float   y = pos.y() * m_sensitivity ;

    if( x==0.0 && y == 0.0 ) {
        return ;
    }

    ooReal  yaw = this->getYaw() - x * osg::PI ;
    ooReal  pitch = this->getPitch() + y * osg::PI ;



    pitch = osg::clampTo(pitch, (ooReal)0.0, (ooReal)osg::PI) ;


    this->setYaw( yaw ) ;
    this->setPitch( pitch ) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
CharacterEx::handleFrame(bool& warp_request, osg::Vec2& warp, bool& handled)
{
    warp_request = true ;
    warp.set(0,0) ;

    handled = true ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
CharacterEx::_moveCharacter(void)
{
    osg::Vec3   axis ;

    const osg::Vec3&    front_versor = this->getFrontVersor() ;
    const osg::Vec3&    rhs_versor = this->getSideVersor() ;

    if( m_motion & MOVE_FRONT ) {
        axis += front_versor ;
    }

    if( m_motion & MOVE_BACK ) {
        axis -= front_versor ;
    }

    if( m_motion & MOVE_RIGHT ) {
        axis += rhs_versor ;
    }

    if( m_motion & MOVE_LEFT ) {
        axis -= rhs_versor ;
    }

    axis.normalize() ;



    this->setMotion( axis * (m_motion != 0) * 5, 1.0e3 ) ;
}
/* ....................................................................... */
/* ======================================================================= */
