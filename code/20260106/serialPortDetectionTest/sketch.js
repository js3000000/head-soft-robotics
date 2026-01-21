let serial;
let latestData = "";
let osc;

function setup() {
 createCanvas(windowWidth, windowHeight);

 serial = new p5.SerialPort();

 serial.list();
 serial.open('/dev/tty.usbmodem141201'); // /dev/tty.usbmodem141201 

 serial.on('connected', serverConnected);

 serial.on('list', gotList);

 serial.on('data', gotData);

 serial.on('error', gotError);

 serial.on('open', gotOpen);

 serial.on('close', gotClose);
  
   osc = new p5.Oscillator('sine');
  osc.amp(0);
  osc.start();
  playBeep();
}

function serverConnected() {
 print("Connected to Server");
}

function gotList(thelist) {
 print("List of Serial Ports:");

 for (let i = 0; i < thelist.length; i++) {
  print(i + " " + thelist[i]);
 }
}

function gotOpen() {
 print("Serial Port is Open");
}

function gotClose(){
 print("Serial Port is Closed");
 latestData = "Serial Port is Closed";
}

function gotError(theerror) {
 print(theerror);
}

function gotData() {
 let currentString = serial.readLine();
  trim(currentString);
 if (!currentString) return;
 console.log(currentString);
 latestData = currentString;
}

function handleSerialData(line) {
  latestData = line.trim();
  if (latestData === 1 && 2 && 3 && 4) {
    playBeep();
    print("YESSSS");
  }
}

function playBeep() {
  osc.freq(800);
  osc.amp(0.5, 0.05);  // fade in quickly
  setTimeout(() => {
    osc.amp(0, 0.2);    // fade out
  }, 100); // short beep
}

function draw() {
  background(latestData/2);
  text("Last message: " + latestData, width / 2, height / 2);

  ellipse(width/2,height/2,latestData, latestData);
}

function gotData() {
  let currentString = serial.readLine();
  currentString = trim(currentString);
  if (!currentString) return;
  console.log(currentString);
  handleSerialData(currentString); // this was missing!
}