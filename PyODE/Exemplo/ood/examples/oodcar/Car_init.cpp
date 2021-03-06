/*!
 * @file Car_init.cpp
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
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "Car"

#include <osgDB/ReadFile>

#include <ood/Engine>
#include <ood/Cylinder>
#include <ood/SuspensionJoint>
#include <ood/Notify>
#include <ood/DifferentialJoint>
#include <ood/SwaybarJoint>
#include <ood/LinearInterpolator>

#include <oos/Source>




using namespace ood ;




namespace {
class OOD_EXPORT WheelCallback: public ood::ODECallback
{
public:
META_Object(ood, WheelCallback) ;


    WheelCallback(void)
    {
    }




    WheelCallback(const WheelCallback& other, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY):
        ODECallback(other, copyop)
    {
    }



    // Compute the axis in world frame and adjust the sound
    virtual void    operator()(ODEObject* obj)
    {
        RigidBody*  body = obj->asRigidBody() ;
        PS_ASSERT1( body != NULL ) ;

        osg::Vec3   axis = body->getQuaternion() * osg::Z_AXIS ;

        body->setFiniteRotationAxis(axis) ;

        traverse(obj) ;
    }

private:
} ;




class OOD_EXPORT BodyCallback: public ood::ODECallback
{
public:
    BodyCallback(oos::Buffer* buffer = NULL)
    {
        PS_ASSERT1( buffer != NULL ) ;

        m_source = new oos::Source() ;
        m_source->setBuffer(buffer) ;

        m_source->setParam(oos::Source::GAIN, 0.0) ;
        m_source->setParam(oos::Source::LOOPING, true) ;

        m_source->play() ;
    }




    // Adjust the wind sound
    virtual void    operator()(ODEObject* obj)
    {
        PS_ASSERT1( m_source.valid() ) ;

        RigidBody*  body = obj->asRigidBody() ;
        PS_ASSERT1( body != NULL ) ;

        const ooReal    speed = body->getLinearVelocity().length() ;

        const ooReal    f = osg::minimum(1.0, speed / 50.0) ;

        m_source->setParam(oos::Source::GAIN, f * 2.0) ;
        m_source->setParam(oos::Source::PITCH, f) ;

        traverse(obj) ;
    }

private:
    osg::ref_ptr<oos::Source>    m_source ;
} ;




class OOD_EXPORT EngineCallback: public ood::ODECallback
{
public:
    EngineCallback(oos::Buffer* buffer = NULL)
    {
        PS_ASSERT1( buffer != NULL ) ;

        m_source = new oos::Source() ;
        m_source->setBuffer(buffer) ;

        m_source->setParam(oos::Source::GAIN, 0.0) ;
        m_source->setParam(oos::Source::LOOPING, true) ;

        m_source->play() ;

        m_source2 = osg::clone( m_source.get() ) ;
        m_source2->play() ;
    }




    // Adjust the wind sound
    virtual void    operator()(ODEObject* obj)
    {
        PS_ASSERT1( m_source.valid() ) ;
        PS_ASSERT1( m_source2.valid() ) ;

        Car*    car = dynamic_cast<Car*>( obj ) ;
        PS_ASSERT1( car != NULL ) ;


        const ooReal    f = car->getEngine()->getSpeed() / car->getEngine()->getSpeedLimit() ;


        {
            const ooReal    gain0 = m_source->getParam(oos::Source::GAIN) ;
            const ooReal    gain1 = osg::maximum(0.1, f * 2.0 * car->getEngine()->getGas()) ;

            const ooReal    pitch0 = m_source->getParam(oos::Source::PITCH) ;
            const ooReal    pitch1 = osg::maximum(0.1, f * 2.0) ;

            const ooReal    N = 10 ;

            m_source->setParam(oos::Source::GAIN, (gain0 * N + gain1) / (N+1) ) ;
            m_source->setParam(oos::Source::PITCH, (pitch0 * N + pitch1) / (N+1) ) ;
        }




        m_source2->setParam(oos::Source::GAIN, osg::maximum((ooReal)0.5, f)) ;
        m_source2->setParam(oos::Source::PITCH, osg::maximum((ooReal)0.125, f)) ;

        traverse(obj) ;
    }

private:
    osg::ref_ptr<oos::Source>    m_source ;
    osg::ref_ptr<oos::Source>    m_source2 ;
} ;
}




void
Car::init(void)
{
    PS_ASSERT1( this->getObjectList().size() == 0 ) ;




    /*
     * [1] create the wheels
     * [2] create the body
     * [3] connect the wheels to the body
     * [4] create the differentials
     * [5] create the swaybars
     * [6] create the engine
     */





    //
    // [1] Wheels:
    //
    {
        // the wheel
        osg::ref_ptr<Cylinder>      wheel = dynamic_cast<Cylinder*>( osgDB::readObjectFile("car_wheel.osgt") ) ;
        PS_ASSERT1( wheel.valid() ) ;


        wheel->setMass( 25.0 ) ;


        // clear the local parameters, if there are any
        wheel->setCollisionParameters(NULL) ;

        // Just to be sure
        wheel->setFiniteRotationMode(true) ;
        wheel->setAutoDisableFlag(false) ;

        // This callback handles the sound and the rotation axis
        wheel->addUpdateCallback( new WheelCallback() ) ;


        // ODE could have a problem with this, but there is a patch
        // TODO: apply the gyroscopic patch
        wheel->setGyroscopicMode( false ) ;



        // Now create and position the wheels


        m_wheel_RL = osg::clone( wheel.get() ) ;
        m_wheel_RR = osg::clone( wheel.get() ) ;
        m_wheel_FR = osg::clone( wheel.get() ) ;
        m_wheel_FL = osg::clone( wheel.get() ) ;


        m_wheel_RL->setPosition( osg::Vec3(-1, -1.5, 0.0) ) ;
        m_wheel_RR->setPosition( osg::Vec3( 1, -1.5, 0.0) ) ;
        m_wheel_FR->setPosition( osg::Vec3( 1,  1.5, 0.0) ) ;
        m_wheel_FL->setPosition( osg::Vec3(-1,  1.5, 0.0) ) ;


        this->Container::addObject( m_wheel_RL ) ;
        this->Container::addObject( m_wheel_RR ) ;
        this->Container::addObject( m_wheel_FR ) ;
        this->Container::addObject( m_wheel_FL ) ;
    }







    //
    // [2] Body:
    //
    {
        m_body = dynamic_cast<RigidBody*>( osgDB::readObjectFile("car_body.osgt") ) ;
        PS_ASSERT1( m_body.valid() ) ;


        m_body->setGyroscopicMode( false ) ;


        oos::Buffer*     buffer = dynamic_cast<oos::Buffer*>( osgDB::readObjectFile("sounds/wind.wav") ) ;
        PS_ASSERT1( buffer ) ;


        // This callback handles the sound source
        m_body->addUpdateCallback( new BodyCallback(buffer) ) ;


        // The mass
//         m_body->setMass( m_body->getMass(), osg::Vec3(1.5, 3, 1), dBoxClass ) ;
        m_body->setMass( 800, osg::Vec3(1.5, 3, 1), dBoxClass ) ;


        this->Container::addObject( m_body ) ;
    }







    //
    // [3] Suspensions
    //
    {
        osg::ref_ptr<osg::Node>     joint_graphics = osgDB::readNodeFile("car_suspension.osgt") ;
        PS_ASSERT1( joint_graphics.valid() ) ;


        m_hinge_RL = _createSuspension( m_wheel_RL, - osg::X_AXIS, joint_graphics ) ;
        m_hinge_FL = _createSuspension( m_wheel_FL, - osg::X_AXIS, joint_graphics ) ;
        m_hinge_RR = _createSuspension( m_wheel_RR,   osg::X_AXIS, joint_graphics ) ;
        m_hinge_FR = _createSuspension( m_wheel_FR,   osg::X_AXIS, joint_graphics ) ;


        this->Container::addObject( m_hinge_RL ) ;
        this->Container::addObject( m_hinge_RR ) ;
        this->Container::addObject( m_hinge_FR ) ;
        this->Container::addObject( m_hinge_FL ) ;
    }




    //
    // [4] differentials
    //
    {
        m_front_differential = new DifferentialJoint() ;
        m_rear_differential = new DifferentialJoint() ;

        m_front_differential->setBody1(m_wheel_FL) ;
        m_front_differential->setBody2(m_wheel_FR) ;

        m_rear_differential->setBody1(m_wheel_RL) ;
        m_rear_differential->setBody2(m_wheel_RR) ;

        m_front_differential->setAxis1( - osg::X_AXIS ) ;
        m_front_differential->setAxis2(   osg::X_AXIS ) ;

        m_rear_differential->setAxis1( - osg::X_AXIS ) ;
        m_rear_differential->setAxis2(   osg::X_AXIS ) ;



        m_front_differential->setFriction( 1.0 - 1.0e-1 ) ;

        m_rear_differential->setFriction(  1.0 - 1.0e-3 ) ;


        this->Container::addObject( m_front_differential ) ;
        this->Container::addObject( m_rear_differential ) ;
    }




    //
    // [5] sway bars
    //
    {
        SwaybarJoint*   front = new SwaybarJoint() ;
        SwaybarJoint*   rear = new SwaybarJoint() ;

        front->setReferenceBody( m_body ) ;
        rear->setReferenceBody( m_body ) ;

        front->setReferenceAxis( osg::Z_AXIS ) ;
        rear->setReferenceAxis( osg::Z_AXIS ) ;

        front->setBody1(m_wheel_FL) ;
        front->setBody2(m_wheel_FR) ;

        rear->setBody1(m_wheel_RL) ;
        rear->setBody2(m_wheel_RR) ;

        front->setAxis1( osg::Z_AXIS ) ;
        rear->setAxis1( osg::Z_AXIS ) ;


        front->setRigidity( 0.75 ) ;
        rear->setRigidity( 0.5 ) ;


        this->Container::addObject( front ) ;
        this->Container::addObject( rear ) ;
    }





    //
    // [6] The engine:
    //
    {
        m_engine = new Engine() ;

        m_engine->setFriction   ( 1.0 ) ;
        m_engine->setInertia    ( 1.0/25.0 ) ;
        m_engine->setDrag       ( 25.0 ) ;



        LinearInterpolator* torque = new LinearInterpolator() ;

        m_engine->setTorqueCurve(torque) ;




        torque->addPoint( inRPM(   0),  50 ) ;
        torque->addPoint( inRPM(1000),  50 ) ;
        torque->addPoint( inRPM(2000),  60 ) ;
        torque->addPoint( inRPM(3000),  80 ) ;
        torque->addPoint( inRPM(4000),  110 ) ;
        torque->addPoint( inRPM(5000),  120 ) ;
        torque->addPoint( inRPM(6000),  120 ) ;
        torque->addPoint( inRPM(7000),  100 ) ;
        torque->addPoint( inRPM(8000),  0 ) ;


        m_engine->setSpeedLimit( inRPM(7250.0) ) ;
        m_engine->setSpeedStall( inRPM(1000.0) ) ;



        Engine::GearList    gears ;

        gears.push_back( -1.0/20.0 ) ;
        gears.push_back( 0.0 ) ;
        gears.push_back( 1.0/16.0 ) ;
        gears.push_back( 1.0/9.0 ) ;
        gears.push_back( 1.0/6.0 ) ;
        gears.push_back( 1.0/4.5 ) ;
        gears.push_back( 1.0/3.5 ) ;
        gears.push_back( 1.0/3.0 ) ;

        m_engine->setGearList( gears ) ;

        m_engine->setCurrentGear(1) ;



        //
        // engine sound
        //
        oos::Buffer*     buffer = dynamic_cast<oos::Buffer*>( osgDB::readObjectFile("sounds/engine.wav") ) ;
        PS_ASSERT1( buffer ) ;

        this->addUpdateCallback( new EngineCallback(buffer) ) ;
    }
}









