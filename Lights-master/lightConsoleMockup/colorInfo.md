Gradient buttons new:


Screens : rgb(8, 8, 8)

BG : rgb(38, 38, 38)

Grey buttons are:
Left HEX: rgb(79, 79, 79)
Right HEX: rgb(39, 38, 38)


Blue buttons are:

Left : rgb(25, 15, 140)
Right : rgb(1, 0, 91)


B:LUE : 

QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0.573, x2:1, y2:0.545, stop:0 rgba(25, 15, 140, 255), stop:1 rgba(1, 0, 91, 255));border-style: solid;border-color: rgb(0, 0, 127);border-width: 1px;border-radius: 5px;}

GRAY:

QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, stop:0 rgba(79, 79, 79, 255), stop:1 rgba(39, 38, 38, 255));border-style: solid;border-color: rgb(90, 90, 90);border-width: 1px;border-radius: 5px;} 

SLIDER CSS:

/*Verticales*/
QSlider::groove:vertical{
border: 1px solid  rgb(102, 102, 102);;
background: rgb(102, 102, 102);
width:6px;
border-radius: 3px;
}

QSlider::handle:vertical{
background: rgb(90, 90, 90);
border: 1px solid #777;
height: 20px;
 margin-left: -14px;
margin-right: -14px;
border-radius: 2px;
}
