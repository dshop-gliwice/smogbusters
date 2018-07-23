$fn=64;

sHeight=7.2;

module screwMount(){
  difference(){
      cylinder(h = sHeight-1.5,
           d = 6.2,
           center = false);
      cylinder(h = sHeight-1.5,
           d = 3.15,
           center = false);  
  }  
}

module spacer(){
    cube([4,5,sHeight-1.5],false);  
}


module main(){
  union(){
   translate([5, 5, 0])
    screwMount();
   translate([21, 5, 0])
    screwMount();

   translate([2,21,0])
    spacer();
   translate([20,21,0])
    spacer();

   translate([0,0,0])
    cube([26,2,sHeight],false);

   translate([0,0,0])
    cube([2,26,sHeight],false);    
   translate([24,0])
    cube([2,26,sHeight],false);
  }  
}


main();

