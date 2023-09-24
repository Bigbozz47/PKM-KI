#include <SoftwareSerial.h>

int arrayLength = 3; //array length untuk data barcode
String BardcodeCodeListItem[3] = {"P58B23040509","8886008101053","8996001600269"}; //data kode barcode
int ItemPrice[3] = {10000,3000,3500}; //harga per item
String ItemName[3] = {"Kotak","aqua","lemineral"}; //nama per item

SoftwareSerial barcode (2,3) ;//(rxPin, txPin, inverse_logic)
int itemIndex =-1;
void setup() {
  // put your setup code here, to run once:
  barcode.begin(9600);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  itemIndex = barcodeScan();
  if(itemIndex >=0){
    Serial.print(ItemName[itemIndex]);
    Serial.print('\t');
    Serial.println(ItemPrice[itemIndex]);
  }
}

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
