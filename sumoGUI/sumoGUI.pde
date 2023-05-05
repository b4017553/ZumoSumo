import processing.serial.*;
import g4p_controls.*;

Serial myPort;

String ports[];

public void setup(){
  size(600, 500, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here
  
  String portName = "COM6";
  
  ports = Serial.list();
  
  println(ports.length);
  
  for(int i = 0 ;i < ports.length ; i++ ){
    
  
    if(portName.equals(ports[i])){
      
      println("Found Port");
    
      myPort = new Serial(this,portName,9600);
      
    }
    
  }
  
  if(myPort == null){
    
    println("Nothing found on " + portName);
  }
  
}

public void draw(){
  background(230);
  
  ArrayList<String> msg = new ArrayList<String>();
  
  if(myPort != null)
  {
    msg.add(myPort.readString());
    
    
    
    if(msg.get(msg.size()-1) != null)
    {
       println(msg.get(msg.size()-1));
       if(msg.get(msg.size()-1).contains("My Score"))
       {
         String s = msg.get(msg.size()-1);
         label2.setText(s);
       }
       else if(msg.get(msg.size()-1).contains("Opponents Score: "))
       {
         String os = msg.get(msg.size()-1);
       
       }
    }
  }
  
  
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
  
  

}