SuspensionJoint*
Car::_createSuspension(RigidBody* wheel, const osg::Vec3& axis2, osg::Node* graphics)
{
    const ooReal    SPRING = 20000.0 ;
    const ooReal    DAMPER_BOUND = 2000.0 ;
    const ooReal    DAMPER_REBOUND = 2000.0 ;
    const ooReal    PRELOAD = 5000.0 ;



    SuspensionJoint*    joint = new SuspensionJoint() ;

    // The anchor of the wheel is 20 centimeters towards the interior
    // of the car
    const ooReal        offset = 0.2 ;


    // The anchor
    joint->setAnchor1( wheel->getPosition() - axis2 * offset ) ;

    // The vertical axis
    joint->setAxis1( osg::Z_AXIS ) ;

    // Rotation axis
    joint->setAxis2( axis2 ) ;

    // It's appropriate that the wheel is the second body
    joint->setBody1( m_body ) ;
    joint->setBody2( wheel ) ;


    // This sets HiStop and LoStop to 0 on axis 1
    joint->setSteerAngle( 0.0 ) ;


    // spring and damper...

    joint->setSpring( SPRING ) ;
    joint->setDamperBound( DAMPER_BOUND ) ;
    joint->setDamperRebound( DAMPER_REBOUND ) ;
    joint->setPreload( PRELOAD ) ;


    // Graphics
    joint->getMatrixTransform()->addChild( graphics ) ;


    return joint ;
}
