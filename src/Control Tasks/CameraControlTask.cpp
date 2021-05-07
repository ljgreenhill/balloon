#include "CameraControlTask.hpp"

CameraControlTask::CameraControlTask(): adaCam(&Serial2){
    delay(3000);
    // see if the card is present and can be initialized:
    if (!SD.begin(254)) {
        Serial.println("Card failed, or not present");
    }  else{
        Serial.println("SD card found");
    }
  
    // Try to locate the camera
    if (adaCam.begin()) {
        Serial.println("Camera Found:");
    } else {
        Serial.println("No camera found?");
    }
    // Print out the camera version information (optional)
    char *reply = adaCam.getVersion();
    if (reply == 0) {
        Serial.print("Failed to get version");
    } else {
        Serial.println("-----------------");
        Serial.print(reply);
        Serial.println("-----------------");
    }

    adaCam.setImageSize(VC0706_640x480);        

    // You can read the size back from the camera (optional, but maybe useful?)
    uint8_t imgsize = adaCam.getImageSize();
    Serial.print("Image size: ");
    if (imgsize == VC0706_640x480) Serial.println("640x480");
    if (imgsize == VC0706_320x240) Serial.println("320x240");
    if (imgsize == VC0706_160x120) Serial.println("160x120");      
}

void CameraControlTask::execute(){  
    SD.begin(254);
    if(sfr::camera::take_photo){
        if (! adaCam.takePicture()) 
            Serial.println("Failed to snap!");
        else 
            Serial.println("Picture taken!");
    
        // Create an image with the name IMAGExx.JPG
        char filename[13];
        strcpy(filename, "IMAGE00.JPG");
        for (int i = 0; i < 100; i++) {
            filename[5] = '0' + i/10;
            filename[6] = '0' + i%10;
            // create if does not exist, do not open existing, write, sync after write
            if (! SD.exists(filename)) {
                break;
            }
        }
    
        // Open the file for writing
        File imgFile = SD.open(filename, FILE_WRITE);

        Serial.println(filename);

        // Get the size of the image (frame) taken  
        uint16_t jpglen = adaCam.frameLength();
        Serial.print("Storing ");
        Serial.print(jpglen, DEC);
        Serial.print(" byte image.");

        while (jpglen > 0) {
            // read 32 bytes at a time;
            uint8_t *buffer;
            uint8_t bytesToRead = min(32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
            buffer = adaCam.readPicture(bytesToRead);
            imgFile.write(buffer, bytesToRead);
            jpglen -= bytesToRead;
        }
        imgFile.close();

        Serial.println("done!");
        sfr::camera::take_photo = false;
    }
}