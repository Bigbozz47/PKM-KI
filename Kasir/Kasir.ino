#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

//lcd------------------------------
LiquidCrystal_I2C lcd(0x27,16,2); //lcd address, width,height

//Printer--------------------------

#include "USBPrinter.h"
#include "ESC_POS_Printer.h"

bool fisrtInit = true;

class PrinterOper : public USBPrinterAsyncOper
{
  public:
    uint8_t OnInit(USBPrinter *pPrinter);
};

uint8_t PrinterOper::OnInit(USBPrinter *pPrinter)
{
  Serial.println(F("USB Printer OnInit"));
  Serial.print(F("Bidirectional="));
  Serial.println(pPrinter->isBidirectional());
  return 0;
}

USB     myusb;
PrinterOper AsyncOper;
USBPrinter  uprinter(&myusb, &AsyncOper);
ESC_POS_Printer printer(&uprinter);
//printer end----------------------

//Payment-------------------------------------------
int maxItemLength = 10;
String listItemBuy[10] = {}; //nama item
int qty[10] = {}; //kuantiti
int priceItemBuy[10]; //harga item
int priceTotalItemBuy[10]; //total harga item
int indexBuyItem = 0; //index arraynya
int priceTotalForPayment = 0;
//end payment---------------------------------------

//Barcode--------------------------------------------
int arrayLength = 10; //array length untuk data barcode
String BardcodeCodeListItem[10] = {"8993175539210","8886008101053","8996001600269","9555123709008","8992696523081","8990044000079","8996001600504","089686010190","711844130111","8992741958790"}; //data kode barcode
int ItemPrice[10] = {2500,3000,3500,7000,3000,4000,3000,3500,7000,4500}; //harga per item
String ItemName[10] = {"Nextar","aqua","lemineral","soya_master","milo","pocky","teh_pucuk","indomie","saos","yupi"}; //nama per item

SoftwareSerial barcode (2,3) ;//(rxPin, txPin, inverse_logic) 2 ka tx barcode, 3 ka rx barcode
int itemIndex =-1;
//end barcode--------------------------------------------------
//warna------------------------------------------------
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibration Values
// *Get these from Calibration Sketch
int redMin = 50; // Red minimum value
int redMax = 700; // Red maximum value
int greenMin = 60; // Green minimum value
int greenMax = 900; // Green maximum value
int blueMin = 40; // Blue minimum value
int blueMax = 800; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

//warna end-------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  // lcd----------------------------------------------------
  lcd.init();
  lcd.backlight();
  lcd.clear();
  //sensor warna-----------------
   // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  //end sensor warna---------------

  //serial-------------------------
  barcode.begin(9600);//barcode serial
  Serial.begin(9600); //serial arduino
  //end serial-------------------------

  //printer------------------------------------
  while (!Serial && millis() < 5000) delay(1);
  lcd.setCursor(0,0);
  if (myusb.Init()) {
    lcd.print("USB host failture");
    Serial.println(F("USB host failed to initialize"));
    while (1) delay(1);
  }
  lcd.print("USB host ok");
  Serial.println(F("USB Host init OK"));
  //end printer------------------------------
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  myusb.Task();// printer init
  if (uprinter.isReady()) {
    printer.begin();
    printer.reset();
    printer.setDefault();
    if(fisrtInit){
      lcd.setCursor(0,0);
      lcd.print("printer init...");
      lcd.setCursor(0,1);
      lcd.print("printing 'printer ok'");
      Serial.println(F("Init ESC POS printer"));
      printer.println(F("Printer ok"));
      printer.feed(2);
      fisrtInit = false;
    }
    lcd.clear();
  
  itemIndex = barcodeScan(); //baco barcode
  rgb(); //baco rgb
  
  if(itemIndex >=0){ //kalau ado item tabaco
    setItems(itemIndex); //simpan item ka array baco di void e
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(ItemName[itemIndex]);
        lcd.print("  Rp."); //spasi
        lcd.print(ItemPrice[itemIndex]);
        Serial.print(ItemName[itemIndex]);
        Serial.print('\t');
        Serial.println(ItemPrice[itemIndex]);
        lcd.setCursor(0,1);
        lcd.print("Total:  Rp.");
        lcd.print(priceTotalForPayment);
       
  }
  String uangTerdeteksi = moneyScan();//scan uang
  uint16_t nominalUang = uangTerdeteksi.toInt(); //ubah ka int 16 bit
  //cetak struk
  if(nominalUang>0){
    if(indexBuyItem>0){
    printItems(nominalUang);
  }}
  }
}

