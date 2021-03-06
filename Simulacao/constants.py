from math import pi

#simulation
FRAMES			=	 30.0
TIMESTEP		=	 1/FRAMES
GRAVITY			=	 (0, -9.81, 0)
WINDOWSIZE		=	 800,600
BACKGROUND		=	 50./255, 153./255, 204./255

#wheel
WHEELRADIUS 	= 	 0.20
WHEELWIDTH  	=	 0.15
WHEELCOLOR		=	 0, 1, 0
MAXSTEERANGLE 	= 	 pi/6
MINSTEERANGLE 	=  	-pi/6

#car
CARLENGTH		=	 3.0
CARWIDTH		=	 1.5
MAINCARCOLOR	=	 0, 0, 1
CARCOLOR		=	 1, 0, 0
CARHEIGHT		=	 1.5
CARWEIGHT		=	 1500.0
MAXTORQUE		=	 1000

#person
PERSONWEIGHT	=	 75
PERSONCOLOR 	=	 146.0/255, 54.0/255, 252.0/255
PERSONHEIGHT	=	 1.8
PERSONRADIUS	=	 0.4
PERSONDENSITY  	=	 1062.0
SPHERERADIUS	=	 0.1

#road
ROADSIZE		=	 3.0
ROADCOLOR		= 	 53.0/255, 55.0/255, 60.0/255
ROADDENSITY		=	 2.0#000.0
ROADHEIGHT		=	 0.01
ROADLENGTH		=	 3000.0

#tree
TREECOLOR		=	 125.0/255, 65.0/255, 39.0/255
TREEDENSITY		=	 600
TREEPOLEHEIGHT	=	 2.5
TREEPOLERADIUS	=	 0.3

#pole
POLECOLOR		=	 211.0/255, 211.0/255, 211.0/255
POLEDENSITY		=	 2500