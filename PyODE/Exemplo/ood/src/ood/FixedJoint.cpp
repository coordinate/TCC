/*!
 * @file FixedJoint.cpp
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2010 - 2015 by Rocco Martino                            *
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
#include <ood/FixedJoint>
#include <ood/StaticWorld>
#include <ood/World>
#include <ood/Notify>
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




using namespace ood ;




/* ======================================================================= */
/* ....................................................................... */
FixedJoint::FixedJoint(void):
    m_oneway_mode       ( false ),
    m_fake_mode         ( false ),
    m_rotation_mode     ( true ),
    m_position_mode     ( true ),
    m_compute_matrix    ( true )
{
    this->setSureMaxInfo(6) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
FixedJoint::FixedJoint(const FixedJoint& other, const osg::CopyOp& copyop):
    BypassJoint         ( other, copyop ),
    m_oneway_mode       ( other.m_oneway_mode ),
    m_fake_mode         ( other.m_fake_mode ),
    m_rotation_mode     ( other.m_rotation_mode ),
    m_position_mode     ( other.m_position_mode ),
    m_compute_matrix    ( other.m_compute_matrix ),
    m_matrix            ( other.m_matrix ),
    m_quat              ( other.m_quat ),
    m_pos               ( other.m_pos )
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
FixedJoint::~FixedJoint(void)
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
FixedJoint::update( ooReal step_size )
{
    int row = 0 ;



    if( ! m_fake_mode ) {


        BypassJoint::BodyMask   mode = m_oneway_mode ? CONSTRAIN_BODY2 : CONSTRAIN_ALL ;


        if( m_rotation_mode ) {

            this->BypassJoint::setRelativeRotation( step_size,
                                                    m_quat,
                                                    row,
                                                    m_erp[0],
                                                    m_cfm[0],
                                                    mode
                            ) ;
        }




        if( m_position_mode ) {

            this->BypassJoint::setRelativePosition( step_size,
                                                    m_pos,
                                                    row,
                                                    m_erp[0],
                                                    m_cfm[0],
                                                    mode
                            ) ;
        }

    }



    this->BypassJoint::setInfo1( row, row ) ;




    this->BypassJoint::update( step_size ) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
FixedJoint::postUpdate( ooReal step_size )
{


    if( m_fake_mode ) {


        PS_ASSERT1( m_oneway_mode == true ) ;

        PS_ASSERT1( getBody2() != NULL ) ;



        RigidBody*  body1 = getBody1() ;

        RigidBody*  body2 = getBody2() ;



        if( m_position_mode ) {

            body2->setPosition( body1->getPosition() + m_pos ) ;

            m_body2->setLinearVelocity( m_body1->getLinearVelocity() ) ;

            m_body2->setAngularVelocity( m_body1->getAngularVelocity() ) ;

        }




        if( m_rotation_mode ) {

            body2->setQuaternion( body1->getQuaternion() * m_quat ) ;

        }



    }




    this->BypassJoint::postUpdate( step_size ) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
FixedJoint::finalize(void)
{
    PS_DBG2("ood::FixedJoint::finalize(%p)", this) ;


    RigidBody*  b1 = NULL ;
    RigidBody*  b2 = NULL ;


    if( m_body1.valid() ) {
        b1 = m_body1->getWorld() ? m_body1 : NULL ;

    }



    if( m_body2.valid() ) {
        b2 = m_body2->getWorld() ? m_body2 : NULL ;
    }




    if( m_compute_matrix ) {

        if( b1 && b2 ) {
            setMatrix( b2->getMatrix() * osg::Matrix::inverse(b1->getMatrix()) ) ;
        }

        else if( b1 ) {
            setMatrix( b1->getMatrix() ) ;
        }

        else if( b2 ) {
            setMatrix( b2->getMatrix() ) ;
        }
    }


    this->BypassJoint::finalize() ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
FixedJoint*
FixedJoint::asFixedJoint(void)
{
    return this ;
}
/* ....................................................................... */
/* ======================================================================= */
