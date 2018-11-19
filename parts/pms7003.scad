$fn=64;

wHeight=10; //wall height
wThick=1.5; //wall thickness
wThicCh=2.5;
floorThick=1.25;
bWidth=48; //board width
bHeight=37.8; //board height


module conector(rectWidth, rectHeight, pipe, tall, hollow, shift){
	difference() {
		color("red") hull() {
		  translate([shift,0,0]) cylinder(1, r=pipe/2);
		  translate([0,0,tall]) cube([rectWidth, rectHeight, 1], true);
		}
    if (hollow) {
      color("green") hull(){
	      translate([shift,0,-0.1]) cylinder(1, r=pipe/2-wThicCh/2);
		    translate([0,0,tall+0.1]) cube([rectWidth-wThicCh, rectHeight-wThicCh, 1], true);
		  }
	  }
  }
}

module extension(diameter, thickness) {
  difference() {
    rotate(a=[90, 0, 0])
      cylinder(h=thickness,d=diameter);
    translate([0, 0.01, 0])
      rotate(a=[90, 0, 0])
        cylinder(h=thickness+0.3, d=diameter-wThicCh);
  }
}


module box() {
  union() {
   //back wall
   translate([0, wThick+bHeight, 0])
     cube([wThick*2+bWidth, wThick, wHeight], false); 
   //front wall
   translate([0, 0, 0])
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
     //hole
     holeSize=20;
     translate([0, bHeight/2+wThick-holeSize/2, -0.01])
       cube([bWidth+2*wThick, holeSize, floorThick+0.1], false);
   }   
  }
}

module leftChannel(hollow) {
  union() {
    translate([11, 49, 3.5])
      rotate(a=[180, 270, 270]) 
        conector(7, 13, 12, 10, hollow, 2.5);
    translate([11,52,6])
      color("blue") extension(12, 3);     
  }
}

module rightChannel(hollow) {
  union() {
    translate([39, 49, 4.5])
      rotate(a=[180, 270, 270]) 
        conector(9, 15.5, 12, 10, hollow, 1.5);
    translate([39,52,6])
       color("blue") extension(12, 3);
  }
}

module drillTemplate(shift) {
  translate([shift, 0 ,0])
    difference() {
      cube([wThick*2+bWidth, 12, 0.5]); //front wall
      translate([11, 6, -0.1]) //left channel
        cylinder(h=1, d=1);
      translate([39, 6, -0.1]) //right channel
        cylinder(h=1, d=1);
    }
}

module adapter() {
  union() {
    difference() {
      box();
      leftChannel();
      rightChannel();
    }
    leftChannel(true);
    rightChannel(true);
  }
}
module main() {
    adapter();
    drillTemplate(70);
}

main();

