/*!
 * @file MatrixManipulator.cpp
 * @author Rocco Martino
 */
/***************************************************************************
 *   Copyright (C) 2012 by Rocco Martino                                   *
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
#include <oodUtil/MatrixManipulator>

#include <ood/Notify>
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
/* ....................................................................... */
/* ======================================================================= */




using namespace oodUtil ;




/* ======================================================================= */
/* ....................................................................... */
MatrixManipulator::MatrixManipulator(void):
    m_matrix( osg::Matrix::identity() )
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
MatrixManipulator::MatrixManipulator(const MatrixManipulator& other, const osg::CopyOp& copyop):
    osgGA::CameraManipulator(other, copyop),
    m_matrix( other.m_matrix )
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
MatrixManipulator::~MatrixManipulator(void)
{
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
MatrixManipulator::setByMatrix(const osg::Matrixd& matrix)
{
    m_matrix = matrix ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
void
MatrixManipulator::setByInverseMatrix(const osg::Matrixd& matrix)
{
    m_matrix = osg::Matrix::inverse(matrix) ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
osg::Matrixd
MatrixManipulator::getMatrix(void) const
{
    return m_matrix ;
}
/* ....................................................................... */
/* ======================================================================= */




/* ======================================================================= */
/* ....................................................................... */
osg::Matrixd
MatrixManipulator::getInverseMatrix(void) const
{
    return osg::Matrix::inverse(m_matrix) ;
}
/* ....................................................................... */
/* ======================================================================= */
