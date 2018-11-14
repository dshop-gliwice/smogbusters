$fn=64;

wHeight=9; //wall height
wThick=1.5; //wall thickness
wThicCh=2.5;
floorThick=1.25;
bWidth=48; //board width
bHeight=37.8; //board height


module conector(rectWidth, rectHeight, pipe, tall, hollow, shift){
	difference(){
		color("red") hull(){
		  translate([shift,0,0] ) cylinder(1,r=pipe/2);
		  translate([0,0,tall] ) cube([rectWidth, rectHeight, 1],true);
		}
    if (hollow) {
      color("green") hull(){
	      translate([shift,0,-0.1] ) cylinder(1,r=pipe/2-wThicCh/2);
		    translate([0,0,tall+0.1] ) cube([rectWidth-wThicCh,rectHeight-wThicCh,1],true);
		  }
	  }
  }
}

module extension(){
  difference(){
    rotate(a=[90,0,0])
      cylinder(h=2,d=12);
    translate([0,0.01,0])
      rotate(a=[90,0,0])
        cylinder(h=2+0.3,d=12-wThicCh);
  }
}


module box() {
  union() {
   //front wall
   translate([0, 0, 0])
     cube([wThick*2+bWidth, wThick, wHeight], false);
   //back wall
   translate([0, wThick+bHeight, 0])
     cube([wThick*2+bWidth, wThick, wHeight], false);

   //side walls
   translate([0, 0, 0])
     cube([wThick, wThick+bHeight+9, wHeight], false);    
   translate([wThick+bWidth, 0, 0])
     cube([wThick, wThick+bHeight+9, wHeight], false);
     
   //floor
   difference() {
     translate([0, 0, 0])
       cube([bWidth+2*wThick, bHeight+2*wThick, floorThick], false);
     //cross
     crossSizeX=10;
     translate([bWidth/2+wThick-crossSizeX/2, -0.0, -0.01])
       cube([crossSizeX, bHeight+2*wThick, floorThick+0.1], false);
     crossSizeY=20;
     translate([0, bHeight/2+wThick-crossSizeY/2, -0.01])
       cube([bWidth+2*wThick, crossSizeY, floorThick+0.1], false);
   }   
  }
}

module leftChannel(hollow){
  union(){
    translate([11, 49, 3.5])
      rotate(a=[180, 270, 270]) 
        conector(7, 13, 12, 10, hollow, 2.5);
    translate([11,51,6])
      color("blue") extension();     
  }
}

module rightChannel(hollow){
  union(){
    translate([40, 49, 4])
      rotate(a=[180, 270, 270]) 
        conector(8, 15, 12, 10, hollow, 2);
    translate([40,51,6])
       color("blue") extension();
  }
}

module main() {
  union(){
    difference(){
      box();
      leftChannel();
      rightChannel();
    }
    leftChannel(true);
    rightChannel(true);
  }
}

main();

