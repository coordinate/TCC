/*!
 * @file ControllerBase.cpp
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2012 - 2017 by Rocco Martino                            *
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
#include <oodUtil/ControllerBase>

#include <cstdio>
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




using namespace oodUtil ;




/* ======================================================================= */
/* ....................................................................... */
ControllerBase::ControllerBase(void):
    m_on_key_pressed    ( new Signal3<const int, const int, bool>() ),
    m_on_key_released   ( new Signal3<const int, const int, bool>() ),

    m_on_left_button    ( new Signal3<const bool, const osg::Vec2, bool>() ),
    m_on_middle_button  ( new Signal3<const bool, const osg::Vec2, bool>() ),
    m_on_right_button   ( new Signal3<const bool, const osg::Vec2, bool>() ),

    m_on_button         ( new Signal3<const int, const osg::Vec2, bool>() ),

    m_on_mouse_wheel    ( new Signal2<const bool, bool>() ),

    m_on_mouse_moved    ( new Signal2<const osg::Vec2, bool>() ),

    m_on_mouse_dragged  ( new Signal2<const osg::Vec2, bool>() ),

    m_on_frame          ( new Signal3<bool, osg::Vec2, bool>() ),

    m_button_mask       ( 0 ),

    m_requesting_warp   ( false )
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
ControllerBase::ControllerBase(const ControllerBase& other, const osg::CopyOp& copyop):
    osgGA::GUIEventHandler(other, copyop),

    m_on_key_pressed    ( other.m_on_key_pressed  ),
    m_on_key_released   ( other.m_on_key_released ),

    m_on_left_button    ( other.m_on_left_button ),
    m_on_middle_button  ( other.m_on_middle_button ),
    m_on_right_button   ( other.m_on_right_button ),

    m_on_button         ( other.m_on_button ),

    m_on_mouse_wheel    ( other.m_on_mouse_wheel ),

    m_on_mouse_moved    ( other.m_on_mouse_moved ),

    m_on_mouse_dragged  ( other.m_on_mouse_dragged ),

    m_on_frame          ( other.m_on_frame ),

    m_key_down          ( other.m_key_down ),
    m_button_mask       ( other.m_button_mask ),

    m_requesting_warp   ( other.m_requesting_warp ),

    m_cursor_position   ( other.m_cursor_position )
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
ControllerBase::~ControllerBase(void)
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
bool
ControllerBase::handle( const osgGA::GUIEventAdapter&   ea,
                        osgGA::GUIActionAdapter&        aa,
                        osg::Object*                    obj,
                        osg::NodeVisitor*               nv)
{
    (void) nv ;
    (void) obj ;


    const int   key = ea.getUnmodifiedKey() ;
    const int   mod_key = ea.getModKeyMask() ;
    bool        handled = false ;

    switch( ea.getEventType() )
    {
        case osgGA::GUIEventAdapter::KEYDOWN:
            if( ! m_key_down[ tolower(key) ] ) {
                m_on_key_pressed->emit( key, mod_key, handled ) ;
                m_key_down[key] = true ;
            }
        break ;




        case osgGA::GUIEventAdapter::KEYUP:
            m_on_key_released->emit( key, mod_key, handled ) ;
            m_key_down[ tolower(key) ] = false ;
        break ;




        case osgGA::GUIEventAdapter::PUSH:
        case osgGA::GUIEventAdapter::RELEASE:
        {
            const unsigned int  mask = ea.getButtonMask() ;
            const unsigned int  trans = mask ^ m_button_mask ;


            osg::Vec2   ndc( ea.getXnormalized(), ea.getYnormalized() ) ;

            m_button_mask = mask ;


            m_on_button->emit( (int)mask, ndc, handled ) ;


            if( trans & osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON ) {

                const bool  pressed =  0 != (mask & osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) ;

                m_on_left_button->emit( pressed, ndc, handled ) ;
            }



            if( trans & osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON ) {

                const bool  pressed =  0 != (mask & osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON) ;

                m_on_middle_button->emit( pressed, ndc, handled ) ;
            }



            if( trans & osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON ) {

                const bool  pressed =  0 != (mask & osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) ;

                m_on_right_button->emit( pressed, ndc, handled ) ;
            }
        }
        break ;




        case osgGA::GUIEventAdapter::MOVE:
        {

            m_cursor_position.set( ea.getXnormalized(), ea.getYnormalized() ) ;


            if( ! m_requesting_warp ) {

                m_on_mouse_moved->emit( m_cursor_position, handled ) ;

            } else {
#ifdef WIN32
                m_on_mouse_moved->emit( m_cursor_position, handled ) ;
#endif

                m_requesting_warp = false ;
            }
        }
        break ;




        case osgGA::GUIEventAdapter::DRAG:
        {

            m_cursor_position.set( ea.getXnormalized(), ea.getYnormalized() ) ;


            if( ! m_requesting_warp ) {

                m_on_mouse_dragged->emit( m_cursor_position, handled ) ;

            } else {
#ifdef WIN32
                m_on_mouse_dragged->emit( m_cursor_position, handled ) ;
#endif

                m_requesting_warp = false ;
            }
        }
        break ;




        case osgGA::GUIEventAdapter::SCROLL:
        {
            int scrolling_motion = ea.getScrollingMotion() ;


            if( scrolling_motion == osgGA::GUIEventAdapter::SCROLL_UP ) {
                m_on_mouse_wheel->emit( true, handled ) ;
            }


            if( scrolling_motion == osgGA::GUIEventAdapter::SCROLL_DOWN ) {
                m_on_mouse_wheel->emit( false, handled ) ;
            }
        }
        break ;




        case osgGA::GUIEventAdapter::FRAME:
        {
            bool        request_warp = false ;
            osg::Vec2   warp ;

            m_on_frame->emit( request_warp, warp, handled ) ;

            if( request_warp ) {
                const float xmin = ea.getXmin() ;
                const float xmax = ea.getXmax() ;
                const float ymin = ea.getYmin() ;
                const float ymax = ea.getYmax() ;

                warp = ( warp + osg::Vec2(1.0, 1.0) ) * 0.5 ;

                warp.x() = xmin + (xmax - xmin) * warp.x() ;
                warp.y() = ymin + (ymax - ymin) * warp.y() ;

                m_requesting_warp = true ;

                aa.requestWarpPointer( warp.x(), warp.y() ) ;
            }
        }
        break ;




        default:
        break ;
    }



    return handled ;
}
/* ....................................................................... */
/* ======================================================================= */