void setItems(int index){
  bool itemListed = false;
  //cek array untuk tambah qty
  for(int i=0;i<maxItemLength;i++){
//    Serial.print(listItemBuy[i]);
//    Serial.print('\t');
//    Serial.println(ItemName[index]);
    
    if(listItemBuy[i] ==  ItemName[index]){
      qty[i] = qty[i]+1;
      priceTotalItemBuy[i] = priceTotalItemBuy[i]+ ItemPrice[index];
      itemListed = true;
    }
  }
  //tambahkan untuk total
  priceTotalForPayment += ItemPrice[index];

  //jika tidak ada item di array tambah item ke array
  if(!itemListed){
    listItemBuy[indexBuyItem] = ItemName[index];
    qty[indexBuyItem] = 1;
    priceItemBuy[indexBuyItem] = ItemPrice[index];
    priceTotalItemBuy[indexBuyItem] = ItemPrice[index];
    indexBuyItem++;
  }
  
}

void printItems(uint16_t uang){
    printer.justify('C');
    printer.boldOn();
    printer.println(F("Zakhimi Anan Sugiarta Mart"));
    printer.boldOff();
    printer.println("");
    printer.println("");
    
    printer.justify('L');
    String text = "Name";
    text += '\t';
    text += "Price";
    text += "  ";
    text += "Qty";
    text += " ";
    text += "Total";
    printer.println(text);
    int totalPrice = 0;
    for(int i=0;i<maxItemLength;i++){ //20 diganti sesuai besar list item buy
      if(listItemBuy[i] !=""){
        text = (listItemBuy[i]);
        text+=('\t');
        text+=(priceItemBuy[i]);
        text+=("   ");
        text+=(qty[i]);
        text+=("  ");
        text+=(priceTotalItemBuy[i]);
        printer.println(text);
        totalPrice += priceTotalItemBuy[i];
      }
    }
    
    printer.justify('R');
    printer.println("------------------------");
    printer.println("");
    text = "Total Price: ";
    uint16_t hargaYangHarusDibayar = (uint16_t)totalPrice;
    text += String(hargaYangHarusDibayar);
    printer.println(text);
    text = "Tunai: ";
    text += String(uang);
    printer.println(text);
    if(uang-hargaYangHarusDibayar >0){
      text = "Kembali: ";
      text+= String(uang-hargaYangHarusDibayar);
      printer.println(text);
    }
    printer.feed(2);
    indexBuyItem = 0;
    for(int i=0;i<maxItemLength;i++){
      listItemBuy[i] = "";
      qty[i] = 0;
      priceItemBuy[i] = 0;
      priceTotalItemBuy[i] = 0;
    }
    priceTotalForPayment = 0;
  /*
  Serial.println("===========================");
  Serial.println("Delano Mart");
  Serial.println("uang anda habis, kami senang");
  int totalPrice = 0;
    for(int i=0;i<50;i++){
      if(listItemBuy[i] !=""){
        Serial.print(listItemBuy[i]);
        Serial.print('\t');
        Serial.print(qty[i]);
        Serial.print('\t');
        Serial.print(priceItemBuy[i]);
        Serial.print('\t');
        Serial.println(priceTotalItemBuy[i]);
        totalPrice += priceTotalItemBuy[i];
      }
    }
    Serial.println();
    Serial.println();
    Serial.print("Total Price: ");
    uint16_t hargaYangHarusDibayar = (uint16_t)totalPrice;
    Serial.println(hargaYangHarusDibayar);
    Serial.print("Tunai : ");
    Serial.println(uang);
    Serial.print("Kembali : ");
    Serial.println(uang-hargaYangHarusDibayar);
    Serial.println("===========================");

    indexBuyItem = 0;
    for(int i=0;i<50;i++){
      listItemBuy[i] = "";
      qty[i] = 0;
      priceItemBuy[i] = 0;
      priceTotalItemBuy[i] = 0;
    }
    */
}

//--------------rgb------------------------------
String moneyScan(){
  if(((redValue>120)&&(redValue<200))&&((greenValue>200)&&(greenValue<230))&&((blueValue>220)&&(blueValue<255))){
    return "50000";  
  }
  else{
    return "0";
  }
}

void rgb(){
  redPW = getRedPW();
  // Map to value from 0-255
  redValue = map(redPW, redMin,redMax,255,0);
  // Delay to stabilize sensor
  delay(200);

  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  // Delay to stabilize sensor
  delay(200);

  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  // Delay to stabilize sensor
  delay(200);

  // Print output to Serial Monitor
//  Serial.print("Red = ");
//  Serial.print(redValue);
//  Serial.print(" - Green = ");
//  Serial.print(greenValue);
//  Serial.print(" - Blue = ");
//  Serial.println(blueValue);
}


// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

//---------------end rgb-----------------------------------
//-------------------------barcode------------------------------
int barcodeScan(){
  int index = -1;
  if(barcode.available()){
    String decodeBarcode = barcode.readString();
    decodeBarcode.trim();
    Serial.println(decodeBarcode);
    for(int i=0;i<arrayLength;i++){
      Serial.println(decodeBarcode == BardcodeCodeListItem[i]);
      if(decodeBarcode == BardcodeCodeListItem[i])index=i;
    }
    
  };
  return index;
}

//------------------------end barcode-----------------------------------
